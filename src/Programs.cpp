#include "OpenCLWorker/Programs.hpp"

namespace OpenCLWorker
{
	void Programs::addProgram(const char* program_name, const char* source)
	{
		cl_int err = 0;

		cl::Context& ocl_context = PlatformManager::Instance().getContext();

		cl::Program ocl_program = cl::Program(ocl_context, source, true, &err);

		if (err != CL_SUCCESS)
		{
			throw std::logic_error("cl::Program's error code isn't CL_SUCCESS");
		}

		programs.insert(std::make_pair(program_name, ocl_program));
	}

	void Programs::addProgram(const char* program_name, cl::Program program)
	{
		programs.insert(std::make_pair(program_name, program));
	}

	cl::Program Programs::getProgram(const char* program_name)
	{
		return programs.at(program_name);
	}

	cl::Kernel Programs::getKernel(const char* program_name, const char* kernel_name)
	{
		return cl::Kernel(programs.at(program_name), kernel_name);
	}
}