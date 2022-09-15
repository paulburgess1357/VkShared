set(TargetName "VkShared")
cmake_minimum_required(VERSION 3.9.0)
project(${TargetName})
set(CMAKE_CXX_STANDARD 23)

# Set headers and cpp files
file(GLOB_RECURSE SourceFiles CONFIGURE_DEPENDS "${TargetName}/*.cpp")
file(GLOB_RECURSE HeaderFiles CONFIGURE_DEPENDS "${TargetName}/*.h")

# Create static library target
add_library(${TargetName} STATIC ${SourceFiles} ${HeaderFiles})
set_target_properties(${TargetName} PROPERTIES DEBUG_POSTFIX d)

# All warnings
target_compile_options(${TargetName} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wno-unknown-pragmas -Wextra -Wpedantic>
)

# Create include and link directory variables
set(IncludeDirectories ${CMAKE_CURRENT_SOURCE_DIR}/${TargetName})
set(LinkDirectories "")

# Build either with or without Conan
set(ConanSetupHasRun False)
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	message("Using Conan for dependency management: ${TargetName}")
	# Conan setup has not run AND this repo is not a shared fetch repo
	if(NOT ${ConanSetupHasRun} AND NOT DEFINED VkSharedFetchContentRepo)
		message("Loading Conan macros")
		include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
		conan_basic_setup(TARGETS NO_OUTPUT_DIRS)
		set(ConanSetupHasRun True)
	endif()

	list(APPEND IncludeDirectories ${CONAN_INCLUDE_DIRS})
	list(APPEND LinkDirectories CONAN_PKG::vulkan-loader)
else()
	find_package(Vulkan REQUIRED)
	list(APPEND IncludeDirectories ${Vulkan_INCLUDE_DIR})
	list(APPEND LinkDirectories ${Vulkan_LIBRARIES})
endif()

# Include/link directories
target_include_directories(${TargetName} PRIVATE 
	${IncludeDirectories}
)
target_link_libraries(${TargetName} PRIVATE
	${LinkDirectories}
)

# Retain directory structure
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HeaderFiles})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SourceFiles})

install(TARGETS ${TargetName})