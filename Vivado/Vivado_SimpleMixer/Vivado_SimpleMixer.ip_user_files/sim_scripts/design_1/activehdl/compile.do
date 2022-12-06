vlib work
vlib activehdl

vlib activehdl/xilinx_vip
vlib activehdl/xpm
vlib activehdl/axi_infrastructure_v1_1_0
vlib activehdl/axi_vip_v1_1_13
vlib activehdl/processing_system7_vip_v1_0_15
vlib activehdl/xil_defaultlib
vlib activehdl/axi_lite_ipif_v3_0_4
vlib activehdl/lib_cdc_v1_0_2
vlib activehdl/interrupt_control_v3_1_4
vlib activehdl/axi_gpio_v2_0_29
vlib activehdl/generic_baseblocks_v2_1_0
vlib activehdl/axi_register_slice_v2_1_27
vlib activehdl/fifo_generator_v13_2_7
vlib activehdl/axi_data_fifo_v2_1_26
vlib activehdl/axi_crossbar_v2_1_28
vlib activehdl/proc_sys_reset_v5_0_13
vlib activehdl/lib_pkg_v1_0_2
vlib activehdl/lib_fifo_v1_0_16
vlib activehdl/lib_srl_fifo_v1_0_2
vlib activehdl/axi_datamover_v5_1_29
vlib activehdl/audio_formatter_v1_0_9
vlib activehdl/i2s_transmitter_v1_0_5
vlib activehdl/i2s_receiver_v1_0_5
vlib activehdl/xlconcat_v2_1_4
vlib activehdl/xlslice_v1_0_2
vlib activehdl/xlconstant_v1_1_7
vlib activehdl/axi_protocol_converter_v2_1_27
vlib activehdl/axi_clock_converter_v2_1_26
vlib activehdl/blk_mem_gen_v8_4_5
vlib activehdl/axi_dwidth_converter_v2_1_27

vmap xilinx_vip activehdl/xilinx_vip
vmap xpm activehdl/xpm
vmap axi_infrastructure_v1_1_0 activehdl/axi_infrastructure_v1_1_0
vmap axi_vip_v1_1_13 activehdl/axi_vip_v1_1_13
vmap processing_system7_vip_v1_0_15 activehdl/processing_system7_vip_v1_0_15
vmap xil_defaultlib activehdl/xil_defaultlib
vmap axi_lite_ipif_v3_0_4 activehdl/axi_lite_ipif_v3_0_4
vmap lib_cdc_v1_0_2 activehdl/lib_cdc_v1_0_2
vmap interrupt_control_v3_1_4 activehdl/interrupt_control_v3_1_4
vmap axi_gpio_v2_0_29 activehdl/axi_gpio_v2_0_29
vmap generic_baseblocks_v2_1_0 activehdl/generic_baseblocks_v2_1_0
vmap axi_register_slice_v2_1_27 activehdl/axi_register_slice_v2_1_27
vmap fifo_generator_v13_2_7 activehdl/fifo_generator_v13_2_7
vmap axi_data_fifo_v2_1_26 activehdl/axi_data_fifo_v2_1_26
vmap axi_crossbar_v2_1_28 activehdl/axi_crossbar_v2_1_28
vmap proc_sys_reset_v5_0_13 activehdl/proc_sys_reset_v5_0_13
vmap lib_pkg_v1_0_2 activehdl/lib_pkg_v1_0_2
vmap lib_fifo_v1_0_16 activehdl/lib_fifo_v1_0_16
vmap lib_srl_fifo_v1_0_2 activehdl/lib_srl_fifo_v1_0_2
vmap axi_datamover_v5_1_29 activehdl/axi_datamover_v5_1_29
vmap audio_formatter_v1_0_9 activehdl/audio_formatter_v1_0_9
vmap i2s_transmitter_v1_0_5 activehdl/i2s_transmitter_v1_0_5
vmap i2s_receiver_v1_0_5 activehdl/i2s_receiver_v1_0_5
vmap xlconcat_v2_1_4 activehdl/xlconcat_v2_1_4
vmap xlslice_v1_0_2 activehdl/xlslice_v1_0_2
vmap xlconstant_v1_1_7 activehdl/xlconstant_v1_1_7
vmap axi_protocol_converter_v2_1_27 activehdl/axi_protocol_converter_v2_1_27
vmap axi_clock_converter_v2_1_26 activehdl/axi_clock_converter_v2_1_26
vmap blk_mem_gen_v8_4_5 activehdl/blk_mem_gen_v8_4_5
vmap axi_dwidth_converter_v2_1_27 activehdl/axi_dwidth_converter_v2_1_27

