# ===== TOOLCHAIN =====
CC = gcc
AS = nasm
LD = ld

# ===== FLAGS =====
CFLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector -nostdlib -c -Ikernel/includes
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

# ===== DIRECTORIES =====
SRC_DIRS = kernel
BUILD_DIR = build

# ===== AUTO SOURCES =====
C_SOURCES   = $(shell find $(SRC_DIRS) -name "*.c")
ASM_SOURCES = $(shell find $(SRC_DIRS) -name "*.asm")

# ===== OBJECTS =====
C_OBJECTS   = $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
ASM_OBJECTS = $(patsubst %.asm,$(BUILD_DIR)/%.o,$(ASM_SOURCES))

OBJECTS = \
build/kernel/kernel.o \
build/kernel/drivers/pic.o \
build/kernel/includes/shell.o \
build/kernel/includes/io.o \
build/kernel/includes/keyboard.o \
build/kernel/includes/string.o \
build/kernel/includes/terminal.o \
build/kernel/cpu/idt.o \
build/kernel/irq.o \
build/kernel/boot.o

# ===== TARGET =====
all: kernel.bin

# ===== LINK =====
kernel.bin: $(OBJECTS)
	@echo "🔗 Linking kernel..."
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

# ===== COMPILE C =====
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "⚙️  CC $<"
	$(CC) $(CFLAGS) $< -o $@

# ===== COMPILE ASM =====
$(BUILD_DIR)/%.o: %.asm
	@mkdir -p $(dir $@)
	@echo "⚙️  ASM $<"
	$(AS) $(ASFLAGS) $< -o $@

# ===== CLEAN =====
clean:
	rm -rf $(BUILD_DIR) kernel.bin

# ===== RUN (QEMU) =====
run: kernel.bin
	qemu-system-i386 -kernel kernel.bin