set(TargetName "VkShared")
message("\nBuilding " ${TargetName})

cmake_minimum_required(VERSION 3.9.0)
project(${TargetName})
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SourceFiles CONFIGURE_DEPENDS "${TargetName}/*.cpp")
file(GLOB_RECURSE HeaderFiles CONFIGURE_DEPENDS "${TargetName}/*.h")

add_library(${TargetName} STATIC ${SourceFiles} ${HeaderFiles})
set_target_properties(${TargetName} PROPERTIES DEBUG_POSTFIX d)

target_compile_options(${TargetName} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wno-unknown-pragmas -Wextra -Wpedantic>
)

set(IncludeDirectories ${CMAKE_CURRENT_SOURCE_DIR}/${TargetName})
set(LinkDirectories)

set(ConanSetupHasRun False)
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	message("Using Conan for dependency management")
	message("Loading Conan macros")
	include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	conan_basic_setup(TARGETS NO_OUTPUT_DIRS)
	set(ConanSetupHasRun True)

	list(APPEND IncludeDirectories ${CONAN_INCLUDE_DIRS})
	list(APPEND LinkDirectories CONAN_PKG::vulkan-loader)
else()
	find_package(Vulkan REQUIRED)
	list(APPEND IncludeDirectories ${Vulkan_INCLUDE_DIR})
	list(APPEND LinkDirectories ${Vulkan_LIBRARIES})
endif()

target_include_directories(${TargetName} PRIVATE 
	${IncludeDirectories}
)
target_link_libraries(${TargetName} PRIVATE
	${LinkDirectories}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HeaderFiles})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles})

install(TARGETS ${TargetName})