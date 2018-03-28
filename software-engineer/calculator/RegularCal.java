import java.util.Stack;
import java.lang.String;
import java.lang.Double;
import java.util.regex.*;
import java.util.EmptyStackException;


public class RegularCal{
    
    private double rResult = 0;
    private double mValue = 0;
    private Pattern expPattern;
    private Matcher match;
    private Stack<Double> numberStack = new Stack<>();
    private Stack<Operator> opStack = new Stack<>();

    double rExpValue(String exp) throws Exception{
        double number = 0;
        numberStack.clear(); opStack.clear();
        // preprocessing expression: replace exp and deal with '-'
        System.out.println("Before Preprocess: " + exp);
        exp = exp.replaceAll("--", "\\+");
        exp = exp.replaceAll("exp", "e^");
        exp = new StringBuilder(exp).reverse().toString();
        exp = exp.replaceAll("-(?=\\D|$)", "-0");
        exp = new StringBuilder(exp).reverse().toString();
        System.out.println("After Preprocess: " + exp);
        // parse whole string expression
        expPattern = Pattern.compile("\\d+(\\.\\d+)?|\\+|-|\\*|/|\\(|\\)|\\^|sqrt|π|e|cos|sin|arccos|arcsin|log2|ln|!|M");
        match = expPattern.matcher(exp);
        // scan whole parsed expression
        while(match.find()){
            String unit = match.group();
            System.out.print("Handle: "); System.out.println(unit);     // debug
            if(Character.isDigit(unit.charAt(0))){
                number = Double.parseDouble(unit);
                numberStack.push(number);
                continue;
            }
            else if(unit.equals("Ans")){
                numberStack.push(rResult);
                continue;
            }
            else if(unit.equals("M")){
                numberStack.push(mValue);
                continue;
            }
            else{
                Operator operator = Operator.getOperator(unit);
                if(operator == Operator.UNKNOWN){
                    throw new Exception("Unkown operator");
                }
                if(operator == Operator.LEFTPAREN){
                    opStack.push(operator);
                    continue;
                }
                else if(operator == Operator.RIGHTPAREN){
                    while(opStack.peek() != Operator.LEFTPAREN)
                        stepCal();
                    opStack.pop();  //pop the left paren
                }
                else{
                    while(!opStack.isEmpty() && 
                          operator.getPriority() <= opStack.peek().getPriority()){
                        stepCal();
                    }
                    opStack.push(operator);
                }
            }
        }
        // calculate remaining in the stack
        if(opStack.isEmpty() && !numberStack.isEmpty()){
            rResult = numberStack.pop();
        }
        while(!opStack.isEmpty())
            stepCal();
        return rResult;
    }

    // get a operator from opStack and
    // get number from numberStack and
    // calculate then put back to numberStack
    void stepCal() throws Exception{
        double lhs =0, rhs = 0;
        Operator op = Operator.UNKNOWN;
        try{
            op = opStack.pop();
            int opNum = op.getNum();
            rhs = numberStack.pop();
            lhs = 0;
            if(opNum == 2)
                lhs = numberStack.pop();
        }catch(EmptyStackException e){
            throw new Exception("Operands or Operator number error");
        }finally{
            rResult = op.compute(lhs, rhs);
            numberStack.push(rResult);
            // check for compute 
            if(Double.isNaN(rResult) || Double.isInfinite(rResult)){
                throw new Exception("Divisor can't be 0 or function parameter out of domain");
            }
        }
    }

    public void setM(double M){
        this.mValue = M;
    }

    // for test
    /*public static void main(String[] args){
        CalExpression cal = new CalExpression();
        cal.setM(5);
        //System.out.println(cal.rExpParse("1+4*M/sqrt(64-64*0-(1+0)*64+4)+(log2(4))!"));
        System.out.println(cal.rExpParse("-2+3-(-2)"));
        return;
    }*/

}

enum Operator {
    LEFTPAREN("(", 0, 0){
        @Override
        public double compute(double lhs, double rhs){
            System.err.println("'(' can't be computed");
            throw new UnsupportedOperationException();
        }
    },
    RIGHTPAREN(")", 0, 0){
        @Override
        public double compute(double lhs, double rhs){
            System.err.println("')' can't be computed");
            throw new UnsupportedOperationException();
        }
    },
    PLUS("+", 1, 2){
        @Override
        public double compute(double lhs, double rhs){
            return lhs + rhs;
        }
    },
    MINUS("-", 1, 2){
        @Override
        public double compute(double lhs, double rhs){
            return lhs - rhs;
        }
    },
    MULTIPLY("*", 2, 2){
        @Override
        public double compute(double lhs, double rhs){
            return lhs * rhs;
        }
    },
    DIVIDE("/", 2, 2){
        @Override
        public double compute(double lhs, double rhs){
            return lhs / rhs;
        }
    },
    POWER("^", 3, 2){
        @Override
        public double compute(double lhs, double rhs){
            return Math.pow(lhs, rhs);
        }
    },
    SQRT("sqrt", 3, 1){
        @Override
        public double compute(double lhs, double rhs){
            return Math.sqrt(rhs);
        }
    },
    COS("cos", 3, 1){
        @Override
        public double compute(double lhs, double rhs){
            return Math.cos(rhs);
        }
    },
    SIN("sin", 3, 1){
        @Override
        public double compute(double lhs, double rhs){
            return Math.sin(rhs);
        }
    },
    ARCCOS("arccos", 3, 1){
        @Override
        public double compute(double lhs, double rhs){
            return Math.acos(rhs);
        }
    },
    ARCSIN("arcsin", 3, 1){
        @Override
        public double compute(double lhs, double rhs){
            return Math.asin(rhs);
        }
    },
    LOG("log2", 3, 1){
        @Override
        public double compute(double lhs, double rhs){
            return Math.log(rhs) / Math.log(2);
        }
    },
    LN("ln", 3, 1){
        @Override
        public double compute(double lhs, double rhs){
            return Math.log(rhs);
        }
    },
    M("!", 3, 1){
        @Override
        public double compute(double lhs, double rhs){
            double res = 1;
            for(int i = 2; i <= Math.floor(rhs); ++i){
                res = res * i;
            }
            return res;
        }
    },
    PI("π", 4, 0){
        @Override
        public double compute(double lhs, double rhs){
            return Math.PI;
        }
    },
    E("e", 4, 0){
        @Override
        public double compute(double lhs, double rhs){
            return Math.E;
        }
    },
    UNKNOWN("", 0, 0){
        @Override
        public double compute(double lhs, double rhs){
            System.err.println("Unknown can't be computed");
            throw new UnsupportedOperationException();
        }
    };

    private String value;
    private int priority;
    private int num;
    
    private Operator(String value, int priority, int num){
        this.value = value;
        this.priority = priority;
        this.num = num;
    }

    public static Operator getOperator(String value){
        for(Operator operator : Operator.values()){
            if(operator.value.equals(value))
                return operator;
        }
        return UNKNOWN;
    }

    public int getPriority(){
        return priority;
    }

    public int getNum(){
        return num;
    }

    public abstract double compute(double lhs, double rhs);
}