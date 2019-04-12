################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lab3/Vec.cpp \
../lab3/VecTester.cpp \
../lab3/tester.cpp 

OBJS += \
./lab3/Vec.o \
./lab3/VecTester.o \
./lab3/tester.o 

CPP_DEPS += \
./lab3/Vec.d \
./lab3/VecTester.d \
./lab3/tester.d 


# Each subdirectory must supply rules for building sources it contributes
lab3/%.o: ../lab3/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


