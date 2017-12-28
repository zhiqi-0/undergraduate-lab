`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:09:00 05/21/2017 
// Design Name: 
// Module Name:    HazardSignal 
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
module HazardSignal(
input rst_n,
// control signals
input BranchE,
input MemtoRegE,
input MemtoRegM,
input MemtoRegW,
input RegWriteM,
input RegWriteD,
input RegWriteE,
input RegWriteW,
input RegDstD,
input JumpE,
input JumpRE,
input PCSrcE,
input JumpPredictE,
// Register Address
input [4:0] RegRsE,
input [4:0] RegRtE,
input [4:0] RegRsD,
input [4:0] RegRtD,
input [4:0] RegWriteAddrE,
input [4:0] RegWriteAddrM,
input [4:0] RegWriteAddrW,
// output signal
output reg StallF,
output reg StallD,
output reg [1:0] ForwardAE,
output reg [1:0] ForwardBE,
output reg FlushD,
output reg [1:0] ForwardDs,		// bgtz
output reg [1:0] ForwardDt
    );

always@(*) begin
	if(~rst_n) begin
		StallF = 0; StallD = 0; FlushD = 0;
		ForwardAE = 0; ForwardBE = 0;
		ForwardDt = 0; ForwardDs = 0;
	end
	else begin
		StallF = 0; StallD = 0; FlushD = 0;
		ForwardAE = 0; ForwardBE = 0;
		ForwardDt = 0; ForwardDs = 0;
		
		if(RegWriteW) begin		// lw, ALU -> ALU		// ok
			if(RegWriteAddrW) begin
				if(RegWriteAddrW == RegRsE)
					ForwardAE = 2'b01;
				if(RegWriteAddrW == RegRtE)
					ForwardBE = 2'b01;
				if(RegWriteAddrW == RegRsD)
					ForwardDs = 2'b11;
				if(RegWriteAddrW == RegRtD)
					ForwardDt = 2'b11;
			end
		end
		
		if(RegWriteM & ~MemtoRegM) begin	// ALU -> ALU	//ok
			if(RegWriteAddrM) begin
				if(RegWriteAddrM == RegRsE)
					ForwardAE = 2'b10;
				if(RegWriteAddrM == RegRtE)
					ForwardBE = 2'b10;
				if(RegWriteAddrM == RegRsD)
					ForwardDs = 2'b10;
				if(RegWriteAddrM == RegRtD)
					ForwardDt = 2'b10;
			end		
		end
		
		if(RegWriteE & ~MemtoRegE) begin // bgtz,j,jr
			if(RegWriteAddrE) begin
				if(RegWriteAddrE == RegRsD)
					ForwardDs = 2'b01;
				if(RegWriteAddrE == RegRtD)
					ForwardDt = 2'b01;
			end
		end
		
		if(RegWriteM & MemtoRegM) begin		// Mem -> ALU don't need stall
			if(RegWriteAddrM) begin
				if(RegWriteAddrM == RegRsE)
					ForwardAE = 2'b11;
				if(RegWriteAddrM == RegRtE)
					ForwardBE = 2'b11;
			end
		end
		
		if(BranchE || JumpE || JumpRE) begin
			if((PCSrcE && ~JumpPredictE) || (~PCSrcE && JumpPredictE))
				FlushD = 1;
			else 
				FlushD = 0;
		end
	end
end

endmodule
