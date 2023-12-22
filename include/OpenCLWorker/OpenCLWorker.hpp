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
		cl::Device device;
		cl::CommandQueue command_queue;
	};

	struct Platform
	{
		cl::Platform platform;
		cl::Context context;
		std::vector<Device> devices;
	};

	class OpenCLWorker
	{
	public:
		static OpenCLWorker& Instance();

		const std::vector<Platform>& getPlatforms() const;

	private:
		OpenCLWorker();

		static OpenCLWorker* _instance;

		std::vector<Platform> _platforms;
	};
}
