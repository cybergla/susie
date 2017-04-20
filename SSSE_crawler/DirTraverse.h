#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>

class DirTraverse
{


public:
	std::vector<std::string>docPaths;
	std::vector<std::string>docNames;

	void getPaths(std::string name)
	{
		DIR *dir;
		struct dirent *entry;

		if (!(dir = opendir(name.c_str())))
		{
			return;
		}

		while (entry = readdir(dir)){
			if (entry->d_type == DT_DIR) {
				std::string path;
				path = name + "\\" + entry->d_name;
				if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
					continue;
				getPaths(path);
			}
			else
			{
				std::string filetype;
				std::string filename = entry->d_name;
				filetype = filename.substr(filename.find(".") % filename.length(), filename.length());
				if (filetype.find('.') == std::string::npos)filetype = "n/a";
				if (filetype == ".txt")
				{
					docPaths.push_back(name + "\\" + filename);
					docNames.push_back(filename);

				}
			}
		}
		closedir(dir);
	}


};