add_rules("mode.debug", "mode.release")

target("${TARGETNAME}")
    set_kind("binary")
    add_files("src/*.c")

${FAQ}
