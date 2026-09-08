#ifndef FLX_INC_FLX_BUILD_CLI_HPP
#define FLX_INC_FLX_BUILD_CLI_HPP

#include <string_view>
#include <iostream>

namespace flx::build
{
	struct cli
	{
		struct colors
		{
			static constexpr const char* BLACK = "\033[30m";
			static constexpr const char* RED = "\033[31m";
			static constexpr const char* GREEN = "\033[32m";
			static constexpr const char* YELLOW = "\033[33m";
			static constexpr const char* BLUE = "\033[34m";
			static constexpr const char* MAGENTA = "\033[35m";
			static constexpr const char* CYAN = "\033[36m";
			static constexpr const char* WHITE = "\033[37m";

			static constexpr const char* BRIGHT_BLACK = "\033[90m";
			static constexpr const char* BRIGHT_RED = "\033[91m";
			static constexpr const char* BRIGHT_GREEN = "\033[92m";
			static constexpr const char* BRIGHT_YELLOW = "\033[93m";
			static constexpr const char* BRIGHT_BLUE = "\033[94m";
			static constexpr const char* BRIGHT_MAGENTA = "\033[95m";
			static constexpr const char* BRIGHT_CYAN = "\033[96m";
			static constexpr const char* BRIGHT_WHITE = "\033[97m";

			static constexpr const char* BOLD = "\033[1m";
			static constexpr const char* DIM = "\033[2m";
			static constexpr const char* ITALIC = "\033[3m";
			static constexpr const char* UNDERLINE = "\033[4m";
			static constexpr const char* RESET = "\033[0m";
		};

		static constexpr const char* INFO = "\033[90m[>] \033[0m";
		static constexpr const char* ERROR = "\033[91m[ERROR] \033[0m";
		static constexpr const char* WARN = "\033[93m[WARN] \033[0m";
		static constexpr const char* PROMPT = "\033[97mflxb>  \033[0m";

		std::istream* input = &std::cin;
		std::ostream* output = &std::cout;

		cli() = default;
		cli(std::istream* in, std::ostream* out);

		void print(std::string_view msg) const;
		void print_info(std::string_view msg) const;
		void print_warning(std::string_view msg) const;
		void print_error(std::string_view msg) const;

		// TODO: resolve Windows storing path as wstring
		void read(std::string& out) const;
	};
} // namespace flx::build

#endif // FLX_INC_FLX_BUILD_CLI_HPP