V=1
SOURCE_DIR=src
BUILD_DIR=build
ROM_NAME=testgame
BLENDER=blender
PYTHON=python
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
# Models
#####

MODEL_SOURCES := $(shell find assets/models -type f -name '*.blend' | sort)
MODELS := $(MODEL_SOURCES:assets/models/%.blend=filesystem/%.aemf)

filesystem/%.aemf: assets/models/%.blend
	@mkdir -p $(dir %@)
	@mkdir -p $(dir $(@:filesystem/%.aemf=$(BUILD_DIR)/asset_staging/%.aemf))
	@echo " [BLENDER CONVERT] $<"
	$(BLENDER) $< -b -P util/blender/convert_model.py --python-exit-code 1 -- $(@:filesystem/%.aemf=$(BUILD_DIR)/asset_staging/%.aemf)
	@echo " [MKMODEL] $@"
	mkasset -o filesystem $(@:filesystem/%.aemf=$(BUILD_DIR)/asset_staging/%.aemf)

#####
# Materials
#####
MATERIAL_SOURCES := $(shell find assets/materials -type f -name '*.json' | sort)
MATERIALS := $(MATERIAL_SOURCES:assets/materials/%.json=filesystem/%.amtl)

filesystem/%.amtl: assets/materials/%.json
	@mkdir -p $(dir %@)
	@mkdir -p $(dir $(@:filesystem/%.amtl=$(BUILD_DIR)/asset_staging/%.amtl))
	@echo " [MATERIAL CONVERT] $<"
	$(PYTHON) util/blender/convert_material.py $< $(@:filesystem/%.amtl=$(BUILD_DIR)/asset_staging/%.amtl)
	@echo " [MKMATERIAL] $@"
	mkasset -o filesystem $(@:filesystem/%.amtl=$(BUILD_DIR)/asset_staging/%.amtl)

#####
# Sources
#####
SOURCES := $(shell find src/ -type f -name '*.c' | sort)
SOURCE_OBJS := $(SOURCES:src/%.c=$(BUILD_DIR)/%.o)
OBJS := $(BUILD_DIR)/main.o $(SOURCE_OBJS)

filesystem/: $(FONTS) $(TEXTURES) $(MODELS) $(MATERIALS)
$(BUILD_DIR)/$(ROM_NAME).dfs: filesystem/ $(FONTS) $(TEXTURES) $(MODELS) $(MATERIALS)
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
