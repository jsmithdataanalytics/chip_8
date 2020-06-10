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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/4a47ce26/sdl.o \
	${OBJECTDIR}/instructions/instructions.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/resources/resources.o \
	${OBJECTDIR}/rom/rom.o


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
LDLIBSOPTIONS=-lSDL2 -lSDL2_mixer

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk chip-8

chip-8: ${OBJECTFILES}
	${LINK.c} -o chip-8 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/4a47ce26/sdl.o: /home/james/NetBeansProjects/chip-8/sdl/sdl.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4a47ce26
	${RM} "$@.d"
	$(COMPILE.c) -g -Iresources -Iinstructions -Irom -Isdl -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4a47ce26/sdl.o /home/james/NetBeansProjects/chip-8/sdl/sdl.c

${OBJECTDIR}/instructions/instructions.o: instructions/instructions.c
	${MKDIR} -p ${OBJECTDIR}/instructions
	${RM} "$@.d"
	$(COMPILE.c) -g -Iresources -Iinstructions -Irom -Isdl -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/instructions/instructions.o instructions/instructions.c

${OBJECTDIR}/main.o: main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Iresources -Iinstructions -Irom -Isdl -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/resources/resources.o: resources/resources.c
	${MKDIR} -p ${OBJECTDIR}/resources
	${RM} "$@.d"
	$(COMPILE.c) -g -Iresources -Iinstructions -Irom -Isdl -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/resources/resources.o resources/resources.c

${OBJECTDIR}/rom/rom.o: rom/rom.c
	${MKDIR} -p ${OBJECTDIR}/rom
	${RM} "$@.d"
	$(COMPILE.c) -g -Iresources -Iinstructions -Irom -Isdl -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rom/rom.o rom/rom.c

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
