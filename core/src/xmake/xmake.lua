target("xmake")
    set_kind("static")

    -- add deps
    add_deps("sv", "lua-cjson", "lua", "lz4", "tbox")
    if is_plat("windows") and has_config("pdcurses") then
        add_deps("pdcurses")
    end

    -- add defines
    add_defines("__tb_prefix__=\"xmake\"")
    if is_mode("debug") then
        add_defines("__tb_debug__", {public = true})
    end

    -- set the auto-generated config.h
    set_configdir("$(buildir)/$(plat)/$(arch)/$(mode)")
    add_configfiles("xmake.config.h.in")

    -- add includes directory
    add_includedirs("..", {interface = true})
    add_includedirs("$(buildir)/$(plat)/$(arch)/$(mode)", {public = true})
    add_includedirs("../xxhash")

    -- add header files
    add_headerfiles("../(xmake/*.h)")
    add_headerfiles("../(xmake/prefix/*.h)")
    add_headerfiles("$(buildir)/$(plat)/$(arch)/$(mode)/xmake.config.h", {prefixdir = "xmake"})

    -- add the common source files
    add_files("**.c|winos/*.c")
    if is_plat("windows", "msys", "cygwin") then
        add_files("winos/*.c")
    end

    -- add options
    add_options("readline")
    if is_plat("windows") then
        add_options("pdcurses")
    else
        add_options("curses")
    end

    -- add defines
    if is_plat("windows") then
        add_defines("UNICODE", "_UNICODE")
    end

