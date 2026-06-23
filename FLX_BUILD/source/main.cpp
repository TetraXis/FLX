#include "flx_build.hpp"

#include <iostream>
#include <filesystem>
#include <regex>

using namespace flx::build;

compiler_family_e compiler_family = compiler_family_e::unknown;
std::filesystem::path installed_path = "";
std::filesystem::path compiler_tools_path = "";
std::filesystem::path temp_dir_path = "";
std::filesystem::path config_path = "";
std::filesystem::path root_path = "";
std::filesystem::path flx_build_cpp_path = "";
std::filesystem::path flx_build_hpp_path = "";

void save_cfg(const std::filesystem::path& cfg_path) noexcept
{
    std::cout << INFO << "Saving cfg: \"" << cfg_path.string() << "\"...\n";

    if (compiler_tools_path.empty() || compiler_family == compiler_family_e::unknown)
    {
        std::cout << WARN << "Saving aborted: Missing compiler path or family\n";
        return;
    }

    std::ofstream cfg(cfg_path, std::ios::out | std::ios::trunc);
    if (!cfg.is_open())
    {
        std::cerr << ERR << "flx_build::save_cfg: Failed to open config file: \"" << cfg_path.string() << "\"\n";
        std::exit(EXIT_FAILURE);
    }

    switch (compiler_family)
    {
        case compiler_family_e::clang:
            cfg << "compiler_family = \"Clang\"\n";
            break;
        case compiler_family_e::gcc:
            cfg << "compiler_family = \"GCC\"\n";
            break;
        case compiler_family_e::msvc:
            cfg << "compiler_family = \"MSVC\"\n";
            break;
        default:
            cfg << "compiler_family = \"UNKNOWN\"\n";
            break;
    }
    cfg << "compiler_tools_path = \"" << compiler_tools_path.string() << "\"\n";
    cfg.close();
    std::cout << INFO << "Saving finished\n";
}

void config_dialog(const std::filesystem::path& cfg_path) noexcept
{
    static std::regex EXIT_RGX("\\s*exit\\s*");
    static std::regex COMPILER_FAMILY_RGX("\\s*family\\s*(.+)");
    static std::regex COMPILER_PATH_RGX("\\s*path\\s*\"(.+)\"");
    std::smatch match;

    std::cout << INFO << "Settings mode.\n";
    std::cout << INFO << "\tTo set compiler family type: family {Clang/GCC/MSVC}\n";
    std::cout << INFO << "\tTo set compiler tools path: path \"{full path to bin/}\"\n";
    std::cout << INFO << "\tTo exit: exit\n";

    std::string user_input = "";

    while (true)
    {
        std::cout << USER;
        std::getline(std::cin, user_input);

        if (std::regex_search(user_input, match, EXIT_RGX))
        {
            std::cout << INFO << "Exiting...\n";
            break;
        }
        else if (std::regex_search(user_input, match, COMPILER_FAMILY_RGX))
        {
            std::string compiler_family_str = match[1].str();

            if (compiler_family_str == "Clang")
            {
                compiler_family = compiler_family_e::clang;
                std::cout << INFO << "Compiler family type set\n";
            }
            else if (compiler_family_str == "GCC")
            {
                compiler_family = compiler_family_e::gcc;
                std::cout << INFO << "Compiler family type set\n";
            }
            else if (compiler_family_str == "MSVC")
            {
                compiler_family = compiler_family_e::msvc;
                std::cout << INFO << "Compiler family type set\n";
            }
            else
            {
                compiler_family = compiler_family_e::unknown;
                std::cerr << ERR << "Unsupported compiler: \"" << compiler_family_str << "\"\n";
            }
        }
        else if (std::regex_search(user_input, match, COMPILER_PATH_RGX))
        {
            compiler_tools_path = match[1].str();
            if (file_exists(compiler_tools_path))
            {
                std::cout << INFO << "Compiler path set\n";
            }
            else
            {
                compiler_tools_path = "";
                std::cerr << ERR << "Compiler path is invalid\n";
            }
        }
    }

    save_cfg(cfg_path);
}

