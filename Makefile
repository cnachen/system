PREFIX	= riscv64-unknown-elf
CC 	= $(PREFIX)-gcc
LD	= $(PREFIX)-ld
OBJCOPY	= $(PREFIX)-objcopy
QEMU	= qemu-system-riscv64
RM	= rm

K	= kern
U	= user
BUILD	= build

SFLAGS	= -g
CFLAGS	= -g -mcmodel=medany
QFLAGS	= -M virt -smp 4 -bios none -serial stdio -display none

SSRC	= $(wildcard $(K)/*.S)
CSRC	= $(wildcard $(K)/*.c)
SOBJ	= $(SSRC:$(K)/%.S=$(BUILD)/%.S.o)
COBJ	= $(CSRC:$(K)/%.c=$(BUILD)/%.o)

all: clean kernel.img

kernel.img: kernel.elf
	$(OBJCOPY) kernel.elf -I binary kernel.img

kernel.elf: $(SOBJ) $(COBJ) $(K)/kernel.ld
	$(LD) -T $(K)/kernel.ld -o kernel.elf $(SOBJ) $(COBJ)

$(BUILD)/%.o: $(K)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.S.o: $(K)/%.S
	$(CC) $(SFLAGS) -c $< -o $@

clean:
	$(RM) -f $(BUILD)/*.S.o $(BUILD)/*.o kernel.elf kernel.img

run: all
	$(QEMU) $(QFLAGS) -kernel kernel.img
