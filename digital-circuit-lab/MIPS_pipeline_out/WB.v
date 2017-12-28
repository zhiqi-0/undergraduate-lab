`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    08:48:29 05/22/2017 
// Design Name: 
// Module Name:    WB 
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
module WB(
input rst_n,
input MemtoRegW,
input [31:0] DataMemDW,
input [31:0] ALUResW,
output reg [31:0] RegWriteDataW
    );

always@(*) begin
	if(~rst_n) begin
		RegWriteDataW <= 0;
	end
	else begin
		if(MemtoRegW == 1)
			RegWriteDataW <= DataMemDW;
		else
			RegWriteDataW <= ALUResW;
	end
end

endmodule
