PROGRAM_NAME := simple
VER := 0.3.36
DIST := ../dist
BUILD_DIR := $(DIST)/build
SOURCE_DIR := ../sources
SOURCE_FILES := $(wildcard $(SOURCE_DIR)/*.c)
OBJECT_FILES := $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCE_FILES:%.c=%.o)))
HEADER_FILES := ../includes/.
SIMPLE_LIB := lib$(PROGRAM_NAME).dylib
ENTRY_FILE := ../simple.c
LIB_FLAGS := -lm -ldl
USR_LOCAL := /usr/local
DISABLE_WARNING_FLAG := -Wno-parentheses-equality
RUNTIME_LIB_PATH_FLAGS := -Wl,-rpath,$(USR_LOCAL)/lib -Wl,-rpath,./
COMPILE_TIME_LIB_PATH_FLAG := -L$(DIST)
PATH_FLAGS := $(COMPILE_TIME_LIB_PATH_FLAG) $(RUNTIME_LIB_PATH_FLAGS)
LINK_FLAGS := -shared
RELOCATION_FLAG := -fPIC

# Folder creation commands
CREATE_BUILD_DIR := mkdir -p $(DIST)/build

# Compile commands
COMPILE_OBJECT_FILES = $(CC) $(DISABLE_WARNING_FLAG) $(RELOCATION_FLAG) $< -c -o $@
COMPILE_LIBRARY := $(CC) $(LINK_FLAGS) $(OBJECT_FILES) $(LIB_FLAGS) -o $(DIST)/$(SIMPLE_LIB)
COMPILE_EXECUTABLE := $(CC) $(PATH_FLAGS) $(ENTRY_FILE) -l$(PROGRAM_NAME) -o $(DIST)/$(PROGRAM_NAME)

# .SILENT:

$(shell $(CREATE_BUILD_DIR))

$(BUILD_DIR)/%.o:$(SOURCE_DIR)/%.c
	$(COMPILE_OBJECT_FILES)

$(DIST)/$(PROGRAM_NAME): $(OBJECT_FILES)
	$(COMPILE_LIBRARY)
	$(COMPILE_EXECUTABLE)

build: $(OBJECT_FILES) $(DIST)/$(PROGRAM_NAME)

install: $(OBJECT_FILES) $(DIST)/$(PROGRAM_NAME)
	echo $(USR_LOCAL)
	# Add executable to /usr/local/bin
	cp $(DIST)/$(PROGRAM_NAME) $(USR_LOCAL)/bin/$(PROGRAM_NAME)
	# Add library to /usr/local/lib
	cp $(DIST)/$(SIMPLE_LIB) $(USR_LOCAL)/lib/$(SIMPLE_LIB)
	# Add header files to /usr/local/include/simple
	cp -a $(HEADER_FILES) $(USR_LOCAL)/include/$(PROGRAM_NAME)

clean:
	rm -rf $(DIST)
	$(CREATE_BUILD_DIR)

uninstall:
	# Remove executable from /usr/local/bin
	rm -f $(USR_LOCAL)/bin/$(PROGRAM_NAME)
	# Remove library from /usr/local/lib
	rm -f $(USR_LOCAL)/lib/$(SIMPLE_LIB)
	# Remove header files from /usr/local/include/simple
	rm -rf $(USR_LOCAL)/include/$(PROGRAM_NAME)

run:
	$(PROGRAM_NAME)


all: uninstall clean install clean run
.PHONY: build all uninstall install clean run
