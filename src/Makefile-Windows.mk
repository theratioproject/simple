#Build simple `Dynamic Modules` for WINDOWS 
# PARSER
#
#Tools Needed
#	MINGWN 
#
#Or any ANSI C development tool that support building with
#a custome make file. The below command is for a typical 
#make in the MINGW Toolchain
#
#cd to the modules/dynamic_modules/parser/  folder. 
#
#This is to ensure That the output generated are in 
#appropriate `dist` folder in modules folder. 
#Execute the below command in your command prompt of bash
#
#modules/dynamic_modules/parser/ $ make -f Makefile-Windows.mk

# Environment
MKDIR=mkdir
GREP=grep
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++

# Flags
CFLAGS=
CCFLAGS=
CXXFLAGS=

# Macros
CND_PLATFORM=Windows
CND_DLIB_EXT=dll
CND_DEXE_EXT=exe
CND_BUILDDIR=build
CND_DISTDIR=../../dist

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
	${OBJECTDIR}/sources/simple_parser.o \
	${OBJECTDIR}/sources/simple_scanner.o \
	${OBJECTDIR}/sources/simple_state.o \
	${OBJECTDIR}/sources/simple_stmt.o \
	${OBJECTDIR}/sources/simple_string.o \
	${OBJECTDIR}/sources/simple_vm.o \
	${OBJECTDIR}/sources/simple_vmblock.o \
	${OBJECTDIR}/sources/simple_vmdll.o \
	${OBJECTDIR}/sources/simple_vmexpr.o \
	${OBJECTDIR}/sources/simple_vmgc.o \
	${OBJECTDIR}/sources/simple_vmlists.o \
	${OBJECTDIR}/sources/simple_vmoop.o \
	${OBJECTDIR}/sources/simple_vmperformance.o \
	${OBJECTDIR}/sources/simple_vmstackvars.o \
	${OBJECTDIR}/sources/simple_vmstate.o \
	${OBJECTDIR}/sources/simple_vmstrindex.o \
	${OBJECTDIR}/sources/simple_vmvars.o
	
# Link Libraries and Options
LDLIBSOPTIONS=

#${CND_DISTDIR}/${CND_PLATFORM}/parser.${CND_DLIB_EXT}: ../../../simple/src/dist/Debug/MinGW-Windows/simple.dll

${CND_DISTDIR}/${CND_PLATFORM}/parser.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_PLATFORM}/parser.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared

${CND_DISTDIR}/${CND_PLATFORM}/simple.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_PLATFORM}/simple.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -static-libgcc -shared

${OBJECTDIR}/sources/simple_api.o: sources/simple_api.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_api.o sources/simple_api.c

${OBJECTDIR}/sources/simple_codegen.o: sources/simple_codegen.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_codegen.o sources/simple_codegen.c

${OBJECTDIR}/sources/simple_expr.o: sources/simple_expr.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_expr.o sources/simple_expr.c

${OBJECTDIR}/sources/simple_hashtable.o: sources/simple_hashtable.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_hashtable.o sources/simple_hashtable.c

${OBJECTDIR}/sources/simple_item.o: sources/simple_item.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_item.o sources/simple_item.c

${OBJECTDIR}/sources/simple_list.o: sources/simple_list.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_list.o sources/simple_list.c

${OBJECTDIR}/sources/simple_misc.o: sources/simple_misc.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_misc.o sources/simple_misc.c

${OBJECTDIR}/sources/simple_parser.o: sources/simple_parser.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_parser.o sources/simple_parser.c

${OBJECTDIR}/sources/simple_scanner.o: sources/simple_scanner.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_scanner.o sources/simple_scanner.c

${OBJECTDIR}/sources/simple_state.o: sources/simple_state.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_state.o sources/simple_state.c

${OBJECTDIR}/sources/simple_stmt.o: sources/simple_stmt.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_stmt.o sources/simple_stmt.c

${OBJECTDIR}/sources/simple_string.o: sources/simple_string.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_string.o sources/simple_string.c

${OBJECTDIR}/sources/simple_vm.o: sources/simple_vm.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vm.o sources/simple_vm.c

${OBJECTDIR}/sources/simple_vmblock.o: sources/simple_vmblock.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmblock.o sources/simple_vmblock.c

${OBJECTDIR}/sources/simple_vmdll.o: sources/simple_vmdll.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmdll.o sources/simple_vmdll.c

${OBJECTDIR}/sources/simple_vmexpr.o: sources/simple_vmexpr.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmexpr.o sources/simple_vmexpr.c

${OBJECTDIR}/sources/simple_vmgc.o: sources/simple_vmgc.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmgc.o sources/simple_vmgc.c

${OBJECTDIR}/sources/simple_vmlists.o: sources/simple_vmlists.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmlists.o sources/simple_vmlists.c

${OBJECTDIR}/sources/simple_vmoop.o: sources/simple_vmoop.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmoop.o sources/simple_vmoop.c

${OBJECTDIR}/sources/simple_vmperformance.o: sources/simple_vmperformance.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmperformance.o sources/simple_vmperformance.c

${OBJECTDIR}/sources/simple_vmstackvars.o: sources/simple_vmstackvars.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmstackvars.o sources/simple_vmstackvars.c

${OBJECTDIR}/sources/simple_vmstate.o: sources/simple_vmstate.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmstate.o sources/simple_vmstate.c

${OBJECTDIR}/sources/simple_vmstrindex.o: sources/simple_vmstrindex.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmstrindex.o sources/simple_vmstrindex.c

${OBJECTDIR}/sources/simple_vmvars.o: sources/simple_vmvars.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmvars.o sources/simple_vmvars.c


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

