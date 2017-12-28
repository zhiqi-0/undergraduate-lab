`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:12:50 05/20/2017 
// Design Name: 
// Module Name:    IDEX 
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
module IDEX(
input clk,
input rst_n,
input [31:0] PCPlus4D,
input [31:0] RegD1D,
input [31:0] RegD2D,
input [31:0] SignImmD,
input [4:0]  ShamtD,
input [4:0]  RegWriteAddrD1,
input [4:0]  RegWriteAddrD2,
output reg [31:0] RegD1E,
output reg [31:0] RegD2E1,
output reg [31:0] SignImmE,
output reg [4:0]  ShamtE,
output reg [4:0]  RegWriteAddrE1,
output reg [4:0]  RegWriteAddrE2,
// control signal
input RegWriteD,
input MemtoRegD,
input MemWriteD,
input ALUSrcAD,
input ALUSrcBD,
input RegDstD,
input [4:0] ALUopD,
input JumpD,
input JumpRD,
input BranchD,
input PCSrcD,
input JumpPredictD,
output reg RegWriteE,
output reg MemtoRegE,
output reg MemWriteE,
output reg ALUSrcAE,
output reg ALUSrcBE,
output reg RegDstE,
output reg [4:0] ALUopE,
output reg JumpE,
output reg JumpRE,
output reg BranchE,
output reg PCSrcE,
output reg JumpPredictE,
// hazard signal
input [4:0] RegRsD,
input [4:0] RegRtD,
//input Interlock,
output reg [4:0] RegRsE,
output reg [4:0] RegRtE
    );

always@(posedge clk or negedge rst_n) begin
	if(~rst_n) begin
		RegD1E <= 0; RegD2E1 <= 0; ShamtE <= 0; PCSrcE <= 0;
		SignImmE <= 0; RegWriteAddrE1 <= 0; RegWriteAddrE2 <= 0;
		RegWriteE <= 0; MemtoRegE <= 0; MemWriteE <= 0; JumpPredictE <= 0;
		RegDstE <= 0; ALUopE <= 0; ALUSrcAE <= 0; ALUSrcBE <= 0;
		RegRsE <= 0; RegRtE <= 0; JumpE <= 0; JumpRE <= 0; BranchE <= 0;
	end
	else begin
		RegD1E <= RegD1D;
		RegD2E1 <= RegD2D;
		SignImmE <= SignImmD;
		ShamtE <= ShamtD;
		RegWriteAddrE1 <= RegWriteAddrD1;
		RegWriteAddrE2 <= RegWriteAddrD2;
		// control signal output
		RegWriteE <= RegWriteD;
		MemtoRegE <= MemtoRegD;
		MemWriteE <= MemWriteD;
		ALUSrcAE <= ALUSrcAD;
		ALUSrcBE <= ALUSrcBD;
		RegDstE <= RegDstD;
		ALUopE <= ALUopD;
		RegRsE <= RegRsD;
		RegRtE <= RegRtD;
		JumpE <= JumpD;
		JumpRE <= JumpRD;
		BranchE <= BranchD;
		PCSrcE <= PCSrcD;
		JumpPredictE <= JumpPredictD;
	end
end

endmodule
