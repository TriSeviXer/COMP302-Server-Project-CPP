################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../network/web/DirectoryPage.cpp \
../network/web/ErrorPage.cpp \
../network/web/ProcPage.cpp \
../network/web/StatusPage.cpp \
../network/web/WebPage.cpp 

OBJS += \
./network/web/DirectoryPage.o \
./network/web/ErrorPage.o \
./network/web/ProcPage.o \
./network/web/StatusPage.o \
./network/web/WebPage.o 

CPP_DEPS += \
./network/web/DirectoryPage.d \
./network/web/ErrorPage.d \
./network/web/ProcPage.d \
./network/web/StatusPage.d \
./network/web/WebPage.d 


# Each subdirectory must supply rules for building sources it contributes
network/web/%.o: ../network/web/%.cpp network/web/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


