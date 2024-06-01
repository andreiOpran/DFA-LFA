//#include "functii L1 LFA.h"
#include "prelucrareInputDFA.h"
#include "validareInputDFA.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector> 
#include <algorithm>
using namespace std;

int main()
{
	string numeFisier = "dfa.txt";
	
	bool fisierValid = false;
	fisierValid = validareFisier(numeFisier);

	if (fisierValid)
	{
		vector<string> content;
		content = loadFile(numeFisier); // date dfa

		vector<string> sectionList;
		sectionList = getSectionList(content); // lista cu sectiuni


		vector<string> sigma, stari, tranzitii;

		sigma = getSectionContent(content, sectionList[0]); // alfabet
		stari = getSectionContent(content, sectionList[1]); // stari
		tranzitii = getSectionContent(content, sectionList[2]); // tranzitii

		string stareInitiala;
		vector <string> stariFinale;

		for (int i = 2; i < stari.size(); i++) // get starea initiala
		{
			if (stari[i] == "S")
				stareInitiala = stari[i - 2];
		}

		for (int i = 1; i < stari.size(); i++) // get starile finale
		{
			if (stari[i] == "F")
				stariFinale.push_back(stari[i - 1]);
		}

		cout << "\nAlfabetul este: ";
		for (int i = 0; i < sigma.size(); i++)
			cout << sigma[i] << ' ';
		cout << endl;
		cout << "\nIntroduceti cuvantul pe care doriti sa il verificati: ";
		string w;
		cin >> w;

		while (true)
		{
			string stareCurenta = stareInitiala;
			bool ok = true; // daca se blocheaza in vreo stare din care nu mai gaseste tranzitii sa iasa si starea aceea e finala
			bool blocaj = false;
			for (int i = 0; i < w.size(); i++)
			{
				bool ok = false;
				for (int j = 0; j < tranzitii.size(); j += 3)
				{
					if (tranzitii[j] == stareCurenta && tranzitii[j + 1][0] == w[i])
					{
						ok = true;
						//cout << "\n\nAm trecut din starea " << stareCurenta << " in starea " << tranzitii[j + 2] << " cu caracterul " << w[i] << endl << endl;
						stareCurenta = tranzitii[j + 2];
						break;
					}
				}
				if (!ok)
				{
					blocaj = true;
					break;
				}
			}

			bool stareFinala = false;
			for (int i = 0; i < stariFinale.size(); i++)
			{
				if (stareCurenta == stariFinale[i])
				{
					stareFinala = true;
					break;
				}
			}

			if (stareFinala && !blocaj)
				cout << "\nCuvantul " << w << " este acceptat.\n";
			else
				cout << "\nCuvantul " << w << " nu este acceptat.\n";

			cout << "\nDoriti sa introduceti un alt cuvant?\n";
			cout << "1. Da\n";
			cout << "2. Nu\n";
			cout << "\n> ";
			string optiune;
			cin >> optiune;
			if (optiune == "2")
			{
				cout << "\nProgramul s-a incheiat cu succes.\n";
				break;
			}
			else
			{
				cout << "\nIntroduceti cuvantul pe care doriti sa il verificati: ";
				cin >> w;
			}

		}
	}
	return 0;
}
