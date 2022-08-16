set(TargetName "VkShared")
message("\nBuilding " TargetName)

cmake_minimum_required(VERSION 3.9.0)
project(${TargetName})
set(CMAKE_CXX_STANDARD 23)

find_package(Vulkan REQUIRED)

file(GLOB_RECURSE SourceFiles CONFIGURE_DEPENDS "*.cpp")
list(FILTER SourceFiles EXCLUDE REGEX "build/.*" )

file(GLOB_RECURSE HeaderFiles CONFIGURE_DEPENDS "*.h")
list(FILTER HeaderFiles EXCLUDE REGEX "build/.*" )

add_library(${TargetName} STATIC ${SourceFiles} ${HeaderFiles})
set_target_properties(${TargetName} PROPERTIES DEBUG_POSTFIX d)

target_include_directories(${TargetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${Vulkan_INCLUDE_DIR})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HeaderFiles})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles})

target_link_libraries(${TargetName} 
	${Vulkan_LIBRARY}
)

install(TARGETS ${TargetName})