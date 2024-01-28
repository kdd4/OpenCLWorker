#pragma once

#include <CL/opencl.hpp>

#include <map>
#include <string>
#include <exception>

namespace OpenCLWorker
{
	class Programs
	{
	public:
		void addProgram(std::string program_name, std::string source);
		void addProgram(std::string program_name, cl::Program program);

		cl::Program getProgram(std::string program_name);
		cl::Kernel getKernel(std::string program_name, std::string kernel_name);
	private:
		std::map<std::string, cl::Program> programs;
	};
}