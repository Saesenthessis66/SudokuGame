#include "Loader.h"

Loader::Loader(GameDifficulty diff)
{
	path = std::filesystem::current_path() / "Assets" / "Highscores";

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

}

std::string Loader::getData()
{
	std::string ans="";

	for (int i = 0; i < 10; i++)
	{
		if (data[i] != 12345)
		{
			int min = data[i] / 60;
			int sec = data[i] % 60;
			std::string tmp = "";
			if (min < 10)
			{
				tmp += "0";
			}
			if (sec < 10)
			{
				tmp += std::to_string(min) + ":0" + std::to_string(sec);
			}
			else  tmp += std::to_string(min) + ":" + std::to_string(sec);

			ans += tmp + "\n";
		}
	}

	return ans;
}
