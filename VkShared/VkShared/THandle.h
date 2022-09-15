#pragma once
#include "VkShared/Macros.h"
#include <utility>
#include <vulkan/vulkan_core.h>

namespace VulkanUtilities::VkShared {

namespace Exceptions {
class VkHandleException final : public std::exception {
 public:
  [[nodiscard]] char const* what() const noexcept override {
    return "VkHandle Creation failed";
  }
};
}  // namespace Exceptions

template <typename T>
class THandle {
 public:
  template <typename... Args>
  explicit THandle(Args&&... args) {
    m_wrapped_handle.create(std::forward<Args>(args)...);
    if (!handle()) {
      VkError("Failed to create Vulkan handle");
#ifndef NDEBUG
      throw Exceptions::VkHandleException();
#endif
    }
  }
  ~THandle() {
    if (!m_destroyed) {
      destroy();
      reset();
    }
  }
  THandle& operator=(THandle&& rhs) noexcept {
    if (this != &rhs) {
      this->m_wrapped_handle = rhs.m_wrapped_handle;
      rhs.reset();
    }
    return *this;
  }

  THandle(THandle&& source) noexcept : m_wrapped_handle{source.m_wrapped_handle} {
    source.reset();
  }

  THandle(const THandle& source) = delete;
  THandle& operator=(const THandle& rhs) = delete;

  [[nodiscard]] auto& handle() const {
    return m_wrapped_handle.handle;
  }

 private:
  void reset() {
    m_wrapped_handle.handle = VK_NULL_HANDLE;
    m_reset = true;
  }

  void destroy() {
    m_wrapped_handle.destroy();
    m_wrapped_handle.handle = VK_NULL_HANDLE;
    m_destroyed = true;
  }

  T m_wrapped_handle{};
  bool m_destroyed{false};
  bool m_reset{false};
};

}  // namespace VulkanUtilities::VkShared
