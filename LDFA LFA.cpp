//#include "functii L1 LFA.h"
#include "prelucrareInputDFA.h"
#include "validareInputDFA.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector> 
#include <algorithm>
using namespace std;

bool existaFisier(const string& numeFisier)  // verifica daca fisierul exista in folder
{
	ifstream file(numeFisier);
	return file.good();
}

int main()
{

	string numeFisier;
	
	while (true) 
	{
		try // validare nume fisier
		{
			cout << "\nIntroduceti numele fisierului de intrare (numele fisierului deja creat in acest proiect este dfa.txt): ";
			getline(cin, numeFisier);
			if (!existaFisier(numeFisier)) // daca fisierul nu exista in folder throw invalid_argument
				throw invalid_argument("\nFisierul nu exista in folder.\n");
			break;
		}
		catch (exception& e)
		{
			cout << e.what();
		}
		catch (...)
		{
			cout << "\nEroare necunoscuta.\n";
		}
	}
	
	
	

	bool fisierValid = false;
	fisierValid = validareFisier(numeFisier);

	if (fisierValid)
	{
		vector<string> content;
		content = loadFile(numeFisier); // date dfa

		vector<string> sectionList;
		sectionList = getSectionList(content); // lista cu sectiuni

		s
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

		cout << "\nIntroduceti cuvantul pe care doriti sa il verificati: ";
		string w;
		cin >> w;

		while (true)
		{
			string stareCurenta = stareInitiala;
			bool ok = true; // daca se blocheaza in vreo stare din care nu mai gaseste tranzitii sa iasa, si starea aceea e finala va spune ca accepta sirul dar este gresit
			bool blocaj = false;
			for (int i = 0; i < w.size(); i++) // parcurge cuvantul
			{
				bool ok = false;
				for (int j = 0; j < tranzitii.size(); j += 3)
				{
					if (tranzitii[j] == stareCurenta && tranzitii[j + 1][0] == w[i]) // daca starea curenta si litera curenta din cuvant sunt egale cu cele din tranzitie
					{
						ok = true;
						stareCurenta = tranzitii[j + 2]; // urmatoarea stare este pe pozitia j+2
						break;
					}
				}
				if (!ok) // daca nu gaseste tranzitie
				{
					blocaj = true; // se blocheaza
					break;
				}
			}

			bool stareFinala = false;
			for (int i = 0; i < stariFinale.size(); i++) // verifica daca starea curenta este finala
			{
				if (stareCurenta == stariFinale[i])
				{
					stareFinala = true;
					break;
				}
			}

			if (stareFinala && !blocaj) // daca a ajuns in stare finala si nu s-a blocat
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
