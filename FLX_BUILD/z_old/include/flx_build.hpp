// WARNING
// Some snippeds of this draft were written with AI assistance.
// For the final version it will be rewritten by human.

// 2026-May-28 15:41
// flx_build uses standard lib provided by compiler.
// See synopsis and example (flx_build.cpp) on how to set it up and use it.
// This header provides functions for build control. Use "flx_build.cpp" as your meta-build programm.
// By default flx_build does not use cache or does anything without user input.
// It was made out of frustration from CMake, xmake and other build systems.
// Everything is noexcept so if anything fails, build stops.
// Only not unessential functions can fail (so far none).

#ifndef FLX_INC_FLX_BUILD_HPP
#define FLX_INC_FLX_BUILD_HPP

#define FLX_BUILD_VERSION "0.0.1"
#define FLX_BUILD_VERSION_MAJOR 0
#define FLX_BUILD_VERSION_MINOR 0
#define FLX_BUILD_VERSION_PATCH 1

#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <filesystem>
#include <iostream>
#include <regex>
#include <unordered_set>
#include <fstream>
#include <array>
#include <utility>

// ===== SYNOPSIS ===== //

namespace flx::build
{
	struct toolchain_flags_t;
	struct toolchain_paths_t;
	struct toolchain_t;
	struct workplace_t;
	struct target_t;

	enum struct compiler_family_e : int8_t
	{
		unknown,
		clang,
		gcc,
		msvc,
	};

	enum struct cpp_standard_e : int8_t
	{
		default_, latest,
		cpp98, cpp03, cpp11, cpp14, cpp17, cpp20, cpp23, cpp26,
		gnu98, gnu11, gnu14, gnu17, gnu20, gnu23, gnu26
	};

	enum struct c_standard_e : uint8_t
	{
		default_, latest,
		c89, c99, c11, c17, c23,
		gnu89, gnu99, gnu11, gnu17, gnu23
	};

	enum struct build_mode_e : int8_t
	{
		debug,
		release
	};

	// TODO: not used
	enum struct target_type_e : int8_t
	{
		unknown,
		executable,
		interface_library,
		static_library,
		dynamic_library,
		phony
	};

	inline std::filesystem::path find_root_dir(const std::string& build_file = "flx_build.cpp") noexcept;
	inline void create_dir(const std::filesystem::path& dir_path) noexcept;

	inline void add_default_flags_clang(toolchain_flags_t& flags_to_mut, build_mode_e build_mode = build_mode_e::release) noexcept;
	inline void add_target_flags(toolchain_flags_t& flags_to_mut, const toolchain_t& toolchain, const target_t& target) noexcept;
	inline void call_driver(const toolchain_t& toolchain, const target_t& target) noexcept;
}



// ===== TABLES ===== //

namespace flx::build::tables
{
	// ===== CPP_STANDARD ===== //

	constexpr std::array<std::pair<std::pair<compiler_family_e, cpp_standard_e>, const char*>, 51> cpp_flags = 
	{ {
		// Clang
		{{compiler_family_e::clang, cpp_standard_e::default_},  ""},
		{{compiler_family_e::clang, cpp_standard_e::latest},    "-std=c++latest"},
		{{compiler_family_e::clang, cpp_standard_e::cpp98},     "-std=c++98"},
		{{compiler_family_e::clang, cpp_standard_e::cpp03},     "-std=c++03"},
		{{compiler_family_e::clang, cpp_standard_e::cpp11},     "-std=c++11"},
		{{compiler_family_e::clang, cpp_standard_e::cpp14},     "-std=c++14"},
		{{compiler_family_e::clang, cpp_standard_e::cpp17},     "-std=c++17"},
		{{compiler_family_e::clang, cpp_standard_e::cpp20},     "-std=c++20"},
		{{compiler_family_e::clang, cpp_standard_e::cpp23},     "-std=c++23"},
		{{compiler_family_e::clang, cpp_standard_e::cpp26},     "-std=c++26"},
		{{compiler_family_e::clang, cpp_standard_e::gnu98},     "-std=gnu++98"},
		{{compiler_family_e::clang, cpp_standard_e::gnu11},     "-std=gnu++11"},
		{{compiler_family_e::clang, cpp_standard_e::gnu14},     "-std=gnu++14"},
		{{compiler_family_e::clang, cpp_standard_e::gnu17},     "-std=gnu++17"},
		{{compiler_family_e::clang, cpp_standard_e::gnu20},     "-std=gnu++20"},
		{{compiler_family_e::clang, cpp_standard_e::gnu23},     "-std=gnu++23"},
		{{compiler_family_e::clang, cpp_standard_e::gnu26},     "-std=gnu++26"},

		// GCC
		{{compiler_family_e::gcc, cpp_standard_e::default_},    ""},
		{{compiler_family_e::gcc, cpp_standard_e::latest},      ""},            // GCC has no "latest"
		{{compiler_family_e::gcc, cpp_standard_e::cpp98},       "-std=c++98"},
		{{compiler_family_e::gcc, cpp_standard_e::cpp03},       "-std=c++03"},
		{{compiler_family_e::gcc, cpp_standard_e::cpp11},       "-std=c++11"},
		{{compiler_family_e::gcc, cpp_standard_e::cpp14},       "-std=c++14"},
		{{compiler_family_e::gcc, cpp_standard_e::cpp17},       "-std=c++17"},
		{{compiler_family_e::gcc, cpp_standard_e::cpp20},       "-std=c++20"},
		{{compiler_family_e::gcc, cpp_standard_e::cpp23},       "-std=c++23"},
		{{compiler_family_e::gcc, cpp_standard_e::cpp26},       "-std=c++26"},
		{{compiler_family_e::gcc, cpp_standard_e::gnu98},       "-std=gnu++98"},
		{{compiler_family_e::gcc, cpp_standard_e::gnu11},       "-std=gnu++11"},
		{{compiler_family_e::gcc, cpp_standard_e::gnu14},       "-std=gnu++14"},
		{{compiler_family_e::gcc, cpp_standard_e::gnu17},       "-std=gnu++17"},
		{{compiler_family_e::gcc, cpp_standard_e::gnu20},       "-std=gnu++20"},
		{{compiler_family_e::gcc, cpp_standard_e::gnu23},       "-std=gnu++23"},
		{{compiler_family_e::gcc, cpp_standard_e::gnu26},       "-std=gnu++26"},

		// MSVC
		{{compiler_family_e::msvc, cpp_standard_e::default_},   ""},
		{{compiler_family_e::msvc, cpp_standard_e::latest},     "/std:c++latest"},
		{{compiler_family_e::msvc, cpp_standard_e::cpp98},      ""},
		{{compiler_family_e::msvc, cpp_standard_e::cpp03},      ""},
		{{compiler_family_e::msvc, cpp_standard_e::cpp11},      ""},
		{{compiler_family_e::msvc, cpp_standard_e::cpp14},      "/std:c++14"},
		{{compiler_family_e::msvc, cpp_standard_e::cpp17},      "/std:c++17"},
		{{compiler_family_e::msvc, cpp_standard_e::cpp20},      "/std:c++20"},
		{{compiler_family_e::msvc, cpp_standard_e::cpp23},      "/std:c++23preview"},
		{{compiler_family_e::msvc, cpp_standard_e::cpp26},      ""},
		{{compiler_family_e::msvc, cpp_standard_e::gnu98},      ""},
		{{compiler_family_e::msvc, cpp_standard_e::gnu11},      ""},
		{{compiler_family_e::msvc, cpp_standard_e::gnu14},      ""},
		{{compiler_family_e::msvc, cpp_standard_e::gnu17},      ""},
		{{compiler_family_e::msvc, cpp_standard_e::gnu20},      ""},
		{{compiler_family_e::msvc, cpp_standard_e::gnu23},      ""},
		{{compiler_family_e::msvc, cpp_standard_e::gnu26},      ""},
	} };

