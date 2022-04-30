################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../network/utilities/ArgHandler.cpp \
../network/utilities/Logger.cpp \
../network/utilities/TimeHandler.cpp 

OBJS += \
./network/utilities/ArgHandler.o \
./network/utilities/Logger.o \
./network/utilities/TimeHandler.o 

CPP_DEPS += \
./network/utilities/ArgHandler.d \
./network/utilities/Logger.d \
./network/utilities/TimeHandler.d 


# Each subdirectory must supply rules for building sources it contributes
network/utilities/%.o: ../network/utilities/%.cpp network/utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


