import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.ThreadLocalRandom;

public class Cache{

    // cache config
    private int cacheType, cacheUnionSize, cacheISize, cacheDSize; // cacheType = 0 if union, 1 if seperate
    private int blockSize, associativity;
    String replace;
    boolean prefetch, writeMiss;
    String write;
    int unionIndexBit, iIndexBit, dIndexBit, offBit; // no need for tag bit calculation
    int unionIndexNum, iIndexNum, dIndexNum;
    
    // cache model cache[index] = {list addr in this index}; size = {}
    private ArrayList<List<Integer>> unionCache = new ArrayList<>();
    private ArrayList<Integer> unionCurrSize = new ArrayList<>();

    private ArrayList<List<Integer>> iCache = new ArrayList<>();
    private ArrayList<Integer> iCurrSize = new ArrayList<>();

    private ArrayList<List<Integer>> dCache = new ArrayList<>();
    private ArrayList<Integer> dCurrSize = new ArrayList<>();

    // cache running data
    private Queue<Integer> dataType = new LinkedList<>();
    private Queue<Integer> dataIndex = new LinkedList<>();
    private Queue<Integer> dataTag = new LinkedList<>();

    // statistics
    int ta, taMiss;
    double taMissRate;
    int ri, riMiss;
    double riMissRate;
    int rd, rdMiss;
    double rdMissRate;
    int wd, wdMiss;
    double wdMissRate;
    
    /* read one instruction from queue
     * search cache, update statistics
     * if can't get instruction, return false
     */
    public boolean singleStep(){
        if(dataType.isEmpty() || dataIndex.isEmpty() || dataTag.isEmpty())
            return false;
        // get data
        int _dataType = dataType.poll();
        int _dataIndex = dataIndex.poll();
        int _dataTag = dataTag.poll();
        // update cache
        updateCache(_dataType, _dataIndex, _dataTag, prefetch);
        return true;
    }

    /* run all data 
     * call singleStep() until it returns false
     */
    public void run(){
        while(singleStep()) {}
    }

    /* to check wether can hit a cache
     * update count every hit time
     */
    private boolean isInCache(int _dataType, int _dataIndex, int _dataTag){
        int pos;
        // union cache
        if(cacheType == 0){
            pos = unionCache.get(_dataIndex).indexOf(_dataTag);
            if(pos != -1){
                if(replace.equals("LRU")){
                    // move to list end
                    unionCache.get(_dataIndex).remove(pos);
                    unionCache.get(_dataIndex).add(_dataTag);
                }
                return true;
            }
        }
        // seperate cache
        else if(_dataType == 2){
            // read instruction type
            pos = iCache.get(_dataIndex).indexOf(_dataTag);
            if(pos != -1){
                if(replace.equals("LRU")){
                    // move to list end
                    iCache.get(_dataIndex).remove(pos);
                    iCache.get(_dataIndex).add(_dataTag);
                }
                return true;
            }
        }
        else{
            // read or write data
            pos = dCache.get(_dataIndex).indexOf(_dataTag);
            if(pos != -1){
                if(replace.equals("LRU")){
                    // move to list end
                    dCache.get(_dataIndex).remove(pos);
                    dCache.get(_dataIndex).add(_dataTag);
                }
                return true;
            }
        }
        return false;
    }

