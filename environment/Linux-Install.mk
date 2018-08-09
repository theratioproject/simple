#
#
#You are not expected to touch this make file directly as it does not 
#build program but just install simple environment programs
#
#This make file installs the following environments
#
#	simplerepl
#	simplepad
#	modular
#	bake
#	webworker
#	simplebridge
#
ifeq ($(PREFIX),)
    PREFIX := /usr/
endif

# Macros
SIMPLE=simple
SUDO=
ENV_PATH=./
SIMPLE_H="$(DESTDIR)$(PREFIX)include/simple/simple.h"
LIB_PATH=-lsimple
BAKE=$(ENV_PATH)/bake/bake.sim
VERSION=s0.3.36-debug
CND_PLATFORM=Linux
ENV_DISTDIR=./dist

clean: 
	mkdir -p $(ENV_DISTDIR)
	$(SUDO) $(SIMPLE) $(BAKE) -F/$(ENV_DISTDIR) --lib $(LIB_PATH) -sh $(SIMPLE_H) $(ARC_FLAG) $(ENV_PATH)/simplerepl/simplerepl.sim
	$(SUDO) $(SIMPLE) $(BAKE) -F/$(ENV_DISTDIR) --lib $(LIB_PATH) -sh $(SIMPLE_H) $(ARC_FLAG) $(ENV_PATH)/modular/modular.sim
	$(SUDO) $(SIMPLE) $(BAKE) -F/$(ENV_DISTDIR) --lib $(LIB_PATH) -sh $(SIMPLE_H) $(ARC_FLAG) $(ENV_PATH)/simplepad/simplepad.sim
	$(SUDO) $(SIMPLE) $(BAKE) -F/$(ENV_DISTDIR) --lib $(LIB_PATH) -sh $(SIMPLE_H) $(ARC_FLAG) $(ENV_PATH)/simplebridge/simplebridge.sim
	$(SUDO) $(SIMPLE) $(BAKE) -F/$(ENV_DISTDIR) --lib $(LIB_PATH) -sh $(SIMPLE_H) $(ARC_FLAG) $(ENV_PATH)/webworker/webworker.sim
	$(SUDO) $(SIMPLE) $(BAKE) -F/$(ENV_DISTDIR) --lib $(LIB_PATH) -sh $(SIMPLE_H) $(ARC_FLAG) $(BAKE)
	cp $(ENV_PATH)/simplebridge/contents.sim $(ENV_DISTDIR)

.PHONY: install
install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install $(ENV_DISTDIR)/* $(DESTDIR)$(PREFIX)/bin/
	rm -r -f $(ENV_DISTDIR)
	
.PHONY: uninstall
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/simplerepl
	rm -f $(DESTDIR)$(PREFIX)/bin/simplepad
	rm -f $(DESTDIR)$(PREFIX)/bin/simplebridge
	rm -f $(DESTDIR)$(PREFIX)/bin/modular
	rm -f $(DESTDIR)$(PREFIX)/bin/bake
	rm -f $(DESTDIR)$(PREFIX)/bin/webworker

#If this make file does not work on your Windows PC or you use 
#alternative compiler e.g Visual Studio, Cygwin e.t.c feel free to 
#write your own Makefile and send us a pull request at 
#https://github.com/simple-lang/modules . Your make file must follow 
#the below format for request to be accepted
#
#File-Name : Makefile-Linux-{Compiler}-{WindowsVersion}.mk
#
#e.g Makefile-Linux-cygwin-Windows8.mk
#
#looking forward to your contribution
#Thank You

