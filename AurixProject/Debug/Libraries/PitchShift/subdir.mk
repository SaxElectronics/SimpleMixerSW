################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/PitchShift/PitchShift.c 

OBJS += \
./Libraries/PitchShift/PitchShift.o 

COMPILED_SRCS += \
./Libraries/PitchShift/PitchShift.src 

C_DEPS += \
./Libraries/PitchShift/PitchShift.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/PitchShift/%.src: ../Libraries/PitchShift/%.c Libraries/PitchShift/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc37x "-fD:/AudioProcessing/Project/Aurix_AudioAppKit-master/Examples/TC375 Lite Kit/ASB_SimpleAudioLoopback_TC375/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc37x -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/PitchShift/%.o: ./Libraries/PitchShift/%.src Libraries/PitchShift/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


