#include "OpenCLWorker/OpenCLWorker.hpp"

OpenCLWorker* OpenCLWorker::instance = NULL;

OpenCLWorker& OpenCLWorker::getInstance()
{
	if (instance == NULL)
	{
		instance = new OpenCLWorker();
	}
	return *instance;
}
