#pragma once
#include <filesystem>
#include <vector>
#include <filesystem>

import helper;

class Saver
{
	GameDifficulty diff;
	int mistakes, time;
	 
	std::vector<int> data;

	std::filesystem::path _path;

	void Load();
	void Save();

public:
	Saver(GameDifficulty _dif, int _mistakes, int _time);
};

