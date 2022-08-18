set(TargetName "VkShared")
message("\nBuilding " ${TargetName})

cmake_minimum_required(VERSION 3.9.0)
project(${TargetName})
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SourceFiles CONFIGURE_DEPENDS "${TargetName}/*.cpp")
file(GLOB_RECURSE HeaderFiles CONFIGURE_DEPENDS "${TargetName}/*.h")

add_library(${TargetName} STATIC ${SourceFiles} ${HeaderFiles})
set_target_properties(${TargetName} PROPERTIES DEBUG_POSTFIX d)

set(USE_CONAN FALSE)
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    message("Using Conan for dependencies")
	set(USE_CONAN TRUE)
endif()
	
if(USE_CONAN)
	include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	conan_basic_setup(TARGETS)
	target_include_directories(${TargetName} PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/${TargetName}
		${CONAN_INCLUDE_DIRS}
	)
	target_link_libraries(${TargetName} 
		CONAN_PKG::vulkan-loader
	)
else()
	find_package(Vulkan REQUIRED)
	
	target_include_directories(${TargetName} PRIVATE 
	    ${CMAKE_CURRENT_SOURCE_DIR}/${TargetName}
		${Vulkan_INCLUDE_DIR}
	)
	target_link_libraries(${TargetName} 
		${Vulkan_LIBRARIES}
	)
endif()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HeaderFiles})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles})

install(TARGETS ${TargetName})