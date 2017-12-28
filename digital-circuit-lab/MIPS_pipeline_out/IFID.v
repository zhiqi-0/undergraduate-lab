`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:12:38 05/20/2017 
// Design Name: 
// Module Name:    IFID 
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
module IFID(
input clk,
input rst_n,
input [31:0] InstrF,
input [31:0] PCPlus4F,
input JumpPredictF,
input [31:0] PCF,
output reg [31:0] InstrD,
output reg [31:0] PCPlus4D,
output reg JumpPredictD,
output reg [31:0] PCD,
// hazard signal
input StallD
    );

always@(posedge clk or negedge rst_n) begin
	if(~rst_n) begin
		InstrD <= 0; PCPlus4D <= 0; JumpPredictD <= 0; PCD <= 0;
	end
	else begin
		if(StallD) begin
			InstrD <= InstrD;
			PCPlus4D <= PCPlus4D;
			JumpPredictD <= JumpPredictD;
			PCD <= PCD;
		end
		else begin
			InstrD <= InstrF;
			PCPlus4D <= PCPlus4F;
			JumpPredictD <= JumpPredictF;
			PCD <= PCF;
		end
	end
end

endmodule