vlog -work xilinx_vip  -sv2k12 "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -sv2k12 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2022.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"C:/Xilinx/Vivado/2022.2/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"C:/Xilinx/Vivado/2022.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93  \
"C:/Xilinx/Vivado/2022.2/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work axi_infrastructure_v1_1_0  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_13  -sv2k12 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ffc2/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work processing_system7_vip_v1_0_15  -sv2k12 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_processing_system7_0_0/sim/design_1_processing_system7_0_0.v" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/design_1_clk_wiz_0_0_mmcm_pll_drp.v" \

vcom -work xil_defaultlib -93  \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/proc_common_v3_00_a/hdl/src/vhdl/design_1_clk_wiz_0_0_conv_funs_pkg.vhd" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/proc_common_v3_00_a/hdl/src/vhdl/design_1_clk_wiz_0_0_proc_common_pkg.vhd" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/proc_common_v3_00_a/hdl/src/vhdl/design_1_clk_wiz_0_0_ipif_pkg.vhd" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/proc_common_v3_00_a/hdl/src/vhdl/design_1_clk_wiz_0_0_family_support.vhd" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/proc_common_v3_00_a/hdl/src/vhdl/design_1_clk_wiz_0_0_family.vhd" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/proc_common_v3_00_a/hdl/src/vhdl/design_1_clk_wiz_0_0_soft_reset.vhd" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/proc_common_v3_00_a/hdl/src/vhdl/design_1_clk_wiz_0_0_pselect_f.vhd" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/axi_lite_ipif_v1_01_a/hdl/src/vhdl/design_1_clk_wiz_0_0_address_decoder.vhd" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/axi_lite_ipif_v1_01_a/hdl/src/vhdl/design_1_clk_wiz_0_0_slave_attachment.vhd" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/axi_lite_ipif_v1_01_a/hdl/src/vhdl/design_1_clk_wiz_0_0_axi_lite_ipif.vhd" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/design_1_clk_wiz_0_0_clk_wiz_drp.vhd" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/design_1_clk_wiz_0_0_axi_clk_config.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/design_1_clk_wiz_0_0_clk_wiz.v" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/design_1_clk_wiz_0_0.v" \

vcom -work axi_lite_ipif_v3_0_4 -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \

vcom -work lib_cdc_v1_0_2 -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work interrupt_control_v3_1_4 -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/a040/hdl/interrupt_control_v3_1_vh_rfs.vhd" \

vcom -work axi_gpio_v2_0_29 -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/6219/hdl/axi_gpio_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93  \
"../../../bd/design_1/ip/design_1_axi_gpio_0_0/sim/design_1_axi_gpio_0_0.vhd" \

vlog -work generic_baseblocks_v2_1_0  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_27  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/f0b4/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work fifo_generator_v13_2_7  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/83df/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_7 -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/83df/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_7  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/83df/hdl/fifo_generator_v13_2_rfs.v" \

vlog -work axi_data_fifo_v2_1_26  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/3111/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_28  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/c40e/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xbar_0/sim/design_1_xbar_0.v" \

vcom -work proc_sys_reset_v5_0_13 -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93  \
"../../../bd/design_1/ip/design_1_rst_ps7_0_100M_0/sim/design_1_rst_ps7_0_100M_0.vhd" \
"../../../bd/design_1/ip/design_1_axi_gpio_1_0/sim/design_1_axi_gpio_1_0.vhd" \
"../../../bd/design_1/ip/design_1_axi_gpio_2_0/sim/design_1_axi_gpio_2_0.vhd" \

vcom -work lib_pkg_v1_0_2 -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/0513/hdl/lib_pkg_v1_0_rfs.vhd" \

vcom -work lib_fifo_v1_0_16 -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/6c82/hdl/lib_fifo_v1_0_rfs.vhd" \

vcom -work lib_srl_fifo_v1_0_2 -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/51ce/hdl/lib_srl_fifo_v1_0_rfs.vhd" \

vcom -work axi_datamover_v5_1_29 -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/2237/hdl/axi_datamover_v5_1_vh_rfs.vhd" \

vlog -work audio_formatter_v1_0_9  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/9554/hdl/audio_formatter_v1_0_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_audio_formatter_0_0/sim/design_1_audio_formatter_0_0.v" \

