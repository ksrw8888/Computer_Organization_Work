#include<iostream>
#include<cmath>
#include<string>
#include"Instruction.h"

using namespace std;

string InstructionCode;

void MIPS_to_MachineCode();


int main() {
	char sw = 'Y';

	while (sw == 'Y' || sw == 'y')
	{
		system("CLS");
		MIPS_to_MachineCode();
		cout << endl << "Do you want to continue?(Y/N)" << endl;
		cin >> sw;
		cin.get();
	}


	//system("pause");
	return 0;
}

void MIPS_to_MachineCode() 
{
	Instruction* Data = new Instruction, * Copy = Data, * Temp;
	bool sw = 0;
	int Number = 0;

	cout << "MIPS InstructionCode :" << endl;
	getline(cin, InstructionCode, '\n');

	while (InstructionCode != "") {
		if (sw == 0) {
			Data = new Instruction(&InstructionCode, Number += 1);
			Data->top = Data;
			Copy = Data;
			sw = 1;
		}
		else {
			Temp = new Instruction(&InstructionCode, Number += 1);
			Temp->top = Data;
			Copy->link = Temp;
			Copy = Temp;
		}
		getline(cin, InstructionCode, '\n');
	}

	Copy = Data;

	while (Copy != NULL)
	{
		Copy->Preprocessing();
		Copy = Copy->link;
	}

	Copy = Data;

	while (Copy != NULL)
	{
		Temp = Data;
		while (Temp != NULL)
		{
			Copy->MediumProcessing(Temp);
			Temp = Temp->link;
		}
		Copy = Copy->link;
	}

	Copy = Data;

	while (Copy != NULL)
	{
		Copy->PostProcessing();
		Copy = Copy->link;
	}

	Copy = Data;

	while (Copy != NULL)
	{
		Temp = Copy->link;
		Copy = NULL;
		Copy = Temp;
	}

	delete Data;
}


