PROGRAM_NAME := simple
VER := 0.3.36
DIST := ../dist
FILE := fulltick
BUILD_DIR := $(DIST)/build
USR_LOCAL_INCLUDE := /usr/local/include
SOURCE_DIR := .
SOURCE_FILES := $(wildcard $(SOURCE_DIR)/*.c $(SOURCE_DIR)/includes/*.cpp)
OBJECT_FILES := $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCE_FILES:%.cpp=%.o)))
DISABLE_WARNING_FLAG := -w # -Wno-implicit-function-declaration -Wno-int-conversion
LINK_FLAGS := -shared
LIB_FLAGS := -lpthread -ldl -lm -lfltk # -lfontconfig -lX11 -lXfixes -lXinerama -lXft
OTHER_FLAGS := -fpermissive -fvisibility-inlines-hidden -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D_THREAD_SAFE -D_REENTRANT
INCLUDE_FLAGS := -I$(USR_LOCAL_INCLUDE) -I$(USR_LOCAL_INCLUDE)/FL/images
RELOCATION_FLAG := -fPIC

OSNAME := $(shell uname)
ifeq ($(OSNAME), Darwin)
LIB_FILE := $(DIST)/$(FILE).dylib
else
LIB_FILE := $(DIST)/$(FILE).so
endif

# Dependency information
SIMPLE_MAIN_SOURCE_DIR := ../../../simple/sources
SIMPLE_MAIN_BUILD_DIR := ../../../simple/dist/build
SIMPLE_MAIN_MAKEFILES_DIR := ../../../simple/makefiles
SIMPLE_MAIN_SOURCE_FILES := $(wildcard $(SIMPLE_MAIN_SOURCE_DIR)/*.c)
SIMPLE_MAIN_OBJECT_FILES := $(addprefix $(SIMPLE_MAIN_BUILD_DIR)/,$(notdir $(SIMPLE_MAIN_SOURCE_FILES:%.c=%.o)))

# Folder creation commands
CREATE_BUILD_DIR := mkdir -p $(BUILD_DIR)

# Compile commands
COMPILE_LIBRARY := $(CXX) $(RELOCATION_FLAG) $(DISABLE_WARNING_FLAG) $(INCLUDE_FLAGS) $(LINK_FLAGS) $(LIB_FLAGS) $(SOURCE_FILES) -o $(LIB_FILE)
BUILD_SIMPLE_MAIN := $(MAKE) -f Makefile-Unix.mk -C $(SIMPLE_MAIN_MAKEFILES_DIR)

# .SILENT:

$(LIB_FILE): $(SOURCE_FILES)
	$(BUILD_SIMPLE_MAIN)
	$(CREATE_BUILD_DIR)
	$(COMPILE_OBJECT_FILE)
	$(COMPILE_LIBRARY)

build: $(LIB_FILE)

clean:
	rm -rf $(DIST)
	$(CREATE_BUILD_DIR)

all: build
.PHONY: build all uninstall run
