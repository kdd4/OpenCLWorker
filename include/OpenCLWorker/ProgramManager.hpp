#pragma once

#include "OpenCLWorker/ProgramLoader.hpp"

namespace OpenCLWorker
{
	class ProgramManager : public ProgramLoader
	{
	public:
		static ProgramManager& Instance();

	private:
		ProgramManager();

		static ProgramManager* instance;
	};
}