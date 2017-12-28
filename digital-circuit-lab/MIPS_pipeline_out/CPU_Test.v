`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:49:58 05/28/2017
// Design Name:   top
// Module Name:   C:/Users/ralzq/Study/ISEexp/MIPS_pipeline_out/CPU_Test.v
// Project Name:  MIPS_pipeline_out
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: top
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module CPU_Test;

	// Inputs
	reg clk;
	reg rst_n;
	reg Hack;
	reg [5:0] DataMemAddr;

	// Outputs
	wire [7:0] Led;

	// Instantiate the Unit Under Test (UUT)
	top uut (
		.clk(clk), 
		.rst_n(rst_n), 
		.Hack(Hack), 
		.DataMemAddr(DataMemAddr), 
		.Led(Led)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		rst_n = 0;
		Hack = 0;
		DataMemAddr = 0;

		// Wait 100 ns for global reset to finish
		#20;
		
		rst_n = 1;
		
		forever begin
			clk = ~clk;
			#10;
		end
        
		// Add stimulus here

	end
      
endmodule

