#include "flx_build.hpp"

#include <iostream>
#include <print>

using namespace flx::build;

int main()
{
	std::print("Running FLXB v0.0\n");

	toolchain a;

	std::print("Should be invalid\n");
	a.detect_toolchain("C:\\Balls");
	std::print("Should not find\n");
	a.detect_toolchain("C:\\C++\\LLVM\\clang+llvm-23.1.0-x86_64-pc-windows-msvc");
	std::print("Info about file\n");
	a.detect_toolchain("C:\\C++\\LLVM\\clang+llvm-23.1.0-x86_64-pc-windows-msvc\\bin\\clang++.exe");
	std::print("Clang\n");
	a.detect_toolchain("C:\\C++\\LLVM\\clang+llvm-23.1.0-x86_64-pc-windows-msvc\\bin");
	std::print("GCC\n");
	a.detect_toolchain("C:\\C++\\MinGW_GCC_16.1\\bin");
	std::print("MSVC\n");
	a.detect_toolchain("C:\\Program Files\\Microsoft Visual Studio\\2022\\Enterprise\\VC\\Tools\\MSVC\\14.44.35207\\bin\\Hostx64\\x64");

	return 0;
}