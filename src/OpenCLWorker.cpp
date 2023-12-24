#include "OpenCLWorker/OpenCLWorker.hpp"

namespace OpenCLWorker
{
	OpenCLWorker* OpenCLWorker::instance = NULL;

	OpenCLWorker& OpenCLWorker::Instance()
	{
		if (instance == NULL)
		{
			instance = new OpenCLWorker();
		}
		return *instance;
	}

	std::vector<Platform>& OpenCLWorker::getPlatforms()
	{
		return platforms;
	}

	void OpenCLWorker::setDefault(int platform_id, int device_id)
	{
		default_platform_id = platform_id;
		default_device_id = device_id;
	}

	cl::Platform& OpenCLWorker::getPlatform()
	{
		return platforms[default_platform_id].ocl_platform;
	}

	cl::Context& OpenCLWorker::getContext()
	{
		return platforms[default_platform_id].ocl_context;
	}

	cl::Device& OpenCLWorker::getDevice()
	{
		return platforms[default_platform_id].devices[default_device_id].ocl_device;
	}

	cl::CommandQueue& OpenCLWorker::getCommandQueue()
	{
		return platforms[default_platform_id].devices[default_device_id].ocl_command_queue;
	}

	OpenCLWorker::OpenCLWorker() : default_platform_id(0), default_device_id(0)
	{
		std::vector<cl::Platform> ocl_platforms;
		cl::Platform::get(&ocl_platforms);			// Getting a vector of platforms

		for (cl::Platform& ocl_platform : ocl_platforms)
		{
			platforms.push_back(Platform());		// Push back a new Platform
			Platform& platform = platforms.back();

			std::vector<cl::Device> ocl_devices;
			ocl_platform.getDevices(CL_DEVICE_TYPE_ALL, &ocl_devices);	// Getting a vector of devices

			platform.ocl_platform = ocl_platform;
			platform.ocl_context = cl::Context(ocl_devices);
			
			for (cl::Device ocl_device : ocl_devices)
			{
				platform.devices.push_back(Device());		// Push back a new Device
				Device& device = platform.devices.back();

				device.ocl_device = ocl_device;
				device.ocl_command_queue = cl::CommandQueue(platform.ocl_context, device.ocl_device);
			}
		}
	}

}