vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/xilinx_vip
vlib modelsim_lib/msim/xpm
vlib modelsim_lib/msim/axi_infrastructure_v1_1_0
vlib modelsim_lib/msim/axi_vip_v1_1_13
vlib modelsim_lib/msim/processing_system7_vip_v1_0_15
vlib modelsim_lib/msim/xil_defaultlib
vlib modelsim_lib/msim/axi_lite_ipif_v3_0_4
vlib modelsim_lib/msim/lib_cdc_v1_0_2
vlib modelsim_lib/msim/interrupt_control_v3_1_4
vlib modelsim_lib/msim/axi_gpio_v2_0_29
vlib modelsim_lib/msim/generic_baseblocks_v2_1_0
vlib modelsim_lib/msim/axi_register_slice_v2_1_27
vlib modelsim_lib/msim/fifo_generator_v13_2_7
vlib modelsim_lib/msim/axi_data_fifo_v2_1_26
vlib modelsim_lib/msim/axi_crossbar_v2_1_28
vlib modelsim_lib/msim/proc_sys_reset_v5_0_13
vlib modelsim_lib/msim/lib_pkg_v1_0_2
vlib modelsim_lib/msim/lib_fifo_v1_0_16
vlib modelsim_lib/msim/lib_srl_fifo_v1_0_2
vlib modelsim_lib/msim/axi_datamover_v5_1_29
vlib modelsim_lib/msim/audio_formatter_v1_0_9
vlib modelsim_lib/msim/i2s_transmitter_v1_0_5
vlib modelsim_lib/msim/i2s_receiver_v1_0_5
vlib modelsim_lib/msim/xlconcat_v2_1_4
vlib modelsim_lib/msim/xlslice_v1_0_2
vlib modelsim_lib/msim/xlconstant_v1_1_7
vlib modelsim_lib/msim/axi_protocol_converter_v2_1_27
vlib modelsim_lib/msim/axi_clock_converter_v2_1_26
vlib modelsim_lib/msim/blk_mem_gen_v8_4_5
vlib modelsim_lib/msim/axi_dwidth_converter_v2_1_27

vmap xilinx_vip modelsim_lib/msim/xilinx_vip
vmap xpm modelsim_lib/msim/xpm
vmap axi_infrastructure_v1_1_0 modelsim_lib/msim/axi_infrastructure_v1_1_0
vmap axi_vip_v1_1_13 modelsim_lib/msim/axi_vip_v1_1_13
vmap processing_system7_vip_v1_0_15 modelsim_lib/msim/processing_system7_vip_v1_0_15
vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib
vmap axi_lite_ipif_v3_0_4 modelsim_lib/msim/axi_lite_ipif_v3_0_4
vmap lib_cdc_v1_0_2 modelsim_lib/msim/lib_cdc_v1_0_2
vmap interrupt_control_v3_1_4 modelsim_lib/msim/interrupt_control_v3_1_4
vmap axi_gpio_v2_0_29 modelsim_lib/msim/axi_gpio_v2_0_29
vmap generic_baseblocks_v2_1_0 modelsim_lib/msim/generic_baseblocks_v2_1_0
vmap axi_register_slice_v2_1_27 modelsim_lib/msim/axi_register_slice_v2_1_27
vmap fifo_generator_v13_2_7 modelsim_lib/msim/fifo_generator_v13_2_7
vmap axi_data_fifo_v2_1_26 modelsim_lib/msim/axi_data_fifo_v2_1_26
vmap axi_crossbar_v2_1_28 modelsim_lib/msim/axi_crossbar_v2_1_28
vmap proc_sys_reset_v5_0_13 modelsim_lib/msim/proc_sys_reset_v5_0_13
vmap lib_pkg_v1_0_2 modelsim_lib/msim/lib_pkg_v1_0_2
vmap lib_fifo_v1_0_16 modelsim_lib/msim/lib_fifo_v1_0_16
vmap lib_srl_fifo_v1_0_2 modelsim_lib/msim/lib_srl_fifo_v1_0_2
vmap axi_datamover_v5_1_29 modelsim_lib/msim/axi_datamover_v5_1_29
vmap audio_formatter_v1_0_9 modelsim_lib/msim/audio_formatter_v1_0_9
vmap i2s_transmitter_v1_0_5 modelsim_lib/msim/i2s_transmitter_v1_0_5
vmap i2s_receiver_v1_0_5 modelsim_lib/msim/i2s_receiver_v1_0_5
vmap xlconcat_v2_1_4 modelsim_lib/msim/xlconcat_v2_1_4
vmap xlslice_v1_0_2 modelsim_lib/msim/xlslice_v1_0_2
vmap xlconstant_v1_1_7 modelsim_lib/msim/xlconstant_v1_1_7
vmap axi_protocol_converter_v2_1_27 modelsim_lib/msim/axi_protocol_converter_v2_1_27
vmap axi_clock_converter_v2_1_26 modelsim_lib/msim/axi_clock_converter_v2_1_26
vmap blk_mem_gen_v8_4_5 modelsim_lib/msim/blk_mem_gen_v8_4_5
vmap axi_dwidth_converter_v2_1_27 modelsim_lib/msim/axi_dwidth_converter_v2_1_27

