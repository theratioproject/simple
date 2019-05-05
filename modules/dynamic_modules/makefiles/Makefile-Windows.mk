#Build simple `Dynamic Modules` for WINDOWS 
#
#Tools Needed
#	MINGWN 
#
#Or any ANSI C development tool that support building with
#a custom make file. The below command is for a typical 
#~~$ make in the MINGW Toolchain
#
#cd to the modules/dynamic_modules/  folder. 
#
#This is to ensure That the output generated are in 
#appropriate `dist` folder in modules folder. 
#Execute the below command in your command prompt of bash
#
#modules/dynamic_modules $ make -f Makefile-Windows.mk
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

# Environment
MKDIR=mkdir
CP = cp
RMDIR=rmdir
RM=rm

# Macros
CND_PLATFORM=Windows
CND_DLIB_EXT=dll
CND_DISTDIR=../dist
CLEAN_DEBUGDIR=../../../s0.4.0-debug
DYNAMIC_MODULEDIR=.modules/dynamic_modules

clean: 
	cd ../archiver/ && $(MAKE) -f Makefile-Windows.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../file_savant/ && $(MAKE) -f Makefile-Windows.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../mathic/ && $(MAKE) -f Makefile-Windows.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../string_savant/ && $(MAKE) -f Makefile-Windows.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../simple_sqlite/ && $(MAKE) -f Makefile-Windows.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../systemic/ && $(MAKE) -f Makefile-Windows.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../core_dynamic_module/ && $(MAKE) -f Makefile-Windows.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../networker/ && $(MAKE) -f Makefile-Windows.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	cd ../security/ && $(MAKE) -f Makefile-Windows.mk ARC_FLAG=$(ARC_FLAG) ARC=$(ARC)
	
	${RM} ${CND_DISTDIR}/build/*.o
	${RM} ${CND_DISTDIR}/build/*.d
	${RM} ${CND_DISTDIR}/build/include/*.o
	${RM} ${CND_DISTDIR}/build/include/*.d
	${RMDIR} ${CND_DISTDIR}/build/includes
	${RMDIR} ${CND_DISTDIR}/build
	#${MKDIR} -p ${CLEAN_DEBUGDIR}/${DYNAMIC_MODULEDIR}
	#${CP} ${CND_DISTDIR}/${CND_PLATFORM}/*.${CND_DLIB_EXT} ${CLEAN_DEBUGDIR}/${DYNAMIC_MODULEDIR}


#This Makefile-Windows.mk was written in adaptation to the MINGW
#description using the Netbeans IDE Makefiles as Guide.
#
#If this make file does not work on your Windows PC or you use 
#alternative compiler e.g Visual Studio, Cygwin e.t.c feel free to 
#write your own Makefile and send us a pull request at 
#https://github.com/simple-lang/modules . Your make file must follow 
#the below format for request to be accepted
#
#File-Name : Makefile-Windows-{Compiler}-{WindowsVersion}.mk
#
#e.g Makefile-Windows-cygwin-Windows8.mk
#
#looking forward to your contribution
#Thank You

