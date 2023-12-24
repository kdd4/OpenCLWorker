#pragma once

#include <CL/opencl.hpp>
#include <map>
#include <string>
#include <exception>

#include "PlatformManager.hpp"

namespace OpenCLWorker
{
	class ProgramManager
	{
	public:
		static ProgramManager& Instance();

		void addProgram(const char* program_name, const char* source);
		void addProgram(const char* program_name, cl::Program program);

		cl::Program getProgram(const char* program_name);
		cl::Kernel getKernel(const char* program_name, const char* kernel_name);

	private:
		ProgramManager();

		static ProgramManager* instance;

		std::map<std::string, cl::Program> programs;
	};
}