set(TargetName "VkShared")
message("\nBuilding " TargetName)

cmake_minimum_required(VERSION 3.9.0)
project(VkShared)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SourceFiles CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE HeaderFiles CONFIGURE_DEPENDS "*.h")

add_library(${TargetName} STATIC ${SourceFiles} ${HeaderFiles})
set_target_properties(${TargetName} PROPERTIES DEBUG_POSTFIX d)

target_include_directories(${TargetName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HeaderFiles})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles})

install(TARGETS VkShared)