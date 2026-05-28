// 2026-May-28 15:41
// flx_build uses standard lib provided by compiler.
// See synopsis and example (flx_build.cpp) on how to set it up and use it.
// This header provides functions for build control. Use "flx_build.cpp" as your meta-build programm.
// By default flx_build does not use cache or does anything without user input.
// It was made out of frustration from CMake, xmake and other build systems.
// Everything is noexcept so if anything fails, build stops.
// Only not unessential functions can fail.

#define FLX_BUILD_VERSION "0.0.0"
#define FLX_BUILD_VERSION_MAJOR 0
#define FLX_BUILD_VERSION_MINOR 0
#define FLX_BUILD_VERSION_PATCH 0

#include <memory>
#include <vector>
#include <string>
#include <filesystem>

namespace flx::build
{
    enum struct compiler_family_e : int8_t
    {
        unknown,
        clang,
        gcc,
        msvc,
        apple_clang
    };

    enum struct cpp_standard_e : int8_t
    {
        default, latest,
        cpp98, cpp03, cpp11, cpp14, cpp17, cpp20, cpp23, cpp26,
        gnu98, gnu11, gnu14, gnu17, gnu20, gnu23, gnu26
    };

    enum struct c_standard_e : uint8_t
    {
        default, latest,
        c89, c99, c11, c17, c23,
        gnu89, gnu99, gnu11, gnu17, gnu23
    };

    struct toolchain_flags_t
    {
        std::vector< std::string > language_standard{};
        std::vector< std::string > optimizations{};
        std::vector< std::string > warning{};
        std::vector< std::string > debug{};
        std::vector< std::string > preprocessor{};
        std::vector< std::string > user_includes{};
        std::vector< std::string > system_includes{};
        std::vector< std::string > output_control{};
        std::vector< std::string > dependency_generation{};
        std::vector< std::string > code_generation{};
        std::vector< std::string > linker{};
        std::vector< std::string > diagnostics{};
        std::vector< std::string > miscellaneous{};
    };

    struct toolchain_paths_t
    {
        std::filesystem::path c_compiler{};
        std::filesystem::path cpp_compiler{};
        std::filesystem::path linker{};
        std::filesystem::path archiver{};
        std::filesystem::path assembler{};
    };

    struct toolchain_t
    {
        toolchain_paths_t paths{};
        toolchain_flags_t flags{};
        std::vector< std::string > defines{};

        compiler_family_e family = compiler_family_e::unknown;
        // cpp_standard_e cpp_standard = cpp_standard_e::default;
        // c_standard_e c_standard = c_standard_e::default;
    };

    enum struct target_type_e : int8_t
    {
        unknown,
        executable,
        interface_library,
        static_library,
        dynamic_library,
        phony
    };

    struct target_t
    {
        toolchain_flags_t flags{}; // will override toolchain flags per category (leaving one category empty will result in global setting used)
        std::string name = "Unnamed target";
        std::vector< std::string > dependencies{};
        std::vector< std::filesystem::path > sources{};
        std::filesystem::path output_path{};
        std::vector< std::filesystem::path > files_build_order;
        // std::unordered_map< std::filesystem::path, std::vector< std::filesystem::path > > file_deps; // should be calculated and discarded when populating files_build_order
        target_type_e type = target_type_e::unknown;
    };

    struct workplace_t
    {
        std::string name = "Unnamed workplace";
        toolchain_t toolchain{};

        std::filesystem::path root_dir{};
        std::filesystem::path output_dir{};
        std::string configuration{}; // release, debug, ...
        // bool is_shared_library_build = false;

        std::vector< std::string > global_defines{};
        std::vector< std::filesystem::path > global_user_includes{};
        std::vector< std::filesystem::path > global_system_includes{};

        std::vector< std::unique_ptr<target_t> > targets{};
        std::vector< std::string > build_order; // target names

        // TODO: add dir creation if non existant

