project "Nyngine"
    location "../Nyngine"
    kind "StaticLib"
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
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/src/**.inl"
    }

    includedirs
    {
        "%{prj.location}/src",
        "%{IncludeDir.SPDLOG}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.GLM}",
        "%{IncludeDir.STB}",
        "%{IncludeDir.tinyobjloader}"
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