	std::string get_cpp_standard(compiler_family_e family, cpp_standard_e standard) noexcept
	{
		for (const auto& [inner, str] : cpp_flags)
		{
			const auto& [fam, std] = inner;
			if (fam == family && std == standard)
			{
				return str;
			}
		}
		return "";
	}



	// ===== PREFIXES ===== //

	// TODO: use enums as numbers to access quicker

	// user includes
	constexpr std::array<std::pair<compiler_family_e, const char*>, 3> user_include_prefixes =
	{ {
		{ compiler_family_e::clang,	"-I"},
		{ compiler_family_e::gcc,	"-I"},
		{ compiler_family_e::msvc,	"/I"}
	} };

	std::string get_user_include_prefix(compiler_family_e family) noexcept
	{
		for (const auto& [fam, str] : user_include_prefixes)
		{
			if (fam == family)
			{
				return str;
			}
		}
		return "";
	}

	// system includes
	constexpr std::array<std::pair<compiler_family_e, const char*>, 3> system_include_prefixes =
	{ {
		{ compiler_family_e::clang,	"-isystem"},
		{ compiler_family_e::gcc,	"-isystem"},
		{ compiler_family_e::msvc,	"/I"}
	} };

	std::string get_system_include_prefix(compiler_family_e family) noexcept
	{
		for (const auto& [fam, str] : system_include_prefixes)
		{
			if (fam == family)
			{
				return str;
			}
		}
		return "";
	}

	// output
	constexpr std::array<std::pair<compiler_family_e, const char*>, 3> output_prefixes =
	{ {
		{ compiler_family_e::clang,	"-o"},
		{ compiler_family_e::gcc,	"-o"},
		{ compiler_family_e::msvc,	"/Fe"}
	} };

	std::string get_output_prefix(compiler_family_e family) noexcept
	{
		for (const auto& [fam, str] : output_prefixes)
		{
			if (fam == family)
			{
				return str;
			}
		}
		return "";
	}
}



// ===== IMPLEMENTATION ===== //

namespace flx::build
{
	#ifdef _WIN32
		constexpr const char* EXE_EXT = ".exe";
	#else
		constexpr const char* EXE_EXT = "";
	#endif

	constexpr const char* BLACK = "\033[30m";
	constexpr const char* RED = "\033[31m";
	constexpr const char* GREEN = "\033[32m";
	constexpr const char* YELLOW = "\033[33m";
	constexpr const char* BLUE = "\033[34m";
	constexpr const char* MAGENTA = "\033[35m";
	constexpr const char* CYAN = "\033[36m";
	constexpr const char* WHITE = "\033[37m";

	constexpr const char* BRIGHT_BLACK = "\033[90m";
	constexpr const char* BRIGHT_RED = "\033[91m";
	constexpr const char* BRIGHT_GREEN = "\033[92m";
	constexpr const char* BRIGHT_YELLOW = "\033[93m";
	constexpr const char* BRIGHT_BLUE = "\033[94m";
	constexpr const char* BRIGHT_MAGENTA = "\033[95m";
	constexpr const char* BRIGHT_CYAN = "\033[96m";
	constexpr const char* BRIGHT_WHITE = "\033[97m";

	constexpr const char* BOLD = "\033[1m";
	constexpr const char* DIM = "\033[2m";
	constexpr const char* ITALIC = "\033[3m";
	constexpr const char* UNDERLINE = "\033[4m";
	constexpr const char* RESET = "\033[0m";

	constexpr const char* INFO = "\033[90m[>] \033[0m";
	constexpr const char* ERR = "\033[91m[ERROR] \033[0m";
	constexpr const char* WARN = "\033[93m[WARN] \033[0m";
	constexpr const char* USER = "\033[97m$ \033[0m";

	struct toolchain_flags_t
	{
		// they are listed in correct order
		std::vector<std::string> language_standard{};
		std::vector<std::string> preprocessor{};
		std::vector<std::string> user_includes{};
		std::vector<std::string> system_includes{};
		std::vector<std::string> optimizations{};
		std::vector<std::string> warning{};
		std::vector<std::string> debug{};
		std::vector<std::string> code_generation{};
		std::vector<std::string> dependency_generation{};
		std::vector<std::string> diagnostics{};
		// std::vector<std::string> miscellaneous{};
		std::vector<std::string> source_files{};
		std::vector<std::string> library_dirs{};
		std::vector<std::string> libraries{};
		std::vector<std::string> linker{};
		std::vector<std::string> output_control{};
	};

