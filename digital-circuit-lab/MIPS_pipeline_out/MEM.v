`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:20:26 05/21/2017 
// Design Name: 
// Module Name:    MEM 
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
module MEM(
input clk,
input rst_n,
input [31:0] ALUResM,
input [31:0] RegD2M,
input MemWriteM,
output [31:0] DataMemDM,
// display
input [5:0] DataMemAddr,
input Hack,
output reg [7:0] Led
    );

reg [6:0] DataAddrChoice;

DataMem			u_DataMem(
.a					(DataAddrChoice),
.d					(RegD2M),
.we				(MemWriteM),
.clk				(clk),
.spo				(DataMemDM)
);

always@(*) begin
	if(~rst_n) begin
		DataAddrChoice <= 0;
	end
	else if(Hack)
		DataAddrChoice <= {0,DataMemAddr};
	else
		DataAddrChoice <= ALUResM[8:2];
end

always@(*) begin
	if(~rst_n) 
		Led <= 0;
	else if(Hack)
		Led <= DataMemDM[7:0];
	else
		Led <= 0;
end

endmodule
