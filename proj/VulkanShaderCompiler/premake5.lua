VulkanShaderCompilerInclude = path.getabsolute("../../include", os.getcwd())

project "VulkanShaderCompiler"
	kind "StaticLib"
	staticruntime "off"
	language "C++"
	cppdialect "C++17"
	location ""
	targetdir "../../build/%{cfg.buildcfg}"
	objdir "obj/%{cfg.buildcfg}"
	files { "../../src/**.hpp", "../../src/**.cpp", "../../include/**.hpp" }

	flags {
		"MultiProcessorCompile"
	}

	includedirs {
		"$(VULKAN_SDK)/include",
		SoftwareCoreInclude,
		VulkanShaderCompilerInclude
	}

	links {
		"$(VULKAN_SDK)/lib/shaderc_shared.lib",
		"SoftwareCore"
	}

	filter "system:windows"
		systemversion "latest"
	filter{}
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		optimize "On"

	filter {}
