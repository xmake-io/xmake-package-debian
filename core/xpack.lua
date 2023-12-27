xpack("xmake")
    set_homepage("https://xmake.io")
    set_title("Xmake build utility ($(arch))")
    set_description("A cross-platform build utility based on Lua.")
    set_copyright("Copyright (C) 2015-present, TBOOX Open Source Group")
    set_author("waruqi@gmail.com")
    set_licensefile("../LICENSE.md")
    set_formats("nsis", "zip")
    add_targets("demo")
    set_bindir(".")
    set_iconfile("src/demo/xmake.ico")

    add_components("LongPath")

    on_load(function (package)
        local arch = package:arch()
        if package:is_plat("windows") then
            if arch == "x64" then
                arch = "win64"
            elseif arch == "x86" then
                arch = "win32"
            end
        end
        package:set("basename", "xmake-v$(version)." .. arch)
        local format = package:format()
        if format == "zip" then
            package:set("prefixdir", "xmake")
        end
    end)

    before_package(function (package)
        import("net.http")
        import("utils.archive")
        import("core.base.global")
        local format = package:format()
        if package:is_plat("windows") and (format == "nsis" or format == "zip") then
            local winenv = path.join(os.programdir(), "winenv")
            if os.isdir(winenv) then
                package:add("installfiles", path.join(winenv, "**"), {rootdir = path.directory(winenv)})
            else
                local arch = package:arch()
                local url_7z = "https://github.com/xmake-mirror/7zip/releases/download/19.00/7z19.00-" .. arch .. ".zip"
                local url_curl = "https://curl.se/windows/dl-8.2.1_11/curl-8.2.1_11-win32-mingw.zip"
                local archive_7z = path.join(package:buildir(), "7z.zip")
                local archive_curl = path.join(package:buildir(), "curl.zip")
                local tmpdir_7z = path.join(package:buildir(), "7z")
                local tmpdir_curl = path.join(package:buildir(), "curl")
                local winenv_bindir = path.join(package:buildir(), "winenv", "bin")
                os.mkdir(winenv_bindir)
                http.download(url_7z, archive_7z, {insecure = global.get("insecure-ssl")})
                if archive.extract(archive_7z, tmpdir_7z) then
                    os.cp(path.join(tmpdir_7z, "*"), winenv_bindir)
                else
                    raise("extract 7z.zip failed!")
                end
                http.download(url_curl, archive_curl, {insecure = global.get("insecure-ssl")})
                if archive.extract(archive_curl, tmpdir_curl) then
                    os.cp(path.join(tmpdir_curl, "*", "bin", "*.exe"), winenv_bindir)
                    os.cp(path.join(tmpdir_curl, "*", "bin", "*.crt"), winenv_bindir)
                else
                    raise("extract curl.zip failed!")
                end
                winenv = path.directory(winenv_bindir)
                package:add("installfiles", path.join(winenv, "**"), {rootdir = path.directory(winenv)})
            end
        end
    end)

xpack_component("LongPath")
    set_title("Enable Long Path")
    set_description("Increases the maximum path length limit, up to 32,767 characters (before 256).")
    on_installcmd(function (component, batchcmds)
        batchcmds:rawcmd("nsis", [[
  ${If} $NoAdmin == "false"
    ; Enable long path
    WriteRegDWORD ${HKLM} "SYSTEM\CurrentControlSet\Control\FileSystem" "LongPathsEnabled" 1
  ${EndIf}]])
    end)

xpack("xmakesrc")
    set_homepage("https://xmake.io")
    set_title("Xmake build utility ($(arch))")
    set_description("A cross-platform build utility based on Lua.")
    set_copyright("Copyright (C) 2015-present, TBOOX Open Source Group")
    set_author("waruqi@gmail.com")
    set_formats("srczip", "srctargz", "runself", "srpm")
    set_basename("xmake-v$(version)")
    set_prefixdir("xmake-$(version)")
    set_license("Apache-2.0")
    before_package(function (package)
        import("devel.git")

        local rootdir = path.join(os.tmpfile(package:basename()) .. ".dir", "repo")
        if not os.isdir(rootdir) then
            os.tryrm(rootdir)
            os.cp(path.directory(os.projectdir()), rootdir)

            git.clean({repodir = rootdir, force = true, all = true})
            git.reset({repodir = rootdir, hard = true})
            if os.isfile(path.join(rootdir, ".gitmodules")) then
                git.submodule.clean({repodir = rootdir, force = true, all = true})
                git.submodule.reset({repodir = rootdir, hard = true})
            end
        end

        local extraconf = {rootdir = rootdir}
        package:add("sourcefiles", path.join(rootdir, "core/**|src/pdcurses/**|src/luajit/**|src/tbox/tbox/src/demo/**"), extraconf)
        package:add("sourcefiles", path.join(rootdir, "xmake/**|scripts/vsxmake/**"), extraconf)
        package:add("sourcefiles", path.join(rootdir, "*.md"), extraconf)
        package:add("sourcefiles", path.join(rootdir, "configure"), extraconf)
        package:add("sourcefiles", path.join(rootdir, "scripts/*.sh"), extraconf)
        package:add("sourcefiles", path.join(rootdir, "scripts/man/**"), extraconf)
        package:add("sourcefiles", path.join(rootdir, "scripts/debian/**"), extraconf)
        package:add("sourcefiles", path.join(rootdir, "scripts/msys/**"), extraconf)
    end)

    on_buildcmd(function (package, batchcmds)
        local format = package:format()
        if format == "srpm" then
            batchcmds:runv("./configure")
            batchcmds:runv("make")
        end
    end)

    on_installcmd(function (package, batchcmds)
        local format = package:format()
        if format == "runself" then
            batchcmds:runv("./scripts/get.sh", {"__local__"})
        elseif format == "srpm" then
            batchcmds:runv("make", {"install", path(package:install_rootdir(), function (p) return "PREFIX=" .. p end)})
        end
    end)
