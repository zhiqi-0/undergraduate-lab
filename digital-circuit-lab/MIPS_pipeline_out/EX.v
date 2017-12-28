`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:52:12 05/21/2017 
// Design Name: 
// Module Name:    EX 
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
module EX(
input rst_n,
input [31:0] RegD1E,
input [31:0] RegD2E1,
input [31:0] SignImmE,
input [4:0]  ShamtE,
input [4:0] RegWriteAddrE1,
input [4:0] RegWriteAddrE2,
input ALUSrcAE,
input ALUSrcBE,
input [4:0] ALUopE,
input RegDstE,
output Zero,
output [31:0] ALUResE,
output reg [4:0] RegWriteAddrE,
output reg [31:0] RegD2E,
// hazard signals
input [31:0] ALUResM,
input [31:0] RegWriteDataW,
input [31:0] DataMemDM,
input [1:0] ForwardAE,
input [1:0] ForwardBE
    );

reg [31:0] ALUR2;
reg [31:0] ALUR1;
reg [31:0] ALUR2t;
reg [31:0] ALUR1t;

ALU				u_ALU(
.alu_a			(ALUR1),
.alu_b			(ALUR2),
.alu_op			(ALUopE),
.zero				(Zero),
.alu_out			(ALUResE)
);


always@(*) begin
	if(~rst_n) begin
		ALUR2 <= 0; ALUR1<= 0;
		RegD2E <= 0;
		RegWriteAddrE <= 0;
	end
	else begin
	
		case(ForwardAE)
		2'b00: ALUR1t <= RegD1E;
		2'b01: ALUR1t <= RegWriteDataW;
		2'b10: ALUR1t <= ALUResM;
		2'b11: ALUR1t <= DataMemDM;
		endcase
		
		case(ForwardBE)
		2'b00: ALUR2t <= RegD2E1;
		2'b01: ALUR2t <= RegWriteDataW;
		2'b10: ALUR2t <= ALUResM;
		2'b11: ALUR2t <= DataMemDM;
		endcase
		
		if(ALUSrcBE == 1)
			ALUR2 <= SignImmE;
		else
			ALUR2 <= ALUR2t;
		
		if(ALUSrcAE == 1)
			ALUR1 <= ShamtE;
		else
			ALUR1 <= ALUR1t;
		
		RegD2E <= ALUR2t;
		
		if(RegDstE == 1)
			RegWriteAddrE <= RegWriteAddrE2;
		else
			RegWriteAddrE <= RegWriteAddrE1;
	end
end

endmodule
