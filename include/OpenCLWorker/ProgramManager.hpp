#pragma once

#include <CL/opencl.hpp>
#include <map>
#include <string>

namespace OpenCLWorker
{
	class ProgramManager
	{
	public:
		static ProgramManager& Instance();

		void addProgram(std::string& path, bool prebuilt = true);
		void addProgram(std::vector<std::string>& paths, bool prebuilt = true);

		cl::Program getProgram(std::string& path);
		cl::Kernel getKernel(std::string& path, std::string& name);

	private:
		ProgramManager();

		static ProgramManager* instance;

		std::map<std::string, cl::Program> programs;
	};
}