    /* update Cache based on all kinds of strategy
     * update statistics
     */
    private void updateCache(int _dataType, int _dataIndex, int _dataTag, boolean prefetchFlag){
        boolean hitFlag = isInCache(_dataType, _dataIndex, _dataTag);
        // update statistics
        switch(_dataType){
            case 0: rd+= 1; if(!hitFlag) rdMiss += 1; rdMissRate = rdMiss / (double)(rd); break;
            case 1: wd+= 1; if(!hitFlag) wdMiss += 1; wdMissRate = wdMiss / (double)(wd); break;
            case 2: ri+= 1; if(!hitFlag) riMiss += 1; riMissRate = riMiss / (double)(ri); break;
        }
        ta += 1;
        if(!hitFlag) taMiss += 1;
        taMissRate = taMiss / (double)(ta);
        // return if hit or meet missing write addr and write allocate is not enabled
        if(hitFlag || (!writeMiss && _dataType == 1)) return;
        // miss 
        int indexNum;
        if(cacheType == 0){
            if(unionCurrSize.get(_dataIndex) < associativity){
                // load to cache
                unionCurrSize.set(_dataIndex, unionCurrSize.get(_dataIndex) + 1);
                unionCache.get(_dataIndex).add(_dataTag);
            }
            else{
                // allocate to cache and remove 1 item
                int removePos = 0;
                if(replace.equals("RAND"))
                    removePos = ThreadLocalRandom.current().nextInt(0, unionCurrSize.get(_dataIndex));
                unionCache.get(_dataIndex).remove(removePos);
                unionCache.get(_dataIndex).add(_dataTag);
            }
            indexNum = unionIndexNum;
        }
        else if(_dataType == 2){
            if(iCurrSize.get(_dataIndex) < associativity){
                // load to cache
                iCurrSize.set(_dataIndex, iCurrSize.get(_dataIndex) + 1);
                iCache.get(_dataIndex).add(_dataTag);
            }
            else{
                // allocate to cache and remove 1 item
                int removePos = 0;
                if(replace.equals("RAND"))
                    removePos = ThreadLocalRandom.current().nextInt(0, iCurrSize.get(_dataIndex));
                iCache.get(_dataIndex).remove(removePos);
                iCache.get(_dataIndex).add(_dataTag);
            }
            indexNum = iIndexNum;
        }
        else{
            if(dCurrSize.get(_dataIndex) < associativity){
                // load to cache
                dCurrSize.set(_dataIndex, dCurrSize.get(_dataIndex) + 1);
                dCache.get(_dataIndex).add(_dataTag);
            }
            else{
                // allocate cache and remove 1 item
                int removePos = 0;
                if(replace.equals("RAND"))
                    removePos = ThreadLocalRandom.current().nextInt(0, dCurrSize.get(_dataIndex));
                dCache.get(_dataIndex).remove(removePos);
                dCache.get(_dataIndex).add(_dataTag);
            }
            indexNum = dIndexNum;
        }
        // prefetch
        if(prefetchFlag && _dataType != 1){
            updateCache(_dataType, (_dataIndex + 1) % indexNum, _dataTag + (_dataIndex + 1) / indexNum, false);
        }
    }


    // read data
    public boolean readData(String filePath){
        dataType.clear(); dataTag.clear(); dataIndex.clear();
        try{
            File file = new File(filePath);
            BufferedReader reader = new BufferedReader(new FileReader(file));
            String text = null;
            while(!(text = reader.readLine()).equals(null)){
                String[] parser = text.split("\\ +");
                int type = Integer.parseInt(parser[0]);
                dataType.add(type);
                long addr = Long.parseLong(parser[1], 16);
                // take off offset bit
                addr = addr >> offBit;
                // get index
                int indexBit;
                if(cacheType == 0) indexBit = unionIndexBit;
                else if(type == 2) indexBit = iIndexBit;
                else indexBit = dIndexBit;
                dataIndex.add((int)(addr - ((addr >> indexBit) << indexBit)));
                // get tag
                dataTag.add((int)(addr >> indexBit));
            }
        }catch(FileNotFoundException e){
            // error info
            return false;
        }catch(Exception e){
            // unknown exception happened
            return false;
        }
        return true;
    }

