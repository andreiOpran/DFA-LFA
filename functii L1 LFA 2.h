#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector> 
#include <string>
#include <cstring>
using namespace std;

vector<string> loadFile(string numeFisier)
{
	ifstream fin(numeFisier);
	vector<string> fisier;
	string linie;
	while (getline(fin, linie))
	{
		if(linie[0] != '#')
			fisier.push_back(linie);
	}

	string header;
	int iHeader;
	bool gasitSF = false;
	bool gasitAlfabet = false;
	for (int i = 0; i < fisier.size(); i++)
	{
		if (fisier[i][fisier[i].size() - 1] == ':')
		{
			gasitSF = gasitAlfabet = false;
			iHeader = i;
			if (fisier[i + 1] != "End" && fisier[i + 1][0] != 'Q')
			{
				fisier[i] += "A";
				gasitAlfabet = true;
				//break;
			}
			else
				while (fisier[i] != "End")
				{
					i++;
					if (fisier[i].find("F") != string::npos || fisier[i].find("S") != string::npos)
						gasitSF = true;
				}
			//cout << "*" << gasitSF << endl;
			if (gasitSF && gasitAlfabet == false)
			{
				if(fisier[iHeader][fisier[iHeader].size() - 1] == ':')
					fisier[iHeader] += "S";
			}
			else
			{
				if (fisier[iHeader][fisier[iHeader].size() - 1] == ':')
					fisier[iHeader] += "T";
			}
				
		}
	}
	return fisier;
}

vector<string> getSectionList(vector<string> content)
{
	vector<string> sectionList;
	for (int i = 0; i < content.size(); i++)
	{
		if (content[i].size() > 1)
		{
			if (content[i][content[i].size() - 2] == ':')
			{
				content[i].erase(content[i].size() - 2);
				sectionList.push_back(content[i]);
			}
		}
	}
	return sectionList;
}

vector<string> getSectionContent(vector<string> content, string sectionName)
{
	vector<string> sectionContent;
	string stare;

	for (int i = 0; i < content.size(); i++)
	{
		bool alfabet = false, stari = false, tranzitii = false;
		if (content[i].substr(0, sectionName.size()) == sectionName)
		{
			if(content[i] == sectionName + ":A")
				alfabet = true;
			if (content[i] == sectionName + ":S")
				stari = true;
			if (content[i] == sectionName + ":T")
				tranzitii = true;
			i++;
			while (content[i] != "End")
			{
				i++;
				if(alfabet)
					sectionContent.push_back(content[i]);
				else
					if (stari)
					{
						stare[]
					}
				
			}
		}
	}
	
	return sectionContent;
}