//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Command: generate_target bd_36cd_wrapper.bd
//Design : bd_36cd_wrapper
//Purpose: IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module bd_36cd_wrapper
   (clk,
    probe0);
  input clk;
  input [31:0]probe0;

  wire clk;
  wire [31:0]probe0;

  bd_36cd bd_36cd_i
       (.clk(clk),
        .probe0(probe0));
endmodule
