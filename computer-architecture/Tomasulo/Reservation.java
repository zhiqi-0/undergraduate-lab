import java.util.LinkedList;
import java.util.Queue;
import java.util.ArrayList;

public class Reservation{
    
    private int addNumber = 3;
    private int loadNumber = 3;
    private int mulNumber = 2;

    private boolean[] busy = new boolean[addNumber + loadNumber + mulNumber];
    private String[] op = new String[addNumber + loadNumber + mulNumber];
    private String[] vj = new String[addNumber + loadNumber + mulNumber];
    private String[] vk = new String[addNumber + loadNumber + mulNumber];
    private String[] qj = new String[addNumber + loadNumber + mulNumber];
    private String[] qk = new String[addNumber + loadNumber + mulNumber];
    private boolean[] onExe = new boolean[addNumber + loadNumber + mulNumber];

    private String operatorToRName(String operator){
        if(operator.equals("ADD.D") || operator.equals("SUB.D"))
            return "ADD";
        else if(operator.equals("L.D"))
            return "Load";
        else if(operator.equals("MULT.D") || operator.equals("DIV.D"))
            return "MUL";
        return "";
    }

    private int rNameToIndex(String rName){
        int index = Integer.parseInt(rName.substring(rName.length() - 1));
        String r = rName.substring(0, rName.length() - 1);
        int base = 0;
        if(r.equals("Load"))
            base = addNumber;
        else if(r.equals("MUL"))
            base = addNumber + loadNumber;
        return base + index;
    }

    private int checkFree(String operator){
        if(operator.equals("ADD.D") || operator.equals("SUB.D")){
            for(int i = 0; i < 3; ++i){
                if(!busy[i])
                    return i;
            }
            return -1;
        }
        else if(operator.equals("L.D") || operator.equals("S.D")){
            for(int i = addNumber; i < addNumber + loadNumber; ++i){
                if(!busy[i])
                    return i;
            }
            return -1;
        }
        else if(operator.equals("MULT.D") || operator.equals("DIV.D")){
            int base = addNumber + loadNumber;
            for(int i = base; i < base + mulNumber; ++i){
                if(!busy[i])
                    return i;
            }
            return -1;
        }
        else
            return -1;
    }

    public String issue(String operator){
        int launch = checkFree(operator);
        if(launch == -1) return "";
        busy[launch] = true;
        op[launch] = operator;
        if(operator.equals("L.D") || operator.equals("S.D"))
            launch -= addNumber;
        else if(operator.equals("MULT.D") || operator.equals("DIV.D"))
            launch -= (addNumber + loadNumber);
        return operatorToRName(operator) + Integer.toString(launch);
    }

    public void setVj(String rName, String val){
        int index = rNameToIndex(rName);
        vj[index] = val;
    }

    public void setVk(String rName, String val){
        int index = rNameToIndex(rName);
        vk[index] = val;
    }

    public void setQj(String rName, String val){
        int index = rNameToIndex(rName);
        qj[index] = val;
    }

    public void setQk(String rName, String val){
        int index = rNameToIndex(rName);
        qk[index] = val;
    }

    public void clear(String rName, String val){
        int index = rNameToIndex(rName);
        busy[index] = false;
        op[index] = "";
        vj[index] = "";
        vk[index] = "";
        qj[index] = "";
        qk[index] = "";
        onExe[index] = false;
        int totalNumber = addNumber + loadNumber + mulNumber;
        for(int i = 0; i < totalNumber; ++i){
            if(qj[i].equals(rName)){
                vj[i] = val;
                qj[i] = "";
            }
            if(qk[i].equals(rName)){
                vk[i] = val;
                qk[i] = "";
            }
        }
    }

    public Queue<String> ready(){
        Queue<String> res = new LinkedList<>();
        for(int i = 0; i < addNumber; ++i){
            if(busy[i] && !onExe[i] && qj[i].equals("") && qk[i].equals("")){
                res.offer("ADD" + Integer.toString(i));
                onExe[i] = true;
            }
        }
        int base = addNumber;
        for(int i = 0; i < loadNumber; ++i){
            if(busy[base + i] && !onExe[base + i] && qj[base + i].equals("") && qk[base + i].equals("")){
                res.offer("Load" + Integer.toString(i));
                onExe[base + i] = true;
            }
        }
        base += loadNumber;
        for(int i = 0; i < mulNumber; ++i){
            if(busy[base + i] && !onExe[base + i] && qj[base + i].equals("") && qk[base + i].equals("")){
                res.offer("MUL" + Integer.toString(i));
                onExe[base + i] = true;
            }
        }
        return res;
    }

    public void reset(){
        int total = addNumber + loadNumber + mulNumber;
        for(int i = 0; i < total; ++i){
            busy[i] = false;
            op[i] = "";
            vj[i] = "";
            vk[i] = "";
            qj[i] = "";
            qk[i] = "";
            onExe[i] = false;
        }
    }

    public void view(){
        System.out.println("-------------------------Reservation State---------------------");
        System.out.println("Name\tBusy\tOp\tVj\tVk\tQj\tQk");
        int total = addNumber + loadNumber + mulNumber;
        for(int i = 0; i < total; ++i){
            if(i < addNumber)
                System.out.print("ADD" + Integer.toString(i));
            else if(i < addNumber + loadNumber)
                System.out.print("Load" + Integer.toString(i - addNumber));
            else
                System.out.print("MUL" + Integer.toString(i - addNumber - loadNumber));
            if(busy[i])
                System.out.print("\tbusy");
            else
                System.out.print("\tfree");
            System.out.println("\t" + op[i] + "\t" + vj[i] + "\t" + vk[i] + "\t" + qj[i] + "\t" + qk[i]);
        }
    }

    public ArrayList<String> stateToString(){
        ArrayList<String> res = new ArrayList<>();
        for(int i = 0; i < addNumber + loadNumber + mulNumber; ++i){
            if(i >= addNumber && i < addNumber + loadNumber) continue;
            String content = "";
            if(busy[i])
                content = "yes:";
            else
                content = "no:";   
            content = content + op[i] + ":";
            if(vj[i].equals("")) content = content + " :";
            else content = content + vj[i] + ":";
            if(vk[i].equals("")) content = content + " :";
            else content = content + vk[i] + ":";
            if(qj[i].equals("")) content = content + " :";
            else content = content + qj[i] + ":";
            if(qk[i].equals("")) content = content + " :";
            else content = content + qk[i] + ":";
            res.add(content);
        }
        return res;
    }
}