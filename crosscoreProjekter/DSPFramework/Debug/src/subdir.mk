################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ISR.c \
../src/Init.c 

CPP_SRCS += \
../src/AlgoTester.cpp \
../src/Algorithm.cpp \
../src/Application.cpp \
../src/Controller.cpp \
../src/Equalizer.cpp \
../src/IIRFilter.cpp \
../src/Process.cpp \
../src/Switch.cpp 

SRC_OBJS += \
./src/AlgoTester.doj \
./src/Algorithm.doj \
./src/Application.doj \
./src/Controller.doj \
./src/Equalizer.doj \
./src/IIRFilter.doj \
./src/ISR.doj \
./src/Init.doj \
./src/Process.doj \
./src/Switch.doj 

C_DEPS += \
./src/ISR.d \
./src/Init.d 

CPP_DEPS += \
./src/AlgoTester.d \
./src/Algorithm.d \
./src/Application.d \
./src/Controller.d \
./src/Equalizer.d \
./src/IIRFilter.d \
./src/Process.d \
./src/Switch.d 


# Each subdirectory must supply rules for building sources it contributes
src/AlgoTester.doj: ../src/AlgoTester.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn.exe -c -file-attr ProjectName="DSPFramework" -proc ADSP-BF533 -flags-compiler --no_wrap_diagnostics -si-revision 0.6 -g -DCORE0 -D_DEBUG @includes-1008d643b9673470d04cc6846373457f.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "src/AlgoTester.d" -c++ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Algorithm.doj: ../src/Algorithm.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn.exe -c -file-attr ProjectName="DSPFramework" -proc ADSP-BF533 -flags-compiler --no_wrap_diagnostics -si-revision 0.6 -g -DCORE0 -D_DEBUG @includes-1008d643b9673470d04cc6846373457f.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "src/Algorithm.d" -c++ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Application.doj: ../src/Application.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn.exe -c -file-attr ProjectName="DSPFramework" -proc ADSP-BF533 -flags-compiler --no_wrap_diagnostics -si-revision 0.6 -g -DCORE0 -D_DEBUG @includes-1008d643b9673470d04cc6846373457f.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "src/Application.d" -c++ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Controller.doj: ../src/Controller.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn.exe -c -file-attr ProjectName="DSPFramework" -proc ADSP-BF533 -flags-compiler --no_wrap_diagnostics -si-revision 0.6 -g -DCORE0 -D_DEBUG @includes-1008d643b9673470d04cc6846373457f.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "src/Controller.d" -c++ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Equalizer.doj: ../src/Equalizer.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn.exe -c -file-attr ProjectName="DSPFramework" -proc ADSP-BF533 -flags-compiler --no_wrap_diagnostics -si-revision 0.6 -g -DCORE0 -D_DEBUG @includes-1008d643b9673470d04cc6846373457f.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "src/Equalizer.d" -c++ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/IIRFilter.doj: ../src/IIRFilter.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn.exe -c -file-attr ProjectName="DSPFramework" -proc ADSP-BF533 -flags-compiler --no_wrap_diagnostics -si-revision 0.6 -g -DCORE0 -D_DEBUG @includes-1008d643b9673470d04cc6846373457f.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "src/IIRFilter.d" -c++ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ISR.doj: ../src/ISR.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn.exe -c -file-attr ProjectName="DSPFramework" -proc ADSP-BF533 -flags-compiler --no_wrap_diagnostics -si-revision 0.6 -g -DCORE0 -D_DEBUG @includes-1008d643b9673470d04cc6846373457f.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "src/ISR.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Init.doj: ../src/Init.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn.exe -c -file-attr ProjectName="DSPFramework" -proc ADSP-BF533 -flags-compiler --no_wrap_diagnostics -si-revision 0.6 -g -DCORE0 -D_DEBUG @includes-1008d643b9673470d04cc6846373457f.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "src/Init.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Process.doj: ../src/Process.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn.exe -c -file-attr ProjectName="DSPFramework" -proc ADSP-BF533 -flags-compiler --no_wrap_diagnostics -si-revision 0.6 -g -DCORE0 -D_DEBUG @includes-1008d643b9673470d04cc6846373457f.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "src/Process.d" -c++ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Switch.doj: ../src/Switch.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn.exe -c -file-attr ProjectName="DSPFramework" -proc ADSP-BF533 -flags-compiler --no_wrap_diagnostics -si-revision 0.6 -g -DCORE0 -D_DEBUG @includes-1008d643b9673470d04cc6846373457f.txt -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "src/Switch.d" -c++ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


