include mkenv.mk
include magic.mk

CFLAGS = -march=armv5te -mfloat-abi=soft -Wall \
	 -Os -ggdb -Iinclude -marm -fno-stack-protector
AFLAGS = 

LDFLAGS = --nostdlib -T autumn.ld
LIBS = lib/libgcc-armv5.a

SRC_C = \
	bionic.c \
	cmd-hex.c \
	cmd-peekpoke.c \
	cmd-load.c \
	hwinit.c \
	main.c \
	serial.c \
	utils.c \
	vectors.c \
	vsprintf.c

SRC_S = \
	start.S

OBJ = $(addprefix $(BUILD)/, $(SRC_S:.S=.o) $(SRC_C:.c=.o))

all: $(BUILD)/firmware.bin

clean:
	$(RM) -rf $(BUILD)

HEADER_BUILD = $(BUILD)/genhdr
$(BUILD)/firmware.bin: $(BUILD)/firmware.elf
	$(OBJCOPY) -S -O binary $(BUILD)/firmware.elf $@

$(BUILD)/firmware.elf: $(OBJ)
	$(LD) $(LDFLAGS) --entry=rv_start -o $@ $(OBJ) $(LIBS)

$(OBJ): $(HEADER_BUILD)/generated.h | $(OBJ_DIRS)
$(HEADER_BUILD)/generated.h: | $(HEADER_BUILD)
	  touch $@

OBJ_DIRS = $(sort $(dir $(OBJ)))
$(OBJ_DIRS):
	$(MKDIR) -p $@
$(HEADER_BUILD):
	$(MKDIR) -p $@
-include $(OBJ:.o=.P)
