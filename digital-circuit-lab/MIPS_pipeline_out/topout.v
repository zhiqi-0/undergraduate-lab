`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:10:33 05/28/2017 
// Design Name: 
// Module Name:    topout 
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
module topout(
input Hack,
input Mode,
input [5:0] DataMemAddr1,
input rst,
input clk,
input Left1,
input Right1,
output [7:0] Led
    );
	 
reg [5:0] DMAddr = 0;
reg [5:0] DataMemAddr;
reg clka = 0;
reg [1:0] cnt = 0;
wire Left;
wire Right;

top				CPU_top(
.clk				(clka),
.rst_n			(~rst),
.Hack				(Hack),
.DataMemAddr	(DataMemAddr),
.Led				(Led)
);

debounce 	L_debounce(
.clk			(clk),
.butt			(Left1),
.rst_n		(~rst),
.Op			(Left)
);

debounce 	R_debounce(
.clk			(clk),
.butt			(Right1),
.rst_n		(~rst),
.Op			(Right)
);

always@(posedge Left or posedge Right) begin
	if(rst) begin
		DMAddr <= 0;
	end
	else if(Left)
		DMAddr <= DMAddr - 1;
	else
		DMAddr <= DMAddr + 1;
end

always@(*) begin
	if(rst)
		DataMemAddr <= 0;
	else if(Mode)
		DataMemAddr <= DMAddr;
	else
		DataMemAddr <= DataMemAddr1;
end

always@(posedge clk) begin
	if(rst) begin
		clka <= 0;
		cnt <= 1;
	end
	else if(cnt == 0) begin
		clka <= ~clka;
		cnt <= cnt + 1;
	end
	else
		cnt <= cnt + 1;
end



endmodule
