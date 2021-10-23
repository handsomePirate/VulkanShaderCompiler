#include <VulkanShaderCompiler/VulkanShaderCompilerAPI.hpp>

int main(int argc, char* argv[])
{
	VulkanShaderCompiler::Compile(VK_NULL_HANDLE, "frufru.vert.glsl");

	return 0;
}