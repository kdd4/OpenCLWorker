cmake_minimum_required(VERSION 3.21)

get_filename_component(SOURCES_DIR "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)

file(GLOB_RECURSE HEADERS ${SOURCES_DIR}/include/OpenCLWorker/*.hpp)
file(GLOB_RECURSE SOURCES ${SOURCES_DIR}/src/*.cpp)

add_library(OpenCLWorker STATIC ${HEADERS} ${SOURCES})

target_include_directories(OpenCLWorker PUBLIC ${SOURCES_DIR}/include)

if (NOT OpenCL_DIR)
	find_package(	OpenCL CONFIG REQUIRED
					PATHS ${CMAKE_SOURCE_DIR}/extlib
				)
endif()
				
target_link_libraries(	OpenCLWorker
						PRIVATE
						OpenCL::OpenCL
						OpenCL::Headers
						OpenCL::HeadersCpp
					)
					