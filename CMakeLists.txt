cmake_minimum_required(VERSION 3.21)

if (NOT CMAKE_CXX_COMPILER_ID)
	message(WARNING "CMAKE_CXX_COMPILER_ID is not defined")
	set(CMAKE_CXX_COMPILER_ID "GCC" CACHE STRING "Enter compiler id" FORCE)
	
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GCC" OR CMAKE_CXX_COMPILER_ID MATCHES "CLANG")
	set(CMAKE_CXX_FLAGS "-Wall -Wpedantic")
	set(CAKE_CXX_FLAGS_DEBUG "-g")
	set(CAKE_CXX_FLAGS_RELEASE "-O3 -Werror")
	
	if (NOT CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose Release or Debug" FORCE)
	endif()
	
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	set(CMAKE_CXX_FLAGS "/Wall")
	set(CAKE_CXX_FLAGS_DEBUG "/g")
	set(CAKE_CXX_FLAGS_RELEASE "/O3 /Werror")
endif()

project(OpenCLWorker CXX)

file(GLOB_RECURSE HEADERS include/OpenCLWorker/*.hpp)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(OpenCLWorker STATIC ${HEADERS} ${SOURCES})

target_include_directories(OpenCLWorker PUBLIC include)

find_package(	OpenCL CONFIG REQUIRED
				PATHS ${CMAKE_SOURCE_DIR}/extlib
			)
				
target_link_libraries(	OpenCLWorker
						PRIVATE
						OpenCL::OpenCL
						OpenCL::Headers
						OpenCL::HeadersCpp
					)
					