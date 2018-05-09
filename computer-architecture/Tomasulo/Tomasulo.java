import java.util.Queue;
import java.util.LinkedList;
import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.regex.*;
import java.util.Map;
import java.util.Scanner;

public class Tomasulo{

    // resources create
    private Reservation RS = new Reservation();
    private RegStat RegisterStat = new RegStat(16, 5);
    private Buffer LoadBuffer = new Buffer();
    private Buffer WriteBuffer = new Buffer();

    // latency --default value
    private int addLatency = 1;
    private int loadLatency = 1;
    private int mulLatency = 9;
    private int divideLatency = 39;
    private int cycle = 0;

    // code queue
    private Queue<String> op = new LinkedList<>();
    private Queue<String> rd = new LinkedList<>();
    private Queue<String> rs = new LinkedList<>();
    private Queue<String> rt = new LinkedList<>();
    private Queue<String> imm = new LinkedList<>();

    // command counter
    private Map<String, Integer> count = new HashMap<String, Integer>();
    private ArrayList<String> onExe = new ArrayList<>();

    // event for every stage after a step
    private Map<String, ArrayList<String> > event = new HashMap<>();


    public void setLatency(int add, int load, int mul, int divide){
        addLatency = add;
        loadLatency = load;
        mulLatency = mul;
        divideLatency = divide;
    }
    
    public void readCommand(String command){
        if(command.equals("")) return;
        Pattern commandPattern = Pattern.compile(".+\\.D|F\\d+|R\\d+|\\d+");
        Matcher match = commandPattern.matcher(command);
        String _op = "", _rd = "", _rs = "", _rt = "", _imm = "0";
        while(match.find()){
            String unit = match.group();
            if(unit.charAt(0) == 'R')
                _rt = unit;
            else if(Character.isDigit(unit.charAt(0)))
                _imm = unit;
            else if(unit.substring(unit.length() - 2).equals(".D")){
                _op = unit;
            }
            else if(unit.charAt(0) == 'F'){
                if(_rd.equals(""))
                    _rd = unit;
                else if(_rs.equals(""))
                    _rs = unit;
                else if(_rt.equals(""))
                    _rt = unit;
            }
        }
        op.offer(_op); rd.offer(_rd); rs.offer(_rs); rt.offer(_rt); imm.offer(_imm);
        // for debug
        System.out.println("[IF] command: " + _op + " " + _rd + " " + _rs + " " + _imm + " " + _rt);
    }

    public void init(String command){
        reset();
        readCommand(command);
    }

    public Map<String, ArrayList<String> > step(String command){
        cycle += 1;
        event.clear();
        // EX 
        Queue<String> ready = RS.ready();
        ArrayList<String> exEvent = new ArrayList<>();
        while(!ready.isEmpty()){
            String rName = ready.peek();
            System.out.println("[Exe] new start: " + rName);
            exEvent.add(rName);
            ready.poll();
            onExe.add(rName);
        }
        for(int i = 0; i < onExe.size(); ++i){
            System.out.println("[Exe] update counter:" + onExe.get(i));
            int val = count.get(onExe.get(i));
            count.remove(onExe.get(i));
            count.put(onExe.get(i), val - 1);
            if(val - 1 == 0){
                System.out.println("[Exe] End of Exe: " + onExe.get(i));
            }
        }
        event.put("EX", exEvent);
        // Write Back (can't before EX, because WB may cause a new start on Exe)
        int i = 0;
        ArrayList<String> wbEvent = new ArrayList<>();
        while(i < onExe.size()){
            if(count.get(onExe.get(i)) == -1){
                RegisterStat.clear(onExe.get(i));
                String res = RegisterStat.setRegVal(onExe.get(i));
                RS.clear(onExe.get(i), res);
                if(onExe.get(i).substring(0, onExe.get(i).length() - 1).equals("Load")){
                    LoadBuffer.clear(onExe.get(i));
                }
                wbEvent.add(onExe.get(i));
                System.out.println("[WB] WriteBack: " + onExe.get(i));
                onExe.remove(i);
                continue;
            }
            i++;
        }
        event.put("WB", wbEvent);
        // ID -- issue
        ArrayList<String> idEvent = new ArrayList<>();
        if(!op.isEmpty()){
            String _op = op.peek();
            String rName = RS.issue(_op);
            System.out.println("[Issue] check op: " + _op + "\trName: " + rName);
            if(!rName.equals("")){
                op.poll();
                String _rd = rd.peek(); rd.poll();
                String _rs = rs.peek(); rs.poll();
                String _rt = rt.peek(); rt.poll();
                String _imm = imm.peek(); imm.poll();
                if(RegisterStat.checkBusy(_rs))
                    RS.setQj(rName, RegisterStat.getRegQi(_rs));
                else{
                    RS.setVj(rName, RegisterStat.getRegVal(_rs));
                    RS.setQj(rName, "");
                }
                String commandType = rName.substring(0, rName.length() - 1);
                // FP operation
                if(commandType.equals("ADD") || commandType.equals("MUL")){
                    if(RegisterStat.checkBusy(_rt))
                        RS.setQk(rName, RegisterStat.getRegQi(_rt));
                    else{
                        RS.setVk(rName, RegisterStat.getRegVal(_rt));
                        RS.setQk(rName, "");
                    }
                    RegisterStat.setRegQi(_rd, rName);
                }
                // Load Operation
                else if(commandType.equals("Load")){
                    int addr = Integer.parseInt(_imm) + Integer.parseInt(RegisterStat.getRegQi(_rt));
                    LoadBuffer.addAddr(rName, addr);
                    RegisterStat.setRegQi(_rd, rName);
                }
                // set counter
                if(_op.equals("ADD.D") || _op.equals("SUB.D"))
                    count.put(rName, addLatency + 1);
                else if(_op.equals("MULT.D"))
                    count.put(rName, mulLatency + 1);
                else if(_op.equals("DIV.D"))
                    count.put(rName, divideLatency + 1);
                else if(_op.equals("L.D") || _op.equals("S.D")){
                    count.put(rName, loadLatency + 1);
                }
                System.out.println("[Issue] add to counter: " + rName);
                idEvent.add(rName);
            }
        }
        event.put("ID", idEvent);
        // IF -- get command
        readCommand(command);
        // console view 
        view();

        return event;
    }

    public void reset(){
        cycle = 0;
        op.clear(); rd.clear(); rs.clear(); rt.clear(); imm.clear();
        onExe.clear(); count.clear();
        RegisterStat.reset();
        RS.reset();
        LoadBuffer.reset();
        WriteBuffer.reset();
    }

    public void view(){
        System.out.println("cycle: " + Integer.toString(cycle));
        RS.view();
        RegisterStat.view();
        LoadBuffer.view();
        //System.out.println("\n");
    }

    public ArrayList<String> getRS(){
        return RS.stateToString();
    }

    public String[] getLoadBuffer(){
        return LoadBuffer.stateToString();
    }

    public String[] getRegState(){
        return RegisterStat.stateToString();
    }
    
    /*static public void main(String[] args){
        Tomasulo toma = new Tomasulo();
        toma.init("L.D F6 21(R2)");
        toma.step("L.D F2 0(R3)");
        toma.step("MULT.D F0 F2 F4");
        toma.step("SUB.D F8 F6 F2");
        toma.step("DIV.D F10 F0 F6");
        toma.step("ADD.D F6 F8 F2");
        String str = "";
        while(!str.equals("q")){
            Scanner s = new Scanner(System.in);
            str = s.next();
            toma.step("");
            toma.view();
        }
    }*/
}