#include "VulkanShaderCompiler/VulkanShaderCompilerAPI.hpp"
#include "Preprocessor.hpp"
#include <SoftwareCore/Filesystem.hpp>
#include <SoftwareCore/Process.hpp>
#include <SoftwareCore/Logger.hpp>
#include <SoftwareCore/DefaultLogger.hpp>
#include <shaderc/shaderc.hpp>
#include <string.h>

VkShaderModule VulkanShaderCompiler::Compile(VkDevice device, const char* filename)
{
	Core::Filesystem filesystem(CoreProcess.GetRuntimePath());
	std::string filenameStr(filesystem.GetAbsolutePath(filename));
	if (!filesystem.FileExists(filename))
	{
		CoreLogError(DefaultLogger, "Compiler: File \'%s\' does not exist.", filename);
		return VK_NULL_HANDLE;
	}

	if (filesystem.Extension(filenameStr) != ".glsl")
	{
		CoreLogWarn(DefaultLogger, "Compiler: File \'%s\' is not a GLSL file.", filename);
	}

	size_t fileSize = filesystem.GetFileSize(filenameStr);
	if (fileSize == 0)
	{
		CoreLogError(DefaultLogger, "Compiler: File \'%s\' is empty.", filename);
		return VK_NULL_HANDLE;
	}

	void* fileData = malloc(fileSize);
	filesystem.ReadFile(filenameStr, fileData, fileSize);

	Preprocessor::Preprocess(fileData, fileSize);

	std::string actualFileName = filesystem.Filename(filenameStr);
	std::string filenameNoExt = filesystem.RemoveExtension(filenameStr);
	std::string shaderKindStr = filesystem.Extension(filenameNoExt);
	shaderc_shader_kind shaderKind;
	if (shaderKindStr == ".vert")
	{
		shaderKind = shaderc_vertex_shader;
	}
	else if (shaderKindStr == ".frag")
	{
		shaderKind = shaderc_fragment_shader;
	}
	else if (shaderKindStr == ".comp")
	{
		shaderKind = shaderc_compute_shader;
	}
	else
	{
		CoreLogError(DefaultLogger, "Compiler: Unsupported shader stage - \'%s\'.", shaderKindStr.c_str());
		return VK_NULL_HANDLE;
	}

	shaderc::CompileOptions options;
	// TODO: Variable version.
	options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
	const bool optimize = true;
	if (optimize)
	{
		options.SetOptimizationLevel(shaderc_optimization_level_performance);
	}
	shaderc::Compiler compiler;
	auto compilationResult = compiler.CompileGlslToSpv((const char*)fileData, fileSize,
		shaderKind, actualFileName.c_str(), "main", options);
	auto compilationStatus = compilationResult.GetCompilationStatus();

	if (compilationStatus != shaderc_compilation_status_success)
	{
		size_t errorCount = compilationResult.GetNumErrors();
		CoreLogError(DefaultLogger, "Compiler: Encountered errors (%zu).", errorCount);

		std::string errorMessage = compilationResult.GetErrorMessage();
		CoreLogError(DefaultLogger, "%s", errorMessage.c_str());

		return VK_NULL_HANDLE;
	}

	std::vector<uint32_t> byteCode(compilationResult.begin(), compilationResult.end());

	VkShaderModuleCreateInfo shaderModuleCreateInfo{};
	shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shaderModuleCreateInfo.codeSize = (uint32_t)(byteCode.size() * sizeof(uint32_t));
	shaderModuleCreateInfo.pCode = byteCode.data();

	VkShaderModule shaderModule;
	VkResult result = vkCreateShaderModule(device, &shaderModuleCreateInfo, nullptr, &shaderModule);
	if (result != VK_SUCCESS)
	{
		CoreLogError(DefaultLogger, "Compiler: Couldn't create shader module.");
	}

	return shaderModule;
}
