#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME_LEN 50
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

typedef struct STUDENT_DATA
{
	char* fName;
	char* lName;
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

vector<PSTUDAT> loadData(vector<PSTUDAT> v)
{
	ifstream file;
	string line;
	file.open("StudentData.txt");
	if (file.is_open())
	{
		while (getline(file, line))
		{
			const char* cLine = line.c_str();
			char *tempFName = new char[MAX_NAME_LEN];
			char* tempLName = new char[MAX_NAME_LEN];
			sscanf(cLine, "%[^,],%[^,]", tempLName, tempFName);

			PSTUDAT n = createStudent(tempLName, tempFName);

			v.push_back(n); 
		}
	}
	return v;
}

void printStudents(vector<PSTUDAT> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << "Name: " << v.at(i)->fName << " " << v.at(i)->lName << endl;
	}
}

int main()
{
	vector<PSTUDAT> students;

	printStudents(loadData(students));

	return 1;
}