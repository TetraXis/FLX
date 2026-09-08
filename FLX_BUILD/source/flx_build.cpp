#include "flx_build.hpp"
#include "flx_build_tables.hpp"
#include "flx_build_cli.hpp"

#include <unordered_map>

namespace flx::build
{
	cli default_cli{};

	bool toolchain::detect_toolchain(const std::filesystem::path& dir)
	{
		namespace fsys = std::filesystem;
		using namespace flx::build::tables;
		using enum flx::build::tables::enums::toolchain_family_e;
		using enum flx::build::tables::enums::tools_e;

		fsys::path dir_abs = fsys::absolute(dir);

		default_cli.print_info("Detecting toolchain at \"" + dir_abs.string() + "\"...\n");

		if (!fsys::exists(dir_abs))
		{
			default_cli.print_error("flx::build::toolchain::detect_toolchain: Invalid path \"" + dir_abs.string() + "\".\n");
			return false;
		}
		if (fsys::is_regular_file(dir_abs))
		{
			default_cli.print_info("Provided path \"" + dir_abs.string() + "\" is a file, detecting within containing folder...\n");
			dir_abs = dir_abs.parent_path();
		}
		if (!fsys::is_directory(dir_abs))
		{
			default_cli.print_error("flx::build::toolchain::detect_toolchain: Provided path must be a directory. \n\tInvalid path: \"" + dir_abs.string() + "\".\n");
			return false;
		}

		paths::path_dict_t all_paths = paths::get_paths(dir_abs);

		for (const auto& family_e : enums::toolchain_families)
		{
			if (family_e == unknown)
			{
				continue;
			}

			if (fsys::exists(all_paths[family_e][cpp_compiler]))
			{
				default_cli.print_info("Detected " + strings::get_string(family_e) + " toolchain.\n");

				for (const auto& tool_e : enums::tools)
				{
					if (!fsys::exists(all_paths[family_e][tool_e]))
					{
						default_cli.print_error("flx::build::toolchain::detect_toolchain: Missing " + strings::get_string(tool_e) + " for " + strings::get_string(family_e) + ".\n");
						default_cli.print("\tExpected to find \"" + all_paths[family_e][tool_e].string() + "\".\n");
						return false;
					}
				}

				this->toolchain_family = family_e;
				this->c_compiler			= all_paths[family_e]	[c_compiler];		
				this->cpp_compiler			= all_paths[family_e]	[cpp_compiler];		
				this->module_dep_scanner	= all_paths[family_e]	[module_dep_scanner];
				this->linker				= all_paths[family_e]	[linker];			
				this->archiver				= all_paths[family_e]	[archiver];			
				this->assembler				= all_paths[family_e]	[assembler];

				default_cli.print_info("Successfully detected all tools.\n");

				return true;
			}
		}

		default_cli.print_error("flx::build::toolchain::detect_toolchain: Could not find any valid toolchain at " + dir_abs.string() + "\".\n");
		default_cli.print("\tToolchains searched:\n");
		for (const auto& family : strings::toolchain_family_strings)
		{
			if (family == strings::get_string(unknown))
			{
				continue;
			}
			default_cli.print("\t\t" + std::string(family) + '\n');
		}

		return false;
	}
} // namespace flx::build