	struct toolchain_paths_t
	{
		std::filesystem::path c_compiler{};
		std::filesystem::path cpp_compiler{};
		std::filesystem::path module_dep_scanner{};
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

		toolchain_t& set_family(compiler_family_e new_family) noexcept
		{
			family = new_family;
			return *this;
		}
		compiler_family_e& get_family() noexcept
		{
			return family;
		}
		const compiler_family_e& get_family() const noexcept
		{
			return family;
		}

		toolchain_t& resolve_tool_paths(const std::filesystem::path& install_dir) noexcept
		{
			if (family == compiler_family_e::unknown)
			{
				std::cerr << ERR << "flx_build::resolve_tool_paths: Unknown compiler family. Specify family first.\n";
				std::exit(EXIT_FAILURE);
			}
			if (family == compiler_family_e::clang)
			{
				bool error = false;

				// C compiler
				std::filesystem::path clang_path = install_dir / "bin" / (std::string("clang") + EXE_EXT);
				if (std::filesystem::is_regular_file(clang_path))
				{
					paths.c_compiler = clang_path;
				}
				else
				{
					error = true;
					std::cerr << ERR << "flx_build::resolve_tool_paths: Failed to resolve C compiler path: \"" << clang_path << "\"\n";
				}

				// C++ compiler
				std::filesystem::path clangxx_path = install_dir / "bin" / (std::string("clang++") + EXE_EXT);
				if (std::filesystem::is_regular_file(clangxx_path))
				{
					paths.cpp_compiler = clangxx_path;
				}
				else
				{
					error = true;
					std::cerr << ERR << "flx_build::resolve_tool_paths: Failed to resolve C++ compiler path: \"" << clangxx_path << "\"\n";
				}

				// archiver
				std::filesystem::path ar_path = install_dir / "bin" / (std::string("llvm-ar") + EXE_EXT);
				if (std::filesystem::is_regular_file(ar_path))
				{
					paths.archiver = ar_path;
				}
				else
				{
					error = true;
					std::cerr << ERR << "flx_build::resolve_tool_paths: Failed to resolve archiver path: \"" << ar_path << "\"\n";
				}

				// assembler
				std::filesystem::path as_path = install_dir / "bin" / (std::string("llvm-as") + EXE_EXT);
				if (std::filesystem::is_regular_file(as_path))
				{
					paths.assembler = as_path;
				}
				else
				{
					error = true;
					std::cerr << ERR << "flx_build::resolve_tool_paths: Failed to resolve assembler path: \"" << as_path << "\"\n";
				}

				// linker
				std::filesystem::path linker_path = install_dir / "bin" / (std::string("ld.lld") + EXE_EXT);
				if (std::filesystem::is_regular_file(linker_path))
				{
					paths.linker = linker_path;
				}
				else
				{
					error = true;
					std::cerr << ERR << "flx_build::resolve_tool_paths: Failed to resolve linker path: \"" << linker_path << "\"\n";
				}

				if (error)
				{
					std::exit(EXIT_FAILURE);
				}
			}
			else if (family == compiler_family_e::gcc)
			{
				std::cerr << ERR << "flx_build::resolve_tool_paths: Unsupported compiler\n";
				std::exit(EXIT_FAILURE);
			}
			else if (family == compiler_family_e::msvc)
			{
				std::cerr << ERR << "flx_build::resolve_tool_paths: Unsupported compiler\n";
				std::exit(EXIT_FAILURE);
			}
			else
			{
				std::cerr << ERR << "flx_build::resolve_tool_paths: Unsupported compiler\n";
				std::exit(EXIT_FAILURE);
			}

			return *this;
		}
	};

	// TODO: add missing remove...

	struct target_t
	{
		toolchain_flags_t flags{};  // will override toolchain flags per category (leaving a category empty will result in global setting used for that category)
		workplace_t* parent = nullptr;
		std::string name = "Unnamed target";
		target_type_e type = target_type_e::unknown;
		cpp_standard_e cpp_standard = cpp_standard_e::default_;
		std::vector< std::string > dependencies{}; // by target name, in order
		std::unordered_set< std::filesystem::path > sources{};
		std::unordered_set< std::filesystem::path > modules{};
		std::unordered_set< std::filesystem::path > libraries{};
		std::unordered_set< std::filesystem::path > user_includes{};
		std::unordered_set< std::filesystem::path > system_includes{};
		std::filesystem::path output_dir{};
		std::vector< std::filesystem::path > files_build_order;
		// std::unordered_map< std::filesystem::path, std::vector< std::filesystem::path > > file_deps; // should be calculated and discarded when populating files_build_order

		target_t& set_name(const std::string& new_name) noexcept
		{
			name = new_name;
			return *this;
		}
		std::string& get_name() noexcept
		{
			return name;
		}
		const std::string& get_name() const noexcept
		{
			return name;
		}

		target_t& set_cpp_standard(cpp_standard_e new_cpp_standard) noexcept
		{
			cpp_standard = new_cpp_standard;
			return *this;
		}
		cpp_standard_e& get_cpp_standard() noexcept
		{
			return cpp_standard;
		}
		const cpp_standard_e& get_cpp_standard() const noexcept
		{
			return cpp_standard;
		}

		target_t& set_output_dir(const std::filesystem::path& output_dir_path) noexcept
		{
			if (std::filesystem::exists(output_dir_path) && std::filesystem::is_directory(output_dir_path))
			{
				output_dir = output_dir_path;
				return *this;
			}
			std::cerr << ERR << "flx_build::set_output_dir: Failed to set output dir to: \"" << output_dir_path.string() << "\"\n";
			std::exit(EXIT_FAILURE);
		}
		std::filesystem::path& get_output_dir() noexcept
		{
			return output_dir;
		}
		const std::filesystem::path& get_output_dir() const noexcept
		{
			return output_dir;
		}

