################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Comp\ org.cpp 

OBJS += \
./src/Comp\ org.o 

CPP_DEPS += \
./src/Comp\ org.d 


# Each subdirectory must supply rules for building sources it contributes
src/Comp\ org.o: ../src/Comp\ org.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Comp org.d" -MT"src/Comp\ org.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


