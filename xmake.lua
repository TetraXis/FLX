-- 2026-05-17 18:12
-- xmake is so much better than CMake.

set_toolchains("clang")

set_plat("windows")
add_rules("mode.release", "mode.debug")
set_languages("c++26")
set_policy("build.c++.modules", true)

set_config("clang", "C:\\C++\\LLVM\\clang+llvm-22.1.5-x86_64-pc-windows-msvc")

add_cxxflags("-stdlib=libc++")
add_ldflags("-stdlib=libc++")

add_defines("FLX_OPT_FORCE_CRT_UCRT")

local core_sources = os.files("CORE/source/*.cpp")
local all_libs = {}

for _, src in ipairs(core_sources) do
    local name = path.basename(src)
    local lib_target = "flx_" .. name
    if is_mode("debug") then
        lib_target = lib_target .. "_d"
    end
    target(lib_target)
        set_kind("static")
        add_files(src)
        add_includedirs("CORE/include")
        -- add module interfaces to every static lib (for dependencies)
        add_files("CORE/include/flx/*.cppm", {public = true})
        if is_mode("debug") then
            add_defines("FLX_OPT_DEBUG")
        else
            add_defines("FLX_OPT_RELEASE")
        end
    table.insert(all_libs, lib_target)
end

target("install_flx")
    set_kind("phony")
    add_deps(all_libs)
    after_build(function ()
        local plat = "$(plat)"
        local arch = "$(arch)"
        local mode = "$(mode)"
        local config_name = string.format("%s-%s-%s", plat, arch, mode)
        local install_root = path.join(os.projectdir(), "INSTALL", config_name)
        local include_dir = path.join(install_root, "flx_core", "include", "flx")
        local libs_dir = path.join(install_root, "flx_core", "libs")

        if os.isdir(install_root) then
            os.rmdir(install_root)
        end
        os.mkdir(include_dir)
        os.mkdir(libs_dir)

        os.cp("CORE/include/flx/*.hpp", include_dir)
        os.cp("CORE/include/flx/*.cppm", include_dir)
        for _, dir in ipairs(os.dirs("CORE/include/flx/*")) do
            os.cp(dir, include_dir)
        end

        local build_dir = path.join("$(builddir)", plat, arch, mode)
        for _, lib in ipairs(all_libs) do
            local libfile = path.join(build_dir, "lib" .. lib .. ".a")
            if not os.isfile(libfile) then
                libfile = path.join(build_dir, lib .. ".lib")
            end
            if os.isfile(libfile) then
                os.cp(libfile, libs_dir)
            end
        end
    end)

target("flx_core")
    set_kind("binary")
    add_files("CORE/main.cpp")
    -- ensure installation is done before linking
    add_deps("install_flx")
    -- tell the linker where to find the installed static libs
    add_linkdirs(path.join(os.projectdir(), "INSTALL", "$(plat)-$(arch)-$(mode)", "flx_core", "libs"))
    -- link each static library
    for _, lib in ipairs(all_libs) do
        add_links(lib)
    end
    add_includedirs("CORE/include")
    if is_mode("debug") then
        add_defines("FLX_OPT_DEBUG")
    else
        add_defines("FLX_OPT_RELEASE")
    end

target("test_core")
    set_kind("binary")
    add_deps("install_flx")
    add_linkdirs(path.join(os.projectdir(), "INSTALL", "$(plat)-$(arch)-$(mode)", "flx_core", "libs"))
    for _, lib in ipairs(all_libs) do
        add_links(lib)
    end
    add_files("TEST/TEST_CORE/*.cpp")
    add_files("TEST/TEST_CORE/test/*.cppm")
    add_includedirs(path.join("INSTALL", "$(plat)-$(arch)-$(mode)", "flx_core", "include"))
    add_cxxflags("-iquote " .. path.join(os.projectdir(), "INSTALL", "$(plat)-$(arch)-$(mode)", "flx_core", "include"))
    if is_mode("debug") then
        add_defines("FLX_OPT_DEBUG")
    else
        add_defines("FLX_OPT_RELEASE")
    end