#include "flx_build.hpp"

#include <iostream>
#include <filesystem>
#include <regex>

flx::build::compiler_family_e compiler_family = flx::build::compiler_family_e::unknown;
std::filesystem::path compiler_path = "";

void save_cfg(const std::filesystem::path& cfg_path) noexcept
{
    std::cout << "Saving cfg...\n";

    std::ofstream cfg(cfg_path, std::ios::out | std::ios::trunc);
    if (!cfg.is_open())
    {
        std::cerr << "flx_build::save_cfg: Failed to open config file: " << cfg_path.string() << '\n';
        std::exit(EXIT_FAILURE);
    }

    switch (compiler_family)
    {
        case flx::build::compiler_family_e::clang:
            cfg << "compiler_family = \"Clang\"\n";
            break;
        case flx::build::compiler_family_e::gcc:
            cfg << "compiler_family = \"GCC\"\n";
            break;
        case flx::build::compiler_family_e::msvc:
            cfg << "compiler_family = \"MSVC\"\n";
            break;
        default:
            cfg << "compiler_family = \"UNKNOWN\"\n";
            break;
    }
    cfg << "compiler_path = \"" << compiler_path.string() << "\"\n";
    cfg.close();
    std::cout << "Saving finished.\n";
}

void mode_settings(const std::filesystem::path& cfg_path) noexcept
{
    static std::regex EXIT_RGX("\\s*exit\\s*");
    static std::regex COMPILER_FAMILY_RGX("\\s*--family\\s*(.+)");
    static std::regex COMPILER_PATH_RGX("\\s*--path\\s*\"(.+)\"");
    std::smatch match;

    std::cout << "Settings mode.\n";
    std::cout << "\tTo set compiler family type: --family {Clang/GCC/MSVC}\n";
    std::cout << "\tTo set compiler path: --path \"{full path to g++/cl.exe}\"\n";
    std::cout << "\tTo exit: exit\n";

    std::string user_input = "";

    while (true)
    {
        std::cout << "\nFLX Build> ";
        std::getline(std::cin, user_input);

        if (std::regex_search(user_input, match, EXIT_RGX))
        {
            std::cout << "Exiting...\n";
            break;
        }
        if (std::regex_search(user_input, match, COMPILER_FAMILY_RGX))
        {
            std::string compiler_family_str = match[1].str();

            if (compiler_family_str == "Clang")
            {
                compiler_family = flx::build::compiler_family_e::clang;
            }
            else if (compiler_family_str == "GCC")
            {
                compiler_family = flx::build::compiler_family_e::gcc;
            }
            else if (compiler_family_str == "MSVC")
            {
                compiler_family = flx::build::compiler_family_e::msvc;
            }
            else
            {
                compiler_family = flx::build::compiler_family_e::unknown;
            }
            std::cout << "Compiler family type set.\n";
        }
        if (std::regex_search(user_input, match, COMPILER_PATH_RGX))
        {
            compiler_path = match[1].str();
            std::cout << "Compiler path set.\n";
        }
    }

    save_cfg(cfg_path);
}

void load_config(const std::filesystem::path& cfg_path) noexcept
{
    static std::regex COMPILER_FAMILY_RGX("\\s*compiler_family\\s*=\\s*\"(.+)\"");
    static std::regex COMPILER_PATH_RGX("\\s*compiler_path\\s*=\\s*\"(.+)\"");
    std::smatch match;

    std::ifstream cfg(cfg_path);
    if (!cfg.is_open())
    {
        std::cerr << "flx_build::load_config: Failed to open config file: " << cfg_path.string() << '\n';
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
                compiler_family = flx::build::compiler_family_e::clang;
            }
            else if (compiler_family_str == "GCC")
            {
                compiler_family = flx::build::compiler_family_e::gcc;
            }
            else if (compiler_family_str == "MSVC")
            {
                compiler_family = flx::build::compiler_family_e::msvc;
            }
            else
            {
                compiler_family = flx::build::compiler_family_e::unknown;
            }
        }
        if (std::regex_search(line, match, COMPILER_PATH_RGX))
        {
            compiler_path = match[1].str();
        }
    }
    cfg.close();

    if (compiler_path == "" || std::filesystem::exists(compiler_path) || compiler_family == flx::build::compiler_family_e::unknown)
    {
        std::cout << "flx_build::load_config: Missing settings, entering settings mode...\n";
        mode_settings(cfg_path);
    }
    else if (compiler_family == flx::build::compiler_family_e::unknown)
    {
        std::cout << "flx_build::load_config: Missing compiler family, entering settings mode...\n";
        mode_settings(cfg_path);
    }
    else if (compiler_path == "" || std::filesystem::exists(compiler_path))
    {
        std::cout << "flx_build::load_config: Missing compiler path, entering settings mode...\n";
        mode_settings(cfg_path);
    }
}

std::filesystem::path find_config(const std::filesystem::path& exe_path) noexcept
{
    std::filesystem::path exe_dir = exe_path.parent_path();

    std::filesystem::path cfg_path = exe_dir.parent_path() / "cfg" / "config.cfg"; // yay, hardcoded path!
    if (std::filesystem::exists(cfg_path) && std::filesystem::is_regular_file(cfg_path))
    {
        return cfg_path;
    }

    flx::build::create_file(cfg_path);
    return cfg_path;
}

int main(int argc, char* argv[])
{
    std::cout << "Running FLX Build: v." << FLX_BUILD_VERSION << '\n';
    std::cout << "argv:\n";
	for (size_t i = 0; i < argc; i++)
	{
		std::cout << i << ": " << argv[i] << '\n';
	}

    std::cout << '\n';

    std::cout << "Loading config:\n";

    load_config(find_config(argv[0]));

    if (argc > 1 && std::strcmp(argv[1], "-cfg") == 0)
    {
        mode_settings(find_config(argv[0]));
    }

    auto root = flx::build::find_root_dir();

    std::cout << "Project root: " << root << '\n';

	return 0;
}