		target_t& add_dependency(const std::string& target_name) noexcept // does not check for unique names, in cases where people need to build something twice or more
		{
			dependencies.emplace_back(target_name);
			return *this;
		}
		target_t& remove_dependency(const std::string& target_name) noexcept
		{
			std::erase(dependencies, target_name);
			return *this;
		}
		std::vector< std::string >& get_dependencies() noexcept
		{
			return dependencies;
		}
		const std::vector< std::string >& get_dependencies() const noexcept
		{
			return dependencies;
		}

		// yes, these are almost identical functions
		target_t& add_sources(const std::filesystem::path& pattern) noexcept
		{
			std::error_code ec;
			std::string pattern_str = pattern.string();

			if (pattern_str.find('*') == std::string::npos)
			{
				if (!std::filesystem::is_regular_file(pattern, ec) || ec)
				{
					std::cerr << ERR << "flx_build::target_t::add_sources: not a regular file: " << pattern << '\n';
					std::exit(EXIT_FAILURE);
				}
				sources.insert(pattern.string());
				return *this;
			}

			std::filesystem::path parent = pattern.parent_path();
			std::string filename_pattern = pattern.filename().string();

			if (!std::filesystem::is_directory(parent, ec) || ec)
			{
				std::cerr << ERR << "flx_build::target_t::add_sources: directory does not exist: " << parent << '\n';
				std::exit(EXIT_FAILURE);
			}

			std::string regex_str = std::regex_replace(filename_pattern, std::regex(R"(\*)"), ".*");
			std::regex pattern_regex(regex_str, std::regex::icase);

			bool found = false;
			for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(parent, ec))
			{
				if (entry.is_regular_file(ec) && !ec)
				{
					std::string filename = entry.path().filename().string();
					if (std::regex_match(filename, pattern_regex))
					{
						found = true;
						sources.insert(entry.path().string());
					}
				}
				if (ec)
				{
					std::cerr << ERR << "flx_build::target_t::add_sources: error parsing sources: " << ec.message() << '\n';
					std::cerr << ERR << "flx_build::Problematic source: " << entry.path() << '\n';
					std::exit(EXIT_FAILURE);
				}
			}

			if (!found)
			{
				std::cerr << ERR << "flx_build::add_source: no files matched pattern: " << pattern << '\n';
				std::exit(EXIT_FAILURE);
			}

			return *this;
		}
		target_t& add_modules(const std::filesystem::path& pattern) noexcept
		{
			std::error_code ec;
			std::string pattern_str = pattern.string();

			if (pattern_str.find('*') == std::string::npos)
			{
				if (!std::filesystem::is_regular_file(pattern, ec) || ec)
				{
					std::cerr << ERR << "flx_build::target_t::add_modules: not a regular file: " << pattern << '\n';
					std::exit(EXIT_FAILURE);
				}
				modules.insert(pattern.string());
				return *this;
			}

			std::filesystem::path parent = pattern.parent_path();
			std::string filename_pattern = pattern.filename().string();

			if (!std::filesystem::is_directory(parent, ec) || ec)
			{
				std::cerr << ERR << "flx_build::target_t::add_modules: directory does not exist: " << parent << '\n';
				std::exit(EXIT_FAILURE);
			}

			std::string regex_str = std::regex_replace(filename_pattern, std::regex(R"(\*)"), ".*");
			std::regex pattern_regex(regex_str, std::regex::icase);

			bool found = false;
			for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(parent, ec))
			{
				if (entry.is_regular_file(ec) && !ec)
				{
					std::string filename = entry.path().filename().string();
					if (std::regex_match(filename, pattern_regex))
					{
						found = true;
						modules.insert(entry.path().string());
					}
				}
				if (ec)
				{
					std::cerr << ERR << "flx_build::target_t::add_modules: error parsing modules: " << ec.message() << '\n';
					std::cerr << ERR << "flx_build::Problematic module: " << entry.path() << '\n';
					std::exit(EXIT_FAILURE);
				}
			}

			if (!found)
			{
				std::cerr << ERR << "flx_build::target_t::add_modules: no files matched pattern: " << pattern << '\n';
				std::exit(EXIT_FAILURE);
			}

