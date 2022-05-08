#pragma once

#ifndef STUDENT
#define STUDENT
#include <iostream>
#include <string>
class Student {
public:
	char Id[11]; char Name[11]; char Address[16];
	char DateEnroll[16]; char temp[16]; int NumberCredit;

	Student();
	Student(char*, char*, char*, char*, char*);
	friend std::istream& operator >> (std::istream& stream, Student& s);
	friend std::ostream& operator << (std::ostream& stream, Student& s);

	void Print(ostream&, char*) const;
	void Clear();
	int Pack(IOBuffer&) const;
	int Unpack(IOBuffer&);
};

Student::Student() {
	Id[0] = 0; Name[0] = 0; Address[0] = 0;
	DateEnroll[0] = 0; temp[0] = 0; NumberCredit = 0;
}

Student::Student(char* id, char* name, char* add, char* date, char* tmp) {
	strcpy(Id, id);
	strcpy(Name, name);
	strcpy(Address, add);
	strcpy(DateEnroll, date);
	strcpy(temp, tmp);
	NumberCredit = stoi(temp);
}

void Student::Print(ostream& stream, char* label = 0) const
{
	if (label == 0) stream << "Student";
	else stream << label;
	stream << "\n\t  Id '" << Id << "'\n"
		<< "\t Name '" << Name << "'\n"
		<< "\t    Address '" << Address << "'\n"
		<< "\t       Date '" << DateEnroll << "'\n"
		<< "\t   Credit '" << temp << "'\n" << flush;
}

void Student::Clear()
{
	// set each field to an empty string
	Id[0] = 0; Name[0] = 0; Address[0] = 0;
	DateEnroll[0] = 0; temp[0] = 0; NumberCredit = 0;
}

int Student::Pack(IOBuffer& Buffer) const
{// pack the fields into a FixedFieldBuffer, 
 // return TRUE if all succeed, FALSE o/w
	int numBytes;
	Buffer.Clear();
	numBytes = Buffer.Pack(Id);//동적 바인딩
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Name);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Address);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(DateEnroll);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(temp);
	if (numBytes == -1) return FALSE;
	return TRUE;
}

int Student::Unpack(IOBuffer& Buffer)
{
	Clear();
	int numBytes;
	//power of virtual functions
	numBytes = Buffer.Unpack(Id);//Unpack()에 대항 F12를 누르면 일치하는 3개 함수 존재 - 동적 바인딩
	if (numBytes == -1) return FALSE;
	Id[numBytes] = 0;
	numBytes = Buffer.Unpack(Name);
	if (numBytes == -1) return FALSE;
	Name[numBytes] = 0;
	numBytes = Buffer.Unpack(Address);
	if (numBytes == -1) return FALSE;
	Address[numBytes] = 0;
	numBytes = Buffer.Unpack(DateEnroll);
	if (numBytes == -1) return FALSE;
	DateEnroll[numBytes] = 0;
	numBytes = Buffer.Unpack(temp);
	if (numBytes == -1) return FALSE;
	temp[numBytes] = 0;

	return TRUE;
}

istream& operator >> (istream& stream, Student& s)
{ // read fields from file
	char delim;
	stream.getline(s.Id, 30, '|');
	if (strlen(s.Id) == 0) return stream;
	stream.getline(s.Name, 30, '|');
	stream.getline(s.Address, 30, '|');
	stream.getline(s.DateEnroll, 30, '|');
	stream.getline(s.temp, 15, '|');
	s.NumberCredit = stoi(s.temp);
	cout << endl << "istream.getline(object, size, '|') 실행됨" << endl;
	return stream;
}
ostream& operator << (ostream& stream, Student& s)
{ // insert fields into file
	cout << "Person 객체를 출력한다" << endl;
	stream << s.Id << '|' << s.Name << '|'
		<< s.Address << '|' << s.DateEnroll << '|'
		<< s.NumberCredit << '|';
	cout << endl;
	return stream;
}
#endif

