cmake_minimum_required( VERSION 3.9.4 )

#include( "cmake/compiler.cmake" )

project( intc_p )

if( MSVC OR MSYS OR MINGW )
    set(CMAKE_CXX_FLAGS "/O3 /std:c++17")
else()
  set(CMAKE_CXX_FLAGS "-march=native -std=c++17")
endif()

file(GLOB INCLUDE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        *.h
        )

file(GLOB SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
		*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/")

add_executable( intc ${INCLUDE_FILES} ${SOURCE_FILES} )

set_target_properties( intc PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
)

target_link_libraries( intc )