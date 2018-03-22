import java.math.BigDecimal;
import java.util.Stack;
import java.lang.String;
import java.lang.Double;
import java.util.regex.*;
import java.util.HashMap;
import java.util.EmptyStackException;


class CalExpression{
    
    private double rResult = 0;
    private double mValue = 0;
    private Pattern expPattern;
    private Matcher match;
    private Stack<Double> numberStack = new Stack<>();
    private Stack<Operator> opStack = new Stack<>();

    double rExpParse(String exp){
        double number = 0;
        double lhs = 0, rhs = 0;
        // parse whole string expression
        expPattern = Pattern.compile("\\d+(\\.\\d+)?|\\+|-|\\*|/|\\(|\\)|\\^|sqrt|π|M");
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
                    System.out.println("Unknown Operator");
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
        while(!opStack.isEmpty())
            stepCal();
        return rResult;
    }

    // get a operator from opStack and
    // get number from numberStack and
    // calculate then put back to numberStack
    void stepCal(){
        double lhs =0, rhs = 0;
        try{
            Operator op = opStack.pop();
            int opNum = op.getNum();
            rhs = numberStack.pop();
            if(opNum == 2)
                lhs = numberStack.pop();
            rResult = op.compute(lhs, rhs);
            numberStack.push(rResult);
        } catch(EmptyStackException e){
            System.out.println("Final Pop: Illegal pop");
        }
    }

    public void setM(double M){
        this.mValue = M;
    }

    public static void main(String[] args){
        CalExpression cal = new CalExpression();
        cal.setM(5);
        System.out.println(cal.rExpParse("1+4*M/sqrt(4)-2"));
        return;
    }

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
    PI("π", 4, 0){
        @Override
        public double compute(double lhs, double rhs){
            throw new UnsupportedOperationException();
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