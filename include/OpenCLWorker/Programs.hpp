#pragma once

#include "OpenCLWorker/PlatformManager.hpp"

#include <CL/opencl.hpp>

#include <map>
#include <string>
#include <exception>

namespace OpenCLWorker
{
	class Programs
	{
	public:
		void addProgram(const char* program_name, const char* source);
		void addProgram(const char* program_name, cl::Program program);

		cl::Program getProgram(const char* program_name);
		cl::Kernel getKernel(const char* program_name, const char* kernel_name);
	private:
		std::map<std::string, cl::Program> programs;
	};
}