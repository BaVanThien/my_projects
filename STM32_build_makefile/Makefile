all: build
GCC_DIR   :=  C:/toolchain/Arm_toolchain
OBJ_COPY  := $(GCC_DIR)/bin/arm-none-eabi-objcopy
CC  	  := $(GCC_DIR)/bin/arm-none-eabi-gcc
OUTPUT_DIR	:= ./Output
LINKER_DIR	:= ./Linker
# Include files
INC_DIRS 	:= ./Driver/Inc ./Core
INC_FILES   := $(foreach INC_DIR, $(INC_DIRS), $(wildcard $(INC_DIR)/*))

# Source files
SRC_DIRS	:= ./Driver/Src ./Core ./Startup
SRC_FILES   := $(foreach SRC_DIR, $(SRC_DIRS), $(wildcard $(SRC_DIR)/*))

# Object files
OBJ_FILES	:= $(patsubst %.c, %.o, $(notdir $(SRC_FILES)))
OBJ_PATHS	:= $(foreach OBJ_FILE, $(OBJ_FILES), $(OUTPUT_DIR)/$(OBJ_FILE))

# CC option for INC_DIRS
INC_DIRS_OPT:= $(foreach INC_DIR, $(INC_DIRS), -I$(INC_DIR))

# Compiler options
CHIP 		:= cortex-m3
CCFLAGS		:= -c -mcpu=$(CHIP) -mthumb -std=gnu11 -O0 $(INC_DIRS_OPT)

# Linker options
LDFLAGS		:= -nostdlib -T $(LINKER_DIR)/stm_ls.ld -Wl,-Map=Output/makefile.map

vpath %.c $(SRC_DIRS)

build: makefile.hex

print-%:
	@echo $($(subst print-,,$@))

clean:
	rm -f Output/*

%.o:%.c
	$(CC) $(CCFLAGS) -o $(OUTPUT_DIR)/$@ $^

makefile.elf:$(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $(OUTPUT_DIR)/$@ $(OBJ_PATHS)

makefile.hex:makefile.elf
	$(OBJ_COPY) -O ihex $(OUTPUT_DIR)/$^ $(OUTPUT_DIR)/$@