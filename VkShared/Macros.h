#pragma once
#include <iostream>
#include <string>
#include <vulkan/vulkan_core.h>

// clang-format off
#ifdef WIN32
#define BREAK(...) __debugbreak() 
#else
#define BREAK(...)
#endif

#ifndef NDEBUG
#define VkTrace(message) std::cout << std::string{message} << std::endl; static_assert(true, "") // Normal
#define VkInfo(message) std::cout << ("\x1B[36m") + std::string{message} + ("\033[0m\t\t") << std::endl; static_assert(true, "") // Blue
#define VkSuccess(message) std::cout << ("\x1B[32m") + std::string{message} + ("\033[0m\t\t") << std::endl; static_assert(true, "") // Green
#define VkError(message) std::cout << ("\x1B[31mError: ") + std::string{message} + ("\033[0m\t\t") << std::endl; static_assert(true, "") // Red
#define VkWarning(message) std::cout << ("\x1B[33mWarning: ") + std::string{message} + ("\033[0m\t\t") << std::endl; static_assert(true, "") // Yellow
#define VkAssert(assert_check, message_if_false) if(!(assert_check)){ VkError(std::string{message_if_false} + "\nFile: " +  std::string{__FILE__} + "\nLine: " +  std::to_string(__LINE__)); BREAK();} static_assert(true, "")
#define VkCheck(value, exception) if((value) != VK_SUCCESS){throw (exception);} static_assert(true, "")

#else
#define VkTrace(...)
#define VkInfo(...)
#define VkSuccess(...)
#define VkError(...)
#define VkWarning(...)
#define VkAssert(...)
#define VkCheck(...)
#endif
