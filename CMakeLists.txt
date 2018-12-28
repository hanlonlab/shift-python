### CMake Version #############################################################

cmake_minimum_required(VERSION 3.10)

### Project Configuration #####################################################

get_filename_component(PROJECT_DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" PROJECT_DIR_NAME ${PROJECT_DIR_NAME})

set(LIB_NAME shift)

### List of Files #############################################################

set(DEMO
    ${PROJECT_SOURCE_DIR}/demo/demo.py
    ${PROJECT_SOURCE_DIR}/demo/initiator.cfg
)

set(INCLUDE
    ${PROJECT_SOURCE_DIR}/include/BestPrice.h
    ${PROJECT_SOURCE_DIR}/include/Common.h
    ${PROJECT_SOURCE_DIR}/include/Order.h
    ${PROJECT_SOURCE_DIR}/include/OrderBook.h
    ${PROJECT_SOURCE_DIR}/include/OrderBookEntry.h
    ${PROJECT_SOURCE_DIR}/include/PortfolioItem.h
    ${PROJECT_SOURCE_DIR}/include/PortfolioSummary.h
    ${PROJECT_SOURCE_DIR}/include/Trader.h
)

set(SRC
    ${PROJECT_SOURCE_DIR}/src/SHIFT.cpp
    ${PROJECT_SOURCE_DIR}/src/Trader.cpp
)

set(OTHER
    ${PROJECT_SOURCE_DIR}/mingw64-build.sh
    ${PROJECT_SOURCE_DIR}/setup.py
    ${PROJECT_SOURCE_DIR}/win-build-clientx86.sh
)

### Compiler Flags ############################################################

# UNIX only
if(NOT WIN32)

    # C++14
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Common Flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexceptions -pedantic-errors")

    # Debug Flags
    set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

    # Release Flags
    # -O2 instead of -O3
    # -flto stands for Link Time Optimization (LTO)
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -flto")

    # GCC / Clang
    if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    endif(UNIX)

    # GCC (Ubuntu 18.04 LTS Bionic Beaver)
    # -Wno-deprecated is required when linking QuickFIX on Ubuntu
    if(UNIX AND NOT APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")
    endif(UNIX AND NOT APPLE)

    # Clang (macOS Mojave 10.14)
    # -Wno-overloaded-virtual is required when linking QuickFIX on macOS
    if(APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-overloaded-virtual")
        include_directories(/usr/local/include)
    endif(APPLE)

endif(NOT WIN32)

# Visual C++ (Visual Studio 2017)
if(WIN32)
	add_definitions(-DCURL_STATICLIB)
    add_subdirectory(pybind11)

    include_directories(${PROJECT_SOURCE_DIR}/include)
    include_directories(${PROJECT_SOURCE_DIR}/../shift-main/LibCoreClient/include)
    include_directories(${PROJECT_SOURCE_DIR}/../shift-main/LibMiscUtils/include)
    include_directories(C:/quickfix/include)    
    include_directories("./pybind11/build/mock_install/include")
    include_directories("C:/Program Files (x86)/Python37-32/include")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -fexceptions -pedantic-errors")
endif(WIN32)

### Build Types ###############################################################

# if no build type is set, the default is Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

### Build Configuration #######################################################


if(NOT WIN32) # UNIX only
    find_package(pybind11 REQUIRED)
endif(NOT WIN32)

if(WIN32)   # Windows
	if(CMAKE_BUILD_TYPE MATCHES Debug)
        find_library(QUICKFIX quickfix
                    PATHS C:/quickfix/lib/debug)
        set(CURL_INCLUDE_DIR "C:/curl-7.58.0/builds/libcurl-vc17-x86-debug-static-ipv6-sspi-winssl/include")
        set(CURL_LIBRARY "C:/curl-7.58.0/builds/libcurl-vc17-x86-debug-static-ipv6-sspi-winssl/lib/libcurl_a_debug.lib")
    endif(CMAKE_BUILD_TYPE MATCHES Debug)
    if(CMAKE_BUILD_TYPE MATCHES Release)
        find_library(QUICKFIX quickfix
                    PATHS C:/quickfix/lib)
        set(CURL_INCLUDE_DIR "C:/curl-7.58.0/builds/libcurl-vc17-x86-release-static-ipv6-sspi-winssl/include")
        set(CURL_LIBRARY "C:/curl-7.58.0/builds/libcurl-vc17-x86-release-static-ipv6-sspi-winssl/lib/libcurl_a.lib") 
    endif(CMAKE_BUILD_TYPE MATCHES Release)

    find_package(CURL REQUIRED)

    if(CURL_FOUND)
        INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
        find_library(CURL curl)
    else(CURL_FOUND)
        message(FATAL_ERROR "Could not find the CURL library")
    endif(CURL_FOUND)
endif(WIN32)

# Always enforce search for SHIFT LibCoreClient
# (necessary when using the same name for Debug and Release)
set (LIBCORECLIENT "LIBCORECLIENT-NOTFOUND")
if(CMAKE_BUILD_TYPE MATCHES Debug)
    find_library(LIBCORECLIENT shift_coreclient-d 
    	PATHS ${PROJECT_SOURCE_DIR}/../shift-main/LibCoreClient/build/Debug)
endif(CMAKE_BUILD_TYPE MATCHES Debug)
if(CMAKE_BUILD_TYPE MATCHES Release)
    find_library(LIBCORECLIENT shift_coreclient 
    	PATHS ${PROJECT_SOURCE_DIR}/../shift-main/LibCoreClient/build/Release)
endif(CMAKE_BUILD_TYPE MATCHES Release) 
if(NOT LIBCORECLIENT)
    message(FATAL_ERROR "SHIFT LibCoreClient was not found.")
endif(NOT LIBCORECLIENT)

# Always enforce search for SHIFT LibMiscUtils
# (necessary when using the same name for Debug and Release)
set (LIBMISCUTILS "LIBMISCUTILS-NOTFOUND")
if(CMAKE_BUILD_TYPE MATCHES Debug)
    find_library(LIBMISCUTILS shift_miscutils-d
    	PATHS ${PROJECT_SOURCE_DIR}/../shift-main/LibMiscUtils/build/Debug)
endif(CMAKE_BUILD_TYPE MATCHES Debug)
if(CMAKE_BUILD_TYPE MATCHES Release)
    find_library(LIBMISCUTILS shift_miscutils
    	PATHS ${PROJECT_SOURCE_DIR}/../shift-main/LibMiscUtils/build/Release)
endif(CMAKE_BUILD_TYPE MATCHES Release)
if(NOT LIBMISCUTILS)
    message(FATAL_ERROR "SHIFT LibMiscUtils was not found.")
endif(NOT LIBMISCUTILS)

pybind11_add_module(${LIB_NAME}
                    ${DEMO} ${INCLUDE} ${SRC} ${OTHER})

target_include_directories(${LIB_NAME}
                           PRIVATE ${PROJECT_SOURCE_DIR}/include)

if(NOT WIN32) # UNIX
    target_link_libraries(${LIB_NAME}
                          PRIVATE ${LIBCORECLIENT})
else(WIN32)   # Windows
    target_link_libraries(${LIB_NAME}
                          PRIVATE ${LIBCORECLIENT} ${CURL_LIBRARY}  ${QUICKFIX}  ${LIBMISCUTILS})
endif(NOT WIN32)

###############################################################################
