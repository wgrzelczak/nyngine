workspace "Nyngolf"
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
IncludeDir["GLM"] = "%{wks.location}/External/glm"
IncludeDir["STB"] = "%{wks.location}/External/stb"
IncludeDir["fx-gltf"] = "%{wks.location}/External/fx-gltf/include"
IncludeDir["fx-gltf-3rd"] = "%{wks.location}/External/fx-gltf/test/thirdparty"


include "premake5_game.lua"
include "premake5_engine.lua"

include "premake5_glfw.lua"
include "premake5_glad.lua"
include "premake5_imgui.lua"