#include "OpenCLWorker/ProgramLoader.hpp"

namespace OpenCLWorker
{
	std::once_flag ProgramLoader::binary_dir_inited;
	std::string ProgramLoader::binary_dir;
	const std::string ProgramLoader::default_binary_dir = "tmp";

	void ProgramLoader::addProgram(const std::string& program_name, const std::string& source)
	{
		size_t hash = std::hash<std::string>{}(source);

		std::string bin_path = getDefaultBinDir() + "/" + std::to_string(hash) + ".bin";
		
		cl::Program::Binaries bin;

		bool program_inited_flag = false;
		cl::Program program;

		if (loadBinaries(bin_path, bin) == 0)
		{
			cl_int err = 0;
			program = cl::Program(cl::Context::getDefault(), { cl::Device::getDefault() }, bin, nullptr, &err);

			if (program.build() == CL_SUCCESS && err == CL_SUCCESS)
				program_inited_flag = true;
		}

		if (!program_inited_flag)
		{
			cl_int err = 0;
			program = cl::Program(source, true, &err);

			if (err != CL_SUCCESS)
			{
				throw std::logic_error(program.getBuildInfo<CL_PROGRAM_BUILD_LOG>()[0].second.c_str());
			}
			saveBinaries(bin_path, program.getInfo<CL_PROGRAM_BINARIES>());
		}

		programs.insert(std::make_pair(program_name, program));
	}

	void ProgramLoader::addProgramFromFile(const std::string& program_name, const std::string& path)
	{
		std::string source;
		std::ifstream source_file(path, std::ios::binary);

		if (!source_file.is_open())
		{
			throw std::logic_error("Error opening the file");
		}

		std::ostringstream stream_source;
		stream_source << source_file.rdbuf();

		addProgram(program_name, stream_source.str());
	}

	cl::Program ProgramLoader::getProgram(std::string program_name)
	{
		return programs.at(program_name);
	}

	cl::Kernel ProgramLoader::getKernel(std::string program_name, std::string kernel_name)
	{
		return cl::Kernel(programs.at(program_name), kernel_name.c_str());
	}

	const std::string& ProgramLoader::getDefaultBinDir()
	{
		std::call_once(binary_dir_inited, binary_dir_init, std::cref(default_binary_dir));
		return binary_dir;
	}

	void ProgramLoader::setDefaultBinDir(const std::string& bin_dir)
	{
		std::call_once(binary_dir_inited, binary_dir_init, std::cref(bin_dir));
	}

	void ProgramLoader::binary_dir_init(const std::string& bin_dir)
	{
		binary_dir = bin_dir;
		if (!std::filesystem::exists(binary_dir))
		{
			std::filesystem::create_directory(binary_dir);
		}
	}

	int ProgramLoader::loadBinaries(const std::string& path, cl::Program::Binaries& bin)
	{
		std::ifstream bin_file(path, std::ios::binary);

		if (!bin_file.is_open())
			return 1;

		int line_cnt = 0;
		bin_file.read(reinterpret_cast<char*>(&line_cnt), sizeof(line_cnt));
		
		bin = std::vector<std::vector<unsigned char>>(line_cnt);

		for (std::vector<unsigned char>& line : bin)
		{
			int line_size = 0;
			bin_file.read(reinterpret_cast<char*>(&line_size), sizeof(int));

			line = std::vector<unsigned char>(line_size);
			bin_file.read((char*)line.data(), line_size);
		}

		return 0;
	}

	int ProgramLoader::saveBinaries(const std::string& path, const cl::Program::Binaries& bin)
	{
		std::ofstream bin_file(path, std::ios::binary | std::ios::trunc);

		if (!bin_file.is_open())
			return 1;

		int line_cnt = bin.size();
		bin_file.write(reinterpret_cast<char*>(&line_cnt), sizeof(int));

		for (const std::vector<unsigned char>& line : bin)
		{
			int line_size = line.size();
			bin_file.write(reinterpret_cast<char*>(&line_size), sizeof(int));
			bin_file.write((const char*)line.data(), line_size);
		}

		return 0;
	}
}