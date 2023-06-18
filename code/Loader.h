#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <fstream>

import helper;

class Loader
{
	std::string time;
	std::filesystem::path path;
	std::vector<int> data;

public:
	Loader(GameDifficulty);

	std::string getData();

};

