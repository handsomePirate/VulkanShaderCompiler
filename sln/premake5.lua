workspace "VulkanShaderCompiler"
	architecture "x64"
	configurations { "Debug", "Release" }
	startproject "Test"
	location ""
	
	flags
	{
		"MultiProcessorCompile"
	}
	
include "../dependencies.lua"
	
include "../proj/VulkanShaderCompiler"
include "../proj/Test"