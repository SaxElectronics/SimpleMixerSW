//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2022.2 (win64) Build 3671981 Fri Oct 14 05:00:03 MDT 2022
//Date        : Tue Jan  3 21:50:38 2023
//Host        : LAPTOP-QKLHUPCP running 64-bit major release  (build 9200)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (DDR_addr,
    DDR_ba,
    DDR_cas_n,
    DDR_ck_n,
    DDR_ck_p,
    DDR_cke,
    DDR_cs_n,
    DDR_dm,
    DDR_dq,
    DDR_dqs_n,
    DDR_dqs_p,
    DDR_odt,
    DDR_ras_n,
    DDR_reset_n,
    DDR_we_n,
    FIXED_IO_ddr_vrn,
    FIXED_IO_ddr_vrp,
    FIXED_IO_mio,
    FIXED_IO_ps_clk,
    FIXED_IO_ps_porb,
    FIXED_IO_ps_srstb,
    LRCK_RX,
    LRCK_TX,
    MCLK_RX,
    MCLK_TX,
    SCLK_RX,
    SCLK_TX,
    SDIN_RX,
    SDOUT_TX,
    btns_4bits_tri_i,
    leds_4bits_tri_o,
    rgb1_tri_o,
    rgb2_tri_o);
  inout [14:0]DDR_addr;
  inout [2:0]DDR_ba;
  inout DDR_cas_n;
  inout DDR_ck_n;
  inout DDR_ck_p;
  inout DDR_cke;
  inout DDR_cs_n;
  inout [3:0]DDR_dm;
  inout [31:0]DDR_dq;
  inout [3:0]DDR_dqs_n;
  inout [3:0]DDR_dqs_p;
  inout DDR_odt;
  inout DDR_ras_n;
  inout DDR_reset_n;
  inout DDR_we_n;
  inout FIXED_IO_ddr_vrn;
  inout FIXED_IO_ddr_vrp;
  inout [53:0]FIXED_IO_mio;
  inout FIXED_IO_ps_clk;
  inout FIXED_IO_ps_porb;
  inout FIXED_IO_ps_srstb;
  output LRCK_RX;
  output LRCK_TX;
  output MCLK_RX;
  output MCLK_TX;
  output SCLK_RX;
  output SCLK_TX;
  input SDIN_RX;
  output SDOUT_TX;
  input [3:0]btns_4bits_tri_i;
  output [3:0]leds_4bits_tri_o;
  output [2:0]rgb1_tri_o;
  output [2:0]rgb2_tri_o;

  wire [14:0]DDR_addr;
  wire [2:0]DDR_ba;
  wire DDR_cas_n;
  wire DDR_ck_n;
  wire DDR_ck_p;
  wire DDR_cke;
  wire DDR_cs_n;
  wire [3:0]DDR_dm;
  wire [31:0]DDR_dq;
  wire [3:0]DDR_dqs_n;
  wire [3:0]DDR_dqs_p;
  wire DDR_odt;
  wire DDR_ras_n;
  wire DDR_reset_n;
  wire DDR_we_n;
  wire FIXED_IO_ddr_vrn;
  wire FIXED_IO_ddr_vrp;
  wire [53:0]FIXED_IO_mio;
  wire FIXED_IO_ps_clk;
  wire FIXED_IO_ps_porb;
  wire FIXED_IO_ps_srstb;
  wire LRCK_RX;
  wire LRCK_TX;
  wire MCLK_RX;
  wire MCLK_TX;
  wire SCLK_RX;
  wire SCLK_TX;
  wire SDIN_RX;
  wire SDOUT_TX;
  wire [3:0]btns_4bits_tri_i;
  wire [3:0]leds_4bits_tri_o;
  wire [2:0]rgb1_tri_o;
  wire [2:0]rgb2_tri_o;

  design_1 design_1_i
       (.DDR_addr(DDR_addr),
        .DDR_ba(DDR_ba),
        .DDR_cas_n(DDR_cas_n),
        .DDR_ck_n(DDR_ck_n),
        .DDR_ck_p(DDR_ck_p),
        .DDR_cke(DDR_cke),
        .DDR_cs_n(DDR_cs_n),
        .DDR_dm(DDR_dm),
        .DDR_dq(DDR_dq),
        .DDR_dqs_n(DDR_dqs_n),
        .DDR_dqs_p(DDR_dqs_p),
        .DDR_odt(DDR_odt),
        .DDR_ras_n(DDR_ras_n),
        .DDR_reset_n(DDR_reset_n),
        .DDR_we_n(DDR_we_n),
        .FIXED_IO_ddr_vrn(FIXED_IO_ddr_vrn),
        .FIXED_IO_ddr_vrp(FIXED_IO_ddr_vrp),
        .FIXED_IO_mio(FIXED_IO_mio),
        .FIXED_IO_ps_clk(FIXED_IO_ps_clk),
        .FIXED_IO_ps_porb(FIXED_IO_ps_porb),
        .FIXED_IO_ps_srstb(FIXED_IO_ps_srstb),
        .LRCK_RX(LRCK_RX),
        .LRCK_TX(LRCK_TX),
        .MCLK_RX(MCLK_RX),
        .MCLK_TX(MCLK_TX),
        .SCLK_RX(SCLK_RX),
        .SCLK_TX(SCLK_TX),
        .SDIN_RX(SDIN_RX),
        .SDOUT_TX(SDOUT_TX),
        .btns_4bits_tri_i(btns_4bits_tri_i),
        .leds_4bits_tri_o(leds_4bits_tri_o),
        .rgb1_tri_o(rgb1_tri_o),
        .rgb2_tri_o(rgb2_tri_o));
endmodule
