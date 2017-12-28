`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:25:06 05/20/2017 
// Design Name: 
// Module Name:    EXMEM 
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
module EXMEM(
input clk,
input rst_n,
input [31:0] ALUResE,
input [31:0] RegD2E,
input [4:0] RegWriteAddrE,
output reg [31:0] ALUResM,
output reg [31:0] RegD2M,
output reg [4:0] RegWriteAddrM,
// control signal
input RegWriteE,
input MemtoRegE,
input MemWriteE,
output reg RegWriteM,
output reg MemtoRegM,
output reg MemWriteM
    );

always@(posedge clk or negedge rst_n) begin
	if(~rst_n) begin
		ALUResM <= 0; RegD2M <= 0; RegWriteAddrM <= 0;
		RegWriteM <= 0; MemtoRegM <= 0; MemWriteM <= 0;
	end
	else begin
		ALUResM <= ALUResE;
		RegD2M <= RegD2E;
		RegWriteAddrM <= RegWriteAddrE;
		// control signal
		RegWriteM <= RegWriteE;
		MemtoRegM <= MemtoRegE;
		MemWriteM <= MemWriteE;
	end
end	

endmodule
