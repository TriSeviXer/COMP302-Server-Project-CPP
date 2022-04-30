################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../network/server/Server.cpp \
../network/server/Signal.cpp \
../network/server/SocketHandler.cpp 

OBJS += \
./network/server/Server.o \
./network/server/Signal.o \
./network/server/SocketHandler.o 

CPP_DEPS += \
./network/server/Server.d \
./network/server/Signal.d \
./network/server/SocketHandler.d 


# Each subdirectory must supply rules for building sources it contributes
network/server/%.o: ../network/server/%.cpp network/server/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


