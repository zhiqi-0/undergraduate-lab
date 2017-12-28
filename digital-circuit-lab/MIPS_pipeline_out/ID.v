`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:32:09 05/21/2017 
// Design Name: 
// Module Name:    ID 
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
module ID(
input clk,
input rst_n,
input [31:0] InstrD,
input RegWriteW,
input [4:0] RegWriteAddrW,
input [31:0] RegWriteDataW,
output [31:0] SignImmD,
output [31:0] RegD1D,
output [31:0] RegD2D,
output [4:0] ShamtD
// hazard signal

    );

SignExtend		u_SignExtend(		// SignImm
.Imm				(InstrD[15:0]),
.SignImm			(SignImmD)
);

RegFile			u_RegFile(
//input
.clk				(clk),
.rst_n			(rst_n),
.r1_addr			(InstrD[25:21]),
.r2_addr			(InstrD[20:16]),
.r3_addr			(RegWriteAddrW),
.r3_wr			(RegWriteW),
.din				(RegWriteDataW),
//output
.r1_dout			(RegD1D),
.r2_dout			(RegD2D)
);

assign ShamtD = InstrD[10:6];

endmodule
