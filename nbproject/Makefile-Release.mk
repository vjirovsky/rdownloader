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
CCC=g++.exe
CXX=g++.exe
FC=gfortran.exe
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Release
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
CFLAGS=-lsupc++

# CC Compiler Flags
CCFLAGS=-lsupc++
CXXFLAGS=-lsupc++

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/C/_CPP_LIBS/libcurl.dll /C/_CPP_LIBS/libeay32.dll /C/_CPP_LIBS/libpcre.dll.a /C/_CPP_LIBS/libpcreposix.dll.a /C/_CPP_LIBS/libssl32.dll /C/_CPP_LIBS/pcre3.dll /C/_CPP_LIBS/pcreposix3.dll /C/_CPP_LIBS/ssleay32.dll

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader.exe: /C/_CPP_LIBS/libcurl.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader.exe: /C/_CPP_LIBS/libeay32.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader.exe: /C/_CPP_LIBS/libpcre.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader.exe: /C/_CPP_LIBS/libpcreposix.dll.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader.exe: /C/_CPP_LIBS/libssl32.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader.exe: /C/_CPP_LIBS/pcre3.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader.exe: /C/_CPP_LIBS/pcreposix3.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader.exe: /C/_CPP_LIBS/ssleay32.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	g++ -lcurl -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/C/_CPP_LIBS/include/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/PremiumUser.o: PremiumUser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/C/_CPP_LIBS/include/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/PremiumUser.o PremiumUser.cpp

${OBJECTDIR}/rdownloader.o: rdownloader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/C/_CPP_LIBS/include/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/rdownloader.o rdownloader.cpp

${OBJECTDIR}/freeuser.o: freeuser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -I/C/_CPP_LIBS/include/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/freeuser.o freeuser.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rdownloader.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
