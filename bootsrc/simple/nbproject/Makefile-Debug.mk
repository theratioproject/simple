#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/sources/simple.o \
	${OBJECTDIR}/sources/simple_api.o \
	${OBJECTDIR}/sources/simple_codegen.o \
	${OBJECTDIR}/sources/simple_expr.o \
	${OBJECTDIR}/sources/simple_ext.o \
	${OBJECTDIR}/sources/simple_hashlib.o \
	${OBJECTDIR}/sources/simple_hashtable.o \
	${OBJECTDIR}/sources/simple_item.o \
	${OBJECTDIR}/sources/simple_items.o \
	${OBJECTDIR}/sources/simple_list.o \
	${OBJECTDIR}/sources/simple_objfile.o \
	${OBJECTDIR}/sources/simple_parser.o \
	${OBJECTDIR}/sources/simple_scanner.o \
	${OBJECTDIR}/sources/simple_state.o \
	${OBJECTDIR}/sources/simple_stmt.o \
	${OBJECTDIR}/sources/simple_string.o \
	${OBJECTDIR}/sources/simple_vm.o \
	${OBJECTDIR}/sources/simple_vmcui.o \
	${OBJECTDIR}/sources/simple_vmdll.o \
	${OBJECTDIR}/sources/simple_vmduprange.o \
	${OBJECTDIR}/sources/simple_vmexit.o \
	${OBJECTDIR}/sources/simple_vmexpr.o \
	${OBJECTDIR}/sources/simple_vmfile.o \
	${OBJECTDIR}/sources/simple_vmfuncs.o \
	${OBJECTDIR}/sources/simple_vmgc.o \
	${OBJECTDIR}/sources/simple_vmjump.o \
	${OBJECTDIR}/sources/simple_vmlistfuncs.o \
	${OBJECTDIR}/sources/simple_vmlists.o \
	${OBJECTDIR}/sources/simple_vmmath.o \
	${OBJECTDIR}/sources/simple_vmoop.o \
	${OBJECTDIR}/sources/simple_vmos.o \
	${OBJECTDIR}/sources/simple_vmperformance.o \
	${OBJECTDIR}/sources/simple_vmrefmeta.o \
	${OBJECTDIR}/sources/simple_vmstackvars.o \
	${OBJECTDIR}/sources/simple_vmstate.o \
	${OBJECTDIR}/sources/simple_vmstrindex.o \
	${OBJECTDIR}/sources/simple_vmtrycatch.o \
	${OBJECTDIR}/sources/simple_vmvars.o \
	${OBJECTDIR}/sources/simplew.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/simple.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/simple.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/simple ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/sources/simple.o: sources/simple.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple.o sources/simple.c

${OBJECTDIR}/sources/simple_api.o: sources/simple_api.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_api.o sources/simple_api.c

${OBJECTDIR}/sources/simple_codegen.o: sources/simple_codegen.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_codegen.o sources/simple_codegen.c

${OBJECTDIR}/sources/simple_expr.o: sources/simple_expr.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_expr.o sources/simple_expr.c

${OBJECTDIR}/sources/simple_ext.o: sources/simple_ext.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_ext.o sources/simple_ext.c

${OBJECTDIR}/sources/simple_hashlib.o: sources/simple_hashlib.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_hashlib.o sources/simple_hashlib.c

${OBJECTDIR}/sources/simple_hashtable.o: sources/simple_hashtable.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_hashtable.o sources/simple_hashtable.c

${OBJECTDIR}/sources/simple_item.o: sources/simple_item.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_item.o sources/simple_item.c

${OBJECTDIR}/sources/simple_items.o: sources/simple_items.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_items.o sources/simple_items.c

${OBJECTDIR}/sources/simple_list.o: sources/simple_list.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_list.o sources/simple_list.c

${OBJECTDIR}/sources/simple_objfile.o: sources/simple_objfile.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_objfile.o sources/simple_objfile.c

