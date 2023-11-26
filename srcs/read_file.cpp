#include "read_file.hpp"

std::string	read_file(const fs::path& path)
{
	//std::cerr << "opening file " << path << std::endl;
	std::ifstream	file(path, std::ios::out);

	if (!file.is_open())
		return {};
	std::string	res{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
	file.close();
	return (res);
}