			return *this;
		}
		target_t& add_libraries(const std::filesystem::path& pattern) noexcept
		{
			std::error_code ec;
			std::string pattern_str = pattern.string();

			if (pattern_str.find('*') == std::string::npos)
			{
				if (!std::filesystem::is_regular_file(pattern, ec) || ec)
				{
					std::cerr << ERR << "flx_build::target_t::add_libraries: not a regular file: " << pattern << '\n';
					std::exit(EXIT_FAILURE);
				}
				libraries.insert(pattern.string());
				return *this;
			}

			std::filesystem::path parent = pattern.parent_path();
			std::string filename_pattern = pattern.filename().string();

			if (!std::filesystem::is_directory(parent, ec) || ec)
			{
				std::cerr << ERR << "flx_build::target_t::add_libraries: directory does not exist: " << parent << '\n';
				std::exit(EXIT_FAILURE);
			}

			std::string regex_str = std::regex_replace(filename_pattern, std::regex(R"(\*)"), ".*");
			std::regex pattern_regex(regex_str, std::regex::icase);

			bool found = false;
			for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(parent, ec))
			{
				if (entry.is_regular_file(ec) && !ec)
				{
					std::string filename = entry.path().filename().string();
					if (std::regex_match(filename, pattern_regex))
					{
						found = true;
						libraries.insert(entry.path().string());
					}
				}
				if (ec)
				{
					std::cerr << ERR << "flx_build::target_t::add_libraries: error parsing libraries: " << ec.message() << '\n';
					std::cerr << ERR << "flx_build::Problematic library: " << entry.path() << '\n';
					std::exit(EXIT_FAILURE);
				}
			}

			if (!found)
			{
				std::cerr << ERR << "flx_build::target_t::add_libraries: no files matched pattern: " << pattern << '\n';
				std::exit(EXIT_FAILURE);
			}

			return *this;
		}
		target_t& add_include_dir(const std::filesystem::path& include_dir) noexcept
		{
			std::error_code ec;
			std::filesystem::path abs_path = std::filesystem::absolute(include_dir, ec);

			if (ec)
			{
				std::cerr << ERR << "flx_build::workplace_t::add_include_dir: Error resolving absolute path: " << ec.message() << '\n';
				std::exit(EXIT_FAILURE);
			}

			if (!std::filesystem::exists(abs_path, ec))
			{
				std::cerr << ERR << "flx_build::workplace_t::add_include_dir: Path does not exist: " << abs_path.string() << '\n';
				std::exit(EXIT_FAILURE);
			}

			if (!std::filesystem::is_directory(abs_path, ec))
			{
				std::cerr << ERR << "flx_build::workplace_t::add_include_dir: Not a directory: " << abs_path.string() << '\n';
				std::exit(EXIT_FAILURE);
			}

			user_includes.emplace(abs_path);
			return *this;
		}
		target_t& add_system_include_dir(const std::filesystem::path& include_dir) noexcept
		{
			std::error_code ec;
			std::filesystem::path abs_path = std::filesystem::absolute(include_dir, ec);

			if (ec)
			{
				std::cerr << ERR << "flx_build::workplace_t::add_system_include_dir: Error resolving absolute path: " << ec.message() << '\n';
				std::exit(EXIT_FAILURE);
			}

			if (!std::filesystem::exists(abs_path, ec))
			{
				std::cerr << ERR << "flx_build::workplace_t::add_system_include_dir: Path does not exist: " << abs_path.string() << '\n';
				std::exit(EXIT_FAILURE);
			}

			if (!std::filesystem::is_directory(abs_path, ec))
			{
				std::cerr << ERR << "flx_build::workplace_t::add_system_include_dir: Not a directory: " << abs_path.string() << '\n';
				std::exit(EXIT_FAILURE);
			}

			system_includes.emplace(abs_path);
			return *this;
		}

		// updates flags based on target members
		target_t& update_flags() noexcept
		{
			return *this;
		}
	};

	// TODO: global_defines are not used. they should be stored in toolchain.flags.preprocessor

	struct workplace_t
	{
		std::string name = "Unnamed workplace";
		toolchain_t toolchain{};

		std::filesystem::path root_dir{};
		std::filesystem::path output_dir{};
		std::string configuration{}; // release, debug, ...
		// bool is_shared_library_build = false;

		cpp_standard_e global_cpp_standard = cpp_standard_e::latest;
		std::unordered_set< std::string > global_defines{};
		std::unordered_set< std::filesystem::path > global_user_includes{};
		std::unordered_set< std::filesystem::path > global_system_includes{};

		std::vector< std::unique_ptr<target_t> > targets{};
		std::vector< std::string > build_order; // target names

		// TODO: change to set when applicable

		workplace_t& set_root_dir(const std::filesystem::path& root_path) noexcept
		{
			std::error_code ec;
			std::filesystem::path abs_path = std::filesystem::absolute(root_path, ec);

			if (ec)
			{
				std::cerr << ERR << "flx_build::workplace_t::set_root_dir: Error resolving absolute path: " << ec.message() << '\n';
				std::exit(EXIT_FAILURE);
			}

			if (!std::filesystem::is_directory(abs_path, ec))
			{
				std::cerr << ERR << "flx_build::workplace_t::set_root_dir: Not a directory: " << abs_path.string() << '\n';
				std::exit(EXIT_FAILURE);
			}

			if (!std::filesystem::exists(abs_path, ec))
			{
				create_dir(abs_path);
			}

			root_dir = abs_path;
			return *this;
		}
		std::filesystem::path& get_root_dir() noexcept
		{
			return root_dir;
		}
		const std::filesystem::path& get_root_dir() const noexcept
		{
			return root_dir;
		}

		workplace_t& set_output_dir(const std::filesystem::path& output_path) noexcept
		{
			std::error_code ec;
			std::filesystem::path abs_path = std::filesystem::absolute(output_path, ec);

			if (ec)
			{
				std::cerr << ERR << "flx_build::workplace_t::set_output_dir: Error resolving absolute path: " << ec.message() << '\n';
				std::exit(EXIT_FAILURE);
			}

			if (!std::filesystem::is_directory(abs_path, ec))
			{
				std::cerr << ERR << "flx_build::workplace_t::set_output_dir: Not a directory: " << abs_path.string() << '\n';
				std::exit(EXIT_FAILURE);
			}

			if (!std::filesystem::exists(abs_path, ec))
			{
				create_dir(abs_path);
			}

			output_dir = abs_path;
			return *this;
		}
		std::filesystem::path& get_output_dir() noexcept
		{
			return output_dir;
		}
		const std::filesystem::path& get_output_dir() const noexcept
		{
			return output_dir;
		}

		workplace_t& set_configuration(const std::string& conf) noexcept
		{
			configuration = conf;
			return *this;
		}
		std::string& get_configuration() noexcept
		{
			return configuration;
		}
		const std::string& get_configuration() const noexcept
		{
			return configuration;
		}

		workplace_t& add_define(const std::string& define) noexcept
		{
			global_defines.emplace(define);
			return *this;
		}
		workplace_t& remove_define(const std::string& define) noexcept
		{
			global_defines.erase(define);
			return *this;
		}
		std::unordered_set< std::string >& get_defines() noexcept
		{
			return global_defines;
		}
		const std::unordered_set< std::string >& get_defines() const noexcept
		{
			return global_defines;
		}

		workplace_t& add_include_dir(const std::filesystem::path& include_path) noexcept
		{
			std::error_code ec;
			std::filesystem::path abs_path = std::filesystem::absolute(include_path, ec);

			if (ec)
			{
				std::cerr << ERR << "flx_build::workplace_t::add_include_dir: Error resolving absolute path: " << ec.message() << '\n';
				std::exit(EXIT_FAILURE);
			}

			if (!std::filesystem::exists(abs_path, ec))
			{
				std::cerr << ERR << "flx_build::workplace_t::add_include_dir: Path does not exist: " << abs_path.string() << '\n';
				std::exit(EXIT_FAILURE);
			}

			if (!std::filesystem::is_directory(abs_path, ec))
			{
				std::cerr << ERR << "flx_build::workplace_t::add_include_dir: Not a directory: " << abs_path.string() << '\n';
				std::exit(EXIT_FAILURE);
			}

			global_user_includes.emplace(abs_path);
			return *this;
		}
		workplace_t& remove_include_dir(const std::filesystem::path& include_path) noexcept
		{
			global_user_includes.erase(include_path);
			return *this;
		}
		std::unordered_set< std::filesystem::path >& get_includes() noexcept
		{
			return global_user_includes;
		}
		const std::unordered_set< std::filesystem::path >& get_includes() const noexcept
		{
			return global_user_includes;
		}

		workplace_t& add_system_include_dir(const std::filesystem::path& system_include_path) noexcept
		{
			std::error_code ec;
			std::filesystem::path abs_path = std::filesystem::absolute(system_include_path, ec);

			if (ec)
			{
				std::cerr << ERR << "flx_build::workplace_t::add_system_include_dir: Error resolving absolute path: " << ec.message() << '\n';
				std::exit(EXIT_FAILURE);
			}

			if (!std::filesystem::exists(abs_path, ec))
			{
				std::cerr << ERR << "flx_build::workplace_t::add_system_include_dir: Path does not exist: " << abs_path.string() << '\n';
				std::exit(EXIT_FAILURE);
			}

			if (!std::filesystem::is_directory(abs_path, ec))
			{
				std::cerr << ERR << "flx_build::workplace_t::add_system_include_dir: Not a directory: " << abs_path.string() << '\n';
				std::exit(EXIT_FAILURE);
			}

			global_system_includes.emplace(abs_path);
			return *this;
		}
		workplace_t& remove_system_include_dir(const std::filesystem::path& system_include_path) noexcept
		{
			global_system_includes.erase(system_include_path);
			return *this;
		}
		std::unordered_set< std::filesystem::path >& get_system_includes() noexcept
		{
			return global_system_includes;
		}
		const std::unordered_set< std::filesystem::path >& get_system_includes() const noexcept
		{
			return global_system_includes;
		}

		workplace_t& create_target(const std::string& target_name) noexcept
		{
			auto it = std::find_if(targets.begin(), targets.end(),
				[&](const std::unique_ptr<target_t>& ptr)
				{
					return ptr && ptr->name == target_name;
				});
			if (it != targets.end())
			{
				std::cerr << ERR << "flx_build::workspace_t::create_target: Target with the name: \"" << target_name << "\" already existed\n";
				std::exit(EXIT_FAILURE);
			}

			targets.emplace_back(std::make_unique<target_t>());
			targets.back()->name = target_name;
			targets.back()->parent = this;
			return *this;
		}
		workplace_t& add_target(std::unique_ptr<target_t> target) noexcept
		{
			targets.emplace_back(std::move(target));
			targets.back()->parent = this;
			return *this;
		}
		workplace_t& remove_target(const std::string& target_name) noexcept
		{
			std::erase_if(targets,
				[&](const std::unique_ptr<target_t>& ptr)
				{
					return ptr && ptr->name == target_name;
				});
			return *this;
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

			std::cerr << ERR << "flx_build::workplace_t::operator []: No target with name: \"" << target_name << "\" found\n";
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

			std::cerr << ERR << "flx_build::workplace_t::operator []: No target with name: \"" << target_name << "\" found\n";
			std::exit(EXIT_FAILURE);
		}

		// marked as "easy", bc it uses simple default behaviour
		workplace_t& easy_build_target(const std::string& target_name, build_mode_e build_mode = build_mode_e::release) noexcept
		{
			target_t target = (*this)[target_name];
			toolchain_t toolchain_copy = toolchain;
			std::cout << INFO << "Easy building \"" << target.name << "\"...\n";

			switch (toolchain.family)
			{
			case compiler_family_e::clang:
				add_default_flags_clang(toolchain_copy.flags, build_mode);
				break;

			case compiler_family_e::gcc:
			case compiler_family_e::msvc:
			default:
				std::cerr << ERR << "flx_build::workplace_t::easy_build_target: Unsupported compiler\n";
				std::exit(EXIT_SUCCESS);
				break;
			}

			call_driver(toolchain_copy, target);

			std::cout << INFO << "Easy building finished";

			return *this;
		}

	}; // workplace_t

	inline std::filesystem::path find_root_dir(const std::string& build_file /* = "flx_build.cpp" */) noexcept
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
				std::cerr << ERR << "flx_build::find_root_dir: Could not find build file: Search reached disc root\n";
				std::exit(EXIT_FAILURE);
			}
			current = current.parent_path();
		}
		std::cerr << ERR << "flx_build::find_root_dir: Could not find build file: Max search depth reached\n";
		std::exit(EXIT_FAILURE);
	} // find_root_dir


	inline bool dir_exists(const std::filesystem::path& path) noexcept
	{
		return std::filesystem::exists(path) && std::filesystem::is_directory(path);
	}

	inline bool file_exists(const std::filesystem::path& path) noexcept
	{
		return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
	}

	inline void create_dir(const std::filesystem::path& dir_path) noexcept
	{
		std::error_code ec;
		std::filesystem::path abs_path = std::filesystem::absolute(dir_path, ec);

		if (ec)
		{
			std::cerr << ERR << "flx_build::create_directory: Error resolving absolute path: " << ec.message() << '\n';
			std::exit(EXIT_FAILURE);
		}

		if (std::filesystem::exists(abs_path, ec))
		{
			if (!std::filesystem::is_directory(abs_path, ec))
			{
				std::cerr << ERR << "flx_build::create_directory: Path exists but is not a directory: " << abs_path.string() << '\n';
				std::exit(EXIT_FAILURE);
			}
			return;
		}

		if (!std::filesystem::create_directories(abs_path, ec))
		{
			std::cerr << ERR << "flx_build::create_directory: Failed to create directory '" << abs_path.string()
				<< "': " << ec.message() << '\n';
			std::exit(EXIT_FAILURE);
		}
	}

	inline void remove_dir(const std::filesystem::path& dir_path) noexcept
	{
		std::error_code ec;
		std::filesystem::path abs_path = std::filesystem::absolute(dir_path, ec);

		if (ec)
		{
			std::cerr << ERR << "flx_build::remove_dir: Error resolving absolute path: " << ec.message() << '\n';
			std::exit(EXIT_FAILURE);
		}

		if (!std::filesystem::exists(abs_path, ec))
		{
			return;
		}

		if (!std::filesystem::is_directory(abs_path, ec))
		{
			std::cerr << ERR << "flx_build::remove_dir: Path exists but is not a directory: " << abs_path.string() << '\n';
			std::exit(EXIT_FAILURE);
		}

		std::filesystem::remove_all(abs_path, ec);
		if (ec)
		{
			std::cerr << ERR << "flx_build::remove_dir: Failed to remove directory '" << abs_path.string() << "': " << ec.message() << '\n';
			std::exit(EXIT_FAILURE);
		}
	}

	inline void create_file(const std::filesystem::path& file_path) noexcept
	{
		std::error_code ec;
		std::filesystem::path abs_path = std::filesystem::absolute(file_path, ec);

		if (ec)
		{
			std::cerr << ERR << "flx_build::create_file: Error resolving absolute path: " << ec.message() << '\n';
			std::exit(EXIT_FAILURE);
		}

		if (std::filesystem::exists(abs_path, ec))
		{
			if (ec)
			{
				std::cerr << ERR << "flx_build::create_file: Error checking existence: " << ec.message() << '\n';
				std::exit(EXIT_FAILURE);
			}

			if (!std::filesystem::is_regular_file(abs_path, ec))
			{
				std::cerr << ERR << "flx_build::create_file: Path exists but is not a regular file: " << abs_path.string() << '\n';
				std::exit(EXIT_FAILURE);
			}
			return;
		}

		std::filesystem::path parent = abs_path.parent_path();
		if (!parent.empty())
		{
			std::filesystem::create_directories(parent, ec);
			if (ec)
			{
				std::cerr << ERR << "flx_build::create_file: Failed to create parent directories for '" << abs_path.string()
					<< "': " << ec.message() << '\n';
				std::exit(EXIT_FAILURE);
			}
		}

		std::ofstream file(abs_path, std::ios::out | std::ios::trunc);
		if (!file.is_open())
		{
			std::cerr << ERR << "flx_build::create_file: Failed to create file '" << abs_path.string() << "'\n";
			std::exit(EXIT_FAILURE);
		}
		file.close();
	}

	inline void remove_file(const std::filesystem::path& file_path) noexcept
	{
		std::error_code ec;
		std::filesystem::path abs_path = std::filesystem::absolute(file_path, ec);

		if (ec)
		{
			std::cerr << ERR << "flx_build::remove_file: Error resolving absolute path: " << ec.message() << '\n';
			std::exit(EXIT_FAILURE);
		}

		if (!std::filesystem::exists(abs_path, ec))
		{
			return;
		}

		if (std::filesystem::is_directory(abs_path, ec))
		{
			std::cerr << ERR << "flx_build::remove_file: Path exists but is a directory: " << abs_path.string() << '\n';
			std::exit(EXIT_FAILURE);
		}

		if (!std::filesystem::remove(abs_path, ec))
		{
			std::cerr << ERR << "flx_build::remove_file: Failed to remove file '" << abs_path.string() << "': " << ec.message() << '\n';
			std::exit(EXIT_FAILURE);
		}
	}

	inline void add_default_flags_clang(toolchain_flags_t& flags_to_mut, build_mode_e build_mode /* = build_mode_e::release */) noexcept
	{

	}

	// TODO:
	// we set, not add, 
	// cant get global settings from workplace here
	inline void add_target_flags(toolchain_flags_t& flags_to_mut, const toolchain_t& toolchain, const target_t& target) noexcept
	{
		// flags_to_mut.language_standard      = target.flags.language_standard.empty()        ? toolchain.flags.language_standard     : target.flags.language_standard;
		flags_to_mut.optimizations          = target.flags.optimizations.empty()            ? toolchain.flags.optimizations         : target.flags.optimizations;
		flags_to_mut.warning                = target.flags.warning.empty()                  ? toolchain.flags.warning               : target.flags.warning;
		flags_to_mut.debug                  = target.flags.debug.empty()                    ? toolchain.flags.debug                 : target.flags.debug;
		flags_to_mut.preprocessor           = target.flags.preprocessor.empty()             ? toolchain.flags.preprocessor          : target.flags.preprocessor;
		flags_to_mut.dependency_generation  = target.flags.dependency_generation.empty()    ? toolchain.flags.dependency_generation : target.flags.dependency_generation;
		flags_to_mut.code_generation        = target.flags.code_generation.empty()          ? toolchain.flags.code_generation       : target.flags.code_generation;
		flags_to_mut.diagnostics            = target.flags.diagnostics.empty()              ? toolchain.flags.diagnostics           : target.flags.diagnostics;
		flags_to_mut.miscellaneous          = target.flags.miscellaneous.empty()            ? toolchain.flags.miscellaneous         : target.flags.miscellaneous;
		flags_to_mut.user_includes          = target.flags.user_includes.empty()            ? toolchain.flags.user_includes         : target.flags.user_includes;
		flags_to_mut.system_includes        = target.flags.system_includes.empty()          ? toolchain.flags.system_includes       : target.flags.system_includes;
		flags_to_mut.source_files           = target.flags.source_files.empty()             ? toolchain.flags.source_files          : target.flags.source_files;
		flags_to_mut.library_dirs           = target.flags.library_dirs.empty()             ? toolchain.flags.library_dirs          : target.flags.library_dirs;
		flags_to_mut.libraries              = target.flags.libraries.empty()                ? toolchain.flags.libraries             : target.flags.libraries;
		flags_to_mut.linker                 = target.flags.linker.empty()                   ? toolchain.flags.linker                : target.flags.linker;
		flags_to_mut.output_control         = target.flags.output_control.empty()           ? toolchain.flags.output_control        : target.flags.output_control;

		// flags that should always be overriden

		flags_to_mut.language_standard.clear();
		flags_to_mut.language_standard.emplace_back(tables::get_cpp_standard(toolchain.family, target.cpp_standard));

		std::string system_include_prefix = tables::get_system_inculde_prefix(toolchain.family);
		std::string user_include_prefix = tables::get_user_inculde_prefix(toolchain.family);

		for (const auto& source_path : target.sources)
		{
			flags_to_mut.source_files.emplace_back(source_path.string());
		}

		// TODO: modules

		for (const auto& u_include_path : target.user_includes)
		{
			flags_to_mut.user_includes.emplace_back(user_include_prefix + u_include_path.string());
		}

		for (const auto& s_include_path : target.system_includes)
		{
			flags_to_mut.system_includes.emplace_back(system_include_prefix + s_include_path.string());
		}

		// TODO: libdirs vs libs?
		for (const auto& lib_path : target.libraries)
		{
			flags_to_mut.libraries.emplace_back(lib_path.string());
		}

		flags_to_mut.output_control.emplace_back(tables::get_output_prefix(toolchain.family) + target.output_dir.string())
	}

	inline void call_driver(const toolchain_t& toolchain, const target_t& target) noexcept
	{
		std::cout << INFO << "Calling driver...\n";

		toolchain_flags_t final_flags = toolchain.flags;
		add_target_flags(final_flags, toolchain, target);

		std::vector<std::string> cmd{};
		std::string cmd_str{};

		cmd.emplace_back("\"" + toolchain.paths.cpp_compiler.string() + "\"");

		cmd.insert(cmd.end(), final_flags.language_standard.begin(),		final_flags.language_standard.end());
		cmd.insert(cmd.end(), final_flags.optimizations.begin(),			final_flags.optimizations.end());
		cmd.insert(cmd.end(), final_flags.warning.begin(),					final_flags.warning.end());
		cmd.insert(cmd.end(), final_flags.debug.begin(),					final_flags.debug.end());
		cmd.insert(cmd.end(), final_flags.preprocessor.begin(),				final_flags.preprocessor.end());
		cmd.insert(cmd.end(), final_flags.dependency_generation.begin(),	final_flags.dependency_generation.end());
		cmd.insert(cmd.end(), final_flags.code_generation.begin(),			final_flags.code_generation.end());
		cmd.insert(cmd.end(), final_flags.diagnostics.begin(),				final_flags.diagnostics.end());
		cmd.insert(cmd.end(), final_flags.miscellaneous.begin(),			final_flags.miscellaneous.end());
		cmd.insert(cmd.end(), final_flags.user_includes.begin(),			final_flags.user_includes.end());
		cmd.insert(cmd.end(), final_flags.system_includes.begin(),			final_flags.system_includes.end());
		cmd.insert(cmd.end(), final_flags.source_files.begin(),				final_flags.source_files.end());
		cmd.insert(cmd.end(), final_flags.library_dirs.begin(),				final_flags.library_dirs.end());
		cmd.insert(cmd.end(), final_flags.libraries.begin(),				final_flags.libraries.end());
		cmd.insert(cmd.end(), final_flags.linker.begin(),					final_flags.linker.end());
		cmd.insert(cmd.end(), final_flags.output_control.begin(),			final_flags.output_control.end());

		for (const auto& command : cmd)
		{
			cmd_str += command + ' ';
		}

		std::cout << INFO << "Full CMD string:\n";
		std::cout << INFO << cmd_str << '\n';

		// // order matters
		// 
		// // driver path
		// cmd.emplace_back("\"" + toolchain.paths.cpp_compiler.string() "\"");
		// 
		// // lang
		// if (!target.flags.language_standard.empty())
		// {
		//     cmd.emplace_back(target.flags.language_standard);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.language_standard);
		// }
		// 
		// // optimizations
		// if (!target.flags.optimizations.empty())
		// {
		//     cmd.emplace_back(target.flags.optimizations);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.optimizations);
		// }
		// 
		// // warnings
		// if (!target.flags.warning.empty())
		// {
		//     cmd.emplace_back(target.flags.warning);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.warning);
		// }
		// 
		// // debug
		// if (!target.flags.debug.empty())
		// {
		//     cmd.emplace_back(target.flags.debug);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.debug);
		// }
		// 
		// // preprocessor
		// if (!target.flags.preprocessor.empty())
		// {
		//     cmd.emplace_back(target.flags.preprocessor);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.preprocessor);
		// }
		// 
		// // TODO: add generate_flags() to generate them from target_t members
		// // system includes
		// if (!target.flags.system_includes.empty())
		// {
		//     cmd.emplace_back(target.flags.system_includes);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.system_includes);
		// }
		// 
		// // user includes
		// if (!target.flags.user_includes.empty())
		// {
		//     cmd.emplace_back(target.flags.user_includes);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.user_includes);
		// }
		// 
		// // dependency generation
		// if (!target.flags.dependency_generation.empty())
		// {
		//     cmd.emplace_back(target.flags.dependency_generation);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.dependency_generation);
		// }
		// 
		// // code generation
		// if (!target.flags.code_generation.empty())
		// {
		//     cmd.emplace_back(target.flags.code_generation);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.code_generation);
		// }
		// 
		// // diagnostics
		// if (!target.flags.diagnostics.empty())
		// {
		//     cmd.emplace_back(target.flags.diagnostics);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.diagnostics);
		// }
		// 
		// // diagnostics
		// if (!target.flags.diagnostics.empty())
		// {
		//     cmd.emplace_back(target.flags.diagnostics);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.diagnostics);
		// }
		// 
		// // source files
		// if (!target.flags.source_files.empty())
		// {
		//     cmd.emplace_back(target.flags.source_files);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.source_files);
		// }
		// 
		// // lib dirs
		// if (!target.flags.library_dirs.empty())
		// {
		//     cmd.emplace_back(target.flags.library_dirs);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.library_dirs);
		// }
		// 
		// // libs
		// if (!target.flags.libraries.empty())
		// {
		//     cmd.emplace_back(target.flags.libraries);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.libraries);
		// }
		// 
		// // linker
		// if (!target.flags.linker.empty())
		// {
		//     cmd.emplace_back(target.flags.linker);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.linker);
		// }
		// 
		// // output control
		// if (!target.flags.output_control.empty())
		// {
		//     cmd.emplace_back(target.flags.output_control);
		// }
		// else
		// {
		//     cmd.emplace_back(toolchain.flags.output_control);
		// }
	}
} // flx::build



#endif // !FLX_INC_FLX_BUILD_HPP