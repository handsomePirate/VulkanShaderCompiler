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
		VulkanShaderCompilerInclude,
		SoftwareCoreInclude,
		"$(VULKAN_SDK)/include"
	}

	links {
		"$(VULKAN_SDK)/lib/vulkan-1.lib",
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