void load_config(const std::filesystem::path& cfg_path) noexcept
{
    std::cout << INFO << "Loading config...\n";

    static std::regex COMPILER_FAMILY_RGX("\\s*compiler_family\\s*=\\s*\"(.*)\"");
    static std::regex COMPILER_PATH_RGX("\\s*compiler_tools_path\\s*=\\s*\"(.*)\"");
    std::smatch match;

    std::ifstream cfg(cfg_path);
    if (!cfg.is_open())
    {
        std::cerr << ERR << "Failed to open config file: " << cfg_path.string() << '\n';
        std::exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(cfg, line))
    {
        if (std::regex_search(line, match, COMPILER_FAMILY_RGX))
        {
            std::string compiler_family_str = match[1].str();

            if (compiler_family_str == "Clang")
            {
                compiler_family = compiler_family_e::clang;
            }
            else if (compiler_family_str == "GCC")
            {
                compiler_family = compiler_family_e::gcc;
            }
            else if (compiler_family_str == "MSVC")
            {
                compiler_family = compiler_family_e::msvc;
            }
            else
            {
                compiler_family = compiler_family_e::unknown;
            }
        }
        else if (std::regex_search(line, match, COMPILER_PATH_RGX))
        {
            compiler_tools_path = match[1].str();
        }
    }
    cfg.close();

    if ((compiler_tools_path == "" || !std::filesystem::exists(compiler_tools_path)) && compiler_family == compiler_family_e::unknown)
    {
        std::cout << INFO << "flx_build::load_config: Missing settings, run \"" << BRIGHT_WHITE << "flxb config" << RESET << "\"\n";
        std::exit(EXIT_FAILURE);
    }
    else if (compiler_family == compiler_family_e::unknown)
    {
        std::cout << INFO << "flx_build::load_config: Missing compiler family, run \"" << BRIGHT_WHITE << "flxb config" << RESET << "\"\n";
        std::exit(EXIT_FAILURE);
        config_dialog(cfg_path);
    }
    else if (compiler_tools_path == "" || !std::filesystem::exists(compiler_tools_path))
    {
        std::cout << INFO << "flx_build::load_config: Missing compiler path, run \"" << BRIGHT_WHITE << "flxb config" << RESET << "\"\n";
        std::exit(EXIT_FAILURE);
    }

    std::cout << INFO << "Loading finished\n";

}

std::filesystem::path find_config(const std::filesystem::path& exe_path) noexcept
{
    std::filesystem::path exe_dir = exe_path.parent_path();

    std::filesystem::path cfg_path = exe_dir.parent_path() / "cfg" / "config.cfg"; // yay, hardcoded path!
    if (std::filesystem::exists(cfg_path) && std::filesystem::is_regular_file(cfg_path))
    {
        return cfg_path;
    }

    create_file(cfg_path);
    return cfg_path;
}

void parse_args(int argc, char* argv[]) noexcept
{
    std::cout << INFO << "Passed argv:\n";

    for (size_t i = 0; i < argc; i++)
    {
        std::cout << BRIGHT_BLACK << "[" << i << "] " << RESET << argv[i] << '\n';
    }

    for (int argi = 1; argi < argc; argi++)
    {
        if (std::strcmp(argv[argi], "config") == 0)
        {
            config_dialog(config_path);
            std::exit(EXIT_SUCCESS);
        }
        else if (std::strcmp(argv[argi], "def") == 0)
        {
            compiler_tools_path = "C:\\C++\\LLVM\\clang+llvm-22.1.5-x86_64-pc-windows-msvc";
            compiler_family = compiler_family_e::clang;
            save_cfg(config_path);
        }
    }
}

std::filesystem::path find_build_source(const std::filesystem::path& root, const std::string& source_name = "flx_build.cpp") noexcept
{
    if (file_exists(root / source_name))
    {
        return root / source_name;
    }
    else
    {
        std::cerr << ERR << "Failed to find build source: " << (root / source_name).string() << '\n';
        std::exit(EXIT_FAILURE);
    }
}

std::filesystem::path find_build_header(const std::filesystem::path& root, const std::string& header_name = "flx_build.hpp") noexcept
{
    if (file_exists(root / header_name))
    {
        return root / header_name;
    }
    else if (file_exists(installed_path / "files" / header_name))
    {
        std::cout << INFO << "Failed to find primary header: \"" << (root / header_name).string() << "\"\n";
        std::cout << INFO << "Used backup header instead: \"" << (installed_path / "files" / header_name).string() << "\"\n";
        return installed_path / "files" / header_name; // yay another hardcoded path
    }
    else
    {
        std::cerr << ERR << "Failed to find primary build header: \"" << (root / header_name).string() << "\"\n";
        std::cerr << ERR << "Failed to find backup build header: \"" << (installed_path / "files" / header_name).string() << "\"\n";
        std::exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[])
{
    // ===== INIT ===== //

    std::cout << INFO << "Running FLX Build: v." << FLX_BUILD_VERSION << '\n';

    installed_path = std::filesystem::absolute(argv[0]).parent_path().parent_path();
    temp_dir_path = root_path / ".flxb";
    config_path = find_config(argv[0]);

    parse_args(argc, argv);

    load_config(config_path);

    root_path = find_root_dir();

    std::cout << INFO << "Project root: " << root_path << '\n';

    flx_build_cpp_path = find_build_source(root_path);
    flx_build_hpp_path = find_build_header(root_path);

    remove_dir(temp_dir_path);
    create_dir(temp_dir_path);



    // ===== BUILD ===== //

    workplace_t wrk;

    wrk
        .set_root_dir(root_path)
        .create_target("flxb")
        .toolchain
            .set_family(compiler_family)
            .resolve_tool_paths(compiler_tools_path);

    wrk["flxb"]
        .set_cpp_standard(cpp_standard_e::cpp26)
        .set_output_dir(temp_dir_path)
        .add_sources(flx_build_cpp_path)
        .add_include_dir(flx_build_hpp_path.parent_path());
    
    wrk.easy_build_target("flxb");

	return 0;
}