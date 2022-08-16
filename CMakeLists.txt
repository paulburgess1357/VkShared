message("\nBuilding VkShared")

cmake_minimum_required(VERSION 3.9.0)
set(CMAKE_CXX_STANDARD 23)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()  

set(TargetName "VkShared")

file(GLOB_RECURSE SourceFiles CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE HeaderFiles CONFIGURE_DEPENDS "*.h")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_library(${TargetName} STATIC ${SourceFiles} ${HeaderFiles})
set_target_properties(${TargetName} PROPERTIES DEBUG_POSTFIX d)

target_include_directories(${TargetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HeaderFiles})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles})  

target_link_libraries(${TargetName} 
	CONAN_PKG::vulkan-loader
)