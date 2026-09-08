#include "flx_build_cli.hpp"

namespace flx::build
{
	cli::cli(std::istream* in, std::ostream* out)
		: input(in), output(out)
	{
	}

	void cli::print(std::string_view msg) const
	{
		(*output) << msg;
		return;
	}

	void cli::print_info(std::string_view msg) const
	{
		(*output) << INFO << msg;
		return;
	}

	void cli::print_warning(std::string_view msg) const
	{
		(*output) << WARN << msg;
		return;
	}

	void cli::print_error(std::string_view msg) const
	{
		(*output) << ERROR << msg;
		return;
	}

	void cli::read(std::string& out) const
	{
		(*input) >> out;
		return;
	}
} // namespace flx::build