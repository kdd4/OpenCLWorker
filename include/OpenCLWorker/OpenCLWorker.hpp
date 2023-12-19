#define CL_TARGET_OPENCL_VERSION 300
#define CL_HPP_TARGET_OPENCL_VERSION 300

#include <CL/opencl.hpp>

class OpenCLWorker
{
public:
	static OpenCLWorker& getInstance();

private:
	static OpenCLWorker* instance;
	OpenCLWorker();
};