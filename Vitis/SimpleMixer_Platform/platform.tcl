# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\AudioProcessing\Project\Repo\SimpleMixer\SW\Vitis\SimpleMixer_Platform\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\AudioProcessing\Project\Repo\SimpleMixer\SW\Vitis\SimpleMixer_Platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {SimpleMixer_Platform}\
-hw {D:\AudioProcessing\Project\Repo\SimpleMixer\SW\Vivado\exported\SimpleMixer_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {D:/AudioProcessing/Project/Repo/SimpleMixer/SW/Vitis}

platform write
platform generate -domains 
platform active {SimpleMixer_Platform}
platform generate
platform active {SimpleMixer_Platform}
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {zynq_fsbl}
platform generate -domains 
platform write
domain active {zynq_fsbl}
domain active {standalone_domain}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate -domains standalone_ps7_cortexa9_0 
