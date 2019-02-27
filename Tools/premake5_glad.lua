project "GLAD"
    location "../External/glad"
    kind "StaticLib"
    language "C"
    
    targetdir (IntDir)
    objdir (OutputDir)

    files
    {
        "%{prj.location}/include/glad/glad.h",
        "%{prj.location}/include/KHR/khrplatform.h",
        "%{prj.location}/src/glad.c"
    }

    includedirs
    {
        "%{prj.location}/include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"


    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"