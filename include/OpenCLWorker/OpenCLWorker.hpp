#pragma once

#define CL_TARGET_OPENCL_VERSION 300
#define CL_HPP_TARGET_OPENCL_VERSION 300

#include <CL/opencl.hpp>
#include <vector>
#include <map>

namespace OpenCLWorker
{
	struct Device
	{
		cl::Device ocl_device;
		cl::CommandQueue ocl_command_queue;
	};

	struct Platform
	{
		cl::Platform ocl_platform;
		cl::Context ocl_context;
		std::vector<Device> devices;
	};

	class OpenCLWorker
	{
	public:
		static OpenCLWorker& Instance();

		std::vector<Platform>& getPlatforms();

		void setDefault(int platform_id, int device_id);
		
		cl::Platform& getPlatform();
		cl::Context& getContext();
		cl::Device& getDevice();
		cl::CommandQueue& getCommandQueue();

	private:
		OpenCLWorker();

		static OpenCLWorker* instance;

		std::vector<Platform> platforms;
		int default_platform_id;
		int default_device_id;
	};
}
