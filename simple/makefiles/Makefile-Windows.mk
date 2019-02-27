#Build simple for WINDOWS 
# SIMPLE
#
#Tools Needed
#	MINGWN 
#
#Or any ANSI C development tool that support building with
#a custome make file. The below command is for a typical 
#make in the MINGW Toolchain
#
#user $ cd simple/src/makefiles/   
#
#This is to ensure That the output generated are in 
#appropriate `dist` folder in modules folder. 
#Execute the below command in your command prompt of bash
#
#simple/src/makefiles/ $ make -f Makefile-Windows.mk

# Environment
MKDIR=mkdir
RMDIR=rmdir
CP=CP
RM=rm
GREP=grep
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
AR=ar

# Flags
CLFLAGS= -lm -ldl
CCFLAGS=
CXXFLAGS=
AR_FLAGS=rcs

# Macros
VERSION=s0.4.0
CND_PLATFORM=
CND_DLIB_EXT=dll
CND_DEXE_EXT=exe
CND_BUILDDIR=build
CND_DISTDIR=../dist
CLEAN_DEBUGDIR=../../../s0.4.0-debug
BINARYDIR=bin

# Object Directory
OBJECTDIR=${CND_DISTDIR}/${CND_BUILDDIR}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/sources/simple_api.o \
	${OBJECTDIR}/sources/simple_codegen.o \
	${OBJECTDIR}/sources/simple_expr.o \
	${OBJECTDIR}/sources/simple_hashtable.o \
	${OBJECTDIR}/sources/simple_item.o \
	${OBJECTDIR}/sources/simple_list.o \
	${OBJECTDIR}/sources/simple_misc.o \
	${OBJECTDIR}/sources/simple_object.o \
	${OBJECTDIR}/sources/simple_parser.o \
	${OBJECTDIR}/sources/simple_scanner.o \
	${OBJECTDIR}/sources/simple_state.o \
	${OBJECTDIR}/sources/simple_stmt.o \
	${OBJECTDIR}/sources/simple_string.o \
	${OBJECTDIR}/sources/simple_vm.o \
	${OBJECTDIR}/sources/simple_vmblock.o \
	${OBJECTDIR}/sources/simple_vmexpr.o \
	${OBJECTDIR}/sources/simple_vmgc.o \
	${OBJECTDIR}/sources/simple_vmlists.o \
	${OBJECTDIR}/sources/simple_vmoop.o \
	${OBJECTDIR}/sources/simple_vmperformance.o \
	${OBJECTDIR}/sources/simple_vmstackvars.o \
	${OBJECTDIR}/sources/simple_vmstate.o \
	${OBJECTDIR}/sources/simple_vmstrindex.o \
	${OBJECTDIR}/sources/simple_vmvars.o
	
# Simple Object File
SIMPLE_OBJECTFILES= \
	${OBJECTDIR}/simple.o
	
# Windows Simple Object File
SIMPLEW_OBJECTFILES= \
	${OBJECTDIR}/simplew.o
	
# Link Libraries and Options
LDLIBSOPTIONS=${CND_DISTDIR}/${CND_PLATFORM}/libsimple.${CND_DLIB_EXT}	

