`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:03:52 05/20/2017 
// Design Name: 
// Module Name:    RegFile 
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
module RegFile(
    input clk,
    input rst_n,
    input [4:0] r1_addr,
    input [4:0] r2_addr,
    input [4:0] r3_addr,
    input [31:0] din,
    input r3_wr,
    output reg [31:0] r1_dout,
    output reg [31:0] r2_dout
);

reg [31:0] Reg[0:31];
integer i;

always@(*) begin
  r1_dout = Reg[r1_addr];
  r2_dout = Reg[r2_addr];
end

always@(negedge clk or negedge rst_n) begin
	if(~rst_n) begin
		for(i=0;i<32;i=i+1)
			Reg[i] <= 0;
	end
	else begin
		if(r3_wr == 1'b1)
			Reg[r3_addr] <= din;
	end
	
end
endmodule
