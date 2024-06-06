#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector> 
using namespace std;


// functie care incarca continutul fisierului in vector
vector<string> loadFile(string numeFisier)
{
	ifstream fin(numeFisier);
	vector<string> fisier;
	string linie;
	while (getline(fin, linie))
	{
		if (linie[0] != '#')
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
			if (fisier[i + 1] != "End" && fisier[i + 1][0] != 'Q') // in sigma nu sunt stari
			{
				fisier[i] += "A"; // sufixam cu A pt ca am gasit o sectiune de alfabet
				gasitAlfabet = true;
				//break;
			}
			else
				// daca se gaseste un F sau un S inainte de End inseamna ca am gasit o sectiune de stari, 
				// astfel in sigma nu exista litere egale cu F sau S
				// in plus in sectiunea de stari trebuie sa existe cel putin un F si un S
				while (fisier[i] != "End") 
				{
					i++;
					if (fisier[i].find("F") != string::npos || fisier[i].find("S") != string::npos) 
						gasitSF = true;
				}
			if (gasitSF && gasitAlfabet == false)
			{
				if (fisier[iHeader][fisier[iHeader].size() - 1] == ':')
					fisier[iHeader] += "S"; // sufixam cu S pt ca am gasit o sectiune de stari
			}
			else // daca nu am gasit niciun F sau S in sectiunea de stari, si nu am gasit ca este alfabet inseamna ca am gasit tranzitii
			{
				if (fisier[iHeader][fisier[iHeader].size() - 1] == ':')
					fisier[iHeader] += "T"; // sufixam cu T pt ca am gasit o sectiune de tranzitii
			}

		}
	}
	return fisier;
}

// functie care returneaza o lista cu sectiunile din fisier
// sectiunile sunt cele care se termina cu :
vector<string> getSectionList(vector<string> content)
{
	vector<string> sectionList;
	for (int i = 0; i < content.size(); i++)
	{
		if (content[i].size() > 1)
		{
			if (content[i][content[i].size() - 2] == ':')
			{
				content[i].erase(content[i].size() - 1);
				sectionList.push_back(content[i]);
			}
		}
	}
	return sectionList;
}

// functie care returneaza continutul unei sectiuni
vector<string> getSectionContent(vector<string> content, string sectionName)
{
	vector<string> sectionContent;
	string stare;

	for (int i = 0; i < content.size(); i++)
	{
		bool alfabet = false, stari = false, tranzitii = false;
		if (content[i].substr(0, sectionName.size()) == sectionName)
		{
			if (content[i] == sectionName + "A") // cu sufixul adaugat in loadFile se stie ce sectiune se prelucreaza 
				alfabet = true;
			if (content[i] == sectionName + "S")
				stari = true;
			if (content[i] == sectionName + "T")
				tranzitii = true;

			if (alfabet)
			{
				i++;
				while (content[i] != "End") // daca e alfabet doar dam push_back la litere
				{
					sectionContent.push_back(content[i]);
					i++;
				}
				/*
				cum se formateaza sectiunea de alfabet:
				0 1
				*/
			}
			if (stari)
			{
				i++;
				while (content[i] != "End") // daca e sectiune de stari, verificam daca e stare initiala sau finala, daca nu gasim F sau S punem -
				{
					int cont = 0;
					string cuvant;
					istringstream iss(content[i]);
					while (iss >> cuvant)
					{
						cont++;
						sectionContent.push_back(cuvant);
					}
					if(cont == 1)
					{
						sectionContent.push_back("-");
						sectionContent.push_back("-");
					}
					else
					if(cont == 2)
					{
						sectionContent.push_back("-");
					}
					i++;
				}

				/*
				cum se formateaza sectiunea de stari: 
				Q1 - - Q2 F - Q3 F S Q4 - -
				*/
			}
			if (tranzitii) // parsam tranzitiile si le adaugam in vector
			{
				
				i++;
				while (content[i] != "End")
				{
					string cuvant;
					istringstream iss(content[i]);
					while (iss >> cuvant)
					{
						sectionContent.push_back(cuvant);
					}
					i++;
				}
				/*
				cum se formateaza sectiunea de tranzitii:
				Q1 0 Q2 Q2 1 Q3 Q2 0 Q2 Q4 1 Q3 Q3 0 Q4
				*/
			}
			
		}
	}

	return sectionContent;
}