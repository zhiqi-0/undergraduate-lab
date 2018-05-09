import java.util.ArrayList;
import java.util.List;

class Buffer{
    private int maxSize = 3;
    private int[] buffer = new int[maxSize];
    private boolean[] busy = new boolean[maxSize]; 

    public boolean checkExist(int addr){
        for(int i = 0; i < maxSize; ++i){
            if(buffer[i] == addr) return true;
        }
        return false;
    }

    public void addAddr(String rName, int addr){
        int index = Integer.parseInt(rName.substring(rName.length() - 1));
        buffer[index] = addr;
        busy[index] = true;
    }

    public void clear(String rName){
        int index = Integer.parseInt(rName.substring(rName.length() - 1));
        busy[index] = false;
        buffer[index] = -1;
    }

    public void reset(){
        for(int i = 0; i < maxSize; ++i){
            busy[i] = false;
            buffer[i] = -1;
        }
    }

    public void view(){
        System.out.println("-----------------------------Buffer---------------------------");
        for(int i = 0; i < maxSize; ++i){
            System.out.println(Integer.toString(i) + "\t:\t" + Integer.toString(buffer[i]));
        }
    }

    public String[] stateToString(){
        String[] res = new String[maxSize];
        for(int i = 0; i < maxSize; ++i){
            if(busy[i]) res[i] = "yes:";
            else res[i] = "no:";
            if(buffer[i] != -1) res[i] = res[i] + Integer.toString(buffer[i]);
            else res[i] = res[i] + "--";
        }
        return res;
    }
}