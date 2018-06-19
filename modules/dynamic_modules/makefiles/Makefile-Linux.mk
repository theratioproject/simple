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
#	consoler
#	file_savant
#	mathic
#	string_savant
#	networker
#	parser
#	security
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
VERSION=s0.3.303
CND_PLATFORM=Linux
CND_DLIB_EXT=so
CND_DISTDIR=../dist
MODULE_BASE=../../
CLEAN_DEBUGDIR=../../../s0.3.303-debug
DYNAMIC_MODULEDIR=.modules/dynamic_modules

clean: 
	cd ../archiver/ && $(MAKE) -f Makefile-Linux.mk
	cd ../consoler/ && $(MAKE) -f Makefile-Linux.mk
	cd ../file_savant/ && $(MAKE) -f Makefile-Linux.mk
	cd ../mathic/ && $(MAKE) -f Makefile-Linux.mk
	cd ../string_savant/ && $(MAKE) -f Makefile-Linux.mk
	cd ../networker/ && $(MAKE) -f Makefile-Linux.mk
	cd ../parser/ && $(MAKE) -f Makefile-Linux.mk
	cd ../security/ && $(MAKE) -f Makefile-Linux.mk
	cd ../systemic/ && $(MAKE) -f Makefile-Linux.mk
	cd ../core_dynamic_module/ && $(MAKE) -f Makefile-Linux.mk
	cd ../fulltick/ && $(MAKE) -f Makefile-Linux.mk
	
	${RM} ${CND_DISTDIR}/build/*.o
	#${RM} ${CND_DISTDIR}/build/*.d
	#${RM} ${CND_DISTDIR}/build/includes/*.o
	#${RM} ${CND_DISTDIR}/build/includes/*.d
	#${RMDIR} ${CND_DISTDIR}/build/includes
	${RMDIR} ${CND_DISTDIR}/build
	#${MKDIR} -p ${CLEAN_DEBUGDIR}/${DYNAMIC_MODULEDIR}
	#${CP} ${CND_DISTDIR}/${CND_PLATFORM}/*.${CND_DLIB_EXT} ${CLEAN_DEBUGDIR}/${DYNAMIC_MODULEDIR}

.PHONY: install
install:
	mkdir -p $(DESTDIR)$(PREFIX)/simple/$(VERSION)/modules/
	mkdir -p $(DESTDIR)$(PREFIX)/simple/$(VERSION)/modules/dynamic_modules/
	install $(CND_DISTDIR)/*.so $(DESTDIR)$(PREFIX)/simple/$(VERSION)/modules/dynamic_modules/
	cp -R $(MODULE_BASE)/archive $(DESTDIR)$(PREFIX)/simple/$(VERSION)/modules/
	cp -R $(MODULE_BASE)/fulltick $(DESTDIR)$(PREFIX)/simple/$(VERSION)/modules/
	cp -R $(MODULE_BASE)/simple $(DESTDIR)$(PREFIX)/simple/$(VERSION)/modules/
	cp -R $(MODULE_BASE)/web $(DESTDIR)$(PREFIX)/simple/$(VERSION)/modules/

#ifeq ($(PREFIX),)
#    PREFIX := /usr/local
#endif
	
.PHONY: uninstall
uninstall:
	rm -r $(DESTDIR)$(PREFIX)/simple/$(VERSION)/modules/dynamic_modules/
	rm -r $(DESTDIR)$(PREFIX)/simple/$(VERSION)/modules/
	rm -r $(DESTDIR)$(PREFIX)/simple/$(VERSION)/
	rm -r $(DESTDIR)$(PREFIX)/simple/

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

