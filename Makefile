V=1
SOURCE_DIR=src
BUILD_DIR=build
ROM_NAME=testgame
include $(N64_INST)/include/n64.mk

all: $(ROM_NAME).z64
.PHONY: all

#####
# Fonts
#####
FONT_SOURCES := $(shell find assets/ -type f -name '*.ttf' | sort)
FONTS := $(FONT_SOURCES:assets/fonts/%.ttf=filesystem/%.font64)

filesystem/%.font64: assets/fonts/%.ttf
	@mkdir -p $(dir $@)
	@echo " [MKFONT] $@"
	mkfont -o filesystem "$<"

#####
# Textures
#####
TEX_SOURCES := $(shell find assets/ -type f -name '*.png' | sort)
TEXTURES := $(TEX_SOURCES:assets/textures/%.png=filesystem/%.sprite)

filesystem/%.sprite: assets/textures/%.png
	@mkdir -p $(dir %@)
	@echo " [MKSPRITE] $@"
	mksprite -o filesystem "$<"

#####
# Sources
#####
SOURCES := $(shell find src/ -type f -name '*.c' | sort)
SOURCE_OBJS := $(SOURCES:src/%.c=$(BUILD_DIR)/%.o)
OBJS := $(BUILD_DIR)/main.o $(SOURCE_OBJS)

filesystem/: $(FONTS) $(TEXTURES)
$(BUILD_DIR)/$(ROM_NAME).dfs: filesystem/ $(FONTS) $(TEXTURES)
$(BUILD_DIR)/$(ROM_NAME).elf: $(OBJS)

$(ROM_NAME).z64: N64_ROM_TITLE="Test Game"
$(ROM_NAME).z64: $(BUILD_DIR)/$(ROM_NAME).dfs

clean:
	rm -rf $(BUILD_DIR)/* *.z64
.PHONY: clean

run: $(ROM_NAME).z64
	 sc64deployer upload $(ROM_NAME).z64 --tv ntsc
.PHONY: run
emu: $(ROM_NAME).z64
	ares $(ROM_NAME).z64
.PHONY: emu

-include $(wildcard $(BUILD_DIR)/*.d)
