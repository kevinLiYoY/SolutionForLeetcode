cmake_minium_required(VERSION 3.2);

project("CalculateTest")

add_definitions(-DUS_BUNDLE_NAME=CalculateTest)
set(CMAKE_CXX_STANDARD_LIBRARIES "-lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 -lwsock32 -lws2_32")
set(ROOTDIR ${PROJECT_SOURCE_DIR})

#设置C++版本
set(CMAKE_CXX_STANDARD 17)

add_definitions(-D_WIN32_WINNNT=0X601)
set(US_CMAKE_MINIMUM_REQUIRED_VERSION 3.2)
cmake_minimum_required(VERSION ${US_CMAKE_MINIMUM_REQUIRED_VERSION})

include(GenerateExportHeader)

#add_subdirectory(src)
FILE(GLOB TMP_FILES ${ROOTDIR}/*.cpp)
set(_srcs ${TMP_FILES})
add_executable(CalculateTest  ${_srcs})