        void set_root_dir(const std::filesystem::path& root_path) noexcept
        {
            std::error_code ec;
            std::filesystem::path abs_path = std::filesystem::absolute(root_path, ec);

            if (ec)
            {
                std::cerr << "workplace_t::set_root_dir: Error resolving absolute path: " << ec.message() << '\n';
                std::exit(EXIT_FAILURE);
            }

            if (!std::filesystem::exists(abs_path, ec))
            {
                std::cerr << "workplace_t::set_root_dir: Path does not exist: " << abs_path.string() << '\n';
                std::exit(EXIT_FAILURE);
            }

            if (!std::filesystem::is_directory(abs_path, ec))
            {
                std::cerr << "workplace_t::set_root_dir: Not a directory: " << abs_path.string() << '\n';
                std::exit(EXIT_FAILURE);
            }

            root_dir = abs_path;
        }
        std::filesystem::path& get_root_dir() noexcept
        {
            return root_dir;
        }
        const std::filesystem::path& get_root_dir() const noexcept
        {
            return root_dir;
        }

        void set_output_dir(const std::filesystem::path& output_path) noexcept
        {
            std::error_code ec;
            std::filesystem::path abs_path = std::filesystem::absolute(output_path, ec);

            if (ec)
            {
                std::cerr << "workplace_t::set_output_dir: Error resolving absolute path: " << ec.message() << '\n';
                std::exit(EXIT_FAILURE);
            }

            if (!std::filesystem::exists(abs_path, ec))
            {
                std::cerr << "workplace_t::set_output_dir: Path does not exist: " << abs_path.string() << '\n';
                std::exit(EXIT_FAILURE);
            }

            if (!std::filesystem::is_directory(abs_path, ec))
            {
                std::cerr << "workplace_t::set_output_dir: Not a directory: " << abs_path.string() << '\n';
                std::exit(EXIT_FAILURE);
            }

            output_dir = abs_path;
        }
        std::filesystem::path& get_output_dir() noexcept
        {
            return output_dir;
        }
        const std::filesystem::path& get_output_dir() const noexcept
        {
            return output_dir;
        }

        void set_configuration(const std::string& conf) noexcept
        {
            configuration = conf;
        }
        std::string& get_configuration() noexcept
        {
            return configuration;
        }
        const std::string& get_configuration() const noexcept
        {
            return configuration;
        }

        void add_define(const std::string& define) noexcept
        {
            global_defines.emplace_back(define);
        }
        bool remove_define(const std::string& define)
        {
            return std::erase(global_defines, define) > 0;
        }
        std::vector< std::string >& get_defines() noexcept
        {
            return global_defines;
        }
        const std::vector< std::string >& get_defines() const noexcept
        {
            return global_defines;
        }

        void add_include_dir(const std::filesystem::path& include_path) noexcept
        {
            std::error_code ec;
            std::filesystem::path abs_path = std::filesystem::absolute(include_path, ec);

            if (ec)
            {
                std::cerr << "workplace_t::add_include_dir: Error resolving absolute path: " << ec.message() << '\n';
                std::exit(EXIT_FAILURE);
            }

            if (!std::filesystem::exists(abs_path, ec))
            {
                std::cerr << "workplace_t::add_include_dir: Path does not exist: " << abs_path.string() << '\n';
                std::exit(EXIT_FAILURE);
            }

            if (!std::filesystem::is_directory(abs_path, ec))
            {
                std::cerr << "workplace_t::add_include_dir: Not a directory: " << abs_path.string() << '\n';
                std::exit(EXIT_FAILURE);
            }

            global_user_includes.emplace_back(abs_path);
        }
        bool remove_include_dir(const std::filesystem::path& include_path)
        {
            return std::erase(global_user_includes, include_path) > 0;
        }
        std::vector< std::filesystem::path >& get_includes() noexcept
        {
            return global_user_includes;
        }
        const std::vector< std::filesystem::path >& get_includes() const noexcept
        {
            return global_user_includes;
        }

