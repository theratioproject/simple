#Build simple `Dynamic Modules` for LINUX
#
#There is no tool or dependency needed on a typical linux
#installation. To build the simple.so and simple change your
#directory to the modules/dynamic_modules/consoler/ folder 
#
#user $ cd modules/dynamic_modules/makefiles/
#
#This is to ensure That the output generated are in 
#appropriate `dist` folder in modules folder. 
#Execute the below command in your command prompt of bash
#
#modules/dynamic_modules/makefiles/ $ make -f Makefile-Linux.mk
#
#This make file generate dynamic library for the following 
#dynamic libraries
#
#	archiver
#	file_savant
#	mathic
#	string_savant
#	networker
#	security
#	simple_sqlite
#	systemic
#	core_dynamic_module
#	fulltick
#
#if you are modifying this file always build fulltick last

# Environment
MKDIR=mkdir
CP = cp
RMDIR=rmdir
RM=rm
MAKE=make

# Macros
VERSION=s0.4.0
CND_PLATFORM=Linux
CND_DLIB_EXT=so
CND_DISTDIR=../dist
MODULE_BASE=../../
CLEAN_DEBUGDIR=../../../$(VERSION)-debug
DYNAMIC_MODULEDIR=modules/dynamic_modules

ifeq ($(PREFIX),)
    PREFIX := /usr/
endif

clean: 
	cd ../archiver/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../file_savant/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../mathic/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../string_savant/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../networker/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../security/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../simple_sqlite/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../systemic/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../core_dynamic_module/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../fulltick/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	
	${RM} ${CND_DISTDIR}/build/*.o
	${RMDIR} ${CND_DISTDIR}/build

.PHONY: termux
termux: 
	cd ../archiver/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../file_savant/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../mathic/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../string_savant/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../networker/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../security/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC) "LDLIBSOPTIONS=-lssl -lcrypto"
	cd ../simple_sqlite/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../systemic/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../core_dynamic_module/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	#cd ../fulltick/ && $(MAKE) -f Makefile-Linux.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	
	${RM} ${CND_DISTDIR}/build/*.o
	${RMDIR} ${CND_DISTDIR}/build

.PHONY: install
install:
	mkdir -p /var/lib/simple/$(VERSION)/docs/
	mkdir -p /var/lib/simple/$(VERSION)/modules/
	mkdir -p /var/lib/simple/$(VERSION)/modules/dynamic_modules/
	install $(CND_DISTDIR)/*.so* /var/lib/simple/$(VERSION)/modules/dynamic_modules/
	install $(MODULE_BASE)/modules-dependencies.conf /var/lib/simple/$(VERSION)/modules/
	cp -R $(MODULE_BASE)/archive /var/lib/simple/$(VERSION)/modules/
	cp -R $(MODULE_BASE)/fulltick /var/lib/simple/$(VERSION)/modules/
	cp -R $(MODULE_BASE)/parser /var/lib/simple/$(VERSION)/modules/
	cp -R $(MODULE_BASE)/simple /var/lib/simple/$(VERSION)/modules/
	cp -R $(MODULE_BASE)/web /var/lib/simple/$(VERSION)/modules/
	cp -R $(MODULE_BASE)/parser /var/lib/simple/$(VERSION)/modules/
	chmod -R 777 /var/lib/simple/
	rm -r -f $(CND_DISTDIR)/
	
#We should not remove the main simple directory because it might contain 
#other simple-lang dependencies and modules for another version
#rm -r -f /var/lib/simple/

.PHONY: uninstall
uninstall:
	rm -r -f /var/lib/simple/$(VERSION)/modules/dynamic_modules/
	rm -r -f /var/lib/simple/$(VERSION)/modules/
	rm -r -f /var/lib/simple/$(VERSION)/

.PHONY: uninstall-termux
uninstall-termux:
	rm -r -f $(PREFIX)/var/lib/simple/$(VERSION)/modules/dynamic_modules/
	rm -r -f $(PREFIX)/var/lib/simple/$(VERSION)/modules/
	rm -r -f $(PREFIX)/var/lib/simple/$(VERSION)/

#If this makefile does not work on your Windows PC or you use 
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

