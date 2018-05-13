import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.Map;
import java.util.HashMap;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.border.EtchedBorder;

/**
 * @author yanqing.qyq 2012-2015@USTC
 * 模板说明：该模板主要提供依赖Swing组件提供的JPanle，JFrame，JButton等提供的GUI。使用“监听器”模式监听各个Button的事件，从而根据具体事件执行不同方法。
 * Tomasulo算法核心需同学们自行完成，见说明（4）
 * 对于界面必须修改部分，见说明(1),(2),(3)
 *
 *  (1)说明：根据你的设计完善指令设置中的下拉框内容
 *	(2)说明：请根据你的设计指定各个面板（指令状态，保留站，Load部件，寄存器部件）的大小
 *	(3)说明：设置界面默认指令
 *	(4)说明： Tomasulo算法实现
 */

public class UI extends JFrame implements ActionListener{
	/*
	 * 界面上有六个面板：
	 * ins_set_panel : 指令设置
	 * EX_time_set_panel : 执行时间设置
	 * ins_state_panel : 指令状态
	 * RS_panel : 保留站状态
	 * Load_panel : Load部件
	 * Registers_state_panel : 寄存器状态
	 */
	private JPanel ins_set_panel,EX_time_set_panel,ins_state_panel,RS_panel,Load_panel,Registers_state_panel;

	/*
	 * 四个操作按钮：步进，进5步，重置，执行
	 */
	private JButton stepbut,step5but,resetbut,startbut;

	/*
	 * 指令选择框
	 */
	private JComboBox inst_typebox[]=new JComboBox[24];

	// control of tomasulo
	private Tomasulo toma = new Tomasulo();
	private Map<String, Integer> checkRName = new HashMap<>();

	/*
	 * 每个面板的名称
	 */
	private JLabel inst_typel, timel, tl1,tl2,tl3,tl4,resl,regl,ldl,insl,stepsl;
	private int time[]=new int[4];

	/*
	 * 部件执行时间的输入框
	 */
	private JTextField tt1,tt2,tt3,tt4;

