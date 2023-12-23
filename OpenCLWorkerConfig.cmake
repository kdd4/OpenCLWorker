cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE HEADERS include/OpenCLWorker/*.hpp)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_library(OpenCLWorker STATIC ${HEADERS} ${SOURCES})

target_include_directories(OpenCLWorker PUBLIC include)

find_package(OpenCL CONFIG REQUIRED)
				
target_link_libraries(	OpenCLWorker
						PRIVATE
						OpenCL::OpenCL
						OpenCL::Headers
						OpenCL::HeadersCpp
					)
					