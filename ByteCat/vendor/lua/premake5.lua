project "Lua"
	kind "StaticLib"
	language "C++"
    cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.c"
	}

	excludes
	{
		"src/lua.c",
		"src/luac.c"
	}

	filter "system:linux"
        pic "on"
        systemversion "latest"

		defines
		{
            "LUA_USE_LINUX"
		}

	filter "system:windows"
		systemversion "latest"

		defines 
		{ 
            "WIN32"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"