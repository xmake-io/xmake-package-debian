target("demo")

    -- disable this target if only build libaries
    if has_config("onlylib") then
        set_default(false)
    end

    -- add deps
    add_deps("xmake")

    -- make as a binary
    set_kind("binary")

    -- add definitions
    add_defines("__tb_prefix__=\"xmake\"")

    -- add includes directory
    add_includedirs("$(projectdir)", "$(projectdir)/src")

    -- add common source files
    add_files("**.c")

    -- add resource files (it will be enabled after publishing new version)
    if is_plat("windows") then
        add_files("*.rc")
    end

    -- add links
    if is_plat("windows") then
        add_syslinks("ws2_32", "advapi32", "shell32")
        add_ldflags("/export:malloc", "/export:free", "/export:memmove")
    elseif is_plat("android") then
        add_syslinks("m", "c")
    elseif is_plat("macosx") and is_config("runtime", "luajit") then
        add_ldflags("-all_load", "-pagezero_size 10000", "-image_base 100000000")
    elseif is_plat("mingw") then
        add_ldflags("-static-libgcc", {force = true})
    elseif is_plat("haiku") then
        add_syslinks("pthread", "network", "m", "c")
    else
        add_syslinks("pthread", "dl", "m", "c")
    end

    -- enable xp compatibility mode
    if is_plat("windows") then
        if is_arch("x86") then
            add_ldflags("/subsystem:console,5.01")
        else
            add_ldflags("/subsystem:console,5.02")
        end
    end

    -- copy target to the build directory
    after_build(function (target)
        os.cp(target:targetfile(), "$(buildir)/xmake" .. (is_plat("windows") and ".exe" or ""))
    end)

