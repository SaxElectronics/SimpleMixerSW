# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: D:\AudioProcessing\Project\Repo\SimpleMixer\SW\Vitis\App_system\_ide\scripts\debugger_app-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source D:\AudioProcessing\Project\Repo\SimpleMixer\SW\Vitis\App_system\_ide\scripts\debugger_app-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Arty Z7 003017B5BD7AA" && level==0 && jtag_device_ctx=="jsn-Arty Z7-003017B5BD7AA-23727093-0"}
fpga -file D:/AudioProcessing/Project/Repo/SimpleMixer/SW/Vitis/SimpleMixer_Platform/hw/design_1_wrapper_I2S_master_LR_24bit.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw D:/AudioProcessing/Project/Repo/SimpleMixer/SW/Vitis/SimpleMixer_Platform/export/SimpleMixer_Platform/hw/design_1_wrapper_I2S_master_LR_24bit.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source D:/AudioProcessing/Project/Repo/SimpleMixer/SW/Vitis/App/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow D:/AudioProcessing/Project/Repo/SimpleMixer/SW/Vitis/App/Debug/App.elf
configparams force-mem-access 0
bpadd -addr &main
