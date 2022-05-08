/*
교재: 367, 20번 programming project
Ledger 대신에 Student, Journal 대신에 course registration class를 정의한다.
*/


#include "recfile.h"
#include "stdlib.h"
#include <fstream>
#include <string.h>
#include "length.h"
#include "student.h"
#include "course_registration.h"
class TranscriptProcess : public MasterTransactionProcess<int>
	// Transcript processing of a Transcript file and a journal file
	// the item type is int to represent an account number
{
public:
	TranscriptProcess(int monthNumber); // constructor

	// Basic list processing methods
	int InitializeList(int ListNumber, char* List1Name);
	int InitializeOutput(char* OutputListName);
	int NextItemInList(int ListNumber); //get next item from this list
	int Item(int ListNumber); // return current item from this list
	int ProcessItem(int ListNumber); // process the item in this list
	int FinishUp(); // complete the processing

	// master/transaction methods
	virtual int ProcessNewMaster();//  when new master read
	virtual int ProcessCurrentMaster();// each transaction for a master
	virtual int ProcessEndMaster();// after all transactions for a master
	virtual int ProcessTransactionError();// no master for transaction

protected:
	// members
	int MonthNumber; // number of month to be processed
	LengthFieldBuffer Lbuffer, Jbuffer; // buffers for files
	RecordFile<Student> TranscriptFile; // list 1
	RecordFile<CourseResistration> JournalFile;// list 2
	int AccountNumber[3]; // current item in each list
	Student student; // current Student object
	CourseResistration CourseR; // current Course Resistration object
	ofstream OutputList; // text output file for post method
	static int LowAcct;// lower than the lowest account number
	static int HighAcct;// higher than the highest account number

	int NextItemInTranscript();
	int NextItemInJournal();
};
int main(void)
{
	//
	Student L1("A1", "A2", "A3", "A4", "5");
	Student L2("B1", "B2", "B3", "B4", "5");
	Student L3("C1", "C2", "C3", "C4", "5");
	Student L4("D1", "D2", "D3", "D4", "5");
	Student L5("E1", "E2", "E3", "E4", "5");
	Student L6("F1", "F2", "F3", "F4", "5");
	Student L7("G1", "G2", "G3", "G4", "5");
	Student L8("H1", "H2", "H3", "H4", "5");
	Student L9("I1", "I2", "I3", "I4", "5");

	//
	CourseResistration J1("CA1", "SA2", 3, 3.5);
	CourseResistration J2("CB1", "SB2", 3, 3.5);
	CourseResistration J3("CC1", "SC2", 3, 3.5);
	CourseResistration J4("CD1", "SD2", 3, 3.5);
	CourseResistration J5("CE1", "SE2", 3, 3.5);
	CourseResistration J6("CF1", "SF2", 3, 3.5);
	CourseResistration J7("CG1", "SG2", 3, 3.5);
	CourseResistration J8("CH1", "SH2", 3, 3.5);
	CourseResistration J9("CI1", "SI2", 3, 3.5);


	LengthFieldBuffer Lbuffer;
	RecordFile<Student> TranscriptFile(Lbuffer);
	int result = TranscriptFile.Create("Transcript.dat", ios::out);
	cout << "Create file " << result << endl;
	if (!result)
	{
		cout << "Unable to Create file " << "Transcript.dat" << endl;
		return 0;
	}
	TranscriptFile.Write(L1);
	//
	TranscriptFile.Close();

	LengthFieldBuffer Jbuffer;
	RecordFile<CourseResistration> journalFile(Jbuffer);
	int flag = journalFile.Create("journal.dat", ios::out);
	cout << "Create file " << flag << endl;
	if (!flag)
	{
		cout << "Unable to Create file " << "journal.dat" << endl;
		return 0;
	}
	journalFile.Write(J1);
    //
	journalFile.Close();

	int res;
	RecordFile<Student> lFile(Lbuffer);
	lFile.Open("Student.dat", ios::in);
	Student Student;
	while (1)
	{
		res = lFile.Read(Student);
		if (res <= 0) break;
		cout << "Student" << endl;
		Student.Print(cout);
	}
	RecordFile<CourseResistration> jFile(Jbuffer);
	jFile.Open("journal.dat", ios::in);
	CourseResistration journal;
	while (1)
	{
		res = jFile.Read(journal);
		if (res <= 0) break;
		journal.PrintLine(cout);
	}
	cout << "Posting " << endl;
	TranscriptProcess Posting(Month);
	/*
	Modify method TranscriptProcess::ProcessEndMaster so it updates the Transcript file 
	with the new account balances for month
	*/

	Posting.PostTransactions("Student.dat", "CourseRegistration.dat", "Transcript.txt");
	//Modify to show the file Transcript.txt
	char ch;
	fstream TranscriptJournal;
	TranscriptJournal.open("Transcript.txt", ios::in);
	while (1) {
		TranscriptJournal >> ch;
		if (TranscriptJournal.fail()) break;
		cout << ch;
	}
	//Modify to show Transcript.Print();
	cout << "Showing the new account balances for the month" << endl;
	lFile.Open("Transcript.dat", ios::in);
	//*
	while (1)
	{
		res = lFile.Read(Transcript);
		if (res <= 0) break;
		cout << "Transcript" << endl;
		Transcript.Print(cout);
	}
	
	system("pause");
	return 1;
}