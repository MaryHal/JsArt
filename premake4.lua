solution "Caves"
    configurations { "Debug", "Release" }
    platforms { "native", "x32", "x64" }

    ---------------------------------------
    -- Test project
    project "Caves"
        language "C++"

        files { "src/**", "game/**" }
        includedirs { "src/" }

        targetdir "bin"
        targetname "Test"

        ---------------------------------------
        -- Link static libraries
        --
        links { "GLEW", "sfml-graphics", "sfml-window", "sfml-audio", "sfml-system" }
        configuration "linux"
            targetprefix "linux_"
            links { "GL", "X11", "Xrandr", "pthread", "m" }

        configuration "windows"
            targetprefix "windows_"

        ---------------------------------------
        -- 32bit / 64bit
        configuration { "native or x64" }
            targetsuffix "64"

        configuration "x32"
            targetsuffix "32"

        configuration "Debug"
            kind "ConsoleApp"
            defines "DEBUG"
            flags { "Symbols", "ExtraWarnings" }

        configuration "Release"
            kind "ConsoleApp"
            flags { "Optimize", "ExtraWarnings" }
