-- 2026-05-17 18:12
-- xmake is so much better than CMake.
-- 2026-05-26 19:17
-- no, xmake is also shit
-- i'm doing my own build system

set_toolchains("clang")

set_plat("windows")
add_rules("mode.release", "mode.debug")
set_languages("c++26")

set_config("clang", "C:\\C++\\LLVM\\clang+llvm-23.1.0-x86_64-pc-windows-msvc")

add_cxxflags("-stdlib=libc++")
add_ldflags("-stdlib=libc++")

add_defines("FLX_OPT_FORCE_CRT_UCRT")

if is_mode("debug") then
    add_defines("FLX_OPT_DEBUG")
else
    add_defines("FLX_OPT_RELEASE")
end

set_policy("build.c++.modules", true)
set_policy("build.ccache", false)
-- set_policy("build.fence", true)

-- For each .cpp exactly one .lib
local all_libs = {}
for _, sourcefile in ipairs(os.files("CORE/source/*.cpp")) do
    local name = path.basename(sourcefile)
	local local_root = path.join(os.projectdir(), "CORE")
    
    target(name) do
        set_kind("static")
        add_files(local_root .. "/include/flx/*.cppm")
        add_includedirs(local_root .. "/include")
        add_files(sourcefile)
        
        if is_mode("debug") then
            set_basename(name .. "_d")
        end
    end

    local libname = name
    if is_mode("debug") then
        libname = libname .. "_d"
    end
    table.insert(all_libs, libname)
end

target("flx_core") do
    -- set_policy("build.fence", true)
	set_kind("binary")
	local local_root = path.join(os.projectdir(), "CORE")
    -- running xmake commands clears this folder???????
    local install_dir = path.join(os.projectdir(), "INSTALL", "$(plat)-$(arch)-$(mode)", "flx_core")
    set_targetdir(install_dir)

    add_files(local_root .. "/include/flx/*.cppm")
    add_includedirs(local_root .. "/include")
    add_files(local_root .. "/main.cpp")

    for _, libname in ipairs(all_libs) do
        add_deps(libname)      -- builds the library first
        add_links(libname)     -- links against it
    end

    -- xmake runs this when just doing 'xmake', wtf?
    before_build(function (target)
        -- print("flx_core::before_build...")
        if os.isdir(install_dir) then
            os.rmdir(install_dir)
        end
    end)

    after_build(function (target)
        print("flx_core::after_build...")
        os.cp(path.join(local_root, "include"), path.join(target:targetdir(), "include"), {force = true})
        local libs_install_dir = path.join(target:targetdir(), "libs")
        os.mkdir(libs_install_dir)
        local libs_built_dir = path.join(os.projectdir(), "build", "$(plat)", "$(arch)", "$(mode)", "*.lib")
        os.cp(libs_built_dir, libs_install_dir, {force = true})
    end)
end -- target("flx_core")

target("test_core") do
    -- set_policy("build.fence", true)
	set_kind("binary")
	local local_root = path.join(os.projectdir(), "TEST", "TEST_CORE")
    local install_dir = path.join(os.projectdir(), "INSTALL", "$(plat)-$(arch)-$(mode)", "flx_core")

    -- add_deps("flx_core", {inherit = false})

    add_files(local_root .. "/test/*.cppm")
    -- add_includedirs(local_root .. "/include")
    add_files(local_root .. "/main.cpp")

    add_files(install_dir .. "/include/flx/*.cppm")
    add_includedirs(install_dir .. "/include")

    -- on_load(function (target)

    -- end)

    before_build(function (target)
    --     print(install_dir .. "/include")
    --     print("flx_core::before_build...")
    --     target:add("includedirs", install_dir .. "/include")
    --     target:add("files", install_dir .. "/include/flx/*.cppm")
    --     -- TODO: link against libs
    end)
end -- target("test_core")

target("flxb") do
	set_kind("binary")
	local local_root = path.join(os.projectdir(), "FLX_BUILD")
    local install_dir = "C:/C++/flx_build/"
    
    set_targetdir(install_dir .. "/bin/")
    set_installdir(install_dir .. "/bin/")

    add_files(local_root .. "/source/main.cpp")
    add_files(local_root .. "/source/flx_build.cpp")
    add_files(local_root .. "/source/flx_build_cli.cpp")
    add_files(local_root .. "/source/flx_build_tables.cpp")
    add_includedirs(local_root .. "/include")

    before_build(function (target)
        if os.isdir(install_dir) then
            os.rmdir(install_dir)
        end
    end)

    after_build(function (target)
        os.cp(path.join(local_root, "include/flx_build.hpp"), install_dir .. "/files/", {force = true})
        os.cp(path.join(local_root, "source/flx_build.cpp"), install_dir .. "/files/", {force = true})
    end)
end -- target("flxb")


