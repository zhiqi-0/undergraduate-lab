import java.math.BigDecimal;
import java.util.Stack;
import java.lang.String;
import java.lang.Double;
import java.util.regex.*;


class CalExpression{
    
    double rResult = 0;

    double rVal(String exp){

        Stack<Double> numberStack = new Stack<>();
        Stack<Operator> opStack = new Stack<>();
        double number = 0;
        boolean dotflag = false;        // avoid a number has to dots
        // parse whole string expression
        Pattern expPattern = Pattern.compile("\\d+(\\.\\d+)?|\\+|-|\\*|/|\\^|sqrt|π");
        Matcher match = expPattern.matcher(exp);
        // scan whole parsed expression
        while(match.find()){
            String unit = match.group();
            System.out.println(unit);
            if(Character.isDigit(unit.charAt(0))){
                number = Double.parseDouble(unit);
                numberStack.push(number);
                continue;
            }
        }
        return rResult;
    }

    public static void main(){
        CalExpression cal = new CalExpreesion();
        cal.rVal("2+3/4+5");
        return;
    }

}

enum Operator {
    LEFTPAREN("(", 0){
        @Override
        public double compute(double num1, double num2){
            throw new UnsupportedOperationException();
        }
        @Override
        public double compute(double num1){
            throw new UnsupportedOperationException();
        }
        @Override
        public double compute(){
            throw new UnsupportedOperationException();
        }
    },
    RIGHTPAREN(")", 0){
        @Override
        public double compute(double num1, double num2){
            throw new UnsupportedOperationException();
        }
        @Override
        public double compute(double num1){
            throw new UnsupportedOperationException();
        }
        @Override
        public double compute(){
            throw new UnsupportedOperationException();
        }
    },
    PLUS("+", 1){
        @Override
        public double compute(double num1, double num2){
            return num1 + num2;
        }
        @Override
        public double compute(double num1){
            throw new UnsupportedOperationException();
        }
        @Override
        public double compute(){
            throw new UnsupportedOperationException();
        }
    },
    MINUS("-", 1){
        @Override
        public double compute(double num1, double num2){
            return num1 - num2;
        }
        @Override
        public double compute(double num1){
            throw new UnsupportedOperationException();
        }
        @Override
        public double compute(){
            throw new UnsupportedOperationException();
        }
    },
    MULTIPLY("*", 2){
        @Override
        public double compute(double num1, double num2){
            return num1 * num2;
        }
        @Override
        public double compute(double num1){
            throw new UnsupportedOperationException();
        }
        @Override
        public double compute(){
            throw new UnsupportedOperationException();
        }
    },
    DIVIDE("/", 2){
        @Override
        public double compute(double num1, double num2){
            return num1 / num2;
        }
        @Override
        public double compute(double num1){
            throw new UnsupportedOperationException();
        }
        @Override
        public double compute(){
            throw new UnsupportedOperationException();
        }
    },
    POWER("^", 3){
        @Override
        public double compute(double num1, double num2){
            return Math.pow(num1, num2);
        }
        @Override
        public double compute(double num1){
            throw new UnsupportedOperationException();
        }
        @Override
        public double compute(){
            throw new UnsupportedOperationException();
        }
    },
    SQRT("sqrt", 3){
        @Override
        public double compute(double num1, double num2){
            throw new UnsupportedOperationException();
        }
        @Override
        public double compute(double num1){
            return Math.sqrt(num1);
        }
        @Override
        public double compute(){
            throw new UnsupportedOperationException();
        }
    },
    PI("π", 4){
        @Override
        public double compute(double num1, double num2){
            throw new UnsupportedOperationException();
        }
        @Override
        public double compute(double num1){
            throw new UnsupportedOperationException();
        }
        @Override
        public double compute(){
            return Math.PI;
        }
    },
    UNKNOWN("", 0){
        @Override
        public double compute(double num1, double num2){
            throw new UnsupportedOperationException();
        }
        @Override
        public double compute(double num1){
            throw new UnsupportedOperationException();
        }
        @Override
        public double compute(){
            return 0;
        }
    };

    private String value;
    private int priority;
    
    private Operator(String value, int priority){
        this.value = value;
        this.priority = priority;
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

    public abstract double compute(double num1, double num2);
    public abstract double compute(double num1);
    public abstract double compute();
}