        void add_system_include_dir(const std::filesystem::path& system_include_path) noexcept
        {
            std::error_code ec;
            std::filesystem::path abs_path = std::filesystem::absolute(system_include_path, ec);

            if (ec)
            {
                std::cerr << "workplace_t::add_system_include_dir: Error resolving absolute path: " << ec.message() << '\n';
                std::exit(EXIT_FAILURE);
            }

            if (!std::filesystem::exists(abs_path, ec))
            {
                std::cerr << "workplace_t::add_system_include_dir: Path does not exist: " << abs_path.string() << '\n';
                std::exit(EXIT_FAILURE);
            }

            if (!std::filesystem::is_directory(abs_path, ec))
            {
                std::cerr << "workplace_t::add_system_include_dir: Not a directory: " << abs_path.string() << '\n';
                std::exit(EXIT_FAILURE);
            }

            global_system_includes.emplace_back(abs_path);
        }
        bool remove_system_include_dir(const std::filesystem::path& system_include_path)
        {
            return std::erase(global_system_includes, system_include_path) > 0;
        }
        std::vector< std::filesystem::path >& get_system_includes() noexcept
        {
            return global_system_includes;
        }
        const std::vector< std::filesystem::path >& get_system_includes() const noexcept
        {
            return global_system_includes;
        }

        void create_target(const std::string& target_name) noexcept
        {
            auto it = std::find_if(targets.begin(), targets.end(),
                [&](const std::unique_ptr<target_t>& ptr)
                {
                    return ptr && ptr->name == target_name;
                });
            if (it != targets.end())
            {
                std::cerr << "workspace_t::create_target: Target with the name: \"" << target_name << "\" already existed.\n";
                std::exit(EXIT_FAILURE);
            }

            targets.emplace_back(std::make_unique<target_t>());
            targets.back()->name = target_name;
        }
        void add_target(std::unique_ptr<target_t> target) noexcept
        {
            targets.emplace_back(std::move(target));
        }
        bool remove_target(const std::string& target_name) noexcept
        {
            return std::erase_if(targets,
                [&](const std::unique_ptr<target_t>& ptr)
                {
                    return ptr && ptr->name == target_name;
                }) > 0;
        }
        target_t& operator [] (const std::string& target_name) noexcept
        {
            auto it = std::find_if(targets.begin(), targets.end(),
                [&](const std::unique_ptr<target_t>& ptr)
                { 
                    return ptr && ptr->name == target_name;
                });
            if (it != targets.end())
            {
                return **it;
            }

            std::cerr << "workplace_t::operator []: No target with name: \"" << target_name << "\" found.\n";
            std::exit(EXIT_FAILURE);
        }
        const target_t& operator [] (const std::string& target_name) const noexcept
        {
            auto it = std::find_if(targets.begin(), targets.end(),
                [&](const std::unique_ptr<target_t>& ptr)
                { 
                    return ptr && ptr->name == target_name;
                });
            if (it != targets.end())
            {
                return **it;
            }

            std::cerr << "workplace_t::operator []: No target with name: \"" << target_name << "\" found.\n";
            std::exit(EXIT_FAILURE);
        }

    }; // workplace_t

    std::filesystem::path find_root_dir(const std::string& build_file = "flx_build.cpp") noexcept
    {
        static constexpr size_t MAX_SEARCH_DEPTH = 10;

        std::filesystem::path current = std::filesystem::current_path();
        for (size_t i = 0; i < MAX_SEARCH_DEPTH; i++)
        {
            if (std::filesystem::exists(current / build_file))
            {
                return current;
            }
            if (current == current.root_path())
            {
                std::cerr << "find_root_dir: Could not find build file: Search reached disc root.\n";
                std::exit(EXIT_FAILURE);
            }
            current = current.parent_path();
        }
        std::cerr << "find_root_dir: Could not find build file: Max search depth reached.\n";
        std::exit(EXIT_FAILURE);
    } // find_root_dir
} // flx::build