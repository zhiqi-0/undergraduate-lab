`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:03:37 05/20/2017 
// Design Name: 
// Module Name:    ALU 
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
module ALU(
input signed [31:0] alu_a,
input signed [31:0] alu_b,
input [4:0] alu_op,
output reg [31:0] alu_out,
output reg zero
);
initial begin
	alu_out = 0;
end

parameter A_NOP = 5'h0, A_ADD = 5'h1, A_SUB = 5'h2;
parameter A_AND = 5'h3, A_OR = 5'h4, A_XOR = 5'h5;
parameter A_NOR = 5'h6, A_ZERO = 5'h7, A_LShift16 = 5'h8;
parameter A_SLL = 5'h9, A_SRL = 5'h10;

always@(*) begin
	case(alu_op)
	A_ADD: alu_out = alu_a + alu_b;
	A_SUB: alu_out = alu_a - alu_b;
	A_AND: alu_out = alu_a & alu_b;
	A_OR : alu_out = alu_a | alu_b;
	A_XOR: alu_out = alu_a ^ alu_b;
	A_NOR: alu_out = ~(alu_a | alu_b);
	A_ZERO: alu_out = 0;
	A_LShift16: alu_out = alu_b << 16;
	A_SLL: alu_out = alu_b << alu_a;
	A_SRL: alu_out = alu_b >> alu_a;
	default: ;
	endcase
end

always@(*) begin
	if(alu_out == 0)
		zero = 1'b1;
	else
		zero = 1'b0;
end

endmodule
