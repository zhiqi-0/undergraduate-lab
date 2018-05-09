
public class RegStat{

    // number of register
    private int fNumber;
    private int rNumber;
    // 10 F Register
    private String[] qi;
    private String[] fRegister;
    private int[] rRegister;
    // Status
    private boolean[] busy;
    private int resultCount = 1;

    RegStat(int fReg, int rReg){
        fNumber = fReg;
        rNumber = rReg;
        qi = new String[fNumber];
        fRegister = new String[fNumber];
        busy = new boolean[fNumber];
        rRegister = new int[rNumber];
        reset();
    }

    public String getRegQi(String regName){
        if(regName.equals("")) return "";
        int index = Integer.parseInt(regName.substring(1)) / 2;
        if(regName.charAt(0) == 'F')
            return qi[index];
        else
            return Integer.toString(rRegister[index * 2]);
    }

    public String getRegVal(String regName){
        if(regName.equals("")) return "";
        int index = Integer.parseInt(regName.substring(1)) / 2;
        if(regName.charAt(0) == 'F'){
            if(fRegister[index].equals("")){
                return regName;
            }
            return fRegister[index];
        }
        return Integer.toString(rRegister[index * 2]);
    }

    public void setRegQi(String regName, String val){
        int index = Integer.parseInt(regName.substring(1)) / 2;
        if(regName.charAt(0) == 'F'){
            qi[index] = val;
            busy[index] = true;
        }
        else
            rRegister[index * 2] = Integer.parseInt(val);
    }

    public String setRegVal(String rName){
        for(int i = 0; i < fNumber; ++i){
            if(qi[i].equals(rName)){
                fRegister[i] = "M" + Integer.toString(resultCount);
            }
        }
        resultCount++;
        return "M" + Integer.toString(resultCount - 1);
    }

    public boolean checkBusy(String regName){
        if(regName.equals("")) return true;
        int index = Integer.parseInt(regName.substring(1)) / 2;
        if(regName.charAt(0) == 'F')
            return busy[index];
        else
            return true;
    }

    public void clear(String rName){
        for(int i = 0; i < fNumber; ++i){
            if(qi[i].equals(rName)){
                //qi[i] = "";
                busy[i] = false;
            }
        }
    }

    public void reset(){
        for(int i = 0; i < fNumber; ++i){
            qi[i] = "";
            busy[i] = false;
            fRegister[i] = "";
        }
        for(int i = 0; i < rNumber; ++i){
            rRegister[i] = 0;
        }
        resultCount = 1;
    }

    public void view(){
        System.out.println("-----------------------------RegStat--------------------------");
        for(int i = 0; i < fNumber; ++i){
            System.out.print("F" + Integer.toString(i) + "\t");
        }
        System.out.println("");
        for(int i = 0; i < fNumber; ++i){
            System.out.print(qi[i] + "\t");
        }
        System.out.println("");
    }

    public String[] stateToString(){
        String[] res = new String[2];
        res[0] = ""; res[1] = "";
        for(int i = 0; i < fNumber; ++i){
            if(qi[i].equals("")) res[0] = res[0] + " :";
            else res[0] = res[0] + qi[i] + ":";
            if(fRegister[i].equals("")) res[1] = res[1] + " :";
            else res[1] = res[1] + fRegister[i] + ":";
        }
        return res;
    }
}