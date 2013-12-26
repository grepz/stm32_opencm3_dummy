PRODUCT = product_name

TOOLCHAIN_DIR = ~/arm-none-eabi/bin

LIBOPENCM3_DIR = /opt/libopencm3/arm-none-eabi
INCLUDE_DIRS = $(LIBOPENCM3_DIR)/include/libopencm3/

CC      = $(TOOLCHAIN_DIR)/arm-none-eabi-gcc
OBJCOPY = $(TOOLCHAIN_DIR)/arm-none-eabi-objcopy
LD      = $(TOOLCHAIN_DIR)/arm-none-eabi-ld

INCLUDE = $(addprefix -I,$(INCLUDE_DIRS))

DEFS =  -DSTM32F4
DEFS += -DAPP_LOAD_ADDRESS=0x08004000
DEFS += -DSTM32F4

CFLAGS = -O0
CFLAGS += -Wall -Wextra -Warray-bounds
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork

LIBS = -lopencm3_stm32f4

LFLAGS = --static -lc -lnosys -nostartfiles -Wl,--gc-sections
LFLAGS += -mthumb -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
LFLAGS += -Tstm32f4.ld -L$(LIBOPENCM3_DIR)/lib

FLAGS += -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Tstm32f4.ld

SRCS = bl.c led.c usb.c

all: $(PRODUCT)

$(PRODUCT): $(PRODUCT).elf

$(PRODUCT).elf: $(SRCS)
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) $(LFLAGS) $^ -o $@ $(LIBS)
	$(OBJCOPY) -O ihex $(PRODUCT).elf $(PRODUCT).hex
	$(OBJCOPY) -O binary $(PRODUCT).elf $(PRODUCT).bin

clean:
	rm -f *.elf *.bin *.hex *.o

$(ELF): $(SRCS)
	$(CC) -o $@ $(SRCS) $(FLAGS)

flash:
	st-flash write $(PRODUCT).bin 0x8000000

.PHONY: debug
debug:
	$(GDB) $(PRODUCT).elf
