#pragma once

#include <CL/opencl.hpp>

#include <mutex>
#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <exception>

namespace OpenCLWorker
{
	class ProgramLoader
	{
	public:
		void addProgram(std::string program_name, std::string source);

		cl::Program getProgram(std::string program_name);
		cl::Kernel getKernel(std::string program_name, std::string kernel_name);

		static const std::string& getDefaultBinDir();
		static void setDefaultBinDir(const std::string& bin_dir);

	private:
		static std::once_flag binary_dir_inited;
		static std::string binary_dir;
		static const std::string default_binary_dir;

		static void binary_dir_init(const std::string& bin_dir);

		static int loadBinaries(const std::string& path, cl::Program::Binaries& bin);
		static int saveBinaries(const std::string& path, const cl::Program::Binaries& bin);

		std::map<std::string, cl::Program> programs;
	};
}