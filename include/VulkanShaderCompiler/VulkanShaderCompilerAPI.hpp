#pragma once
#include <vulkan/vulkan.hpp>

namespace VulkanShaderCompiler
{
	VkShaderModule Compile(VkDevice device, const char* filename);
}