${OBJECTDIR}/sources/simple_parser.o: sources/simple_parser.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_parser.o sources/simple_parser.c

${OBJECTDIR}/sources/simple_scanner.o: sources/simple_scanner.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_scanner.o sources/simple_scanner.c

${OBJECTDIR}/sources/simple_state.o: sources/simple_state.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_state.o sources/simple_state.c

${OBJECTDIR}/sources/simple_stmt.o: sources/simple_stmt.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_stmt.o sources/simple_stmt.c

${OBJECTDIR}/sources/simple_string.o: sources/simple_string.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_string.o sources/simple_string.c

${OBJECTDIR}/sources/simple_vm.o: sources/simple_vm.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vm.o sources/simple_vm.c

${OBJECTDIR}/sources/simple_vmcui.o: sources/simple_vmcui.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmcui.o sources/simple_vmcui.c

${OBJECTDIR}/sources/simple_vmdll.o: sources/simple_vmdll.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmdll.o sources/simple_vmdll.c

${OBJECTDIR}/sources/simple_vmduprange.o: sources/simple_vmduprange.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmduprange.o sources/simple_vmduprange.c

${OBJECTDIR}/sources/simple_vmexit.o: sources/simple_vmexit.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmexit.o sources/simple_vmexit.c

${OBJECTDIR}/sources/simple_vmexpr.o: sources/simple_vmexpr.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmexpr.o sources/simple_vmexpr.c

${OBJECTDIR}/sources/simple_vmfile.o: sources/simple_vmfile.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmfile.o sources/simple_vmfile.c

${OBJECTDIR}/sources/simple_vmfuncs.o: sources/simple_vmfuncs.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmfuncs.o sources/simple_vmfuncs.c

${OBJECTDIR}/sources/simple_vmgc.o: sources/simple_vmgc.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmgc.o sources/simple_vmgc.c

${OBJECTDIR}/sources/simple_vmjump.o: sources/simple_vmjump.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmjump.o sources/simple_vmjump.c

${OBJECTDIR}/sources/simple_vmlistfuncs.o: sources/simple_vmlistfuncs.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmlistfuncs.o sources/simple_vmlistfuncs.c

${OBJECTDIR}/sources/simple_vmlists.o: sources/simple_vmlists.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmlists.o sources/simple_vmlists.c

${OBJECTDIR}/sources/simple_vmmath.o: sources/simple_vmmath.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmmath.o sources/simple_vmmath.c

${OBJECTDIR}/sources/simple_vmoop.o: sources/simple_vmoop.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmoop.o sources/simple_vmoop.c

${OBJECTDIR}/sources/simple_vmos.o: sources/simple_vmos.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmos.o sources/simple_vmos.c

${OBJECTDIR}/sources/simple_vmperformance.o: sources/simple_vmperformance.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmperformance.o sources/simple_vmperformance.c

${OBJECTDIR}/sources/simple_vmrefmeta.o: sources/simple_vmrefmeta.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmrefmeta.o sources/simple_vmrefmeta.c

${OBJECTDIR}/sources/simple_vmstackvars.o: sources/simple_vmstackvars.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmstackvars.o sources/simple_vmstackvars.c

${OBJECTDIR}/sources/simple_vmstate.o: sources/simple_vmstate.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmstate.o sources/simple_vmstate.c

${OBJECTDIR}/sources/simple_vmstrindex.o: sources/simple_vmstrindex.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmstrindex.o sources/simple_vmstrindex.c

${OBJECTDIR}/sources/simple_vmtrycatch.o: sources/simple_vmtrycatch.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmtrycatch.o sources/simple_vmtrycatch.c

${OBJECTDIR}/sources/simple_vmvars.o: sources/simple_vmvars.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_vmvars.o sources/simple_vmvars.c

${OBJECTDIR}/sources/simplew.o: sources/simplew.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simplew.o sources/simplew.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
