cmake_minimum_required(VERSION 3.12)
file(READ "version.txt" VERSION)
project(AIagent VERSION ${VERSION})


include(GNUInstallDirs)
include(FindPkgConfig)
include(${PROJECT_SOURCE_DIR}/cmake/git.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/uninstall.cmake)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_C_STANDARD            11)
set(CMAKE_C_EXTENSIONS          ON)
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_INSTALL_PREFIX  /opt/${PROJECT_NAME})


include(${PROJECT_SOURCE_DIR}/cmake/systemd.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/gen_debian_control.cmake)

add_compile_options(-Wall -Wfatal-errors)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_compile_options(-g)
endif()

set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE}   -O2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")



set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(RKLLM_RT_LIB ${CMAKE_SOURCE_DIR}/3rdparty/lib/librkllmrt.so)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${RKLLM_RT_LIB} pthread)


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${PROJECT_SOURCE_DIR}/3rdparty/lib/librkllmrt.so  DESTINATION ${CMAKE_INSTALL_BINDIR})


add_subdirectory(pack)
