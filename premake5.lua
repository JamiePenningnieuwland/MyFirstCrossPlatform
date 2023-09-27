workspace "Gauntlet"
    architecture "x64"
    startproject "Windows"

    configurations { "Debug","Release" }


project "Windows"
    location "Gauntlet"
    kind "ConsoleApp"
    cppdialect "C++17"
    language "C++"
    staticruntime "on"

    targetdir ('bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}')
    objdir ('bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}')

    files 
    {
        "Gauntlet/src/**.h",
        "Gauntlet/src/**.cpp",
        "Windows/**.h",
        "Windows/**.cpp",
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "WINDOWS"
        }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "on"
        --[[
project "Raspberry"
    location "Raspberry"
    kind "ConsoleApp"
    cppdialect "C++17"
    language "C++"
    staticruntime "on"

    targetdir ("bin/ .. outputdir .. /%{prj.name}")
    objdir ("bin-int/ .. outputdir .. /%{prj.name}")

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    filter "system:linux"
        systemversion "latest"

        defines
        {
            "LINUX",
        }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "RELEASE"
        runtime "Release"
        optimize "on"
        --]]