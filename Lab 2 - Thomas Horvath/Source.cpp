#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME_LEN 50
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

#define PreRelease

using namespace std;

typedef struct STUDENT_DATA
{
	char* fName;
	char* lName;
#ifdef PreRelease
	char* email;
#endif

} STUDAT, *PSTUDAT;

PSTUDAT createStudent(char* l, char* f)
{
	PSTUDAT s = (PSTUDAT)malloc(sizeof(PSTUDAT));

	s->fName = new char[MAX_NAME_LEN];
	s->lName = new char[MAX_NAME_LEN];

	s->fName = f;
	s->lName = l;

	return s;
}
#ifdef PreRelease
PSTUDAT createStudentEmail(char* l, char* f, char* e)
{
	PSTUDAT s = (PSTUDAT)malloc(sizeof(PSTUDAT) + sizeof(char*)); // had to make + sizeof(char*) for email allocation, not sure why it doesnt work otherwise since PreRelease is defined

	s->fName = new char[MAX_NAME_LEN];
	s->lName = new char[MAX_NAME_LEN];
	s->email = new char[MAX_NAME_LEN];

	s->fName = f;
	s->lName = l;
	s->email = e;

	return s;
}
#endif
vector<PSTUDAT> loadData(vector<PSTUDAT> v)
{
	ifstream file;
	string line;
	string filename;
#ifdef PreRelease
	filename = "StudentData_Emails.txt";
#else
	filename = "StudentData.txt";
#endif 

	file.open(filename);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			const char* cLine = line.c_str();
			char* tempFName = new char[MAX_NAME_LEN];
			char* tempLName = new char[MAX_NAME_LEN];
#ifdef PreRelease
			char* email = new char[MAX_NAME_LEN];
			sscanf(cLine, "%[^,],%[^,],%[^,]", tempLName, tempFName, email);
			PSTUDAT n = createStudentEmail(tempLName, tempFName, email);
#else
			sscanf(cLine, "%[^,],%[^,]", tempLName, tempFName);
			PSTUDAT n = createStudent(tempLName, tempFName);
#endif 
			v.push_back(n); 
		}
	}
	return v;
}

void printStudents(vector<PSTUDAT> v)
{
	for (int i = 0; i < v.size(); i++)
	{
#ifdef PreRelease
		cout << "Name: " << v.at(i)->fName << " " << v.at(i)->lName << " " << v.at(i)->email << endl;
#else
		cout << "Name: " << v.at(i)->fName << " " << v.at(i)->lName << endl;
#endif 
	}
}

int main()
{
#ifdef PreRelease
	cout << "Running PreRelease \n";
#else
	cout << "Running Standard \n"
#endif 

	vector<PSTUDAT> students;

	students = loadData(students);

#ifdef _DEBUG
	printStudents(students);
#endif

	return 1;
}