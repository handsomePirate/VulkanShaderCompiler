workspace "VulkanShaderCompiler"
	architecture "x64"
	configurations { "Debug", "Release" }
	location ""
	
	flags
	{
		"MultiProcessorCompile"
	}
	
include "../dependencies.lua"
	
include "../proj/VulkanShaderCompiler"
include "../proj/Test"