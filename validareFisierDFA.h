//#include "functii L1 LFA.h"
//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <fstream>
//#include <vector> 
//#include <algorithm>
//using namespace std;
//
//typedef char matricechar[256][256];
//
//
//// FUNCTIILE DIN "functii L1 LFA.h"
//matricechar* load_file(char s[256]);
//vector<char*> get_section_list(matricechar* content);
//vector<char*> get_section_content(matricechar* content, char section_name[256]);
//
//void validareFisier(char file_name[100])
//{
//	bool errors = false;
//	cout << "Show errors? (y/n): ";
//	char yn;
//	cin >> yn;
//	if (yn == 'y')
//		errors = true;
//	
//
//	matricechar* content;
//	vector<char*> sec_lst, sec_cnt;
//
//	content = load_file(file_name);
//
//	sec_lst = get_section_list(content);
//
//
//	for (int i = 0; i < sec_lst.size(); i++)
//	{
//		bool okA = false, okB = false, okC = false; // o sa verificam daca gasim toate sectiunile 
//		sec_cnt = get_section_content(content, sec_lst[i]); // la fiecare i avem o sectiune
//		// copiez sec_lst[i] intr un auxiliar ca sa ii verific ultima litera sa vad ce tip este
//
//
//		cout << endl;
//		char aux[256];
//		strcpy(aux, sec_lst[i]);
//		char ultimaLitera = aux[strlen(aux) - 1];
//		if (ultimaLitera == 'A') // sectiunea este de tip alfabet, nu avem ce sa verificam, starile si tranzitiile sunt bazate pe aceasta sectiune
//			okA = true;
//		else
//			if (ultimaLitera == 'B') // sectiunea este de tip stari, trebuie sa verificam daca se exista duplicate
//			{
//				okB = true;
//				for (int j = 0; j < sec_cnt.size(); j++)
//				{
//					for (int k = j + 1; k < sec_cnt.size(); k++)
//					{
//						char aux1[5], aux2[5]; // copiem primele 2 litere, adica starea din variabilele sec_cnt[j] si sec_cnt[k]
//						strncpy(aux1, sec_cnt[j], 2);
//						strncpy(aux2, sec_cnt[k], 2);
//						aux1[2] = '\0';
//						aux2[2] = '\0';
//						if (strcmp(aux1, aux2) == 0)
//						{
//							if (errors)
//								cout << "Eroare! Starea " << sec_cnt[j] << " este duplicata in sectiunea " << sec_lst[i] << endl;
//						}
//					}
//				}
//			}
//			else
//				if (ultimaLitera == 'C') // sectiunea este de tip tranzitii, trebuie sa verificam intram in toate sectiuniile A(alfabet) si B(stari) si sa verificam daca tranzitiile sunt valide
//				{
//					// sectiunea C(tranzitii) este un vector de forma: vector[i] = stare1, vector[i+1] = litera, vector[i+2] = stare2
//					okC = true;
//					// trebuie sa verificam daca exista tranzitii care au starea 1 sau starea 2 care nu exista in sectiunea B(stari)
//					vector<char*> stari; // intr-un vector auxiliar(stari) copiem starile fara sa fie duplicate
//					for (int iter = 0; iter < sec_cnt.size(); iter++)
//					{
//						char primaLitera;
//						primaLitera = sec_cnt[iter][0];
//						if (primaLitera == 'Q')
//						{
//							// nu bagam dubluri in stari
//							bool ok = true;
//							for (int j = 0; j < stari.size(); j++)
//								if (strcmp(stari[j], sec_cnt[iter]) == 0)
//									ok = false;
//							if (ok)
//								stari.push_back(sec_cnt[iter]);
//						}
//					}
//					// acum ca avem starile in vectorul stari, mergem in sectiunile de tip B(stari), poate sunt mai multe, si verificam daca exista starea in vectorii stari
//					for (int iter = 0; iter < sec_lst.size(); iter++)
//					{
//						char aux[256];
//						strcpy(aux, sec_lst[iter]);
//						char ultimaLitera = aux[strlen(aux) - 1];
//						if (ultimaLitera == 'B')
//						{
//							vector <char*> stariB;
//							stariB = get_section_content(content, sec_lst[iter]);
//							int marimeStariB = stariB.size();
//							vector <char*> newStariB; // un alt vector in care formatam cum trebuie = stergem F si S
//							for (int j = 0; j < marimeStariB; j++)
//							{
//								char* oStareB = new char[5];
//								oStareB[0] = stariB[j][0];
//								oStareB[1] = stariB[j][1];
//								oStareB[2] = '\0';
//								newStariB.push_back(oStareB);
//							}
//							stariB = newStariB;
//
//							bool ok = true;
//								int cont = 0;
//							for (int j = 0; j < stari.size(); j++)
//							{
//								for (int k = 0; k < newStariB.size(); k++)
//									if (strcmp(stari[j], newStariB[k]) == 0)
//										cont++;
//								/*else
//									if (errors)
//										cout << "Starea " << stari[j] << " din sectiunea de tranzitii nu se regaseste in sectiunile de stari." << endl;*/
//							}
//							if (cont != stari.size() && errors)
//								// cout << "Starea " << stari[j] << " din sectiunea de tranzitii nu se regaseste in sectiunile de stari." << endl;
//								cout << "Exista stari in sectiunile de tranzitie care nu se regasesc in sectiunile de stari.";
//
//
//							/*TO DO validare pentru litera din sectiunea de tranzitii*/
//
//							//// acum trebuie sa verificam daca litera din sectiunea de tranzitii se regaseste in sectiunea de alfabet
//							//vector<char*> alfabet;
//							//vector<char*> alfabetAux;
//							//for (int j = 0; j < sec_lst.size(); j++)
//							//{
//							//	char aux[256];
//							//	strcpy(aux, sec_lst[j]);
//							//	char ultimaLitera = aux[strlen(aux) - 1];
//							//	if (ultimaLitera == 'A')
//							//	{
//							//		alfabetAux = get_section_content(content, sec_lst[j]);
//							//		for(int i=0;i<alfabetAux.size();i++)
//							//		{
//							//			// il adaugam doar daca nu este deja in alfabet
//							//			if (find(alfabet.begin(), alfabet.end(), alfabetAux[i]) == alfabet.end())
//							//				alfabet.push_back(alfabetAux[i]);
//							//		}
//							//	}
//							//}
//							//// acum avem alfabetul in vectorul alfabet si putem sa verificam daca litera din sectiunea de tranzitii se regaseste in alfabet
//							//for (int j = 1; j < sec_cnt.size(); j += 3)
//							//{
//							//	bool ok = false;
//							//	for (int k = 0; k < alfabet.size(); k++)
//							//		if (strcmp(sec_cnt[j + 1], alfabet[k]) == 0)
//							//			ok = true;
//							//	if (!ok && errors)
//							//	{
//							//		cout << "Litera " << sec_cnt[j] << " din sectiunea de tranzitii nu se regaseste in sectiunea de alfabet." << endl;
//							//		ok = true;
//							//	}
//							//}
//						}
//					}
//
//				}
//	}
//}
