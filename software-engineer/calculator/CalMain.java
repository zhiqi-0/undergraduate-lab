/*
 * File Information: Main GUI for Calculator
 */
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;
import javafx.scene.layout.HBox;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.RowConstraints;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TabPane;
import javafx.scene.control.Tab;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.stage.WindowEvent;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;

public class CalMain extends Application{

    enum Mode {Regular, Matrix, Function;}

    protected Mode currentMode = Mode.Regular;
    protected final RegularCal rCal = new RegularCal();
    protected final MatrixCal mCal = new MatrixCal();

    // basic items
    protected final TextArea inputArea = new TextArea();            // input area
    protected final TextArea outputArea = new TextArea();              // result area
    protected final Button[] digitButtons = new Button[10];         // digit buttion 0-9
    protected final Button[] opButtons = new Button[]{        // 14 operators
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
    // subwindows define
    protected final Stage modeSubStage = new Stage();
    protected final Stage rSubStage = new Stage();
    protected final Stage mSubStage = new Stage();
    protected final Stage fSubStage = new Stage();
    protected boolean[] subStageState = {false, false, false, false};
    private int unMatchParen = 0;
    private boolean cleanFlag = false;

    public static void main(String[] args){
        launch(args);
    }
    
    @Override
    public void start(Stage primaryStage){
        // basic info for gui design
        final int defaultLen = 300; //300
        final int defaultWid = 555;
        final int buttonRow = 5;
        final int buttonCol = 5;

        VBox vbox = new VBox();
        /* define input text */
        inputArea.setPrefSize(defaultLen, 120);
        inputArea.setPromptText("put your numbers here...");
        vbox.getChildren().add(inputArea);
        /* define output label */
        outputArea.setPrefSize(defaultLen, 120);
        outputArea.setEditable(false);
        vbox.getChildren().add(outputArea);
        /* define basic number layout */
        GridPane buttonGrid = new GridPane();
        buttonGrid.setPrefSize(300, 310);
        buttonGrid.setPadding(Insets.EMPTY);
        setGridPane(buttonGrid, buttonCol, buttonRow, 60, 60);
        // add left extend button
        Button leftExtendButton = new Button("<");
        leftExtendButton.setOnAction(new EventHandler<ActionEvent>(){
            @Override
            public void handle(ActionEvent event){
                switch(currentMode){
                    case Regular:
                    if(subStageState[0] == false){
                        subStageState[0] = true;
                        rSubStage.setX(primaryStage.getX() - 120);
                        rSubStage.setY(primaryStage.getY() + 260);
                        rSubStage.show();
                    }
                    else{
                        subStageState[0] = false;
                        rSubStage.close();
                    }
                    break;
                    case Matrix:
                    rSubStage.close(); fSubStage.close();
                    if(subStageState[1] == false){
                        subStageState[1] = true;
                        mSubStage.setX(primaryStage.getX() - 120);
                        mSubStage.setY(primaryStage.getY() + 260);
                        mSubStage.show();
                    }
                    else{
                        subStageState[1] = false;
                        mSubStage.close();
                    }
                    break;
                    case Function:
                    break;
                }
            }
        });
        // add select mode button
        Button modeButton = new Button("Mode");
        modeButton.setOnAction(new EventHandler<ActionEvent>(){
            @Override
            public void handle(ActionEvent event){
                if(!subStageState[3]){
                    subStageState[3] = true;
                    modeSubStage.show();
                }
                else{
                    subStageState[3] = false;
                    modeSubStage.close();
                }
            }
        });
        // add useless button
        Button rightExtendButton = new Button(">");
        leftExtendButton.setPrefSize(60, 10);
        leftExtendButton.setPadding(Insets.EMPTY);
        modeButton.setPadding(Insets.EMPTY);
        modeButton.setPrefSize(60 ,10);
        rightExtendButton.setPrefSize(100, 10);
        rightExtendButton.setPadding(Insets.EMPTY);
        setGridPane(buttonGrid, 5, 1, 60, 10);
        GridPane.setRowIndex(leftExtendButton, 5); GridPane.setColumnIndex(leftExtendButton, 0);
        GridPane.setRowIndex(modeButton, 5); GridPane.setColumnIndex(modeButton, 2);
        GridPane.setRowIndex(rightExtendButton, 5); GridPane.setColumnIndex(rightExtendButton, 4);
        buttonGrid.getChildren().addAll(leftExtendButton, rightExtendButton, modeButton);
        // add digit button and operation button
        addDigitButton(buttonGrid, buttonRow - 1);
        addBasicOperation(buttonGrid, buttonRow - 1);
        vbox.getChildren().add(buttonGrid);
        /* boot all SubPanes */
        selectStage(primaryStage);
        regularMode();
        matrixMode();
        functionMode();
        /* create and show the main scene */
        Scene scene = new Scene(vbox, defaultLen, defaultWid, Color.WHITE);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Calculator - Regular");
        primaryStage.setResizable(false);
        // when close main GUI, close all sub windows
        primaryStage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            @Override
            public void handle(WindowEvent arg0){
                modeSubStage.close();
                rSubStage.close();
                mSubStage.close();
                fSubStage.close();
            }
        });
        primaryStage.show();
    }

    protected static void addButton(GridPane gridPane, Button button, int rowPos, int colPos){
        button.setPadding(Insets.EMPTY);
        button.setPrefSize(60, 60);
        gridPane.setRowIndex(button, rowPos);
        gridPane.setColumnIndex(button, colPos);
        gridPane.getChildren().add(button);
    }

    private void selectStage(Stage primaryStage){
        HBox hbox = new HBox();
        Button rButton = new Button("Regular");
        Button mButton = new Button("Matrix");
        Button fButton = new Button("Function");
        rButton.setPrefSize(90, 30);
        mButton.setPrefSize(90, 30);
        fButton.setPrefSize(90, 30);
        hbox.getChildren().addAll(rButton, mButton, fButton);
        rButton.setOnAction(new EventHandler<ActionEvent>(){
            @Override
            public void handle(ActionEvent event){
                currentMode = Mode.Regular;
                mSubStage.close();
                fSubStage.close();
                modeSubStage.close();
                primaryStage.setTitle("Calculator - Regular");
            }
        });
        mButton.setOnAction(new EventHandler<ActionEvent>(){
            @Override
            public void handle(ActionEvent event){
                currentMode = Mode.Matrix;
                rSubStage.close();
                fSubStage.close();
                modeSubStage.close();
                primaryStage.setTitle("Calculator - Matrix");
            }
        });
        fButton.setOnAction(new EventHandler<ActionEvent>(){
            @Override
            public void handle(ActionEvent event){
                currentMode = Mode.Function;
                rSubStage.close();
                mSubStage.close();
                modeSubStage.close();
                primaryStage.setTitle("Calculator - Funtion");
            }
        });
        Scene scene = new Scene(hbox, 270, 30);
        modeSubStage.setScene(scene);
        modeSubStage.initStyle(StageStyle.TRANSPARENT);
    }

    public void regularMode(){
        // 5*2 operations
        final int columnNum = 2;
        final int rowNum = 5;
        Button[] opButtons = new Button[]{
            new Button("^"), new Button("sqrt"),
            new Button("exp"), new Button("ln"),
            new Button("log2"),new Button("!"),
            new Button("cos"), new Button("sin"),
            new Button("arccos"), new Button("arcsin")
        };
        GridPane buttonGrid = new GridPane();
        buttonGrid.setPadding(Insets.EMPTY);
        setGridPane(buttonGrid, columnNum, rowNum, 60, 60);
        for(int i = 0; i < opButtons.length; ++i){
            addButton(buttonGrid, opButtons[i], i / 2, i % 2);
        }
        Scene scene = new Scene(buttonGrid, columnNum * 60, rowNum * 60);
        rSubStage.setScene(scene);
        rSubStage.initStyle(StageStyle.TRANSPARENT);

        /* add button function */
        for(int i = 0; i < opButtons.length; ++i){
            final int index = i;
            opButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                @Override
                public void handle(ActionEvent event){
                    setClean();
                    inputArea.appendText(opButtons[index].getText());
                }
            });
        }
    }

    public void matrixMode(){
        // 5*2 operations
        final int columnNum = 2;
        final int rowNum = 5;
        Button[] opButtons = new Button[]{
            new Button("A+"), new Button("B+"),
            new Button("A"), new Button("B"),
            new Button("[]"), new Button("det"),
            new Button("inv"), new Button("rank"),
            new Button("T"), new Button("solve")
        };
        GridPane buttonGrid = new GridPane();
        buttonGrid.setPadding(Insets.EMPTY);
        setGridPane(buttonGrid, columnNum, rowNum, 60, 60);
        for(int i = 0; i < opButtons.length; ++i){
            addButton(buttonGrid, opButtons[i], i / 2, i % 2);
        }
        Scene scene = new Scene(buttonGrid, columnNum * 60, rowNum * 60);
        mSubStage.setScene(scene);
        mSubStage.initStyle(StageStyle.TRANSPARENT);

        /* add button function */
        opButtons[0].setOnAction(new EventHandler<ActionEvent>(){
            @Override                           // A+
            public void handle(ActionEvent event){
                mCal.setMatrix("A", inputArea.getText());
                cleanFlag = true;
            }
        });
        opButtons[1].setOnAction(new EventHandler<ActionEvent>(){
            @Override                           // B+
            public void handle(ActionEvent event){
                mCal.setMatrix("B", inputArea.getText());
                cleanFlag = true;
            }
        });
        for(int i = 0; i < 8; ++i){
            final int index = i + 2;
            opButtons[index].setOnAction(new EventHandler<ActionEvent>(){
                @Override
                public void handle(ActionEvent event){
                    setClean();
                    inputArea.appendText(opButtons[index].getText());
                }
            });
        }
        opButtons[8].setOnAction(new EventHandler<ActionEvent>(){
            @Override                           // T
            public void handle(ActionEvent event){
                setClean();
                inputArea.appendText("transpose");
            }
        });
    }

    public void functionMode(){}

    protected void setGridPane(GridPane gridPane, int columnNum, int rowNum,
                            int columnWidth, int rowHeiht){
        ColumnConstraints[] columnSet = new ColumnConstraints[columnNum];
        for(int i = 0; i < columnNum; ++i){
            columnSet[i] = new ColumnConstraints(columnWidth);
            gridPane.getColumnConstraints().add(columnSet[i]);
        }
        RowConstraints[] rowSet = new RowConstraints[rowNum];
        for(int i = 0; i < rowNum; ++i){
            rowSet[i] = new RowConstraints(rowHeiht);
            gridPane.getRowConstraints().add(rowSet[i]);
        }    
    }

    private void setClean(){
        if(cleanFlag){
            inputArea.setText("");
            outputArea.setText("");
            unMatchParen = 0;
            cleanFlag = false;
        }
    }

    protected void addDigitButton(GridPane gridPane, int buttonMaxRowIndex){
        for(int i = 0; i < 10; ++i){
            int colPos = (i - 1) % 3;
            if(i == 0)
                colPos = 0;
            int rowPos = buttonMaxRowIndex - (i + 2) / 3;
            digitButtons[i] = new Button(Integer.toString(i));
            final int index = i;
            // add click event
            digitButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                @Override
                public void handle(ActionEvent event){
                    inputArea.appendText(digitButtons[index].getText());
                    if(unMatchParen == 0 && currentMode == Mode.Regular){
                        String calExp = inputArea.getText();
                        double res = rCal.rExpValue(calExp);
                        outputArea.setText(Double.toString(res));
                    }
                }
            });
            addButton(gridPane, digitButtons[i], rowPos, colPos);
        }
    }

    public void addBasicOperation(GridPane gridPane, int buttonMaxRowIndex){
        for(int i = 0; i < 8; ++i){
            addButton(gridPane, opButtons[i], 1 + i / 2, 3 + i % 2);
        }
        for(int i = 0; i < 5; ++i){
            addButton(gridPane, opButtons[i + 8], 0, i);
        }
        addButton(gridPane, opButtons[13], buttonMaxRowIndex, 1);
        addButton(gridPane, opButtons[14], buttonMaxRowIndex, 2);
        for(int i = 0; i < opButtons.length; ++i){
            switch(i){
                case 0:     //DEL
                opButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                    @Override
                    public void handle(ActionEvent event){
                        String textContent = inputArea.getText();
                        inputArea.setText(textContent.substring(0, textContent.length() - 1));
                    }
                });
                break;
                case 1:     //AC
                opButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                    @Override
                    public void handle(ActionEvent event){
                        inputArea.setText("");
                        outputArea.setText("");
                    }
                });
                break;
                case 2:     //x
                opButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                    @Override
                    public void handle(ActionEvent event){
                        inputArea.appendText("*");
                    }
                });
                break;
                case 7:     //=
                opButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                    @Override
                    public void handle(ActionEvent event){
                        String calExp = inputArea.getText();
                        if(currentMode == Mode.Regular){
                            double res = rCal.rExpValue(calExp);
                            outputArea.setText(Double.toString(res));
                        }
                        else if(currentMode == Mode.Matrix){
                            outputArea.setText(mCal.calMatrix(calExp));
                        }
                        cleanFlag = true;
                    }
                });
                break;
                case 9:     //(
                final int lParenIndex = i;
                opButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                    @Override
                    public void handle(ActionEvent event){
                        setClean();
                        inputArea.appendText(opButtons[lParenIndex].getText());
                        unMatchParen++;
                    }
                });
                break;
                case 10:     //)
                final int rParenIndex = i;
                opButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                    @Override
                    public void handle(ActionEvent event){
                        inputArea.appendText(opButtons[rParenIndex].getText());
                        unMatchParen--;
                        if(unMatchParen == 0 && currentMode == Mode.Regular){
                            String calExp = inputArea.getText();
                            double res = rCal.rExpValue(calExp);
                            outputArea.setText(Double.toString(res));
                        }
                    }
                });
                break;
                case 12:   //M+
                opButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                    @Override
                    public void handle(ActionEvent event){
                        String calExp = inputArea.getText();
                        double res = rCal.rExpValue(calExp);
                        outputArea.setText(Double.toString(res));
                        rCal.setM(res);
                    }
                });
                break;
                case 14:    //EE
                opButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                    @Override
                    public void handle(ActionEvent event){
                        inputArea.appendText("10^");
                    }
                });
                break;
                default:
                final int index = i;
                opButtons[i].setOnAction(new EventHandler<ActionEvent>(){
                    @Override
                    public void handle(ActionEvent event){
                        inputArea.appendText(opButtons[index].getText());
                    }
                });
            }
        }
    }
}