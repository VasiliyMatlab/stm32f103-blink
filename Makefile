# Директории
CURPATH := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BINPATH := $(CURPATH)bin
OBJPATH := $(CURPATH)build
LIBPATH := $(CURPATH)lib
INCPATH := $(CURPATH)include
SRCPATH := $(CURPATH)src
PROJECT := $(BINPATH)/executable

# Компилятор, линковщик
PREFIX ?= arm-none-eabi-
CC := $(PREFIX)gcc
LD := $(PREFIX)gcc
OBJCOPY := $(PREFIX)objcopy
SIZE := $(PREFIX)size

# Линкер-скрипт
# LDSCRIPT := $(SRCPATH)/mine.ld
LDSCRIPT := $(SRCPATH)/STM32F103C8TX_FLASH.ld

# Флаги компилятора
CFLAGS := -Os -g -std=c99
CFLAGS += -mthumb -mcpu=cortex-m3 -msoft-float -mfix-cortex-m3-ldrd
CFLAGS += -DSTM32F1 -MD -Wall -Wundef -Wextra -Wshadow
CFLAGS += -Wimplicit-function-declaration -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes
CFLAGS += -fno-common -ffunction-sections -fdata-sections

# Флаги линковщика
LDFLAGS := --static -Wall -Wextra
LDFLAGS += -mthumb -mcpu=cortex-m3 -msoft-float -mfix-cortex-m3-ldrd
LDFLAGS += -Wl,-Map=$(PROJECT).map
LDFLAGS += -Wl,--gc-sections

# Программа для прошивки FLASH-памяти
STFLASH := $(shell which st-flash)

# Исходники, объектники и библиотеки
SRCS := $(wildcard $(SRCPATH)/*.c)
SRCS_ASS += $(wildcard $(SRCPATH)/*.s)
OBJS := $(patsubst $(SRCPATH)/%.c, $(OBJPATH)/%.o, $(SRCS))
OBJS_ASS += $(patsubst $(SRCPATH)/%.s, $(OBJPATH)/%.o, $(SRCS_ASS))
LIBS := -lc -lgcc

all: start $(PROJECT).elf $(PROJECT).bin $(PROJECT).hex
	$(info Building is complete)

start:
	$(info Building is started)
	@ mkdir -pv $(BINPATH)
	@ mkdir -pv $(OBJPATH)

$(PROJECT).elf: $(OBJS) $(OBJS_ASS)
	$(LD) $(LDFLAGS) -T$(LDSCRIPT) $(OBJS) $(OBJS_ASS) -L$(LIBPATH) $(LIBS) -o $@
	$(SIZE) $@

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -Obinary $< $@

$(PROJECT).hex: $(PROJECT).elf
	$(OBJCOPY) -Oihex $< $@

$(OBJPATH)/%.o: $(SRCPATH)/%.c
	$(CC) $(CFLAGS) -I$(INCPATH) -c $< -o $@

$(OBJPATH)/%.o: $(SRCPATH)/%.s
	$(CC) $(CFLAGS) -I$(INCPATH) -c $< -o $@

clean:
	rm -rfv $(BINPATH) $(OBJPATH)

flash_rom:
	$(STFLASH) write $(PROJECT).bin 0x8000000

flash_ram:
	$(STFLASH) write $(PROJECT).bin 0x20000000

.PHONY: all start clean flash
