# Avoid default flag values
#--------------------------------------
# message("CMAKE_C_FLAGS:              ${CMAKE_C_FLAGS}")
# message("CMAKE_CXX_FLAGS:            ${CMAKE_CXX_FLAGS}")
# message("CMAKE_OBJC_FLAGS:           ${CMAKE_C_FLAGS}")
# message("CMAKE_OBJCXX_FLAGS:         ${CMAKE_CXX_FLAGS}")

# message("CMAKE_C_FLAGS_DEBUG:        ${CMAKE_C_FLAGS_DEBUG}")
# message("CMAKE_CXX_FLAGS_DEBUG:      ${CMAKE_CXX_FLAGS_DEBUG}")
# message("CMAKE_C_FLAGS_DEBUG:        ${CMAKE_C_FLAGS_DEBUG}")
# message("CMAKE_CXX_FLAGS_DEBUG:      ${CMAKE_CXX_FLAGS_DEBUG}")

# message("CMAKE_OBJC_FLAGS_RELEASE:   ${CMAKE_C_FLAGS_RELEASE}")
# message("CMAKE_OBJCXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")
# message("CMAKE_OBJC_FLAGS_RELEASE:   ${CMAKE_C_FLAGS_RELEASE}")
# message("CMAKE_OBJCXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")

set(CMAKE_C_FLAGS "" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_DEBUG "" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "" CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS "" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "" CACHE STRING "" FORCE)

set(CMAKE_OBJC_FLAGS "" CACHE STRING "" FORCE)
set(CMAKE_OBJC_FLAGS_DEBUG "" CACHE STRING "" FORCE)
set(CMAKE_OBJC_FLAGS_RELEASE "" CACHE STRING "" FORCE)

set(CMAKE_OBJCXX_FLAGS "" CACHE STRING "" FORCE)
set(CMAKE_OBJCXX_FLAGS_DEBUG "" CACHE STRING "" FORCE)
set(CMAKE_OBJCXX_FLAGS_RELEASE "" CACHE STRING "" FORCE)

# Enable compiler features
#--------------------------------------
# message("C:")
# foreach(fea ${CMAKE_C_COMPILE_FEATURES})
#     message(" - ${fea}")
# endforeach(fea)
# message("C++:")
# foreach(fea ${CMAKE_CXX_COMPILE_FEATURES})
#     message(" - ${fea}")
# endforeach(fea)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set Flags
#--------------------------------------
if(MSVC)
    # Warning level
    add_compile_options(/W3)
    # add_compile_options(/wd4100)    # unused parameter
    # add_compile_options(/wd4324)    # structure was padded due to alignment specifier
    # add_compile_options(/wd4201)    # nonstandard extension used: nameless struct/union
    add_compile_options(/wd4244)    # 'conversion' conversion from 'type1' to 'type2', possible loss of data
    add_compile_options(/wd26451)   # arithmetic overflow 
    # add_compile_options(/wd26812)   # arithmetic overflow 
    # Security check
    add_compile_options(/GS)
    # Function level linking
    add_compile_options(/Gy)
    # Exceptions
    add_compile_options(/EHsc)
    # SDL checks 2015+
    if(MSVC_VERSION GREATER_EQUAL 1900)
        add_compile_options(/sdl)
    endif()
    # Runtime library
    add_compile_options("$<IF:$<CONFIG:Debug>,/MDd,/MD>")
    # Program database for edit and continue
    add_compile_options("$<IF:$<CONFIG:Debug>,/ZI,/Zi>")
    # Optimizations
    add_compile_options("$<IF:$<CONFIG:Debug>,/Od,/O2>")
    # Inline function expansion
    add_compile_options("$<IF:$<CONFIG:Debug>,/Ob0,/Ob2>")
    # Basic runtime checks
    add_compile_options("$<$<CONFIG:Debug>:/RTC1>")
    # Enable intrinsics
    add_compile_options("$<$<CONFIG:RELEASE>:/Oi>")
else()
    add_compile_options("$<$<CONFIG:Debug>:-g>")
    add_compile_options("$<IF:$<CONFIG:Debug>,-O0,-O2>")
    add_compile_options(-Wall -Wextra)
    add_compile_options(-Wno-switch -Wno-unused-function -Wno-unused-parameter)
endif()

# Set preprocessor definitions
#--------------------------------------
if(WIN32)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_definitions(_WIN32_WINNT=0x0600)
    add_compile_definitions(WIN32)
endif(WIN32)