    /* init cache config including reading data and allocate cache memory
     * if _cacheType = 0: Union Cache; 1: Seperate Cache with _cacheSize[I-size, D-size]
     * all integer parameters are in Bytes, except _ass is _ass-way set associate 
     */
    public void setConfig(int _cacheType, int[] _cacheSize, int _blockSize,
                   int _ass, String _replace, boolean _prefetch,
                   String _write, boolean _writeMiss, String filename){
        cacheType = _cacheType;
        blockSize = _blockSize;
        associativity = _ass;
        replace = _replace;
        prefetch = _prefetch;
        write = _write;
        writeMiss = _writeMiss;
        
        if(cacheType == 0){
            // Union Cache
            cacheUnionSize = _cacheSize[0];
            cacheISize = cacheDSize = 0;
            unionIndexNum = cacheUnionSize / (_ass * blockSize);
            unionIndexBit = log2(unionIndexNum);
            while(unionCache.size() < unionIndexNum) unionCache.add(new ArrayList<Integer>());
            while(unionCurrSize.size() < unionIndexNum) unionCurrSize.add(0, 0);
            iIndexBit = dIndexBit = 0;
        }
        else if(cacheType == 1){
            // seperate Cache
            cacheISize = _cacheSize[0];
            cacheDSize = _cacheSize[1];
            cacheUnionSize = 0;

            dIndexNum = cacheDSize / (_ass * blockSize);
            dIndexBit = log2(dIndexNum);
            while(dCache.size() < dIndexNum) dCache.add(new ArrayList<Integer>());
            while(dCurrSize.size() < dIndexNum) dCurrSize.add(0, 0);

            iIndexNum = cacheISize / (_ass * blockSize);
            iIndexBit = log2(iIndexNum);
            while(iCache.size() < iIndexNum) iCache.add(new ArrayList<Integer>());
            while(iCurrSize.size() < iIndexNum) iCurrSize.add(0, 0);
            unionIndexBit = 0;
        }
        else{
            // error info
        }
        // set offset bit
        offBit = log2(blockSize);
        // tag bit is no need for calculation
        // since the remaining address is the tag.
        printConfig();
        readData(filename);
    }


    private int log2(int n){
        int result = 0;
        while(n != 1){
            n = n >> 1;
            result += 1;
        }
        return result;
    }

    public double[] getStatistics(){
        double[] stat = new double[12];
        stat[0] = ta; stat[1] = taMiss; stat[2] = taMissRate;
        stat[3] = ri; stat[4] = riMiss; stat[5] = riMissRate;
        stat[6] = rd; stat[7] = rdMiss; stat[8] = rdMissRate;
        stat[9] = wd; stat[10] = wdMiss; stat[11] = wdMissRate;
        return stat;
    }

    private void printConfig(){
        String cacheTypeString = "Union";
        if(cacheType == 1) cacheTypeString = "I-Cache, D-Cache";
        String cacheUnionSizeString = Integer.toString(cacheUnionSize) + "B";
        String cacheDSizeString = Integer.toString(cacheDSize) + "B";
        String cacheISizeString = Integer.toString(cacheISize) + "B";
        String blockSizeString = Integer.toString(blockSize) + "B";
        String assString = Integer.toString(associativity) + "-way";
        String prefetchString = "No Prefetch";
        if(prefetch) prefetchString = "Prefetch on writing miss";
        String writeString = write;
        String writeMissString = "No Allocate";
        if(writeMiss) writeMissString = "Allocate";
        System.out.println("-------------------- cache config --------------------");
        System.out.println("Cache type: " + cacheTypeString);
        if(cacheType == 0)
            System.out.println("Cache Size: " + cacheUnionSizeString);
        else
            System.out.println("I-Cache Size: " + cacheISizeString + "  D-Cache Size: " + cacheDSizeString);
        System.out.println("Cache Block Size: " + blockSizeString);
        System.out.println("Cache Associativity: " + assString);
        System.out.println("Cache Prefetch Strategy: " + prefetchString);
        System.out.println("Cache Write Strategy: " + writeString);
        System.out.println("Cache WriteMiss Strategy: " + writeMissString);
        System.out.println("Bit info: offset Bit: " + Integer.toString(offBit));
        System.out.println("Bit info: Union Cache Index Bit: " + Integer.toString(unionIndexBit));
        System.out.println("Bit info: I-Cache Index Bit: " + Integer.toString(iIndexBit));
        System.out.println("Bit info: D-Cache Index Bit: " + Integer.toString(dIndexBit));
        System.out.println("------------------------------------------------------");
    }

    public void reset(){
        ta = 0; taMiss = 0; taMissRate = 0;
        ri = 0; riMiss = 0; riMissRate = 0;
        rd = 0; rdMiss = 0; rdMissRate = 0;
        wd = 0; wdMiss = 0; wdMissRate = 0;
        unionCache.clear(); unionCurrSize.clear();
        iCache.clear(); iCurrSize.clear();
        dCache.clear(); dCurrSize.clear();
        dataTag.clear(); dataIndex.clear(); dataType.clear();
    }

}