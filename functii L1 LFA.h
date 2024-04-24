#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector> 
#include <algorithm>
using namespace std;

typedef char matricechar[256][256]; // am creat acest tip de date pentru a putea returna o matrice de caractere prin intermediul functiei de la LINIA 19

int i; // variabila globala pentru numarul de linii din matricea de caractere cu toate datele prelucrate din fisier

matricechar* load_file(char s[256]) // functia care returneaza o matrice de caractere cu sectiunile din fisier, la fiecare inceput de sectiune, ultima pozitie a etichetei va fi tipul sectiunii: alfabet == A, stari = B, tranzitii == C (REFERINTA LINIILE [75,100])
{
	ifstream fin(s);

	matricechar mat; // matricia de returnat
	char linie[256], * p, sep[] = " "; // linie = linia curenta din fisier, p = pointer pentru strtok, sep = separatorul pentru strtok

	while (fin.getline(linie, 256))
	{
		if (linie[0] != '#') // daca linia incepe cu #, inseamna ca e un comentariu
		{
			/*
			de aici incepem sa prelucram o sectiune, luam ca atare toate datele (REFERINTA LA LINIA 42),
			iar mai apoi in functiile urmatoare le prelucram atfel:
			"By validation we ask to check that transition
			section has valid states(first and third word) and valid letters(word two).Note
			that states can be succeeded by ”F”, ”S”, both or nothing.”S” symbol can
			succeed only one state."
			*/
			if (linie[strlen(linie) - 1] == ':')
			{
				strcpy(mat[i], linie);
				i++;
				while (fin.getline(linie, 200))
				{
					if (strcmp(linie, "End") == 0) // adaugam si end-ul in matrice, poate fi util mai tarziu
					{
						strcpy(mat[i], linie);
						i++;
						break;
					}
					if (linie[0] != '#')
					{
						p = strtok(linie, sep);
						while (p)
						{
							strcpy(mat[i], p);
							p = strtok(NULL, sep);
							i++;
						}
					}
				}
			}
		}
	}
	// prelucram matricea de caractere pentru a seta tipul fiecarei sectiuni

	int fixare_tip = -1, cont = 0, indice_fixare_tip; // fixare_tip = linia din matrice unde incepe o sectiune, cont = contor pentru virgula (REFERINTA LA LINIA 87), indice_fixare_tip = un auxiliar pentru plasarea tipului sectiunii (A, B, C)
	char aux[256]; // aux = auxiliar pentru a retine o linie din matrice

	for (int j = 0; j < i; j++) // setam tipul pe ultima pozitie a fiecarei etichete de unde incepe o sectiune
	{
		cont = 0;
		strcpy(aux, mat[j]);
		if (aux[strlen(aux) - 1] == ':')
			fixare_tip = j;
		if (fixare_tip != -1 && aux[strlen(aux) - 1] != ':')
		{
			if (aux[0] != 'Q' && strcmp(aux, "End") != 0) // inseamna ca e alfabet
			{
				indice_fixare_tip = strlen(mat[fixare_tip]);
				mat[fixare_tip][indice_fixare_tip - 1] = 'A';
			}
			else
			{
				for (int i = 0; i < strlen(aux); i++) // acum trebuie sa decidem daca e stare sau tranzitie in functie de ce se afla dupa a doua virgula
				{
					if (aux[i] == ',')
						cont++;
					if (cont == 2 && aux[i] == 'Q') // daca am gasit 2 virgule si urmatorul caracter fix dupa a doua virgula e Q, inseamna ca e tranzitie. daca gaseam F, sau S, inseamna ca este o stare (REFERINTA LINIA 95)
					{
						indice_fixare_tip = strlen(mat[fixare_tip]);
						mat[fixare_tip][indice_fixare_tip - 1] = 'C';
						break;
					}
					else
						if (cont == 1 && (aux[i] == 'F' || aux[i] == 'S'))
						{
							indice_fixare_tip = strlen(mat[fixare_tip]);
							mat[fixare_tip][indice_fixare_tip - 1] = 'B';
							break;
						}
				}
			}
		}

	}
	return &mat;
}
vector<char*> get_section_list(matricechar* content) // functia care returneaza o lista cu toate sectiunile din fisier 
{
	/*
	aceasta functie a fost facuta dupa cateva zile de la cea de mai sus,
	si am realizat ca este prea complicat de lucrat cu matricea de char,
	in concluzie am apelat la un vector de pointeri char
	*/
	vector<char*> sectiuni; // vectorul de returnat
	char cuvant[256], verificare_end[256]; // in cuvant copiem fiecare linie din matrice, iar in verificare_end copiem linia anterioara lui cuvant prin care verificam daca am ajuns la sfarsitul unei sectiuni

	for (int j = 0; j < i; j++)
	{
		if (j > 0) // nu se poate copia o linie anterioara lui cuvant daca j = 0
			strcpy(verificare_end, content[0][j - 1]);
		strcpy(cuvant, content[0][j]);
		if (j == 0 || strcmp(verificare_end, "End") == 0) //numele unei sectiuni este pe prima linie sau fix dupa un "End"
			sectiuni.push_back(content[0][j]);
	}
	return sectiuni;
}
vector <char*> get_section_content(matricechar* content, char section_name[256]) // functia care returneaza continutul unei sectiuni
{
	vector<char*> continut, rez; // continut = continutul sectiunii cerute, rez ne ajuta la formatarea continutului urmand sa fie returnat
	char cuvant[256], verificare_end[256]; // cuvant = auxiliar pentru a copia fiecare linie din matriece, verificare_end = ne ajuta sa iesim din while cand dam de "End"
	int verificare = 1;

	for (int j = 0; j < i; j++)
	{
		strcpy(cuvant, content[0][j - 1]);
		if (strcmp(cuvant, section_name) == 0)
		{
			while (strcmp(verificare_end, "End") != 0 && strcmp(verificare_end, section_name) != 0)
			{
				continut.push_back(content[0][j]);
				j++;
				strcpy(verificare_end, content[0][j]);
			}
		}
	}
	if (section_name[strlen(section_name) - 1] == 'A') // daca 'A' e pe ultima pozitie a etichetei, inseamna ca e alfabet
	{
		char verificare_q[256];
		for (int j = 0; j < continut.size(); j++)
		{
			if (count(rez.begin(), rez.end(), continut[j]) == 0) // ii dam push doar daca nu este deja in vector, eliminand dublurile
				rez.push_back(continut[j]);

			strcpy(verificare_q, continut[j]); // verificam daca este vreun 'Q' sau 'q' in litera din alfabet
			for (int k = 0; k < strlen(verificare_q); k++)
				if (verificare_q[k] == 'Q' || verificare_q[k] == 'q')
				{
					cout << "Eroare pentru continut de tip <<Alfabet>>, s-a gasit un <<Q>>" << endl; // daca da, afisam un mesaj de eroare si returnam un vector gol
					rez.clear();
					return rez;
				}
		}
		return rez;
	}
	else
		if (section_name[strlen(section_name) - 1] == 'B') // daca 'B' e pe ultima pozitie a etichetei, inseamna ca e o sectiune de stari
		{
			int gasit_s = 0; // numaram cate etichete 'S' gasim, (REFERINTA LINIILE [174,175])
			char aux1[256]; // auxiliar pentru a copia fiecare linie din continut
			for (int j = 0; j < continut.size(); j++)
			{
				strcpy(aux1, continut[j]);
				for (int k = 0; k < strlen(aux1); k++)
					if (aux1[k] == 'S')
						gasit_s++;
				if (count(rez.begin(), rez.end(), continut[j]) == 0 && gasit_s < 2) // ii dam push doar daca nu este deja in vector, si daca nu am gasit inca 2 etichete 'S'
					rez.push_back(continut[j]);
			}
			if (gasit_s > 1) // daca am gasit mai mult de o eticheta 'S', afisam un mesaj de eroare si returnam un vector gol
			{
				cout << "Eroare pentru continut de tip <<Stare>>, s-au gasit " << gasit_s << " etichete cu proprietatea <<S>>" << endl;
				rez.clear();
				return rez;
			}
			else
				return rez;
		}
		else
			if (section_name[strlen(section_name) - 1] == 'C') // daca 'C' e pe ultima pozitie a etichetei, inseamna ca e o sectiune de tranzitii
			{
				int ok1, ok2, ok3; // ok1 = 1 daca prima stare este corect formata, ok2 = 1 daca litera este corect formata, ok3 = 1 daca a doua stare este corect formata
				char aux[256], numere[] = "0123456789"; // auxiliar pentru a copia pointer-ul
				char* p; // pointer pentru strtok
				ok1 = 1;
				ok2 = 1;
				ok3 = 1;
				for (int j = 0; j < continut.size(); j++)
				{
					p = strtok(continut[j], ","); // prima stare
					rez.push_back(p);
					strcpy(aux, p);
					for (int k = 1; k < strlen(aux); k++)
						if (strchr(numere, aux[k]) == NULL) // verificam daca dupa Q urmeaza numere == formatarea corecta
							ok1 = 0;

					p = strtok(NULL, ","); // litera
					rez.push_back(p);
					strcpy(aux, p);
					for (int k = 0; k < strlen(aux); k++) // verificam daca in litera se afla Q sau q == formatarea corecta
					{
						if (aux[k] == 'Q')
							ok2 = 0;
					}

					p = strtok(NULL, ","); // a doua stare
					rez.push_back(p);
					strcpy(aux, p);
					for (int k = 1; k < strlen(aux); k++)
						if (strchr(numere, aux[k]) == NULL) // verificam daca dupa Q urmeaza numere == formatarea corecta
							ok3 = 0;

					if (ok1 == 0 || ok2 == 0 || ok3 == 0) // daca una din cele 3 variabile este 0, inseamna ca nu este formata corect o linie din tranzitie
					{
						cout << "Eroare pentru continut de tip <<Tranzitie>>, linia " << j + 1 << " nu respecta formatul -> "; // afisam un mesaj de eroare si numarul linii eronate si returnam un vector gol
						if (ok1 == 0)
							cout << "prima stare nu este formatata corect" << endl;
						if (ok2 == 0)
							cout << "litera nu este formatata corect" << endl;
						if (ok3 == 0)
							cout << "a doua stare nu este formatata corect" << endl;
						rez.clear();
						return rez;
					}
				}
				return rez;
			}
	cout << "Eroare la tipul sectiunii, nu s-a gasit identificatorul pe ultima pozitie" << endl; // daca nu am gasit niciun tip de sectiune, afisam un mesaj de eroare si returnam un vector gol
	rez.clear();
	return rez;
}