-- target("target_name") do
-- 	-- Load phase
--     on_load(function (target)
--     end)
-- 
--     -- Config phase
--     on_config(function (target)
--     end)
-- 
--     -- Prepare phase (C++ modules, etc.)
--     before_prepare(function (target)
--     end)
--     on_prepare(function (target)
--     end)
--     after_prepare(function (target)
--     end)
-- 
--     -- Build phase (compilation)
--     before_build(function (target)
--     end)
--     -- For each source file (optional)
--     on_build_file(function (target, sourcefile)
--     end)
--     -- Full build override (rare)
--     on_build(function (target)
--     end)
--     after_build(function (target)
--     end)
-- 
--     -- Link phase
--     before_link(function (target)
--     end)
--     on_link(function (target)
--     end)
--     after_link(function (target)
--     end)
-- 
--     -- Clean phase
--     before_clean(function (target)
--     end)
--     on_clean(function (target)
--     end)
--     after_clean(function (target)
--     end)
-- 
--     -- Install phase
--     before_install(function (target)
--     end)
--     on_install(function (target)
--     end)
--     after_install(function (target)
--     end)
-- 
--     -- Uninstall phase
--     before_uninstall(function (target)
--     end)
--     on_uninstall(function (target)
--     end)
--     after_uninstall(function (target)
--     end)
-- 
--     -- Run phase (for executables)
--     on_run(function (target)
--     end)
-- end -- target("flx_core")


-- -- static libs
-- local core_sources = os.files("CORE/source/*.cpp")
-- local all_libs = {}
-- for _, src in ipairs(core_sources) do
--     local name = path.basename(src)
--     local lib_target = "flx_" .. name
--     if is_mode("debug") then
--         lib_target = lib_target .. "_d"
--     end
--     target(lib_target)
--         set_kind("static")
--         add_files(src)
--         add_includedirs("CORE/include")
--         -- add module interfaces to every static lib (for dependencies)
--         add_files("CORE/include/flx/*.cppm", {public = true})
--         if is_mode("debug") then
--             add_defines("FLX_OPT_DEBUG")
--         else
--             add_defines("FLX_OPT_RELEASE")
--         end
--     table.insert(all_libs, lib_target)
-- end
-- 
-- target("clean_all")
--     set_kind("phony")
--     on_run(function ()
--         local function rmdir(path)
--             if os.isdir(path) then
--                 os.rmdir(path)
--                 print("removed " .. path)
--             end
--         end
--         local function rmfile(path)
--             if os.isfile(path) then
--                 os.remove(path)
--                 print("removed " .. path)
--             end
--         end
--         rmdir("build")
--         rmdir(".xmake")
--         rmfile("xmake.lua.local")
--         rmfile(".clang-format")
--         rmfile(".clang-tidy")
--         print("Full clean completed. Run 'xmake f' to reconfigure.")
--     end)
-- 
-- target("install_flx")
--     set_kind("phony")
--     add_deps(all_libs, {inherit = false})
--     after_build(function ()
--         local plat = "$(plat)"
--         local arch = "$(arch)"
--         local mode = "$(mode)"
--         local config_name = string.format("%s-%s-%s", plat, arch, mode)
--         local install_root = path.join(os.projectdir(), "INSTALL", config_name)
--         local include_dir = path.join(install_root, "flx_core", "include", "flx")
--         local libs_install_dir = path.join(install_root, "flx_core", "libs")
-- 
--         if os.isdir(install_root) then
--             os.rmdir(install_root)
--         end
--         os.mkdir(include_dir)
--         os.mkdir(libs_install_dir)
-- 
--         os.cp("CORE/include/flx/*.hpp", include_dir)
--         os.cp("CORE/include/flx/*.cppm", include_dir)
--         for _, dir in ipairs(os.dirs("CORE/include/flx/*")) do
--             os.cp(dir, include_dir)
--         end
-- 
--         local build_dir = path.join("$(builddir)", plat, arch, mode)
--         for _, lib in ipairs(all_libs) do
--             local libfile = path.join(build_dir, "lib" .. lib .. ".a")
--             if not os.isfile(libfile) then
--                 libfile = path.join(build_dir, lib .. ".lib")
--             end
--             if os.isfile(libfile) then
--                 os.cp(libfile, libs_install_dir)
--             end
--         end
--     end)
-- 
-- target("flx_core")
--     set_kind("binary")
--     before_build(function (target)
--         import("core.base.task")
--         -- Run clean_all (fully, await)
--         task.run("clean_all", {await = true})
--         -- Run install_flx (fully, await) – this will also build the static libs because install_flx depends on them
--         task.run("install_flx", {await = true})
--     end)
--     add_files("CORE/main.cpp")
--     add_linkdirs(path.join(os.projectdir(), "INSTALL", "$(plat)-$(arch)-$(mode)", "flx_core", "libs"))
--     for _, lib in ipairs(all_libs) do
--         add_links(lib)
--     end
--     add_includedirs("CORE/include")
--     if is_mode("debug") then
--         add_defines("FLX_OPT_DEBUG")
--     else
--         add_defines("FLX_OPT_RELEASE")
--     end
-- 
-- target("test_core")
--     set_kind("binary")
--     before_build(function (target)
--         import("core.base.task")
--         -- Run clean_all and install_flx before building tests
--         task.run("clean_all", {await = true})
--         task.run("flx_core", {await = true})
--     end)
--     add_linkdirs(path.join(os.projectdir(), "INSTALL", "$(plat)-$(arch)-$(mode)", "flx_core", "libs"))
--     for _, lib in ipairs(all_libs) do
--         add_links(lib)
--     end
--     add_files("TEST/TEST_CORE/*.cpp")
--     add_files("TEST/TEST_CORE/test/*.cppm")
--     add_includedirs(path.join("INSTALL", "$(plat)-$(arch)-$(mode)", "flx_core", "include"))
--     add_cxxflags("-iquote " .. path.join(os.projectdir(), "INSTALL", "$(plat)-$(arch)-$(mode)", "flx_core", "include"))
--     if is_mode("debug") then
--         add_defines("FLX_OPT_DEBUG")
--     else
--         add_defines("FLX_OPT_RELEASE")
--     end