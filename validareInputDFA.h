#pragma once

bool validareFisier(string numeFisier)
{

	cout << "\nValidare fisier " << numeFisier << "\n";
	cout << "\nDoriti afisarea erorilor si oprirea programului in caz de gasire a unei erori?\n1. Da\n2. Nu\n";
	cout << "\n> ";
	string raspuns;
	cin >> raspuns;
	if (raspuns == "2")
	{
		return true;
	}

	bool ok = false;

	vector<string> content, sectionList, sigma, stari, tranzitii;
	content = loadFile(numeFisier);
	sectionList = getSectionList(content);

	sigma = getSectionContent(content, sectionList[0]); 
	stari = getSectionContent(content, sectionList[1]);
	tranzitii = getSectionContent(content, sectionList[2]); 

	vector <string> stariFinale;

	// verificare existenta stare start / a mai multor stari de start
	int nrStariStart = 0;
	for (int i = 2; i < stari.size(); i++) 
	{
		if (stari[i] == "S")
			nrStariStart++;
	}
	if(nrStariStart > 1)
	{
		cout << "\nAti introdus " << nrStariStart << " stari de start in fisierul " << numeFisier << ".\n";
		return false;
	}
	if(nrStariStart == 0)
	{
		cout << "\nNu ati introdus starea de start in fisierul " << numeFisier << ".\n";
		return false;
	}



	// verificare existenta stari finale
	for (int i = 1; i < stari.size(); i++) 
	{
		if (stari[i] == "F")
			stariFinale.push_back(stari[i - 1]);
	}
	if(stariFinale.size() == 0)
	{
		cout << "\nNu ati introdus stari finale in fisierul " << numeFisier << ".\n";
		return false;
	}



	// verificare daca toate literele din tranzitii exista in alfabet
	for(int i = 1; i < tranzitii.size(); i += 3)
	{
		ok = false;
		for(string litera : sigma)
		{
			if (tranzitii[i] == litera)
			{
				ok = true;
				break;
			}
		}
		if(ok == false)
		{
			cout << "\nLitera " << tranzitii[i][0] << " din tranzitii nu exista in alfabet.\n";
			return false;
		}
	}



	// verificare daca toate starile din tranzitii exista in lista de stari
	for (int i = 0; i < tranzitii.size(); i++)
	{
		if (i % 3 != 1)
		{
			ok = false;
			for (string stare : stari)
			{
				if (tranzitii[i] == stare)
				{
					ok = true;
					break;
				}
			}
			if (ok == false)
			{
				cout << "\nStarea " << tranzitii[i] << " din tranzitii nu exista in lista de stari.\n";
				return false;
			}
		}
	}



	// verificare daca exista litere in alfabet cu lungimea mai mare de 1
	// dupa cum fac emularea dfa-ului, parcurgand litera cu litera cuvantul de verificat, nu pot verifica un dfa care are un sigma cu litere cu lungimi mai mari ca 1
	for (string litera : sigma)
	{
		if (litera.size() > 1)
		{
			cout << "\nLitera " << litera << " din alfabet are lungimea mai mare de 1.\n";
			return false;
		}
	}



	// verificare daca exista litere in alfabet care sunt stari
	for (string litera : sigma)
	{
		for (string stare : stari)
		{
			if (litera == stare)
			{
				cout << "\nLitera " << litera << " din alfabet este o stare.\n";
				return false;
			}
		}
	}



	// verificare stari dubluri
	for (int i = 0; i < stari.size(); i++)
	{
		for (int j = i + 1; j < stari.size(); j++)
		{
			if (stari[i] == stari[j] && stari[i] != "-" && stari[i] != "F" && stari[i] != "S")
			{
				cout << "\nStarea " << stari[i] << " apare de mai multe ori in lista de stari.\n";
				return false;
			}
		}
	}



	// verificare dubluri tranzitii care au starea 1 si litera egale
	for (int i = 0; i < tranzitii.size(); i += 3)
	{
		for (int j = i + 3; j < tranzitii.size(); j += 3)
		{
			if (tranzitii[i] == tranzitii[j] && tranzitii[i + 1] == tranzitii[j + 1])
			{
				cout << "\nTranzitia " << tranzitii[i] << " -> " << tranzitii[i + 1] << " -> QX apare de mai multe ori in lista de tranzitii.\n";
				return false;
			}
		}
	}



	cout << "\nFisierul " << numeFisier << " este valid.\n";
	return true;
}