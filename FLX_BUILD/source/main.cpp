#include <iostream>
#include <filesystem>
using namespace std::filesystem;

#include "flx_build.hpp"


// path find_project_root(const std::string& marker = "flx_build.cpp")
// {
//     path current = current_path();
//     std::cout << "Called-from path: " << current << '\n';
//     while (true)
//     {
//         if (exists(current / marker))
//             return current;
//         if (current == current.root_path())
//             break;
//         current = current.parent_path();
//     }
//     return {};
// }

int main(int argc, char* argv[])
{
    //std::cout << FLX_BUILD_VERSION << '\n';
    std::cout << "argv:\n";
	for (size_t i = 0; i < argc; i++)
	{
		std::cout << i << ": " << argv[i] << '\n';
	}

    std::cout << '\n';

    auto root = flx::build::find_project_root();
    if (root.empty())
    {
        std::cerr << "No build.cpp found in any parent directory.\n";
        return 1;
    }
    std::cout << "Project root: " << root << '\n';

	return 0;
}