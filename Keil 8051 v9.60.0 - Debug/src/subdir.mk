################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
A51_UPPER_SRCS += \
C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/SILABS_STARTUP.A51 

C_SRCS += \
../src/InitDevice.c \
../src/Interrupts.c \
../src/main.c 

OBJS += \
./src/InitDevice.OBJ \
./src/Interrupts.OBJ \
./src/SILABS_STARTUP.OBJ \
./src/main.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/%.OBJ: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/InitDevice.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8SB1/inc/SI_EFM8SB1_Register_Enums.h C:/Users/Yoshida_Lab/SimplicityStudio/v5_workspace/temperature_measurement/inc/InitDevice.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8SB1/inc/SI_EFM8SB1_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/Interrupts.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8SB1/inc/SI_EFM8SB1_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8SB1/inc/SI_EFM8SB1_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/SILABS_STARTUP.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/SILABS_STARTUP.A51 src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Assembler'
	AX51 "@$(patsubst %.OBJ,%.__ia,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/main.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8SB1/inc/SI_EFM8SB1_Register_Enums.h C:/Users/Yoshida_Lab/SimplicityStudio/v5_workspace/temperature_measurement/inc/InitDevice.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/EFM8SB1/inc/SI_EFM8SB1_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h


