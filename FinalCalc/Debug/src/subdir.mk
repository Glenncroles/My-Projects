################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FinalCalc\ copy.cpp \
../src/FinalCalc.cpp 

OBJS += \
./src/FinalCalc\ copy.o \
./src/FinalCalc.o 

CPP_DEPS += \
./src/FinalCalc\ copy.d \
./src/FinalCalc.d 


# Each subdirectory must supply rules for building sources it contributes
src/FinalCalc\ copy.o: ../src/FinalCalc\ copy.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/FinalCalc copy.d" -MT"src/FinalCalc\ copy.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


