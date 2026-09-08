#include "flx_build_tables.hpp"

namespace flx::build::tables
{
	namespace paths
	{
		path_dict_t get_paths(const std::filesystem::path& dir)
		{
			using namespace flx::build::tables::strings;
			using enum flx::build::tables::enums::toolchain_family_e;
			using enum flx::build::tables::enums::tools_e;
			namespace fsys = std::filesystem;

			fsys::path dir_abs = fsys::absolute(dir);

			path_dict_t result{};

			result	[clang]	[c_compiler]			= dir_abs / CLANG_C_COMPILER;			
			result	[clang]	[cpp_compiler]			= dir_abs / CLANG_CPP_COMPILER;		
			result	[clang]	[module_dep_scanner]	= dir_abs / CLANG_MODULE_DEP_SCANNER;	
			result	[clang]	[linker]				= dir_abs / CLANG_LINKER;				
			result	[clang]	[archiver]				= dir_abs / CLANG_ARCHIVER;			
			result	[clang]	[assembler]				= dir_abs / CLANG_ASSEMBLER;			

			result	[gcc]	[c_compiler]			= dir_abs / GCC_C_COMPILER;			
			result	[gcc]	[cpp_compiler]			= dir_abs / GCC_CPP_COMPILER;			
			result	[gcc]	[module_dep_scanner]	= dir_abs / GCC_MODULE_DEP_SCANNER;	
			result	[gcc]	[linker]				= dir_abs / GCC_LINKER;				
			result	[gcc]	[archiver]				= dir_abs / GCC_ARCHIVER;				
			result	[gcc]	[assembler]				= dir_abs / GCC_ASSEMBLER;			

			result	[msvc]	[c_compiler]			= dir_abs / MSVC_C_COMPILER;			
			result	[msvc]	[cpp_compiler]			= dir_abs / MSVC_CPP_COMPILER;		
			result	[msvc]	[module_dep_scanner]	= dir_abs / MSVC_MODULE_DEP_SCANNER;	
			result	[msvc]	[linker]				= dir_abs / MSVC_LINKER;				
			result	[msvc]	[archiver]				= dir_abs / MSVC_ARCHIVER;			
			result	[msvc]	[assembler]				= dir_abs / MSVC_ASSEMBLER;			

			return result;
		}
	} // namespace flx::build::tables::paths
} // namespace flx::build::tables
