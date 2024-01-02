#include "OpenCLWorker/ProgramManager.hpp"

namespace OpenCLWorker
{
	ProgramManager* ProgramManager::instance = NULL;

	ProgramManager& ProgramManager::Instance()
	{
		if (instance == NULL)
		{
			instance = new ProgramManager();
		}
		return *instance;
	}

	ProgramManager::ProgramManager() {}
}