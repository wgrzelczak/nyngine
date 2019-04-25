project "Game"
    location "../Game"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"


    debugdir "$(SolutionDir)"

    targetdir (OutputDir)
    objdir (IntDir)

--  pchheader "pch.h"
--  pchsource "%{prj.location}/src/pch.cpp"

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
        "%{wks.location}/Nyngine/src",
        "%{IncludeDir.SPDLOG}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}"
    
    }

    links 
    {
    	"Nyngine"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        defines
        {
        }

    filter "configurations:Debug"
        defines ""
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines ""
        runtime "Release"
        optimize "On"