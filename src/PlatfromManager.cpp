#include "OpenCLWorker/PlatformManager.hpp"

namespace OpenCLWorker
{
	PlatformManager* PlatformManager::instance = NULL;

	PlatformManager& PlatformManager::Instance()
	{
		if (instance == NULL)
		{
			instance = new PlatformManager();
		}
		return *instance;
	}

	std::vector<Platform>& PlatformManager::getPlatforms()
	{
		return platforms;
	}

	void PlatformManager::setDefault(int platform_id, int device_id)
	{
		default_platform_id = platform_id;
		default_device_id = device_id;
	}

	cl::Platform& PlatformManager::getPlatform()
	{
		return platforms[default_platform_id].ocl_platform;
	}

	cl::Context& PlatformManager::getContext()
	{
		return platforms[default_platform_id].ocl_context;
	}

	cl::Device& PlatformManager::getDevice()
	{
		return platforms[default_platform_id].devices[default_device_id].ocl_device;
	}

	cl::CommandQueue& PlatformManager::getCommandQueue()
	{
		return platforms[default_platform_id].devices[default_device_id].ocl_command_queue;
	}

	PlatformManager::PlatformManager() : default_platform_id(0), default_device_id(0)
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