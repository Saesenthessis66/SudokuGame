#include "Saver.h"
#include <fstream>

#include <iostream>
#include <fstream>

void Saver::Load()
{
	std::filesystem::path path = std::filesystem::current_path() / "Assets" / "Highscores";

	switch (diff)
	{
	case Easy:

		path.append("easy.txt");

		break;

	case Medium:

		path.append("medium.txt");

		break;

	case Hard:

		path.append("hard.txt");

		break;

	case Random:

		path.append("random.txt");

		break;

	default:
		break;
	}

	_path = path;

	if (std::filesystem::exists(path))
	{
		std::string tmp;
		std::ifstream file(path);

		while (std::getline(file, tmp))
		{
			data.push_back(std::stoi(tmp));
		}

		if (data.size() < 10)
		{
			for (int i = data.size(); i < 10; i++)
			{
				data.push_back(12345);
			}
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			data.push_back(12345);
		}
	}
	data.push_back(time);
	std::sort(data.begin(), data.end());
}

void Saver::Save()
{
	std::ofstream file;
	file.open(_path);

	for(int i =0;i<10;i++)
	{
		file << data[i] << std::endl;
	}
}

Saver::Saver(GameDifficulty _dif, int _mistakes, int _time) : diff(_dif), mistakes(_mistakes), time(_time)
{
	Load();
	Save();
}
