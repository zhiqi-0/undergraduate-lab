`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:14:26 05/21/2017 
// Design Name: 
// Module Name:    SignImm 
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
module SignExtend(
input signed [15:0] Imm,
output reg [31:0] SignImm
    );
	 
always@(*) begin
	if(Imm[15:15] == 1)
		SignImm = {16'b1111111111111111,Imm};
	else
		SignImm = {16'b0,Imm};
end

endmodule