${CND_DISTDIR}/${CND_PLATFORM}/simple.${CND_DEXE_EXT}: ${OBJECTFILES} ${SIMPLEW_OBJECTFILES} ${SIMPLE_OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_PLATFORM}
	${LINK.c} $(ARC_FLAG) -o ${CND_DISTDIR}/${CND_PLATFORM}/libsimple.${CND_DLIB_EXT} ${OBJECTFILES} -static-libgcc -shared
	${LINK.c} -mwindows $(ARC_FLAG) -o ${CND_DISTDIR}/${CND_PLATFORM}/simplew.${CND_DEXE_EXT} ${SIMPLEW_OBJECTFILES} ${LDLIBSOPTIONS}
	${LINK.c} $(ARC_FLAG) -o ${CND_DISTDIR}/${CND_PLATFORM}/simple.${CND_DEXE_EXT} ${SIMPLE_OBJECTFILES} ${LDLIBSOPTIONS}
	${LINK.c} $(ARC_FLAG) -o ${CND_DISTDIR}/${CND_PLATFORM}/simple.${CND_DEXE_EXT} ${SIMPLE_OBJECTFILES} ${LDLIBSOPTIONS}
	${AR} ${AR_FLAGS} ${CND_DISTDIR}/${CND_PLATFORM}/libsimple.a ${OBJECTFILES}
	
	#Removing Build File(s)
	${RM} ${OBJECTDIR}/sources/*.o
	${RM} ${OBJECTDIR}/sources/*.d
	${RM} ${OBJECTDIR}/*.o
	${RM} ${OBJECTDIR}/*.d
	${RMDIR} ${OBJECTDIR}/sources
	${RMDIR} ${OBJECTDIR}
	
	#Copy the Generated Binary to debug folder 
	#${MKDIR} -p ${CLEAN_DEBUGDIR}/${BINARYDIR}
	#${CP} ${CND_DISTDIR}/${CND_PLATFORM}/* ${CLEAN_DEBUGDIR}/${BINARYDIR}

${OBJECTDIR}/sources/simple_api.o: ../sources/simple_api.c
	${MKDIR} -p ${OBJECTDIR}/sources
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_api.o ../sources/simple_api.c

${OBJECTDIR}/sources/simple_codegen.o: ../sources/simple_codegen.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_codegen.o ../sources/simple_codegen.c

${OBJECTDIR}/sources/simple_expr.o: ../sources/simple_expr.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_expr.o ../sources/simple_expr.c

${OBJECTDIR}/sources/simple_hashtable.o: ../sources/simple_hashtable.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_hashtable.o ../sources/simple_hashtable.c

${OBJECTDIR}/sources/simple_item.o: ../sources/simple_item.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_item.o ../sources/simple_item.c

${OBJECTDIR}/sources/simple_list.o: ../sources/simple_list.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_list.o ../sources/simple_list.c

${OBJECTDIR}/sources/simple_misc.o: ../sources/simple_misc.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_misc.o ../sources/simple_misc.c

${OBJECTDIR}/sources/simple_object.o: ../sources/simple_object.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_object.o ../sources/simple_object.c

${OBJECTDIR}/sources/simple_parser.o: ../sources/simple_parser.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_parser.o ../sources/simple_parser.c

${OBJECTDIR}/sources/simple_scanner.o: ../sources/simple_scanner.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_scanner.o ../sources/simple_scanner.c

${OBJECTDIR}/sources/simple_state.o: ../sources/simple_state.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_state.o ../sources/simple_state.c

${OBJECTDIR}/sources/simple_stmt.o: ../sources/simple_stmt.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_stmt.o ../sources/simple_stmt.c

${OBJECTDIR}/sources/simple_string.o: ../sources/simple_string.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_string.o ../sources/simple_string.c

${OBJECTDIR}/sources/simple_vm.o: ../sources/simple_vm.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_vm.o ../sources/simple_vm.c

${OBJECTDIR}/sources/simple_vmblock.o: ../sources/simple_vmblock.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_vmblock.o ../sources/simple_vmblock.c

${OBJECTDIR}/sources/simple_vmexpr.o: ../sources/simple_vmexpr.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_vmexpr.o ../sources/simple_vmexpr.c

${OBJECTDIR}/sources/simple_vmgc.o: ../sources/simple_vmgc.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_vmgc.o ../sources/simple_vmgc.c

${OBJECTDIR}/sources/simple_vmlists.o: ../sources/simple_vmlists.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_vmlists.o ../sources/simple_vmlists.c

${OBJECTDIR}/sources/simple_vmoop.o: ../sources/simple_vmoop.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_vmoop.o ../sources/simple_vmoop.c

${OBJECTDIR}/sources/simple_vmperformance.o: ../sources/simple_vmperformance.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_vmperformance.o ../sources/simple_vmperformance.c

${OBJECTDIR}/sources/simple_vmstackvars.o: ../sources/simple_vmstackvars.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_vmstackvars.o ../sources/simple_vmstackvars.c

${OBJECTDIR}/sources/simple_vmstate.o: ../sources/simple_vmstate.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_vmstate.o ../sources/simple_vmstate.c

${OBJECTDIR}/sources/simple_vmstrindex.o: ../sources/simple_vmstrindex.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_vmstrindex.o ../sources/simple_vmstrindex.c

${OBJECTDIR}/sources/simple_vmvars.o: ../sources/simple_vmvars.c
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/sources/simple_vmvars.o ../sources/simple_vmvars.c
	
${OBJECTDIR}/simple.o: ../simple.c
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" $(ARC_FLAG) -o ${OBJECTDIR}/simple.o ../simple.c
	
${OBJECTDIR}/simplew.o: ../simplew.c
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -mwindows $(ARC_FLAG) -o ${OBJECTDIR}/simplew.o ../simplew.c


#This Makefile-Windows.mk was written in adaptation to the MINGW
#description using the Netbeans IDE Makefiles as Guide.
#
#If this make file does not work on your Windows PC or you use 
#alternative compiler e.g Visual Studio, Cygwin e.t.c feel free to 
#write your own Makefile and send us a pull request at 
#https://github.com/simple-lang/simple . Your make file must follow 
#the below format for request to be accepted
#
#File-Name : Makefile-Windows-{Compiler}-{WindowsVersion}.mk
#
#e.g Makefile-Windows-cygwin-Windows8.mk
#
#looking forward to your contributions
#Thank You

