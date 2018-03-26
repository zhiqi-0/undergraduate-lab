import Jama.*;
import java.lang.String;
import java.lang.Double;
import java.util.regex.*;
import java.util.Stack;
import java.util.EmptyStackException;

public class MatrixCal{

    double[][] defaultValue = {{0}};
    Matrix mResult = new Matrix(defaultValue, 1, 1);
    public Matrix A = new Matrix(defaultValue, 1, 1);
    public Matrix B = new Matrix(defaultValue, 1, 1);

    public void setMatrix(String matrixName, String matrixDefine){
        Pattern rowPattern = Pattern.compile("\\[[^\\[\\]]+\\]");
        Matcher rowMatch = rowPattern.matcher(matrixDefine);
        Pattern numPattern = Pattern.compile("\\d+(\\.\\d+)?");
        int row = 0, col = 0;
        while(rowMatch.find()){
            row++;
            System.out.println(rowMatch.group());
            if(row == 1){
                Matcher columnMatcher = numPattern.matcher(rowMatch.group());
                while(columnMatcher.find()){
                    col++;
                }
            }
            else{
                Matcher columnMatcher = numPattern.matcher(rowMatch.group());
                int numCount = 0;
                while(columnMatcher.find()){
                    numCount++;
                }
                if(numCount != col){
                    System.err.println("Error: Matrix column number varies.");
                }
            }
        }
        double[][] array = new double[row][col];
        Matcher numMatch = numPattern.matcher(matrixDefine);
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                if(numMatch.find())
                    array[i][j] = Double.parseDouble(numMatch.group());
                else
                    array[i][j] = 0;
            }
        }
        if(matrixName.equals("A"))
            A = new Matrix(array, row, col);
        else if(matrixName.equals("B"))
            B = new Matrix(array, row, col);
    }

    public String calMatrix(String exp){
        Pattern expPattern = Pattern.compile("A|B|inv|transpose|\\+|-|\\*|\\.\\*|\\./|det|rank|solve");
        Matcher expMatcher = expPattern.matcher(exp);
        Stack<Matrix> mStack = new Stack<>();
        int numMatrix = 0, numOp = 0;
        MOperator operator = MOperator.UNKNOWN;
        while(expMatcher.find()){
            String unit = expMatcher.group();
            System.out.println("handle: " + unit);
            if(unit.equals("A")){
                numMatrix++;
                mStack.push(A);
            }
            else if(unit.equals("B")){
                numMatrix++;
                mStack.push(B);
            }
            else{
                numOp++;
                operator = MOperator.getOperator(unit);
            }
            if(numMatrix > 2 || numOp > 1){
                System.err.println("Matrix Operators more than 1 or op nums more than 2");
                return "";
            }
        }
        if(numMatrix == 0){
            System.err.println("Not enough Matrix");
            return "";
        }
        Matrix rhs = new Matrix(defaultValue, 1, 1);
        Matrix lhs = new Matrix(defaultValue, 1, 1);
        rhs = mStack.pop();
        if(operator == MOperator.UNKNOWN){
            if(numMatrix == 2){
                // error info
                return "";
            }
            mResult = rhs;
        }
        else{
            int opNum = operator.getNum();
            if(opNum != numMatrix){
                // error info
                return "";
            }
            if(opNum == 1)
                mResult = operator.compute(lhs, rhs);
            else{
                lhs = mStack.pop();
                mResult = operator.compute(lhs, rhs);
            }
        }
        return dumpMatrix(mResult);
    }

    /*public static void main(String[] args){
        CalMatrix Ma = new CalMatrix();
        Ma.setMatrix("A", "[[1,2,3],[4,5,6],[7,8,9]]");
        Ma.setMatrix("B", "[[1,2,3],[4,5,6],[7,8,9]]");
        System.out.print(Ma.calMatrix("transpose(A)"));
    }*/

    public String dumpMatrix(Matrix matrix){
        String out = "[";
        int row = matrix.getRowDimension();
        int col = matrix.getColumnDimension();
        for(int i = 0; i < row; ++i){
            if(i != 0)
                out = out + " [";
            else    
                out = out + "[";
            for(int j = 0; j < col; ++j){
                if(j == col - 1)
                    out = out + Double.toString(matrix.get(i,j));
                else    
                    out = out + Double.toString(matrix.get(i,j)) + " ";
            }
            if(i == row - 1)
                out = out + "]";
            else
                out = out + "],\n";
        }
        out = out + "]\n";
        return out;
    }
}

enum MOperator{
    PLUS("+", 2){
        @Override
        public Matrix compute(Matrix a, Matrix b){
            return a.plus(b);
        }
    },
    MINUS("-", 2){
        @Override
        public Matrix compute(Matrix a, Matrix b){
            return a.minus(b);
        }
    },
    MULTIPLY("*", 2){
        @Override
        public Matrix compute(Matrix a, Matrix b){
            return a.times(b);
        }
    },
    ELEMMULTI(".*", 2){
        @Override
        public Matrix compute(Matrix a, Matrix b){
            return a.arrayTimes(b);
        }
    },
    ELEMDIVIDE("./", 2){
        @Override
        public Matrix compute(Matrix a, Matrix b){
            return a.arrayRightDivide(b);
        }
    },
    INV("inv", 1){
        @Override
        public Matrix compute(Matrix a, Matrix b){
            return b.inverse();
        }
    },
    DET("det", 1){
        @Override
        public Matrix compute(Matrix a, Matrix b){
            double[][] res = {{b.det()}};
            return new Matrix(res);
        }
    },
    RANK("rank", 1){
        @Override
        public Matrix compute(Matrix a, Matrix b){
            double[][] rank = {{b.rank()}};
            return new Matrix(rank);
        }
    },
    TRANSPOSE("transpose", 1){
        @Override
        public Matrix compute(Matrix a, Matrix b){
            return b.transpose();
        }
    },
    SOLVE("solve", 2){
        // Solve A * X = B equation
        @Override
        public Matrix compute(Matrix a, Matrix b){
            return a.solve(b);
        }
    },
    UNKNOWN("", 0){
        @Override
        public Matrix compute(Matrix a, Matrix b){
            double[][] defaultValue = {{0}};
            return new Matrix(defaultValue);
        }
    
    };

    private String opName;
    private int opNum;

    private MOperator(String opName, int opNum){
        this.opName = opName;
        this.opNum = opNum;
    }

    public static MOperator getOperator(String name){
        for(MOperator operator : MOperator.values()){
            if(operator.opName.equals(name))
                return operator;
        }
        return UNKNOWN;
    }

    public int getNum(){
        return opNum;
    }

    public abstract Matrix compute(Matrix a, Matrix b);
}

