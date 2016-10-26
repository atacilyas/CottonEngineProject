#include "XMLReader.h"
#include <fstream>
#include <string>

XMLReader::XMLReader()
{
}


XMLReader::~XMLReader()
{
}

vector<Data> XMLReader::ReadFile(string path)
{
	vector<Data> result;
	string line;
	fstream myfile(path.c_str());
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			size_t begin = line.find("SubTexture");
			if (begin != std::string::npos)
			{
				//title="data" title="data"
				string sub = line.substr(begin + 11);
				size_t found = sub.find('"');
				Data newdata;
				while (found != std::string::npos)
				{
					//title
					newdata.title.push_back(sub.substr(0, found - 1));
					sub = sub.substr(found + 1);

					found = sub.find('"');
					//data
					sub.substr(0, found);

					newdata.data.push_back(sub.substr(0, found));
					sub = sub.substr(found+2);

					found = sub.find('"');
				}
				result.push_back(newdata);
			}
		}
		myfile.close();
	}

	else cout << "Unable to open file";

	return result;
}