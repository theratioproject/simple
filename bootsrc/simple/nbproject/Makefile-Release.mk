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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/sources/ring_api.o \
	${OBJECTDIR}/sources/ring_codegen.o \
	${OBJECTDIR}/sources/ring_expr.o \
	${OBJECTDIR}/sources/ring_ext.o \
	${OBJECTDIR}/sources/ring_hashlib.o \
	${OBJECTDIR}/sources/ring_hashtable.o \
	${OBJECTDIR}/sources/ring_item.o \
	${OBJECTDIR}/sources/ring_items.o \
	${OBJECTDIR}/sources/ring_list.o \
	${OBJECTDIR}/sources/ring_objfile.o \
	${OBJECTDIR}/sources/ring_parser.o \
	${OBJECTDIR}/sources/ring_scanner.o \
	${OBJECTDIR}/sources/ring_state.o \
	${OBJECTDIR}/sources/ring_stmt.o \
	${OBJECTDIR}/sources/ring_string.o \
	${OBJECTDIR}/sources/ring_vm.o \
	${OBJECTDIR}/sources/ring_vmcui.o \
	${OBJECTDIR}/sources/ring_vmdll.o \
	${OBJECTDIR}/sources/ring_vmduprange.o \
	${OBJECTDIR}/sources/ring_vmexit.o \
	${OBJECTDIR}/sources/ring_vmexpr.o \
	${OBJECTDIR}/sources/ring_vmfile.o \
	${OBJECTDIR}/sources/ring_vmfuncs.o \
	${OBJECTDIR}/sources/ring_vmgc.o \
	${OBJECTDIR}/sources/ring_vmjump.o \
	${OBJECTDIR}/sources/ring_vmlistfuncs.o \
	${OBJECTDIR}/sources/ring_vmlists.o \
	${OBJECTDIR}/sources/ring_vmmath.o \
	${OBJECTDIR}/sources/ring_vmoop.o \
	${OBJECTDIR}/sources/ring_vmos.o \
	${OBJECTDIR}/sources/ring_vmperformance.o \
	${OBJECTDIR}/sources/ring_vmrefmeta.o \
	${OBJECTDIR}/sources/ring_vmstackvars.o \
	${OBJECTDIR}/sources/ring_vmstate.o \
	${OBJECTDIR}/sources/ring_vmstrindex.o \
	${OBJECTDIR}/sources/ring_vmtrycatch.o \
	${OBJECTDIR}/sources/ring_vmvars.o \
	${OBJECTDIR}/sources/ringw.o \
	${OBJECTDIR}/sources/simple.o \
	${OBJECTDIR}/sources/simple_misc.o


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

${OBJECTDIR}/sources/ring_api.o: sources/ring_api.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_api.o sources/ring_api.c

${OBJECTDIR}/sources/ring_codegen.o: sources/ring_codegen.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_codegen.o sources/ring_codegen.c

${OBJECTDIR}/sources/ring_expr.o: sources/ring_expr.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_expr.o sources/ring_expr.c

${OBJECTDIR}/sources/ring_ext.o: sources/ring_ext.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_ext.o sources/ring_ext.c

${OBJECTDIR}/sources/ring_hashlib.o: sources/ring_hashlib.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_hashlib.o sources/ring_hashlib.c

${OBJECTDIR}/sources/ring_hashtable.o: sources/ring_hashtable.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_hashtable.o sources/ring_hashtable.c

${OBJECTDIR}/sources/ring_item.o: sources/ring_item.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_item.o sources/ring_item.c

${OBJECTDIR}/sources/ring_items.o: sources/ring_items.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_items.o sources/ring_items.c

${OBJECTDIR}/sources/ring_list.o: sources/ring_list.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_list.o sources/ring_list.c

${OBJECTDIR}/sources/ring_objfile.o: sources/ring_objfile.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_objfile.o sources/ring_objfile.c

${OBJECTDIR}/sources/ring_parser.o: sources/ring_parser.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_parser.o sources/ring_parser.c

