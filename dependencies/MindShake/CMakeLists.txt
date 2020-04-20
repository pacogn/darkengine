cmake_minimum_required(VERSION 3.10.0)
project(MindShake VERSION 0.1.0)

message("Processing " ${PROJECT_NAME})

# Avoid RelWithDebInfo and MinSizeRel
#--------------------------------------
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# Define Release by default
#--------------------------------------
message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "Build type not specified: Use Release by default")
endif(NOT CMAKE_BUILD_TYPE)

# Files
#--------------------------------------
set(SRC_FILES
    Common/Core/configCoreLib.h
    Common/Core/platform.h
    Common/Core/stringAux.h
    Common/Core/console/msColors.h

    Core/log/CLogConsole.cpp
    Core/log/CLogConsole.h
    Core/log/CLogFile.cpp
    Core/log/CLogFile.h
    Core/log/CLogger.cpp
    Core/log/CLogger.h
    Core/log/CLogSystem.cpp
    Core/log/CLogSystem.h
    Core/log/log.h
    Core/log/logEnums.h

    Core/memory/memory.h
    Core/memory/memory.cpp

    Core/utils/pathUtils.h
    Core/utils/pathUtils.cpp

    Common/Kernel/configKernelLib.h
    Common/Kernel/mt/CMiniCriticalSection.h

    Kernel/timer/CChronoTimer.cpp
    Kernel/timer/CChronoTimer.h
    Kernel/timer/sleep.cpp
    Kernel/timer/sleep.h

    Common/Math/configMathLib.h
    Common/Math/constants.h
    Common/Math/math_funcs.h

    Math/types/CVector2.h
    Math/types/CVector3.h
    Math/types/CVector4.h
    Math/types/CMatrix2.h
    Math/types/CMatrix3.h
    Math/types/CMatrix4.h
    Math/types/CQuaternion.h

    Math/types/CVector2.cpp
    Math/types/CVector3.cpp
    Math/types/CVector4.cpp
    Math/types/CMatrix2.cpp
    Math/types/CMatrix3.cpp
    Math/types/CMatrix4.cpp
    Math/types/CQuaternion.cpp

    Math/random/FastRand2.h
    Math/random/FastRand2.cpp    
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SRC_FILES})

if(APPLE)
    set(SRC_FILES_APPLE
        # Objective C++
        Kernel/timer/sleep.mm
    )
    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SRC_FILES_APPLE})
else()
    set(SRC_FILES_APPLE )
endif(APPLE)

# Library
#--------------------------------------
add_library(${PROJECT_NAME} STATIC
    ${SRC_FILES} 
    ${SRC_FILES_APPLE}
)

target_include_directories(${PROJECT_NAME} PUBLIC  .)

if (CMAKE_VERSION VERSION_GREATER 3.7.8)
    if (MSVC_IDE)
        option(VS_ADD_NATIVE_VISUALIZERS "Configure project to use Visual Studio native visualizers" TRUE)
    else()
        set(VS_ADD_NATIVE_VISUALIZERS FALSE CACHE INTERNAL "Native visualizers are Visual Studio extension" FORCE)
    endif()

    # add natvis file to the library so it will automatically be loaded into Visual Studio
    if(VS_ADD_NATIVE_VISUALIZERS)
        target_sources(${PROJECT_NAME} PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/mindshake.natvis
        )
    endif()
endif()

