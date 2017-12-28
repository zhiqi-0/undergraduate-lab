`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:29:27 05/21/2017 
// Design Name: 
// Module Name:    IF 
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
module IF(
input clk,
input rst_n,
input PCSrcD,
input [31:0] PCBranch,
input [31:0] PCD,
output reg [31:0] PCPlus4F,
output [31:0] InstrF,
output reg [31:0] PC,
// hazard signals
output reg JumpPredictF,
input JumpPredictD,
input StallF
    );

reg [31:0] nPC;
reg [31:0] JPC;
reg [31:0] JPCStore;

InstrMem			u_InstrMem(
.a					(PC[8:2]),
.spo				(InstrF)
);

always@(posedge clk or negedge rst_n) begin
	if(~rst_n) begin
		PC <= 0;
	end
	else begin
		if(StallF)
			PC <= PC;
		else
			PC <= nPC;
	end
end

always@(*) begin
	if(~rst_n) begin
		PCPlus4F <= 0; 
	end
	else begin
		PCPlus4F <= PC + 32'd4;
	end
end

always@(*) begin
	if(~rst_n) begin
		nPC <= 0;
		JumpPredictF <= 0;
	end
	else if(PC == JPC && PC != 0) begin
		nPC <= JPCStore;
		JumpPredictF <= 1;
	end
	else if(StallF) begin
		nPC <= nPC;
		JumpPredictF <= JumpPredictF;
	end
	else begin
		if(~JumpPredictD && PCSrcD) begin
			nPC <= PCBranch;
			JumpPredictF <= 0;
		end
		else if(JumpPredictD && ~PCSrcD) begin
			nPC <= PCD + 32'd4;
			JumpPredictF <= 0;
		end
		else begin
			nPC <= PCPlus4F;
			JumpPredictF <= 0;
		end
	end
end

always@(negedge clk or negedge rst_n) begin
	if(~rst_n) begin
		JPCStore <= 0; JPC <= 0;
	end
	else begin
		if(~JumpPredictD && PCSrcD) begin
			JPCStore <= PCBranch;
			JPC <= PCD;
		end
		else begin
			JPCStore <= JPCStore;
			JPC <= JPC;
		end
	end
end

endmodule
