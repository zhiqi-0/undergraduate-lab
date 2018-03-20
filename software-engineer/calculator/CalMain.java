/*
 * File Information: Main GUI for Calculator
 */

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.RowConstraints;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;

public class CalMain extends Application{

    public enum Mode {Regular, Matrix, Function;}

    Mode currentMode = Mode.Regular;
    double regularRes = 0;
    double regularM = 0;

    // basic items
    TextArea inputArea = new TextArea();            // input area
    TextArea outputArea = new TextArea();              // result area
    Button[] digitButtons = new Button[10];         // digit buttion 0-9
    Button[] operatorButtons = new Button[]{        // 14 operators
        new Button("DEL"),
        new Button("AC"),
        new Button("x"),
        new Button("/"),
        new Button("+"),
        new Button("-"),
        new Button("Ans"),
        new Button("="),
        new Button("π"),    //8
        new Button("("),
        new Button(")"),
        new Button("M"),
        new Button("M+"),
        new Button("."),    //13
        new Button("EE")
    };


    public static void main(String[] args){
        launch(args);
    }
    
    @Override
    public void start(Stage primaryStage){
        // basic info for gui design
        final int defaultLen = 300;
        final int defaultWid = 560;
        final int buttonRow = 5;
        final int buttonCol = 5;

        VBox hbox = new VBox();
        /* define input text */
        inputArea.setPrefSize(defaultLen, 120);
        inputArea.setPromptText("put your numbers here...");
        hbox.getChildren().add(inputArea);
        /* define output label */
        outputArea.setPrefSize(defaultLen, 120);
        hbox.getChildren().add(outputArea);
        /* define basic number layout */
        GridPane buttonGrid = new GridPane();
        // init grid
        buttonGrid.setPadding(Insets.EMPTY);
        ColumnConstraints[] columnSet = new ColumnConstraints[5];
        for(int i = 0; i < 5; ++i){
            columnSet[i] = new ColumnConstraints(defaultLen / buttonCol);
            buttonGrid.getColumnConstraints().add(columnSet[i]);
        }
        RowConstraints[] rowSet = new RowConstraints[buttonRow];
        for(int i = 0; i < buttonRow; ++i){
            rowSet[i] = new RowConstraints(60);
            buttonGrid.getRowConstraints().add(rowSet[i]);
        }
        // add buttons
        addDigitButton(buttonGrid, buttonRow - 1);
        addBasicOperation(buttonGrid, buttonRow - 1);
        hbox.getChildren().add(buttonGrid);
        /* create and show the scene */
        Scene scene = new Scene(hbox, defaultLen, defaultWid, Color.WHITE);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Calculator - Regualr Mode");
        primaryStage.show();
    }

    public void addDigitButton(GridPane gridPane, int buttonMaxRowIndex){
        for(int i = 0; i < 10; ++i){
            int colPos = (i - 1) % 3;
            if(i == 0)
                colPos = 0;
            int rowPos = buttonMaxRowIndex - (i + 2) / 3;
            digitButtons[i] = new Button(Integer.toString(i));
            final int index = i;
            digitButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                @Override
                public void handle(ActionEvent event){
                    inputArea.appendText(digitButtons[index].getText());
                }
            });
            addButton(gridPane, digitButtons[i], rowPos, colPos);
        }
    }

    public void addBasicOperation(GridPane gridPane, int buttonMaxRowIndex){
        for(int i = 0; i < 8; ++i){
            addButton(gridPane, operatorButtons[i], 1 + i / 2, 3 + i % 2);
        }
        for(int i = 0; i < 5; ++i){
            addButton(gridPane, operatorButtons[i + 8], 0, i);
        }
        addButton(gridPane, operatorButtons[13], buttonMaxRowIndex, 1);
        addButton(gridPane, operatorButtons[14], buttonMaxRowIndex, 2);
        for(int i = 0; i < operatorButtons.length; ++i){
            switch(i){
                case 0:     //DEL
                operatorButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                    @Override
                    public void handle(ActionEvent event){
                        String textContent = inputArea.getText();
                        inputArea.setText(textContent.substring(0, textContent.length() - 1));
                    }
                });
                break;
                case 1:     //AC
                operatorButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                    @Override
                    public void handle(ActionEvent event){
                        inputArea.setText("");
                        outputArea.setText("");
                    }
                });
                break;
                case 12:   //M+
                operatorButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                    @Override
                    public void handle(ActionEvent event){
                        // need to be completed
                        regularM = regularRes;
                    }
                });
                break;
                default:
                final int index = i;
                operatorButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                    @Override
                    public void handle(ActionEvent event){
                        inputArea.appendText(operatorButtons[index].getText());
                    }
                });
            }
        }
    }

    public void addButton(GridPane gridPane, Button button, int rowPos, int colPos){
        button.setPadding(Insets.EMPTY);
        button.setPrefSize(60, 60);
        gridPane.setRowIndex(button, rowPos);
        gridPane.setColumnIndex(button, colPos);
        gridPane.getChildren().add(button);
    }

    /* Button Click Event */
    
}