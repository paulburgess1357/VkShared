#pragma once
#define VMA_VULKAN_VERSION 1002000
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wparentheses"

#pragma warning(push, 0)
#include <vk_mem_alloc.h>
#pragma warning(pop)

#pragma GCC diagnostic pop

namespace VkShared::VMA_TEST {
	[[nodiscard]] VmaAllocation test();
} // namespace VkShared::VMA_TEST