	private int intv[][]=new int[6][4],cnow,inst_typenow=0;
	private int cal[][]={{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0}};
	private int ld[][]={{0,0},{0,0},{0,0}};
	private int ff[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	private int stepCount = 0;

	/*
	 * (1)说明：根据你的设计完善指令设置中的下拉框内容
	 * inst_type： 指令下拉框内容:"NOP","L.D","ADD.D","SUB.D","MULT.D","DIV.D"…………
	 * regist_table：       目的寄存器下拉框内容:"F0","F2","F4","F6","F8" …………
	 * rx：       源操作数寄存器内容:"R0","R1","R2","R3","R4","R5","R6","R7","R8","R9" …………
	 * ix：       立即数下拉框内容:"0","1","2","3","4","5","6","7","8","9" …………
	 */
	private String  inst_type[]={"NOP","L.D","ADD.D","SUB.D","MULT.D","DIV.D"},
					regist_table[]={"F0","F2","F4","F6","F8","F10","F12","F14","F16"
							,"F18","F20","F22","F24","F26","F28","F30","F32"},
					rx[]={"R0","R1","R2","R3","R4","R5","R6"},
					ix[]={"0","1","2","3","4","5","6","21"};

	/*
	 * (2)说明：请根据你的设计指定各个面板（指令状态，保留站，Load部件，寄存器部件）的大小
	 * 		指令状态 面板
	 * 		保留站 面板
	 * 		Load部件 面板
	 * 		寄存器 面板
	 * 					的大小
	 */
	private	String  my_inst_type[][]=new String[7][4], my_rs[][]=new String[6][8],
					my_load[][]=new String[4][4], my_regsters[][]=new String[3][17];
	private	JLabel  inst_typejl[][]=new JLabel[7][4], resjl[][]=new JLabel[6][8],
					ldjl[][]=new JLabel[4][4], regjl[][]=new JLabel[3][17];

//构造方法
	public UI(){
		super("Tomasulo Simulator");

		//设置布局
		Container cp=getContentPane();
		FlowLayout layout=new FlowLayout();
		cp.setLayout(layout);

		//指令设置。GridLayout(int 指令条数, int 操作码+操作数, int hgap, int vgap)
		inst_typel = new JLabel("指令设置");
		ins_set_panel = new JPanel(new GridLayout(6,4,0,0));
		ins_set_panel.setPreferredSize(new Dimension(350, 150));
		ins_set_panel.setBorder(new EtchedBorder(EtchedBorder.RAISED));

		//操作按钮:执行，重设，步进，步进5步
		timel = new JLabel("执行时间设置");
		EX_time_set_panel = new JPanel(new GridLayout(2,4,0,0));
		EX_time_set_panel.setPreferredSize(new Dimension(280, 80));
		EX_time_set_panel.setBorder(new EtchedBorder(EtchedBorder.RAISED));

		//指令状态
		insl = new JLabel("指令状态");
		ins_state_panel = new JPanel(new GridLayout(7,4,0,0));
		ins_state_panel.setPreferredSize(new Dimension(420, 175));
		ins_state_panel.setBorder(new EtchedBorder(EtchedBorder.RAISED));


		//寄存器状态
		regl = new JLabel("寄存器");
		Registers_state_panel = new JPanel(new GridLayout(3,17,0,0));
		Registers_state_panel.setPreferredSize(new Dimension(740, 75));
		Registers_state_panel.setBorder(new EtchedBorder(EtchedBorder.RAISED));
		//保留站
		resl = new JLabel("保留站");
		RS_panel = new JPanel(new GridLayout(6,7,0,0));
		RS_panel.setPreferredSize(new Dimension(420, 150));
		RS_panel.setBorder(new EtchedBorder(EtchedBorder.RAISED));
		//Load部件
		ldl = new JLabel("Load部件");
		Load_panel = new JPanel(new GridLayout(4,4,0,0));
		Load_panel.setPreferredSize(new Dimension(200, 100));
		Load_panel.setBorder(new EtchedBorder(EtchedBorder.RAISED));

		tl1 = new JLabel("Load");
		tl2 = new JLabel("加/减");
		tl3 = new JLabel("乘法");
		tl4 = new JLabel("除法");

//操作按钮:执行，重设，步进，步进5步
		stepsl = new JLabel();
		stepsl.setPreferredSize(new Dimension(200, 30));
		stepsl.setHorizontalAlignment(SwingConstants.CENTER);
		stepsl.setBorder(new EtchedBorder(EtchedBorder.RAISED));
		stepbut = new JButton("步进");
		stepbut.addActionListener(this);
		step5but = new JButton("步进5步");
		step5but.addActionListener(this);
		startbut = new JButton("执行");
		startbut.addActionListener(this);
		resetbut= new JButton("重设");
		resetbut.addActionListener(this);
		tt1 = new JTextField("2");
		tt2 = new JTextField("2");
		tt3 = new JTextField("10");
		tt4 = new JTextField("40");

//指令设置
		/*
		 * 设置指令选择框（操作码，操作数，立即数等）的default选择
		 */
		for (int i=0;i<2;i++)
			for (int j=0;j<4;j++){
				if (j==0){
					inst_typebox[i*4+j]=new JComboBox(inst_type);
				}
				else if (j==1){
					inst_typebox[i*4+j]=new JComboBox(regist_table);
				}
				else if (j==2){
					inst_typebox[i*4+j]=new JComboBox(ix);
				}
				else {
					inst_typebox[i*4+j]=new JComboBox(rx);
				}
				inst_typebox[i*4+j].addActionListener(this);
				ins_set_panel.add(inst_typebox[i*4+j]);
			}
		for (int i=2;i<6;i++)
			for (int j=0;j<4;j++){
				if (j==0){
					inst_typebox[i*4+j]=new JComboBox(inst_type);
				}
				else {
					inst_typebox[i*4+j]=new JComboBox(regist_table);
				}
				inst_typebox[i*4+j].addActionListener(this);
				ins_set_panel.add(inst_typebox[i*4+j]);
			}
		/*
		 * (3)说明：设置界面默认指令，根据你设计的指令，操作数等的选择范围进行设置。
		 * 默认6条指令。待修改
		 */
//		inst_typebox[0].setSelectedIndex(1);
//		inst_typebox[1].setSelectedIndex(3);
//		inst_typebox[2].setSelectedIndex(21);
//		inst_typebox[3].setSelectedIndex(2);
//
//		inst_typebox[4].setSelectedIndex(1);
//		inst_typebox[5].setSelectedIndex(1);
//		inst_typebox[6].setSelectedIndex(20);
//		inst_typebox[7].setSelectedIndex(3);
//
//		inst_typebox[8].setSelectedIndex(4);
//		inst_typebox[9].setSelectedIndex(0);
//		inst_typebox[10].setSelectedIndex(1);
//		inst_typebox[11].setSelectedIndex(2);
//
//		inst_typebox[12].setSelectedIndex(3);
//		inst_typebox[13].setSelectedIndex(4);
//		inst_typebox[14].setSelectedIndex(3);
//		inst_typebox[15].setSelectedIndex(1);
//
//		inst_typebox[16].setSelectedIndex(5);
//		inst_typebox[17].setSelectedIndex(5);
//		inst_typebox[18].setSelectedIndex(0);
//		inst_typebox[19].setSelectedIndex(3);
//
//		inst_typebox[20].setSelectedIndex(2);
//		inst_typebox[21].setSelectedIndex(3);
//		inst_typebox[22].setSelectedIndex(4);
//		inst_typebox[23].setSelectedIndex(1);

//执行时间设置
		EX_time_set_panel.add(tl1);
		EX_time_set_panel.add(tt1);
		EX_time_set_panel.add(tl2);
		EX_time_set_panel.add(tt2);
		EX_time_set_panel.add(tl3);
		EX_time_set_panel.add(tt3);
		EX_time_set_panel.add(tl4);
		EX_time_set_panel.add(tt4);

//指令状态设置
		for (int i=0;i<7;i++)
		{
			for (int j=0;j<4;j++){
				inst_typejl[i][j]=new JLabel(my_inst_type[i][j]);
				inst_typejl[i][j].setBorder(new EtchedBorder(EtchedBorder.RAISED));
				ins_state_panel.add(inst_typejl[i][j]);
			}
		}
//保留站设置
		for (int i=0;i<6;i++)
		{
			for (int j=0;j<8;j++){
				resjl[i][j]=new JLabel(my_rs[i][j]);
				resjl[i][j].setBorder(new EtchedBorder(EtchedBorder.RAISED));
				RS_panel.add(resjl[i][j]);
			}
		}
//Load部件设置
		for (int i=0;i<4;i++)
		{
			for (int j=0;j<4;j++){
				ldjl[i][j]=new JLabel(my_load[i][j]);
				ldjl[i][j].setBorder(new EtchedBorder(EtchedBorder.RAISED));
				Load_panel.add(ldjl[i][j]);
			}
		}
//寄存器设置
		for (int i=0;i<3;i++)
		{
			for (int j=0;j<17;j++){
				regjl[i][j]=new JLabel(my_regsters[i][j]);
				regjl[i][j].setBorder(new EtchedBorder(EtchedBorder.RAISED));
				Registers_state_panel.add(regjl[i][j]);
			}
		}

//向容器添加以上部件
		cp.add(inst_typel);
		cp.add(ins_set_panel);
		cp.add(timel);
		cp.add(EX_time_set_panel);

		cp.add(startbut);
		cp.add(resetbut);
		cp.add(stepbut);
		cp.add(step5but);

		cp.add(Load_panel);
		cp.add(ldl);
		cp.add(RS_panel);
		cp.add(resl);
		cp.add(stepsl);
		cp.add(Registers_state_panel);
		cp.add(regl);
		cp.add(ins_state_panel);
		cp.add(insl);

		stepbut.setEnabled(false);
		step5but.setEnabled(false);
		ins_state_panel.setVisible(false);
		insl.setVisible(false);
		RS_panel.setVisible(false);
		ldl.setVisible(false);
		Load_panel.setVisible(false);
		resl.setVisible(false);
		stepsl.setVisible(false);
		Registers_state_panel.setVisible(false);
		regl.setVisible(false);
		setSize(820,620);
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}

/*
 * 点击”执行“按钮后，根据选择的指令，初始化其他几个面板
 */
	public void init(){
		// get value
		for (int i=0;i<6;i++){
			intv[i][0]=inst_typebox[i*4].getSelectedIndex();
			if (intv[i][0]!=0){
				intv[i][1]=2*inst_typebox[i*4+1].getSelectedIndex();
				if (intv[i][0]==1){
					intv[i][2]=inst_typebox[i*4+2].getSelectedIndex();
					intv[i][3]=inst_typebox[i*4+3].getSelectedIndex();
				}
				else {
					intv[i][2]=2*inst_typebox[i*4+2].getSelectedIndex();
					intv[i][3]=2*inst_typebox[i*4+3].getSelectedIndex();
				}
			}
		}
		time[0]=Integer.parseInt(tt1.getText());
		time[1]=Integer.parseInt(tt2.getText());
		time[2]=Integer.parseInt(tt3.getText());
		time[3]=Integer.parseInt(tt4.getText());
		//System.out.println(time[0]);
		// set 0
		my_inst_type[0][0]="指令";
		my_inst_type[0][1]="流出";
		my_inst_type[0][2]="执行";
		my_inst_type[0][3]="写回";


		my_load[0][0]="名称";
		my_load[0][1]="Busy";
		my_load[0][2]="地址";
		my_load[0][3]="值";
		my_load[1][0]="Load0";
		my_load[2][0]="Load1";
		my_load[3][0]="Load2";
		my_load[1][1]="no";
		my_load[2][1]="no";
		my_load[3][1]="no";

		my_rs[0][0]="Time";
		my_rs[0][1]="名称";
		my_rs[0][2]="Busy";
		my_rs[0][3]="Op";
		my_rs[0][4]="Vj";
		my_rs[0][5]="Vk";
		my_rs[0][6]="Qj";
		my_rs[0][7]="Qk";
		my_rs[1][1]="Add0";
		my_rs[2][1]="Add1";
		my_rs[3][1]="Add2";
		my_rs[4][1]="Mult0";
		my_rs[5][1]="Mult1";
		my_rs[1][2]="no";
		my_rs[2][2]="no";
		my_rs[3][2]="no";
		my_rs[4][2]="no";
		my_rs[5][2]="no";

		my_regsters[0][0]="字段";
		for (int i=1;i<17;i++){
			//System.out.print(i+" "+regist_table[i-1];
			my_regsters[0][i]=regist_table[i-1];

		}
		my_regsters[1][0]="状态";
		my_regsters[2][0]="值";

		for (int i=1;i<7;i++)
		for (int j=0;j<4;j++){
			if (j==0){
				int temp=i-1;
				String disp;
				disp = inst_type[inst_typebox[temp*4].getSelectedIndex()]+" ";
				if (inst_typebox[temp*4].getSelectedIndex()==0) disp=disp;
				else if (inst_typebox[temp*4].getSelectedIndex()==1){
					disp=disp+regist_table[inst_typebox[temp*4+1].getSelectedIndex()]+','+ix[inst_typebox[temp*4+2].getSelectedIndex()]+'('+rx[inst_typebox[temp*4+3].getSelectedIndex()]+')';
				}
				else {
					disp=disp+regist_table[inst_typebox[temp*4+1].getSelectedIndex()]+','+regist_table[inst_typebox[temp*4+2].getSelectedIndex()]+','+regist_table[inst_typebox[temp*4+3].getSelectedIndex()];
				}
				my_inst_type[i][j]=disp;
			}
			else my_inst_type[i][j]="";
		}
		for (int i=1;i<6;i++)
		for (int j=0;j<8;j++)if (j!=1&&j!=2){
			my_rs[i][j]="";
		}
		for (int i=1;i<4;i++)
		for (int j=2;j<4;j++){
			my_load[i][j]="";
		}
		for (int i=1;i<3;i++)
		for (int j=1;j<17;j++){
			my_regsters[i][j]="";
		}
		inst_typenow=0;
		for (int i=0;i<5;i++){
			for (int j=1;j<3;j++) cal[i][j]=0;
			cal[i][0]=-1;
		}
		for (int i=0;i<3;i++)
			for (int j=0;j<2;j++) ld[i][j]=0;
		for (int i=0;i<17;i++) ff[i]=0;
	}

/*
 * 点击操作按钮后，用于显示结果
 */
	public void display(){
		for (int i=0;i<7;i++)
			for (int j=0;j<4;j++){
				inst_typejl[i][j].setText(my_inst_type[i][j]);
			}
		for (int i=0;i<6;i++)
			for (int j=0;j<8;j++){
				resjl[i][j].setText(my_rs[i][j]);
			}
		for (int i=0;i<4;i++)
			for (int j=0;j<4;j++){
				ldjl[i][j].setText(my_load[i][j]);
			}
		for (int i=0;i<3;i++)
			for (int j=0;j<17;j++){
				regjl[i][j].setText(my_regsters[i][j]);
			}
		stepsl.setText("当前周期："+String.valueOf(cnow-1));
	}

	public void actionPerformed(ActionEvent e){
//点击“执行”按钮的监听器
		if (e.getSource()==startbut) {
			for (int i=0;i<24;i++) inst_typebox[i].setEnabled(false);
			tt1.setEnabled(false);tt2.setEnabled(false);
			tt3.setEnabled(false);tt4.setEnabled(false);
			stepbut.setEnabled(true);
			step5but.setEnabled(true);
			startbut.setEnabled(false);
			//根据指令设置的指令初始化其他的面板
			init();
			cnow=1;
			//展示其他面板
			display();
			ins_state_panel.setVisible(true);
			RS_panel.setVisible(true);
			Load_panel.setVisible(true);
			Registers_state_panel.setVisible(true);
			insl.setVisible(true);
			ldl.setVisible(true);
			resl.setVisible(true);
			stepsl.setVisible(true);
			regl.setVisible(true);


			// set exe time
			int load = Integer.parseInt(tt1.getText()) - 1;
			int add = Integer.parseInt(tt2.getText()) - 1;
			int mul = Integer.parseInt(tt3.getText()) - 1;
			int div = Integer.parseInt(tt4.getText()) - 1;
			toma.setLatency(add, load, mul, div);
			// debug
			System.out.println("Initialize Toma with latency:");
			System.out.println("add: " + Integer.toString(add + 1) + " load: " + Integer.toString(load + 1)
							   + " mul " + Integer.toString(mul + 1) + " div: " + Integer.toString(div + 1));
			// init tomasulo
			String command = "";
			for(int i = 0; i < 4; ++i){
				command = command + inst_typebox[i].getSelectedItem();
				if(command.equals("NOP")) break;
				command = command + " ";
			}
			stepCount = 1;
			toma.init(command);
		}
//点击“重置”按钮的监听器
		if (e.getSource()==resetbut) {
			for (int i=0;i<24;i++) inst_typebox[i].setEnabled(true);
			tt1.setEnabled(true);tt2.setEnabled(true);
			tt3.setEnabled(true);tt4.setEnabled(true);
			stepbut.setEnabled(false);
			step5but.setEnabled(false);
			startbut.setEnabled(true);
			ins_state_panel.setVisible(false);
			insl.setVisible(false);
			RS_panel.setVisible(false);
			ldl.setVisible(false);
			Load_panel.setVisible(false);
			resl.setVisible(false);
			stepsl.setVisible(false);
			Registers_state_panel.setVisible(false);
			regl.setVisible(false);
			toma.reset();
		}
//点击“步进”按钮的监听器
		if (e.getSource()==stepbut) {
			core();
			cnow++;
			display();
		}
//点击“进5步”按钮的监听器
		if (e.getSource()==step5but) {
			for (int i=0;i<5;i++){
				core();
				cnow++;
			}
			display();
		}

		for (int i=0;i<24;i=i+4)
		{
			if (e.getSource()==inst_typebox[i]) {
				if (inst_typebox[i].getSelectedIndex()==1){
					inst_typebox[i+2].removeAllItems();
					for (int j=0;j<ix.length;j++) inst_typebox[i+2].addItem(ix[j]);
					inst_typebox[i+3].removeAllItems();
					for (int j=0;j<rx.length;j++) inst_typebox[i+3].addItem(rx[j]);
				}
				else {
					inst_typebox[i+2].removeAllItems();
					for (int j=0;j<regist_table.length;j++) inst_typebox[i+2].addItem(regist_table[j]);
					inst_typebox[i+3].removeAllItems();
					for (int j=0;j<regist_table.length;j++) inst_typebox[i+3].addItem(regist_table[j]);
				}
			}
		}
	}
/*
 * This is for step exe
 */
	public void core()
	{
		// get command
		String command = "";
		for(int i = 0; i < 4; ++i){
			if(stepCount > 5) break;
			command = command + inst_typebox[stepCount * 4 + i].getSelectedItem();
			if(command.equals("NOP")){
				command = "";
				break;
			}
			command = command + " ";
		}
		Map<String, ArrayList<String> > event = toma.step(command);
		// get WB result
		ArrayList<String> wbEvent = event.get("WB");
		for(int i = 0; i < wbEvent.size(); ++i){
			int instrIndex = checkRName.get(wbEvent.get(i));
			my_inst_type[instrIndex + 1][3] = Integer.toString(cnow);
			System.out.println("[UI WB] move index: " + wbEvent.get(i));
			checkRName.remove(wbEvent.get(i));
		}
		// get Ex result
		ArrayList<String> exEvent = event.get("EX");
		for(int i = 0; i < exEvent.size(); ++i){
			System.out.println("[UI EX] EX index: " + exEvent.get(i));
			int instrIndex = checkRName.get(exEvent.get(i));
			my_inst_type[instrIndex + 1][2] = Integer.toString(cnow);
		}
		// get ID result
		ArrayList<String> idEvent = event.get("ID");
		if(idEvent.size() != 0){
			System.out.println("[UI ID] Issue index: " + idEvent.get(0));
			checkRName.put(idEvent.get(0), stepCount - 1);
			my_inst_type[stepCount][1] = Integer.toString(cnow);
			stepCount++;
		}
		// set Reservation
		ArrayList<String> rsState = toma.getRS();
		for(int i = 0; i < 5; ++i){
			String[] parser = rsState.get(i).split(":");
			for(int j = 0; j < 6; ++j){
				my_rs[i + 1][j + 2] = parser[j];
			}
		}
		// set buffer
		String[] loadState = toma.getLoadBuffer();
		for(int i = 0; i < 3; ++i){
			String[] parser = loadState[i].split(":");
			for(int j = 0; j < 2; ++j){
				my_load[i + 1][j + 1] = parser[j]; 
			}
		}
		// set reg state
		String[] regState = toma.getRegState();
		String[] regQi = regState[0].split(":");
		String[] regVal = regState[1].split(":");
		for(int i = 0; i < 16; ++i){
			my_regsters[1][i + 1] = regQi[i];
			my_regsters[2][i + 1] = regVal[i];
		}
		System.out.println();
	}

	public static void main(String[] args) {
		new UI();
	}

}
