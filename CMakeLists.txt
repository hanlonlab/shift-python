### CMake Version ##############################################################

cmake_minimum_required(VERSION 3.10)

### Project Configuration ######################################################

get_filename_component(PROJECT_DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" PROJECT_DIR_NAME ${PROJECT_DIR_NAME})

project(${PROJECT_DIR_NAME}
        VERSION 1.7.5 # <major>.<minor>.<patch>
        LANGUAGES CXX)

set(LIB_NAME shift)

### List of Files ##############################################################

set(DEMO
    ${PROJECT_SOURCE_DIR}/demo/credentials.py
    ${PROJECT_SOURCE_DIR}/demo/demo.py
    ${PROJECT_SOURCE_DIR}/demo/FIX50SP2.xml
    ${PROJECT_SOURCE_DIR}/demo/FIXT11.xml
    ${PROJECT_SOURCE_DIR}/demo/goodcbfs.py
    ${PROJECT_SOURCE_DIR}/demo/initiator.cfg
    ${PROJECT_SOURCE_DIR}/demo/zitrader.py
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
    ${PROJECT_SOURCE_DIR}/setup.py
)

### Compiler Flags #############################################################

# Important for libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions("-DHAVE_STD_UNIQUE_PTR=1") # QuickFIX C++17 compatibility req.

# Common Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexceptions -pedantic-errors")

# Debug Flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

# Release Flags
# -O2 instead of -O3
# -flto stands for Link Time Optimization (LTO)
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -finline-functions -flto")

# GCC (Ubuntu 20.04 LTS Focal Fossa)
if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif(UNIX AND NOT APPLE)

# GCC (Raspbian Buster for Raspberry Pi 4)
# Ubuntu rules apply here as well
if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "armv7l")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "armv7l")

# Clang (macOS Catalina 10.15)
if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-overloaded-virtual")
    include_directories(/usr/local/include)
endif(APPLE)

### Build Types ################################################################

# if no build type is set, the default is Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

### Build Configuration ########################################################

find_package(pybind11 REQUIRED)

# Always enforce search for SHIFT LibCoreClient
# (necessary when using the same name for Debug and Release)
set (LIBCORECLIENT "LIBCORECLIENT-NOTFOUND")
if(CMAKE_BUILD_TYPE MATCHES Debug)
    find_library(LIBCORECLIENT shift_coreclient-d)
endif(CMAKE_BUILD_TYPE MATCHES Debug)
if(CMAKE_BUILD_TYPE MATCHES Release)
    find_library(LIBCORECLIENT shift_coreclient)
endif(CMAKE_BUILD_TYPE MATCHES Release)
if(NOT LIBCORECLIENT)
    message(FATAL_ERROR "SHIFT LibCoreClient was not found.")
endif(NOT LIBCORECLIENT)

pybind11_add_module(${LIB_NAME}
                    ${DEMO} ${INCLUDE} ${SRC} ${OTHER})

target_include_directories(${LIB_NAME}
                           PRIVATE ${CMAKE_PREFIX_PATH}/include
                           PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${LIB_NAME}
                      PRIVATE ${LIBCORECLIENT})

################################################################################