vlog -work xilinx_vip  -incr -mfcu  -sv -L i2s_receiver_v1_0_5 -L i2s_transmitter_v1_0_5 -L axi_vip_v1_1_13 -L processing_system7_vip_v1_0_15 -L xilinx_vip "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
"C:/Xilinx/Vivado/2022.2/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -incr -mfcu  -sv -L i2s_receiver_v1_0_5 -L i2s_transmitter_v1_0_5 -L axi_vip_v1_1_13 -L processing_system7_vip_v1_0_15 -L xilinx_vip "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2022.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"C:/Xilinx/Vivado/2022.2/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"C:/Xilinx/Vivado/2022.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm  -93  \
"C:/Xilinx/Vivado/2022.2/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work axi_infrastructure_v1_1_0  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_13  -incr -mfcu  -sv -L i2s_receiver_v1_0_5 -L i2s_transmitter_v1_0_5 -L axi_vip_v1_1_13 -L processing_system7_vip_v1_0_15 -L xilinx_vip "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ffc2/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work processing_system7_vip_v1_0_15  -incr -mfcu  -sv -L i2s_receiver_v1_0_5 -L i2s_transmitter_v1_0_5 -L axi_vip_v1_1_13 -L processing_system7_vip_v1_0_15 -L xilinx_vip "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_processing_system7_0_0/sim/design_1_processing_system7_0_0.v" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/design_1_clk_wiz_0_0_mmcm_pll_drp.v" \

vcom -work xil_defaultlib  -93  \
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

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/design_1_clk_wiz_0_0_clk_wiz.v" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/design_1_clk_wiz_0_0.v" \

vcom -work axi_lite_ipif_v3_0_4  -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \

vcom -work lib_cdc_v1_0_2  -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work interrupt_control_v3_1_4  -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/a040/hdl/interrupt_control_v3_1_vh_rfs.vhd" \

vcom -work axi_gpio_v2_0_29  -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/6219/hdl/axi_gpio_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib  -93  \
"../../../bd/design_1/ip/design_1_axi_gpio_0_0/sim/design_1_axi_gpio_0_0.vhd" \

vlog -work generic_baseblocks_v2_1_0  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_27  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/f0b4/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work fifo_generator_v13_2_7  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/83df/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_7  -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/83df/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_7  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/83df/hdl/fifo_generator_v13_2_rfs.v" \

vlog -work axi_data_fifo_v2_1_26  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/3111/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_28  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/c40e/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xbar_0/sim/design_1_xbar_0.v" \

vcom -work proc_sys_reset_v5_0_13  -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib  -93  \
"../../../bd/design_1/ip/design_1_rst_ps7_0_100M_0/sim/design_1_rst_ps7_0_100M_0.vhd" \
"../../../bd/design_1/ip/design_1_axi_gpio_1_0/sim/design_1_axi_gpio_1_0.vhd" \
"../../../bd/design_1/ip/design_1_axi_gpio_2_0/sim/design_1_axi_gpio_2_0.vhd" \

