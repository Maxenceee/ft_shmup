#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

std::string	read_file(const fs::path& path);