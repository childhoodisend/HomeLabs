// lab5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include<cstdlib>
#include<string>

using namespace std;

class STUDENT
{
public:
	string Iold;
	string sfName;
	string slName;
	STUDENT* pNext;
};

STUDENT* pHead = nullptr;

void gett(STUDENT* ptr) {

	ptr->pNext = pHead;
	pHead = ptr;
}
STUDENT* get_data() {

	string fname, lname, old;

	cout << "Enter fname " << endl;
	getline(cin, fname);	
	if (fname == "exit") 
		return 0;
	
	cout << "Enter lname " << endl;
	getline(cin, lname);	
	if (lname == "exit") 
		return 0;

	cout << "Enter old " << endl;
	cin >> old;
	if (old == "0")
		return 0;
	
	STUDENT* ptr = new STUDENT;
	ptr->sfName = fname;
	ptr->slName = lname;
	ptr->Iold = old;
	ptr->pNext = nullptr;
	return ptr;
}
int main() {
	STUDENT* ptr;
	while (ptr = get_data()) 
		gett(ptr);
	
	for (STUDENT* first = pHead; first; first = first->pNext) 
		cout << first->sfName <<" "<< first->slName <<" " << first->Iold << endl;
	
	system("pause");
	cin.ignore();
	return 0;
}

