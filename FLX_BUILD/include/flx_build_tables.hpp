#ifndef FLX_INC_FLX_BUILD_TABLES_HPP
#define FLX_INC_FLX_BUILD_TABLES_HPP

#include <array>
#include <map>
#include <string_view>
#include <string>
#include <filesystem>
#include <tuple>

namespace flx::build::tables
{
	namespace enums
	{
		// coupled with strings
		enum struct toolchain_family_e : unsigned char
		{
			clang = 0,
			gcc = 1,
			msvc = 2,
			unknown = 3
		};
		constexpr std::array< toolchain_family_e, 3> toolchain_families =
		{
			toolchain_family_e::clang,
			toolchain_family_e::gcc,
			toolchain_family_e::msvc
		};

		// coupled with strings
		enum struct tools_e : unsigned char
		{
			c_compiler = 0,
			cpp_compiler = 1,
			module_dep_scanner = 2,
			linker = 3,
			archiver = 4,
			assembler = 5
		};
		constexpr std::array< tools_e, 6> tools =
		{
			tools_e::c_compiler,
			tools_e::cpp_compiler,
			tools_e::module_dep_scanner,
			tools_e::linker,
			tools_e::archiver,
			tools_e::assembler
		};
	} // namespace flx::build::tables::enums

	namespace strings
	{
		// coupled with enums
		constexpr std::array<std::string_view, 4> toolchain_family_strings =
		{
			"Clang",
			"GCC",
			"MSVC",
			"Unknown"
		};

		// coupled with enums
		constexpr std::array<std::string_view, 6> tool_strings =
		{
			"C Compiler",
			"Cpp Compiler",
			"Module Dep. Scanner",
			"Linker",
			"Archiver",
			"Assembler",
		};

		constexpr std::string get_string(flx::build::tables::enums::toolchain_family_e family_enum)
		{
			return std::string(toolchain_family_strings[static_cast<int>(family_enum)]);
		}

		constexpr std::string get_string(flx::build::tables::enums::tools_e tool_enum)
		{
			return std::string(tool_strings[static_cast<int>(tool_enum)]);
		}
	} // namespace flx::build::tables::strings

	namespace paths
	{
		#ifdef _WIN32
			constexpr const char* CLANG_C_COMPILER			= "clang.exe";
			constexpr const char* CLANG_CPP_COMPILER		= "clang++.exe";
			constexpr const char* CLANG_MODULE_DEP_SCANNER	= "clang-scan-deps.exe";
			constexpr const char* CLANG_LINKER				= "lld.exe";
			constexpr const char* CLANG_ARCHIVER			= "llvm-ar.exe";
			constexpr const char* CLANG_ASSEMBLER			= "clang++.exe";

			constexpr const char* GCC_C_COMPILER			= "gcc.exe";
			constexpr const char* GCC_CPP_COMPILER			= "g++.exe";
			constexpr const char* GCC_MODULE_DEP_SCANNER	= "g++.exe";
			constexpr const char* GCC_LINKER				= "ld.exe";
			constexpr const char* GCC_ARCHIVER				= "ar.exe";
			constexpr const char* GCC_ASSEMBLER				= "as.exe";

			constexpr const char* MSVC_C_COMPILER			= "cl.exe";
			constexpr const char* MSVC_CPP_COMPILER			= "cl.exe";
			constexpr const char* MSVC_MODULE_DEP_SCANNER	= "cl.exe";
			constexpr const char* MSVC_LINKER				= "link.exe";
			constexpr const char* MSVC_ARCHIVER				= "lib.exe";

			#if defined(_M_X64) || defined(__x86_64__)
				constexpr const char* MSVC_ASSEMBLER = "ml64.exe";
			#elif defined(_M_IX86) || defined(__i386__)
				constexpr const char* MSVC_ASSEMBLER = "ml.exe";
			#elif defined(_M_ARM64) || defined(__aarch64__)
				constexpr const char* MSVC_ASSEMBLER = "armasm64.exe";
			#elif defined(_M_ARM) || defined(__arm__)
				constexpr const char* MSVC_ASSEMBLER = "armasm.exe";
			#else
				#error "Unknown architecture"
			#endif
		#else
			constexpr const char* CLANG_C_COMPILER			= "clang";
			constexpr const char* CLANG_CPP_COMPILER		= "clang++";
			constexpr const char* CLANG_MODULE_DEP_SCANNER	= "clang-scan-deps";
			constexpr const char* CLANG_LINKER				= "lld";
			constexpr const char* CLANG_ARCHIVER			= "llvm-ar";
			constexpr const char* CLANG_ASSEMBLER			= "clang++";

			constexpr const char* GCC_C_COMPILER			= "gcc";
			constexpr const char* GCC_CPP_COMPILER			= "g++";
			constexpr const char* GCC_MODULE_DEP_SCANNER	= "g++";
			constexpr const char* GCC_LINKER				= "ld";
			constexpr const char* GCC_ARCHIVER				= "ar";
			constexpr const char* GCC_ASSEMBLER				= "as";

			constexpr const char* MSVC_C_COMPILER			= "cl";
			constexpr const char* MSVC_CPP_COMPILER			= "cl";
			constexpr const char* MSVC_MODULE_DEP_SCANNER	= "cl";
			constexpr const char* MSVC_LINKER				= "link";
			constexpr const char* MSVC_ARCHIVER				= "lib";
			#if defined(_M_X64) || defined(__x86_64__)
						constexpr const char* MSVC_ASSEMBLER = "ml64";
			#elif defined(_M_IX86) || defined(__i386__)
						constexpr const char* MSVC_ASSEMBLER = "ml";
			#elif defined(_M_ARM64) || defined(__aarch64__)
						constexpr const char* MSVC_ASSEMBLER = "armasm64";
			#elif defined(_M_ARM) || defined(__arm__)
						constexpr const char* MSVC_ASSEMBLER = "armasm";
			#else
				#error "Unknown architecture"
			#endif
		#endif

		//				             family	                                                 tool	                             path
		using path_dict_t = std::map<flx::build::tables::enums::toolchain_family_e, std::map<flx::build::tables::enums::tools_e, std::filesystem::path>>;
		
		path_dict_t get_paths(const std::filesystem::path& dir);
	} // namespace flx::build::tables::paths
} // namespace flx::build::tables

#endif // FLX_INC_FLX_BUILD_TABLES_HPP