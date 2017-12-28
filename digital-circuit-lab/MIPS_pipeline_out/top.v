`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:16:30 05/20/2017 
// Design Name: 
// Module Name:    top 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module top(
input clk,
input rst_n,
input Hack,
input [5:0] DataMemAddr,
output [7:0] Led
    );

wire [31:0] InstrF;
wire [31:0] InstrD;
wire [31:0] PCF;
wire [31:0] PCD;
wire [31:0] PCPlus4F;
wire [31:0] PCPlus4D;
wire [31:0] PCBranch;
wire [31:0] RegD1D;
wire [31:0]	RegD2D;
wire [31:0] RegD1E;
wire [31:0] RegD2E1;
wire [31:0] RegD2E;
wire [31:0] RegD2M;
wire [4:0]  ShamtD;
wire [4:0]  ShamtE;
wire [31:0] SignImmD;
wire [31:0] SignImmE;
wire [4:0]  RegWriteAddrE1;
wire [4:0]  RegWriteAddrE2;
wire [4:0]  RegWriteAddrM;
wire [4:0]  RegWriteAddrW;
wire [4:0]  RegWriteAddrE;
wire [31:0] ALUResE;
wire [31:0] ALUResM;
wire [31:0] ALUResW;
wire [31:0] DataMemDM;
wire [31:0] DataMemDW;
wire [31:0] RegWriteDataW;
// control signal wires
wire RegWriteD;
wire RegWriteE;
wire RegWriteM;
wire MemtoRegD;
wire MemtoRegE;
wire MemtoRegM;
wire MemtoRegW;
wire MemWriteD;
wire MemWriteE;
wire MemWriteM;
wire ALUSrcAD;
wire ALUSrcAE;
wire ALUSrcBD;
wire ALUSrcBE;
wire RegDstD;
wire RegDstE;
wire [4:0] ALUopD;
wire [4:0] ALUopE;
wire PCSrcD;
wire PCSrcE;
wire BranchD;
wire BranchE;
wire JumpD;
wire JumpE;
wire JumpRD;
wire JumpRE;
wire JumpPredictF;
wire JumpPredictD;
wire JumpPredictE;
// hazard signals
wire [4:0]  RegRsE;
wire [4:0]  RegRtE;
wire StallF;
wire StallD;
wire [1:0] ForwardAE;
wire [1:0] ForwardBE;
wire FlushD;
wire [1:0] ForwardDs;
wire [1:0] ForwardDt;

IF					u_IF(
// input
.clk				(clk),
.rst_n			(rst_n),
.PCSrcD			(PCSrcD),
.PCBranch		(PCBranch),
.PCD				(PCD),
// output
.PCPlus4F		(PCPlus4F),
.InstrF			(InstrF),
.PC				(PCF),
// hazard signal
.JumpPredictF	(JumpPredictF),
.JumpPredictD	(JumpPredictD),
.StallF			(StallF)
);

IFID 				u_IFID(
// input
.clk				(clk),
.rst_n			(rst_n),
.PCPlus4F		(PCPlus4F),
.InstrF			(InstrF),
.JumpPredictF	(JumpPredictF),
.PCF				(PCF),
// output
.PCPlus4D		(PCPlus4D),
.InstrD			(InstrD),
.JumpPredictD	(JumpPredictD),
.PCD				(PCD),
// hazard signals
.StallD			(StallD)
);

ID					u_ID(
.clk				(clk),
.rst_n			(rst_n),
.InstrD			(InstrD),
.RegWriteW		(RegWriteW),
.RegWriteAddrW	(RegWriteAddrW),
.RegWriteDataW	(RegWriteDataW),
.SignImmD		(SignImmD),
.RegD1D			(RegD1D),
.RegD2D			(RegD2D),
.ShamtD			(ShamtD)
);

IDEX				u_IDEX(
// input
.clk					(clk),
.rst_n				(rst_n),
.PCPlus4D			(PCPlus4D),
.RegD1D				(RegD1D),
.RegD2D				(RegD2D),
.SignImmD			(SignImmD),
.ShamtD				(ShamtD),
.RegWriteAddrD1	(InstrD[20:16]),
.RegWriteAddrD2	(InstrD[15:11]),
// output
.RegD1E				(RegD1E),		
.RegD2E1				(RegD2E1),		
.SignImmE			(SignImmE),
.ShamtE				(ShamtE),
.RegWriteAddrE1	(RegWriteAddrE1),
.RegWriteAddrE2	(RegWriteAddrE2),
// control signal
.RegWriteD			(RegWriteD),
.MemtoRegD			(MemtoRegD),
.MemWriteD			(MemWriteD),
.ALUSrcAD			(ALUSrcAD),
.ALUSrcBD			(ALUSrcBD),
.RegDstD				(RegDstD),	
.ALUopD				(ALUopD),
.JumpD				(JumpD),
.JumpRD				(JumpRD),
.BranchD				(BranchD),
.PCSrcD				(PCSrcD),
.JumpPredictD		(JumpPredictD),
.RegWriteE			(RegWriteE),
.MemtoRegE			(MemtoRegE),
.MemWriteE			(MemWriteE),
.ALUSrcAE			(ALUSrcAE),
.ALUSrcBE			(ALUSrcBE),
.RegDstE				(RegDstE),
.ALUopE				(ALUopE),
.JumpE				(JumpE),
.JumpRE				(JumpRE),
.BranchE				(BranchE),
.PCSrcE				(PCSrcE),
.JumpPredictE		(JumpPredictE),
// hazard signal
.RegRsD				(InstrD[25:21]),
.RegRtD				(InstrD[20:16]),
.RegRsE				(RegRsE),
.RegRtE				(RegRtE)
);

EX						u_EX(
.rst_n				(rst_n),
.RegD1E				(RegD1E),
.RegD2E1				(RegD2E1),
.SignImmE			(SignImmE),
.ShamtE				(ShamtE),
.RegWriteAddrE1 	(RegWriteAddrE1),
.RegWriteAddrE2	(RegWriteAddrE2),
.ALUSrcAE			(ALUSrcAE),
.ALUSrcBE			(ALUSrcBE),
.ALUopE				(ALUopE),
.RegDstE				(RegDstE),	
.Zero					(Zero),
.ALUResE				(ALUResE),
.RegWriteAddrE		(RegWriteAddrE),
.RegD2E				(RegD2E),
// hazard signals
.ALUResM				(ALUResM),
.RegWriteDataW		(RegWriteDataW),
.DataMemDM			(DataMemDM),
.ForwardAE			(ForwardAE),
.ForwardBE			(ForwardBE)
);

EXMEM				u_EXMEM(
// input
.clk					(clk),
.rst_n				(rst_n),
.ALUResE				(ALUResE),
.RegD2E				(RegD2E),
.RegWriteAddrE		(RegWriteAddrE),
// output
.ALUResM				(ALUResM),
.RegD2M				(RegD2M),
.RegWriteAddrM		(RegWriteAddrM),
// control signal
.RegWriteE			(RegWriteE),
.MemtoRegE			(MemtoRegE),
.MemWriteE			(MemWriteE),
.RegWriteM			(RegWriteM),
.MemtoRegM			(MemtoRegM),
.MemWriteM			(MemWriteM)
);

MEM				u_MEM(
.clk				(clk),
.rst_n			(rst_n),
.ALUResM			(ALUResM),
.RegD2M			(RegD2M),
.MemWriteM		(MemWriteM),
.DataMemDM		(DataMemDM),
.DataMemAddr	(DataMemAddr),
.Hack				(Hack),
.Led				(Led)
);

MEMWB				u_MEMWB(
//input
.clk					(clk),
.rst_n				(rst_n),
.DataMemDM			(DataMemDM),		// Data Memory Read Data
.ALUResM				(ALUResM),
.RegWriteAddrM		(RegWriteAddrM),
//output
.DataMemDW			(DataMemDW),
.ALUResW				(ALUResW),
.RegWriteAddrW		(RegWriteAddrW),
// control signal
.MemtoRegM			(MemtoRegM),
.RegWriteM			(RegWriteM),
.MemtoRegW			(MemtoRegW),
.RegWriteW			(RegWriteW)
);

WB					u_WB(
.rst_n			(rst_n),
.MemtoRegW		(MemtoRegW),
.DataMemDW		(DataMemDW),
.ALUResW			(ALUResW),
.RegWriteDataW	(RegWriteDataW)
);

control			u_control(
//input
.clk				(clk),
.rst_n			(rst_n),
.op				(InstrD[31:26]),
.funct			(InstrD[5:0]),
.SignImmD		(SignImmD),
.Zero				(Zero),
.RegAddrD1		(InstrD[25:21]),
.RegAddrD2		(InstrD[20:16]),
.RegD1D			(RegD1D),
.RegD2D			(RegD2D),
.ALUResM			(ALUResM),
.RegWriteDataW	(RegWriteDataW),
.PCPlus4D		(PCPlus4D),
//output
.ALUopD			(ALUopD),
.ALUSrcAD		(ALUSrcAD),
.ALUSrcBD		(ALUSrcBD),
.RegDstD			(RegDstD),
.MemWriteD		(MemWriteD),
.MemtoRegD		(MemtoRegD),
.RegWriteD		(RegWriteD),
.JumpD			(JumpD),
.JumpRD			(JumpRD),
.BranchD			(BranchD),
.PCSrcD			(PCSrcD),
.PCBranch		(PCBranch),
// hazard signal
.ForwardDs		(ForwardDs),
.ForwardDt		(ForwardDt),
.FlushD			(FlushD),
.ALUResE			(ALUResE)
);

HazardSignal		u_HazardSignal(
.rst_n				(rst_n),
// control signals
.MemtoRegE			(MemtoRegE),
.MemtoRegW			(MemtoRegW),
.MemtoRegM			(MemtoRegM),
.RegWriteM			(RegWriteM),
.RegWriteD			(RegWriteD),
.RegWriteE			(RegWriteE),
.RegWriteW			(RegWriteW),
.RegDstD				(RegDstD),
.JumpE				(JumpE),
.JumpRE				(JumpRE),
.BranchE				(BranchE),
.PCSrcE				(PCSrcE),
.JumpPredictE		(JumpPredictE),
// Register Address
.RegRsE				(RegRsE),
.RegRtE				(RegRtE),
.RegRsD				(InstrD[25:21]),
.RegRtD				(InstrD[20:16]),
.RegWriteAddrE		(RegWriteAddrE),
.RegWriteAddrM		(RegWriteAddrM),
.RegWriteAddrW		(RegWriteAddrW),
// output signal
.StallF				(StallF),
.StallD				(StallD),
.ForwardAE			(ForwardAE),
.ForwardBE			(ForwardBE),
.FlushD				(FlushD),
.ForwardDs			(ForwardDs),
.ForwardDt			(ForwardDt)
);

endmodule
