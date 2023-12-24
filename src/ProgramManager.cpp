#include "OpenCLWorker/ProgramManager.hpp"

namespace OpenCLWorker
{
	ProgramManager* ProgramManager::instance = NULL;

	ProgramManager& OpenCLWorker::ProgramManager::Instance()
	{
		if (instance == NULL)
		{
			instance = new ProgramManager();
		}
		return *instance;
	}
}