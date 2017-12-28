`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:13:44 05/20/2017 
// Design Name: 
// Module Name:    MEMWB 
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
module MEMWB(
input clk,
input rst_n,
input [31:0] DataMemDM,
input [31:0] ALUResM,
input [4:0] RegWriteAddrM,
output reg [31:0] DataMemDW,
output reg [31:0] ALUResW,
output reg [4:0] RegWriteAddrW,
// control signals
input MemtoRegM,
input RegWriteM,
output reg MemtoRegW,
output reg RegWriteW
);

always@(posedge clk or negedge rst_n) begin
	if(~rst_n) begin
		DataMemDW <= 0; ALUResW <= 0; RegWriteAddrW <= 0; MemtoRegW <= 0;
	end
	else begin
		DataMemDW <= DataMemDM;
		ALUResW <= ALUResM;
		RegWriteAddrW <= RegWriteAddrM;
		// control signals
		MemtoRegW <= MemtoRegM;
		RegWriteW <= RegWriteM;
	end
end

endmodule
