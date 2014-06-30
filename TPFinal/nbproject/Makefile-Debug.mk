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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ClassicTyping.o \
	${OBJECTDIR}/Final.o \
	${OBJECTDIR}/FuncionesBasicas.o \
	${OBJECTDIR}/SourceFinal.o \
	${OBJECTDIR}/Te9.o


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
LDLIBSOPTIONS=`pkg-config --libs allegro-5.0` `pkg-config --libs allegro_acodec-5.0` `pkg-config --libs allegro_audio-5.0` `pkg-config --libs allegro_font-5.0` `pkg-config --libs allegro_image-5.0` `pkg-config --libs allegro_primitives-5.0` `pkg-config --libs allegro_ttf-5.0`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpfinal

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpfinal: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpfinal ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/ClassicTyping.o: ClassicTyping.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ClassicTyping.o ClassicTyping.c

${OBJECTDIR}/Final.o: Final.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Final.o Final.c

${OBJECTDIR}/FuncionesBasicas.o: FuncionesBasicas.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FuncionesBasicas.o FuncionesBasicas.c

${OBJECTDIR}/SourceFinal.o: SourceFinal.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SourceFinal.o SourceFinal.c

${OBJECTDIR}/Te9.o: Te9.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Te9.o Te9.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tpfinal

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
