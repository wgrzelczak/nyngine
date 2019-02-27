workspace "golf_cpp"
    location ".."
    architecture "x64"
    startproject "Game"

    configurations
    {
        "Debug",
        "Release"
    }


OutputDir = "%{wks.location}/Build/bin/%{prj.name}/%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"
IntDir    = "%{wks.location}/Build/obj/%{prj.name}/%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

IncludeDir = {}
IncludeDir["SPDLOG"] = "%{wks.location}/External/spdlog/include"
IncludeDir["GLFW"] = "%{wks.location}/External/glfw/include"
IncludeDir["GLAD"] = "%{wks.location}/External/glad/include"
IncludeDir["ImGui"] = "%{wks.location}/External/ImGui"



project "Game"
    location "../Game"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

    targetdir (OutputDir)
    objdir (IntDir)

    pchheader "pch.h"
    pchsource "%{prj.location}/src/pch.cpp"

    files
    {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.hpp",
        "%{prj.location}/src/**.c",
        "%{prj.location}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.location}/src",
        "%{IncludeDir.SPDLOG}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}"
    }

    links 
    { 
        "GLFW",
        "GLAD",
        "ImGui"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        defines
        {
           "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines ""
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines ""
        runtime "Release"
        optimize "On"

include "premake5_glfw.lua"
include "premake5_glad.lua"
include "premake5_imgui.lua"