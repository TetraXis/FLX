#ifndef FLX_INC_FLX_BUILD_HPP
#define FLX_INC_FLX_BUILD_HPP

#define FLX_BUILD_VERSION "0.0.1"
#define FLX_BUILD_VERSION_MAJOR 0
#define FLX_BUILD_VERSION_MINOR 0
#define FLX_BUILD_VERSION_PATCH 1

#include "flx_build_tables.hpp"
#include "flx_build_cli.hpp"

#include <filesystem>

// ===== SYNOPSIS ===== //

namespace flx::build
{
	struct toolchain;
	struct project;
	struct target;

	extern cli default_cli;
} // namespace flx::build



// ===== DEFINITION ===== //

namespace flx::build
{
	struct toolchain
	{
		std::filesystem::path c_compiler{};
		std::filesystem::path cpp_compiler{};
		std::filesystem::path module_dep_scanner{};
		std::filesystem::path linker{};
		std::filesystem::path archiver{};
		std::filesystem::path assembler{};
		flx::build::tables::enums::toolchain_family_e toolchain_family = flx::build::tables::enums::toolchain_family_e::unknown;

		bool detect_toolchain(const std::filesystem::path& dir);
	}; // toolchain
} // namespace flx::build

#endif // FLX_INC_FLX_BUILD_HPP