${OBJECTDIR}/sources/ring_scanner.o: sources/ring_scanner.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_scanner.o sources/ring_scanner.c

${OBJECTDIR}/sources/ring_state.o: sources/ring_state.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_state.o sources/ring_state.c

${OBJECTDIR}/sources/ring_stmt.o: sources/ring_stmt.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_stmt.o sources/ring_stmt.c

${OBJECTDIR}/sources/ring_string.o: sources/ring_string.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_string.o sources/ring_string.c

${OBJECTDIR}/sources/ring_vm.o: sources/ring_vm.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vm.o sources/ring_vm.c

${OBJECTDIR}/sources/ring_vmcui.o: sources/ring_vmcui.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmcui.o sources/ring_vmcui.c

${OBJECTDIR}/sources/ring_vmdll.o: sources/ring_vmdll.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmdll.o sources/ring_vmdll.c

${OBJECTDIR}/sources/ring_vmduprange.o: sources/ring_vmduprange.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmduprange.o sources/ring_vmduprange.c

${OBJECTDIR}/sources/ring_vmexit.o: sources/ring_vmexit.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmexit.o sources/ring_vmexit.c

${OBJECTDIR}/sources/ring_vmexpr.o: sources/ring_vmexpr.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmexpr.o sources/ring_vmexpr.c

${OBJECTDIR}/sources/ring_vmfile.o: sources/ring_vmfile.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmfile.o sources/ring_vmfile.c

${OBJECTDIR}/sources/ring_vmfuncs.o: sources/ring_vmfuncs.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmfuncs.o sources/ring_vmfuncs.c

${OBJECTDIR}/sources/ring_vmgc.o: sources/ring_vmgc.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmgc.o sources/ring_vmgc.c

${OBJECTDIR}/sources/ring_vmjump.o: sources/ring_vmjump.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmjump.o sources/ring_vmjump.c

${OBJECTDIR}/sources/ring_vmlistfuncs.o: sources/ring_vmlistfuncs.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmlistfuncs.o sources/ring_vmlistfuncs.c

${OBJECTDIR}/sources/ring_vmlists.o: sources/ring_vmlists.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmlists.o sources/ring_vmlists.c

${OBJECTDIR}/sources/ring_vmmath.o: sources/ring_vmmath.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmmath.o sources/ring_vmmath.c

${OBJECTDIR}/sources/ring_vmoop.o: sources/ring_vmoop.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmoop.o sources/ring_vmoop.c

${OBJECTDIR}/sources/ring_vmos.o: sources/ring_vmos.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmos.o sources/ring_vmos.c

${OBJECTDIR}/sources/ring_vmperformance.o: sources/ring_vmperformance.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmperformance.o sources/ring_vmperformance.c

${OBJECTDIR}/sources/ring_vmrefmeta.o: sources/ring_vmrefmeta.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmrefmeta.o sources/ring_vmrefmeta.c

${OBJECTDIR}/sources/ring_vmstackvars.o: sources/ring_vmstackvars.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmstackvars.o sources/ring_vmstackvars.c

${OBJECTDIR}/sources/ring_vmstate.o: sources/ring_vmstate.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmstate.o sources/ring_vmstate.c

${OBJECTDIR}/sources/ring_vmstrindex.o: sources/ring_vmstrindex.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmstrindex.o sources/ring_vmstrindex.c

${OBJECTDIR}/sources/ring_vmtrycatch.o: sources/ring_vmtrycatch.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmtrycatch.o sources/ring_vmtrycatch.c

${OBJECTDIR}/sources/ring_vmvars.o: sources/ring_vmvars.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ring_vmvars.o sources/ring_vmvars.c

${OBJECTDIR}/sources/ringw.o: sources/ringw.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/ringw.o sources/ringw.c

${OBJECTDIR}/sources/simple.o: sources/simple.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple.o sources/simple.c

${OBJECTDIR}/sources/simple_misc.o: sources/simple_misc.c
	${MKDIR} -p ${OBJECTDIR}/sources
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sources/simple_misc.o sources/simple_misc.c

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
