# This makefiile generates the following dynamic libraries:
# - archiver
# - consoler
# - file_savant
# - mathic
# - string_savant
# - networker
# - parser
# - security
# - systemic
# - core_dynamic_module
# - fulltick

PROGRAM_NAME := simple
VER := 0.3.36
VAR_VER_DIR := /var/lib/$(PROGRAM_NAME)/s$(VER)
VAR_MODULE_DIR := $(VAR_VER_DIR)/modules
VAR_DYNAMIC_MODULES_DIR := $(VAR_MODULE_DIR)/dynamic_modules
DIST := ../dist
MODULE_DIR := ../..
DYNAMIC_MODULES_DIR := ..
DYNAMIC_MODULES_EXCLUDE := $(addprefix $(DYNAMIC_MODULES_DIR)/,dist makefiles)
DYNAMIC_MODULES_FOLDERS := $(filter-out $(DYNAMIC_MODULES_EXCLUDE), $(wildcard $(DYNAMIC_MODULES_DIR)/*))
OSNAME := $(shell uname)

ifeq ($(OSNAME), Darwin)
LIB_FILES := $(addprefix $(DIST)/,$(notdir $(DYNAMIC_MODULES_FOLDERS:%=%.dylib)))
else
LIB_FILES := $(addprefix $(DIST)/,$(notdir $(DYNAMIC_MODULES_FOLDERS:%=%.so)))
endif

# Folder creation commands
CREATE_BUILD_DIR := mkdir -p $(DIST)/build
CREATE_VAR_MODULE_DIR := mkdir -p $(VAR_DYNAMIC_MODULES_DIR) $(VAR_MODULE_DIR)/docs

# Compile commands
RECURSIVE_MAKE =  $(MAKE) -f Makefile-Unix.mk -C $(DYNAMIC_MODULES_DIR)/$*

# .SILENT:

$(DIST)/%.so: $(DYNAMIC_MODULES_DIR)/%
	$(RECURSIVE_MAKE)

$(DIST)/%.dylib: $(DYNAMIC_MODULES_DIR)/%
	$(RECURSIVE_MAKE)

build: $(LIB_FILES)

install: $(LIB_FILES)
	$(CREATE_VAR_MODULE_DIR)
	rsync -q -av $(MODULE_DIR) $(VAR_MODULE_DIR) --exclude README.md --exclude dynamic_modules
	rsync -q -av $(LIB_FILES) $(VAR_DYNAMIC_MODULES_DIR)
	chmod -R 777 /var/lib/$(PROGRAM_NAME)

clean:
	rm -rf $(DIST)
	$(CREATE_BUILD_DIR)

# NOTE:
#   We don't remove the main simple directory from /var/lib because it
#   it may contain dependencies and modules for another simple version
uninstall:
	rm -rf -f $(VAR_VER_DIR)

all: uninstall clean install clean
.PHONY: build all uninstall install clean
