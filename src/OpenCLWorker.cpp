#include "OpenCLWorker/OpenCLWorker.hpp"

namespace OpenCLWorker
{
	OpenCLWorker* OpenCLWorker::_instance = NULL;

	OpenCLWorker& OpenCLWorker::Instance()
	{
		if (_instance == NULL)
		{
			_instance = new OpenCLWorker();
		}
		return *_instance;
	}

	std::vector<Platform>& OpenCLWorker::getPlatforms()
	{
		return _platforms;
	}

	cl::Platform& OpenCLWorker::getPlatform()
	{
		return _platforms[default_platform].platform;
	}

	cl::Context& OpenCLWorker::getContext()
	{
		return _platforms[default_platform].context;
	}

	cl::Device& OpenCLWorker::getDevice()
	{
		return _platforms[default_platform].devices[default_device].device;
	}

	cl::CommandQueue& OpenCLWorker::getCommandQueue()
	{
		return _platforms[default_platform].devices[default_device].command_queue;
	}

	void OpenCLWorker::setDefault(int platform, int device)
	{
		default_platform = platform;
		default_device = device;
	}

	OpenCLWorker::OpenCLWorker() : default_platform(0), default_device(0)
	{
		std::vector<cl::Platform> ocl_platforms;
		cl::Platform::get(&ocl_platforms);

		for (cl::Platform& ocl_platform : ocl_platforms)
		{
			_platforms.push_back(Platform());
			Platform& platform = _platforms.back();

			std::vector<cl::Device> ocl_devices;
			ocl_platform.getDevices(CL_DEVICE_TYPE_ALL, &ocl_devices);

			platform.platform = ocl_platform;
			platform.context = cl::Context(ocl_devices);
			
			for (cl::Device ocl_device : ocl_devices)
			{
				platform.devices.push_back(Device());
				Device& device = platform.devices.back();

				device.device = ocl_device;
				device.command_queue = cl::CommandQueue(platform.context, device.device);
			}
		}
	}

}