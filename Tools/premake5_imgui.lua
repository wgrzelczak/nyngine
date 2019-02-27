project "ImGui"
    location "../External/ImGui"
    kind "StaticLib"
    language "C"
    
    targetdir (IntDir)
    objdir (OutputDir)

    files
    {
        "%{prj.location}/imconfig.h",
        "%{prj.location}/imgui.h",
        "%{prj.location}/imgui.cpp",
        "%{prj.location}/imgui_draw.cpp",
        "%{prj.location}/imgui_internal.h",
        "%{prj.location}/imgui_widgets.cpp",
        "%{prj.location}/imstb_rectpack.h",
        "%{prj.location}/imstb_textedit.h",
        "%{prj.location}/imstb_truetype.h",
        "%{prj.location}/imgui_demo.cpp"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"


    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"