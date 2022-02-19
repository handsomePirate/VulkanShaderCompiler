project "Test"
	kind "ConsoleApp"
	staticruntime "off"
	language "C++"
	cppdialect "C++17"
	location ""
	targetdir "../../Test/build/%{cfg.buildcfg}"
	objdir "obj/%{cfg.buildcfg}"
	files { "../../Test/src/**.hpp", "../../Test/src/**.cpp", "../../Test/src/**.glsl" }
	
	includedirs {
		"$(VULKAN_SDK)/include",
		SoftwareCoreInclude,
		VulkanShaderCompilerInclude
	}
	
	links {
		"SoftwareCore",
		"VulkanShaderCompiler"
	}
	
	filter "system:windows"
		links {
			"$(VULKAN_SDK)/lib/vulkan-1.lib"
		}
	filter "system:linux"
		links {
			"$(VULKAN_SDK)/lib/libvulkan.so"
		}
	filter{}
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "RELEASE" }
		runtime "Release"
		optimize "On"

	filter {}