vcom -work lib_pkg_v1_0_2  -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/0513/hdl/lib_pkg_v1_0_rfs.vhd" \

vcom -work lib_fifo_v1_0_16  -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/6c82/hdl/lib_fifo_v1_0_rfs.vhd" \

vcom -work lib_srl_fifo_v1_0_2  -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/51ce/hdl/lib_srl_fifo_v1_0_rfs.vhd" \

vcom -work axi_datamover_v5_1_29  -93  \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/2237/hdl/axi_datamover_v5_1_vh_rfs.vhd" \

vlog -work audio_formatter_v1_0_9  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/9554/hdl/audio_formatter_v1_0_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_audio_formatter_0_0/sim/design_1_audio_formatter_0_0.v" \

vcom -work xil_defaultlib  -93  \
"../../../bd/design_1/ip/design_1_rst_clk_wiz_0_49M_0/sim/design_1_rst_clk_wiz_0_49M_0.vhd" \

vlog -work i2s_transmitter_v1_0_5  -incr -mfcu  -sv -L i2s_receiver_v1_0_5 -L i2s_transmitter_v1_0_5 -L axi_vip_v1_1_13 -L processing_system7_vip_v1_0_15 -L xilinx_vip "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/8aae/hdl/i2s_transmitter_v1_0_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L i2s_receiver_v1_0_5 -L i2s_transmitter_v1_0_5 -L axi_vip_v1_1_13 -L processing_system7_vip_v1_0_15 -L xilinx_vip "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_i2s_transmitter_0_0/sim/design_1_i2s_transmitter_0_0.sv" \

vlog -work i2s_receiver_v1_0_5  -incr -mfcu  -sv -L i2s_receiver_v1_0_5 -L i2s_transmitter_v1_0_5 -L axi_vip_v1_1_13 -L processing_system7_vip_v1_0_15 -L xilinx_vip "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/9736/hdl/i2s_receiver_v1_0_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L i2s_receiver_v1_0_5 -L i2s_transmitter_v1_0_5 -L axi_vip_v1_1_13 -L processing_system7_vip_v1_0_15 -L xilinx_vip "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_i2s_receiver_0_0/sim/design_1_i2s_receiver_0_0.sv" \

vlog -work xlconcat_v2_1_4  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/4b67/hdl/xlconcat_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xlconcat_0_0/sim/design_1_xlconcat_0_0.v" \

vlog -work xlslice_v1_0_2  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/11d0/hdl/xlslice_v1_0_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xlslice_0_0/sim/design_1_xlslice_0_0.v" \

vlog -work xlconstant_v1_1_7  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/badb/hdl/xlconstant_v1_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xlconstant_0_0/sim/design_1_xlconstant_0_0.v" \
"../../../bd/design_1/ip/design_1_xlconcat_2_0/sim/design_1_xlconcat_2_0.v" \
"../../../bd/design_1/ip/design_1_system_ila_0_0/bd_0/sim/bd_f60c.v" \
"../../../bd/design_1/ip/design_1_system_ila_0_0/bd_0/ip/ip_0/sim/bd_f60c_ila_lib_0.v" \
"../../../bd/design_1/ip/design_1_system_ila_0_0/sim/design_1_system_ila_0_0.v" \
"../../../bd/design_1/sim/design_1.v" \

vlog -work axi_protocol_converter_v2_1_27  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/aeb3/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_auto_pc_8/sim/design_1_auto_pc_8.v" \

vlog -work axi_clock_converter_v2_1_26  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b8be/hdl/axi_clock_converter_v2_1_vl_rfs.v" \

vlog -work blk_mem_gen_v8_4_5  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/25a8/simulation/blk_mem_gen_v8_4.v" \

vlog -work axi_dwidth_converter_v2_1_27  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
"../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/4675/hdl/axi_dwidth_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/ee60/hdl" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/7698" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/1b7e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/122e/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/b205/hdl/verilog" "+incdir+../../../../SimpleMixer_New.gen/sources_1/bd/design_1/ipshared/fd26/hdl/verilog" "+incdir+C:/Xilinx/Vivado/2022.2/data/xilinx_vip/include" \
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

