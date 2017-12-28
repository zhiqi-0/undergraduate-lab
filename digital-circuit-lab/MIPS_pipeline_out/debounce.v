`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:13:54 05/28/2017 
// Design Name: 
// Module Name:    debounce 
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
module debounce(
	input clk,
	input butt,
	input rst_n,
	output reg Op
);


reg [19:0] cnt=20'd0;
reg flag=0;

initial Op=0;

always@(posedge clk)
begin
	if (~rst_n)
	begin
		cnt<=20'd0;
		Op <= 0;
		flag <= 0;
	end
	
	else 
	begin
		if (Op==1)
			Op<=0;
			
		if (~butt)
		begin
			cnt<=20'd0;
			flag <= 0;
		end
		
		else 
		begin
			if (cnt==20'd999_99)
			begin
					if (flag==0)
					begin
						Op<=1;
						flag <= 1;
					end	
			end
			else
				cnt<=cnt+20'd1;
			end
	end
end

endmodule
