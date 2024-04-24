//#include "functii L1 LFA.h"
#include "validareFisierDFA.h"
#include "functii L1 LFA 2.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector> 
#include <algorithm>
using namespace std;

typedef char matricechar[256][256];


// FUNCTIILE DIN "functii L1 LFA.h"
//matricechar* load_file(char s[256]);
//vector<char*> get_section_list(matricechar* content);
//vector<char*> get_section_content(matricechar* content, char section_name[256]);

//FUNCTIA DIN "validareFisierDFA.h"
//void validareFisier(char file_name[100]);

// FUNCTIA DIN "functii L1 LFA 2.h"
vector<string> loadFile(string);

int main()
{
	string numeFisier = "dfa.txt";
	vector<string> content;
	content = loadFile(numeFisier);
	for (int j = 0; j < content.size(); j++)
		cout << content[j] << endl;
	cout << endl;

	vector<string> sectionList;
	sectionList = getSectionList(content);
	for(int j = 0; j < sectionList.size(); j++)
		cout << sectionList[j] << endl;
	
	cout << endl;

	vector<string> sectionContent;
	sectionContent = getSectionContent(content, sectionList[1]);
	for (int j = 0; j < sectionContent.size(); j++)
		cout << sectionContent[j] << endl;

	/*char numeFisier[] = "dfa.txt";
	validareFisier(numeFisier);
	
	matricechar* content;
	vector<char*> sec_lst, sec_cnt;

	cout << "AFISARE FORMATARE TextFile2.txt:" << endl << endl;
	content = load_file(numeFisier);
	for (int j = 0; j < i; j++)
		cout << content[0][j] << endl;
	cout << endl;*/
	return 0;
}


// EXEMPLU AFISARE A FUNCTIILOR DIN FISIERUL HEADER "functii L1 LFA.h"



/*
char file_name[] = "TextFile2.txt";
	matricechar* content;
	vector<char*> sec_lst, sec_cnt;

	cout << "AFISARE FORMATARE TextFile2.txt:" << endl << endl;
	content = load_file(file_name);
	for (int j = 0; j < i; j++)
		cout << content[0][j] << endl;
	cout << endl;

	cout << "AFISARE SECTIUNI IMPREUNA CU ETICHETA DE PE ULTIMUL CARACTER INSERATA AUTOMAT:" << endl << endl;
	sec_lst = get_section_list(content);
	for (int j = 0; j < sec_lst.size(); j++)
		cout << sec_lst[j] << endl;
	cout << endl;

	cout << "AFISARE CONTINUT PENTRU FIECARE SECTIUNE:" << endl << endl;

	sec_cnt = get_section_content(content, sec_lst[0]);
	for (int j = 0; j < sec_cnt.size(); j++)
		cout << sec_cnt[j] << ' ';
	cout << endl << endl;

	sec_cnt = get_section_content(content, sec_lst[1]);
	for (int j = 0; j < sec_cnt.size(); j++)
		cout << sec_cnt[j] << ' ';
	cout << endl << endl;

	sec_cnt = get_section_content(content, sec_lst[2]);
	for (int j = 0; j < sec_cnt.size(); j += 3)
		cout << sec_cnt[j] << ' ' << sec_cnt[j + 1] << ' ' << sec_cnt[j + 2] << endl;
*/

// COM DESKTOP