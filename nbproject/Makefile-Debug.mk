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
CC=g++
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/PremiumUser.o \
	${OBJECTDIR}/rdownloader.o \
	${OBJECTDIR}/freeuser.o


# C Compiler Flags
CFLAGS=-lstdc++

# CC Compiler Flags
CCFLAGS=-lstdc++
CXXFLAGS=-lstdc++

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpcre -lpcre -lpcrecpp -lpcrecpp -lpcreposix -lpcreposix

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	g++ -lcurl -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I/C/_CPP_LIBS/include/include -I/home/vaclavjirovsky/_SEMESTRALKA/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/PremiumUser.o: PremiumUser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I/C/_CPP_LIBS/include/include -I/home/vaclavjirovsky/_SEMESTRALKA/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/PremiumUser.o PremiumUser.cpp

${OBJECTDIR}/rdownloader.o: rdownloader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I/C/_CPP_LIBS/include/include -I/home/vaclavjirovsky/_SEMESTRALKA/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/rdownloader.o rdownloader.cpp

${OBJECTDIR}/freeuser.o: freeuser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I/C/_CPP_LIBS/include/include -I/home/vaclavjirovsky/_SEMESTRALKA/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/freeuser.o freeuser.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