vcom -work xil_defaultlib -93  \
"../../../bd/design_1/ip/design_1_rst_clk_wiz_0_49M_0/sim/design_1_rst_clk_wiz_0_49M_0.vhd" \

vlog -work i2s_transmitter_v1_0_5  -sv2k12 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/8aae/hdl/i2s_transmitter_v1_0_rfs.sv" \

vlog -work xil_defaultlib  -sv2k12 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_i2s_transmitter_0_0/sim/design_1_i2s_transmitter_0_0.sv" \

vlog -work i2s_receiver_v1_0_5  -sv2k12 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/9736/hdl/i2s_receiver_v1_0_rfs.sv" \

vlog -work xil_defaultlib  -sv2k12 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_i2s_receiver_0_0/sim/design_1_i2s_receiver_0_0.sv" \

vlog -work xlconcat_v2_1_4  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/4b67/hdl/xlconcat_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xlconcat_0_0/sim/design_1_xlconcat_0_0.v" \

vlog -work xlslice_v1_0_2  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/11d0/hdl/xlslice_v1_0_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xlslice_0_0/sim/design_1_xlslice_0_0.v" \

vlog -work xlconstant_v1_1_7  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/badb/hdl/xlconstant_v1_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xlconstant_0_0/sim/design_1_xlconstant_0_0.v" \
"../../../bd/design_1/ip/design_1_xlconcat_2_0/sim/design_1_xlconcat_2_0.v" \
"../../../bd/design_1/ip/design_1_system_ila_0_0/bd_0/sim/bd_f60c.v" \
"../../../bd/design_1/ip/design_1_system_ila_0_0/bd_0/ip/ip_0/sim/bd_f60c_ila_lib_0.v" \
"../../../bd/design_1/ip/design_1_system_ila_0_0/sim/design_1_system_ila_0_0.v" \
"../../../bd/design_1/sim/design_1.v" \

vlog -work axi_protocol_converter_v2_1_27  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/aeb3/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_auto_pc_8/sim/design_1_auto_pc_8.v" \

vlog -work axi_clock_converter_v2_1_26  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b8be/hdl/axi_clock_converter_v2_1_vl_rfs.v" \

vlog -work blk_mem_gen_v8_4_5  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/25a8/simulation/blk_mem_gen_v8_4.v" \

vlog -work axi_dwidth_converter_v2_1_27  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/4675/hdl/axi_dwidth_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_auto_us_0/sim/design_1_auto_us_0.v" \
"../../../bd/design_1/ip/design_1_auto_us_1/sim/design_1_auto_us_1.v" \
"../../../bd/design_1/ip/design_1_auto_us_2/sim/design_1_auto_us_2.v" \
"../../../bd/design_1/ip/design_1_auto_ds_0/sim/design_1_auto_ds_0.v" \
"../../../bd/design_1/ip/design_1_auto_pc_0/sim/design_1_auto_pc_0.v" \
"../../../bd/design_1/ip/design_1_auto_ds_1/sim/design_1_auto_ds_1.v" \
"../../../bd/design_1/ip/design_1_auto_pc_1/sim/design_1_auto_pc_1.v" \
"../../../bd/design_1/ip/design_1_auto_ds_2/sim/design_1_auto_ds_2.v" \
"../../../bd/design_1/ip/design_1_auto_pc_2/sim/design_1_auto_pc_2.v" \
"../../../bd/design_1/ip/design_1_auto_ds_3/sim/design_1_auto_ds_3.v" \
"../../../bd/design_1/ip/design_1_auto_pc_3/sim/design_1_auto_pc_3.v" \
"../../../bd/design_1/ip/design_1_auto_ds_4/sim/design_1_auto_ds_4.v" \
"../../../bd/design_1/ip/design_1_auto_pc_4/sim/design_1_auto_pc_4.v" \
"../../../bd/design_1/ip/design_1_auto_ds_5/sim/design_1_auto_ds_5.v" \
"../../../bd/design_1/ip/design_1_auto_pc_5/sim/design_1_auto_pc_5.v" \
"../../../bd/design_1/ip/design_1_auto_pc_6/sim/design_1_auto_pc_6.v" \
"../../../bd/design_1/ip/design_1_auto_ds_6/sim/design_1_auto_ds_6.v" \
"../../../bd/design_1/ip/design_1_auto_pc_7/sim/design_1_auto_pc_7.v" \

vlog -work xil_defaultlib \
"glbl.v"

