#include "OpenCLWorker/Programs.hpp"

namespace OpenCLWorker
{
	void Programs::addProgram(std::string program_name, std::string source)
	{
		cl_int err = 0;

		cl::Program program = cl::Program(source, true, &err);

		if (err != CL_SUCCESS)
		{
			throw std::logic_error("cl::Program's error code isn't CL_SUCCESS");
		}

		programs.insert(std::make_pair(program_name, program));
	}

	void Programs::addProgram(std::string program_name, cl::Program program)
	{
		programs.insert(std::make_pair(program_name, program));
	}

	cl::Program Programs::getProgram(std::string program_name)
	{
		return programs.at(program_name);
	}

	cl::Kernel Programs::getKernel(std::string program_name, std::string kernel_name)
	{
		return cl::Kernel(programs.at(program_name), kernel_name.c_str());
	}
}