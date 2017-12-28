`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:11:37 05/20/2017 
// Design Name: 
// Module Name:    control 
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
module control(
input clk,
input rst_n,
input [5:0] op,
input [5:0] funct,
input Zero,
input [31:0] RegD1D,
input [31:0] RegD2D,
input [4:0] RegAddrD1,
input [4:0] RegAddrD2,
input [31:0] SignImmD,
input [31:0] PCPlus4D,
input [31:0] ALUResE,
input [31:0] ALUResM,
input [31:0] RegWriteDataW,
output reg [4:0] ALUopD,
output reg ALUSrcAD,
output reg ALUSrcBD,
output reg RegDstD,
output reg MemWriteD,
output reg MemtoRegD,
output reg RegWriteD,
output reg JumpD,
output reg JumpRD,
output reg BranchD,
output reg PCSrcD,
output reg [31:0] PCBranch,
// hazard signals
input [1:0] ForwardDs,
input [1:0] ForwardDt,
input FlushD
    );

reg [31:0] Compares;
reg [31:0] Comparet;
reg [2:0] BranchOp = 0;
reg ConditionD;

always@(*) begin
	if(~rst_n) begin
		Compares <= 0; Comparet <= 0;
	end
	else begin
		case(ForwardDs)
		2'b00: Compares <= RegD1D;
		2'b01: Compares <= ALUResE;
		2'b10: Compares <= ALUResM;
		2'b11: Compares <= RegWriteDataW;
		endcase
		case(ForwardDt)
		2'b00: Comparet <= RegD2D;
		2'b01: Comparet <= ALUResE;
		2'b10: Comparet <= ALUResM;
		2'b11: Comparet <= RegWriteDataW;
		endcase
	end
end
	
always@(*) begin   //negedge clk or negedge rst_n
	if(~rst_n) begin
		MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
		RegWriteD <= 0; ALUopD <= 0; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
	end
	else if(FlushD) begin
		MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
		RegWriteD <= 0; ALUopD <= 0; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
	end
	else begin
		case(op)
		6'b000000: begin 
			case(funct)
			6'b100000: begin	//add
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
				RegWriteD <= 1; ALUopD <= 5'h1; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 1; JumpRD <= 0;
			end
			6'b100001: begin //addu
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
				RegWriteD <= 1; ALUopD <= 5'h1; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 1; JumpRD <= 0;
			end
			6'b100010: begin  // sub
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
				RegWriteD <= 1; ALUopD <= 5'h2; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 1; JumpRD <= 0;
			end
			6'b100011: begin // subu
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
				RegWriteD <= 1; ALUopD <= 5'h2; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 1; JumpRD <= 0;
			end
			6'b100100: begin // and
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
				RegWriteD <= 1; ALUopD <= 5'h3; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 1; JumpRD <= 0;
			end
			6'b100110: begin // xor
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
				RegWriteD <= 1; ALUopD <= 5'h5; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 1; JumpRD <= 0;
			end
			6'b100101: begin // or
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
				RegWriteD <= 1; ALUopD <= 5'h4;ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 1; JumpRD <= 0;
			end
			6'b100111: begin // nor
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
				RegWriteD <= 1; ALUopD <= 5'h6; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 1; JumpRD <= 0;
			end
			6'b001000: begin //jr
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 3'h2;
				RegWriteD <= 0; ALUopD <= 5'h7; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 1;
			end
			6'b000000: begin //sll +
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
				RegWriteD <= 1; ALUopD <= 5'h9; ALUSrcAD <= 1; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
			end
			6'b000100: begin //sllv +
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
				RegWriteD <= 1; ALUopD <= 5'h9; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
			end
			6'b000010: begin // srl +
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
				RegWriteD <= 1; ALUopD <= 5'h10; ALUSrcAD <= 1; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
			end
			6'b000110: begin // srlv +
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
				RegWriteD <= 1; ALUopD <= 5'h10; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
			end
			default: begin
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
				RegWriteD <= 0; ALUopD <= 5'h7; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 1; JumpRD <= 0;
			end
			endcase
		end
		6'b001000: begin //addi
			MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
			RegWriteD <= 1; ALUopD <= 5'h1;ALUSrcAD <= 0; ALUSrcBD <= 1;; RegDstD <= 0; JumpRD <= 0;
		end
		6'b001100: begin //andi
			MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
			RegWriteD <= 1; ALUopD <= 5'h3; ALUSrcAD <= 0; ALUSrcBD <= 1; RegDstD <= 0; JumpRD <= 0;
		end
		6'b100011: begin //lw
			MemtoRegD <= 1; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
			RegWriteD <= 1; ALUopD <= 5'h1; ALUSrcAD <= 0; ALUSrcBD <= 1; RegDstD <= 0; JumpRD <= 0;
		end
		6'b101011: begin //sw
			MemtoRegD <= 1; MemWriteD <= 1; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
			RegWriteD <= 0; ALUopD <= 5'h1; ALUSrcAD <= 0; ALUSrcBD <= 1; RegDstD <= 0;JumpRD <= 0;
		end
		6'b000111: begin //bgtz
			MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 1;JumpD <= 0; BranchOp <= 3'h1;
			RegWriteD <= 0; ALUopD <= 5'h7; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
		end
		
		6'b000101: begin //bne
			MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 1; JumpD <= 0; BranchOp <= 3'h4;
			RegWriteD <= 0; ALUopD <= 5'h7; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
		end
		6'b000100: begin //beq  +
			MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 1; JumpD <= 0; BranchOp <= 3'h5;
			RegWriteD <= 0; ALUopD <= 5'h7; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
		end
		6'b000001: begin
			case(RegAddrD2)
			5'b00000: begin // bltz +
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 1; JumpD <= 0; BranchOp <= 3'h3;
				RegWriteD <= 0; ALUopD <= 5'h7; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
			end
			5'b00001: begin // bgez +
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 1; JumpD <= 0; BranchOp <= 3'h6;
				RegWriteD <= 0; ALUopD <= 5'h7; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
			end
			default: begin
				MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 3'h6;
				RegWriteD <= 0; ALUopD <= 5'h7; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
			end
			endcase
		end
		6'b000010: begin //j
			MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 1; BranchOp <= 3'h2;
			RegWriteD <= 0; ALUopD <= 5'h7; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
		end
		6'b001101: begin //ori  +
			MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
			RegWriteD <= 1; ALUopD <= 5'h4; ALUSrcAD <= 0; ALUSrcBD <= 1; RegDstD <= 0; JumpRD <= 0;
		end
		6'b001111: begin // lui  +
			MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
			RegWriteD <= 1; ALUopD <= 5'h8; ALUSrcAD <= 0; ALUSrcBD <= 1; RegDstD <= 0; JumpRD <= 0;
		end
		6'b000000: begin //noop +
			MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
			RegWriteD <= 0; ALUopD <= 5'h0; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
		end
		default: begin
			MemtoRegD <= 0; MemWriteD <= 0; BranchD <= 0; JumpD <= 0; BranchOp <= 0;
			RegWriteD <= 0; ALUopD <= 5'h0; ALUSrcAD <= 0; ALUSrcBD <= 0; RegDstD <= 0; JumpRD <= 0;
		end
		endcase
	end
end

always@(*) begin
	if(~rst_n) begin
		ConditionD <= 0;
	end
	else begin
		case(BranchOp)
			3'h0: ConditionD <= 0;
			3'h1: begin									// bgtz
				if(Compares[31:31] == 0 && Compares > 0)
					ConditionD <= 1;
				else
					ConditionD <= 0;
			end
			3'h2: ConditionD <= 1;					//j, jr
			3'h3: begin									// bltz
				if(Compares[31:31] == 1)
					ConditionD <= 1;
				else
					ConditionD <= 0;
			end
			3'h4: begin									// bne
				if(Compares != Comparet) 
					ConditionD <= 1;
				else
					ConditionD <= 0;
			end
			3'h5: begin									//beq
				if(Compares == Comparet)
					ConditionD <= 1;
				else
					ConditionD <= 0;
			end
			3'h6: begin									//bgez
				if(Compares[31:31] == 0)
					ConditionD <= 1;
				else
					ConditionD <= 0;
			end
			
			default: ConditionD <= 0;
		endcase
	end
end

always@(*) begin
	PCSrcD <= ConditionD;
end

always@(*) begin
	if(~rst_n) begin
		PCBranch <= 0;
	end
	else begin
		if(JumpD == 1)
			PCBranch <= (SignImmD << 2);
		else if(JumpRD == 1)
			PCBranch <= Compares;
		else 
			PCBranch <= PCPlus4D + (SignImmD << 2);
	end
end

endmodule
