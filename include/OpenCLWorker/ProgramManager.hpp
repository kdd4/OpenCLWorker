#pragma once

#include "OpenCLWorker/Programs.hpp"

namespace OpenCLWorker
{
	class ProgramManager : public Programs
	{
	public:
		static ProgramManager& Instance();

	private:
		ProgramManager();

		static ProgramManager* instance;
	};
}