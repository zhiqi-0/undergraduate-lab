import javafx.fxml.FXML;

import javafx.scene.control.TextField;
import javafx.stage.FileChooser;

import java.io.File;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TabPane;

public class MainPaneController{

    @FXML private TabPane cacheTypeChoice;
    @FXML private ComboBox<String> cacheUnionSizeChoice, cacheISizeChoice, cacheDSizeChoice;
    @FXML private ComboBox<String> blockSizeChoice;
    @FXML private ComboBox<String> assSizeChoice;
    @FXML private ComboBox<String> replaceChoice;
    @FXML private ComboBox<String> prefetchChoice;
    @FXML private ComboBox<String> writeMissChoice;
    @FXML private ComboBox<String> writeChoice;
    @FXML private TextField taText, taMissText, taMissRateText;
    @FXML private TextField riText, riMissText, riMissRateText;
    @FXML private TextField rdText, rdMissText, rdMissRateText;
    @FXML private TextField wdText, wdMissText, wdMissRateText;
    @FXML private TextField pathText;
    @FXML private Button stepButton, runButton, scanButton, resetButton;
    private boolean dataReady = false;
    Cache cacheModel = new Cache();

    @FXML
    private void initialize(){
        // cache size option list
        ObservableList<String> cacheSizeList = FXCollections.observableArrayList(
            "2KB", "4KB", "8KB", "16KB", "32KB", "64KB", "128KB", "256KB", "512KB", "1024KB"
        );
        cacheUnionSizeChoice.setItems(cacheSizeList);
        cacheDSizeChoice.setItems(cacheSizeList);
        cacheISizeChoice.setItems(cacheSizeList);
        // block size option list
        ObservableList<String> blockSizeList = FXCollections.observableArrayList(
            "16B", "32B", "64B", "128B", "256B"
        );
        blockSizeChoice.setItems(blockSizeList);
        // associativity 
        ObservableList<String> assList = FXCollections.observableArrayList(
            "direct", "2-way", "4-way", "8-way", "16-way", "32-way"
        );
        assSizeChoice.setItems(assList);
        // replacement strategy
        ObservableList<String> replaceList = FXCollections.observableArrayList(
            "LRU", "FIFO", "RAND"
        );
        replaceChoice.setItems(replaceList);
        // prefetch strategy
        ObservableList<String> prefetchList = FXCollections.observableArrayList(
            "No Prefetch", "Prefetch when Miss"
        );
        prefetchChoice.setItems(prefetchList);
        // write strategy
        ObservableList<String> writeList = FXCollections.observableArrayList(
            "Write-back", "Write-through"
        );
        writeChoice.setItems(writeList);
        // write miss strategy
        ObservableList<String> writeMissList = FXCollections.observableArrayList(
            "Allocate", "Not Allocate"
        );
        writeMissChoice.setItems(writeMissList);
    }
    @FXML
    protected void buttonActionScan(ActionEvent event){
        FileChooser fileStage = new FileChooser();
        File file = fileStage.showOpenDialog(null);
        if(file != null){
            String path = file.getPath();
            pathText.setText(path);
            dataReady = false;
        }
    }
    @FXML
    protected void buttonStepRun(ActionEvent event){
        if(!dataReady){
            setCache();
            dataReady = true;
        }
        cacheModel.singleStep();
        setResult();
    }

    @FXML
    protected void buttonRun(ActionEvent event){
        //cacheModel.reset();
        setCache();
        cacheModel.run();
        setResult();
        dataReady = false; 
    }

    @FXML
    protected void buttonReset(ActionEvent event){
        dataReady = false;
        cacheModel.reset();
        setResult();
    }

    private void setCache(){
        // block size
        String blockSizeString = blockSizeChoice.getValue();
        if(blockSizeString.length() > 0)
            blockSizeString = blockSizeString.substring(0, blockSizeString.length() - 1);
        int blockSize = Integer.parseInt(blockSizeString);
        // associativity
        String assString = assSizeChoice.getValue();
        int ass = 1;
        if(!assString.equals("direct")){
            assString = assString.substring(0, 1);
            ass = Integer.parseInt(assString);
        }
        // replace
        String replace = replaceChoice.getValue();
        // prefetch
        String prefetchString = prefetchChoice.getValue();
        
        boolean prefetch = true;
        if(prefetchString.equals("No Prefetch")) prefetch = false;
        // write strategy
        String writeString = writeChoice.getValue();
        // write miss strategy
        String writeMissString = writeMissChoice.getValue();
        boolean writeMiss = false;
        if(writeMissString.equals("Allocate")) writeMiss = true;
        // cache type
        int cacheType = cacheTypeChoice.getSelectionModel().getSelectedIndex();
        // get cache size
        int[] cacheSize = new int[2];
        if(cacheType == 0){
            String size = cacheUnionSizeChoice.getValue();
            size = size.substring(0, size.length() - 2);
            cacheSize[0] = Integer.parseInt(size) * 1024;
        }
        else{
            String sizeI = cacheISizeChoice.getValue();
            sizeI = sizeI.substring(0, sizeI.length() - 2);
            cacheSize[0] = Integer.parseInt(sizeI) * 1024;
            String sizeD = cacheDSizeChoice.getValue();
            sizeD = sizeD.substring(0, sizeD.length() - 2);
            cacheSize[1] = Integer.parseInt(sizeD) * 1024;
        }
        // file open path
        String filename = pathText.getText();
        cacheModel.setConfig(cacheType, cacheSize, blockSize, ass,
                             replace, prefetch, writeString, writeMiss, filename);
    }

    @FXML
    private void setResult(){
        double[] stat = cacheModel.getStatistics();
        taText.setText(Double.toString(stat[0]));
        taMissText.setText(Double.toString(stat[1]));
        taMissRateText.setText(Double.toString(stat[2]));
        riText.setText(Double.toString(stat[3]));
        riMissText.setText(Double.toString(stat[4]));
        riMissRateText.setText(Double.toString(stat[5]));
        rdText.setText(Double.toString(stat[6]));
        rdMissText.setText(Double.toString(stat[7]));
        rdMissRateText.setText(Double.toString(stat[8]));
        wdText.setText(Double.toString(stat[9]));
        wdMissText.setText(Double.toString(stat[10]));
        wdMissRateText.setText(Double.toString(stat[11]));
    }
}