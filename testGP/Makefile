TARGET=testGP
EXECUTABLE=testGP.elf

CC=arm-none-eabi-gcc
CCPP=arm-none-eabi-g++
LD=arm-none-eabi-ld
#LD=arm-none-eabi-gcc                                                           
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
OD=arm-none-eabi-objdump
OBJCOPY=arm-none-eabi-objcopy

SYSPERIPHDIR=$(CURDIR)/../Libraries/STM32F4xx_StdPeriph_Driver
CMSISDIR=$(CURDIR)/../Libraries/CMSIS/ST/STM32F4xx



INCLUDE=-I$(SYSPERIPHDIR)/inc
##INCLUDE+=-I$(CMSISDIR)/../Libraries/STM32F4xx_StdPeriph_Driver/inc
INCLUDE+=-I.
INCLUDE+=-I$(CMSISDIR)/Include
INCLUDE+=-I$(CURDIR)/../Libraries/CMSIS/Include

vpath %.s $(CURDIR)

vpath %.c $(CMSISDIR)/Source/Templates/ \
          $(SYSPERIPHDIR)/src/ \
          $(CURDIR)

vpath %.cpp $(CURDIR)




BUILD_DIR=$(CURDIR)/build
BIN_DIR=$(CURDIR)/binary
SRCCPP_DIR=$(CURDIR)/src


DEFS=-DUSE_STDPERIPH_DRIVER
CDEFS+=-DSTM32F4XX
CDEFS+=-DHSE_VALUE=8000000
CDEFS+=-D__FPU_PRESENT=1
CDEFS+=-D__FPU_USED=1
CDEFS+=-DARM_MATH_CM4

MCUFLAGS=-mcpu=cortex-m4 -mthumb
COMMONFLAGS=-O$(OPTLVL) $(DBG) -Wall


SRCCPP=main.cpp
SRCCPP+=TestClass.cpp
SRCCPP+=StringPrinter.cpp

SRC=Timer.c
#SRC+=itoa.c
SRC+=system_stm32f4xx.c
SRC+=misc.c
##SRC+=stm32f4xx_dma.c
SRC+=stm32f4xx_rcc.c
## SRC+=stm32f4xx_adc.c
#SRC+=stm32f4xx_exti.c
## SRC+=stm32f4xx_rng.c
## SRC+=stm32f4xx_can.c
#SRC+=stm32f4xx_flash.c
## SRC+=stm32f4xx_rtc.c
## SRC+=stm32f4xx_crc.c
## SRC+=stm32f4xx_fsmc.c
## SRC+=stm32f4xx_sdio.c
## SRC+=stm32f4xx_cryp_aes.c
SRC+=stm32f4xx_gpio.c
## SRC+=stm32f4xx_spi.c
## SRC+=stm32f4xx_cryp.c
## SRC+=stm32f4xx_hash.c
## SRC+=stm32f4xx_syscfg.c
## SRC+=stm32f4xx_cryp_des.c
## SRC+=stm32f4xx_hash_md5.c
## SRC+=stm32f4xx_tim.c
## SRC+=stm32f4xx_cryp_tdes.c
## SRC+=stm32f4xx_hash_sha1.c
SRC+=stm32f4xx_usart.c
## SRC+=stm32f4xx_dac.c
## SRC+=stm32f4xx_i2c.c
## SRC+=stm32f4xx_wwdg.c
## SRC+=stm32f4xx_dbgmcu.c
## SRC+=stm32f4xx_iwdg.c
## SRC+=stm32f4xx_dcmi.c
## SRC+=stm32f4xx_pwr.c

##TOOLCHAIN_ROOT=/home/gabriele/arm/arm-none-eabi/lib
##TOOLCHAIN_ROOT=/usr/lib/arm-none-eabi/lib
TOOLCHAIN_ROOT=/home/malle/arm/arm-none-eabi/lib


COMMONFLAGS=-fno-exceptions
#-fno-rtti -fno-exceptions
ASRC=startup_stm32f4xx.s
LINKER_SCRIPT:=$(CURDIR)/stm32_flash.ld

CFLAGS=$(COMMONFLAGS) $(MCUFLAGS) $(INCLUDE) $(CDEFS) -mfloat-abi=hard
##CFLAGS=$(INCLUDE)

LDLIBS=$(TOOLCHAIN_ROOT)/fpu/libc_s.a $(TOOLCHAIN_ROOT)/fpu/libm.a
LDFLAGS=$(COMMONFLAGS) -fno-exceptions -ffunction-sections -fdata-sections -nostartfiles -Wl,--gc-sections,-T$(LINKER_SCRIPT) -specs=rdimon.specs -u _printf_float -mfloat-abi=hard

OBJCPP = $(SRCCPP:%.cpp=$(BUILD_DIR)/%.o)
#OBJCPP = $($(SRCCPP_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

#OBJS=$(OBJ) $(CPPOBJ)


$(BUILD_DIR)/%.o: %.c
	@echo [CC] $(notdir $<)
	@$(CC) $(CFLAGS) $< -c -o $@

$(BUILD_DIR)/%.o: %.cpp
	@echo [CCPP] $(notdir $<)
	@$(CCPP) $(CFLAGS) $< -c -o $@

##	

all: $(OBJ) $(OBJCPP)
	@echo [AS] $(ASRC)
	@$(AS) -o $(ASRC:%.s=$(BUILD_DIR)/%.o) $(ASRC)
	@echo [LD] $(TARGET).elf
	@$(CC) -o $(BIN_DIR)/$(TARGET).elf $(LDFLAGS) $(OBJ) $(OBJCPP) $(ASRC:%.s=$(BUILD_DIR)/%.o) $(LDLIBS)
	@echo [OBJCOPY] $(TARGET).hex
	@echo [OBJCOPY] $(OBJCOPY) -O ihex $(BIN_DIR)/$(TARGET).elf $(BIN_DIR)/$(TARGET).hex
	@$(OBJCOPY) -O ihex $(BIN_DIR)/$(TARGET).elf $(BIN_DIR)/$(TARGET).hex
	@echo [OBJCOPY] $(TARGET).bin
	@$(OBJCOPY) -O binary $(BIN_DIR)/$(TARGET).elf $(BIN_DIR)/$(TARGET).bin

.PHONY: clean

clean:
	@echo [RM] OBJ
	@rm -f $(OBJ) 
	echo [RM] CPP OBJ
	@rm -f $(CPPOBJ)
	echo [RM] AOBJ
	@rm -f $(ASRC:%.s=$(BUILD_DIR)/%.o)
	@echo [RM] BIN
	@rm -f $(BIN_DIR)/$(TARGET).elf
	@rm -f $(BIN_DIR)/$(TARGET).hex
	@rm -f $(BIN_DIR)/$(TARGET).bin