#include"Instruction.h"
#include<iostream>
#include<cmath>
#include<string>

using namespace std;

void  Decimal_to_Binary(string& a, int x)				//10 to 2
{	
	int size = int(a.size());
	int bit = 0;
	for (size -= 1; size >= 0; size--)
	{
		if (x == 0)
			return;

		if (x - int(pow(2, size)) >= 0)
		{
			a[bit] = '1';
			x = x - int(pow(2, size));
		}
		bit++;
	}
	return;
};

int string_to_int(string& a)
{
	int size = int(a.size()) - 1;
	int sum = 0;

	for (int i = 0; i <= size; i++)
	{
		sum += (int(a[i]) - int(48)) * pow(10, size - i);
	}

	return sum;
};

void Instruction::Format()
{
	if ((InstructionCode.find("add", 0) != -1) || (InstructionCode.find("sub", 0) != -1))
		type = 1;

	else if ((InstructionCode.find("lw", 0) != -1) || (InstructionCode.find("sw", 0) != -1))
		type = 2;
	else if ((InstructionCode.find("beq", 0) != -1) || (InstructionCode.find("bne", 0) != -1))
	{
		type = 2;
		JSwitch = 1;
	}	 
	else
		type = 0;
	return;
}

void Instruction::StringProcessing()
{
	int i = 0;

	switch (type)
	{
	case 0:
		cout << "Input format is error\n";
		break;

	default:
		if (InstructionCode.find(":", 0) != -1)
		{
			lable = new string;
			while ((InstructionCode[i] == ' ') || (InstructionCode[i] == ','))
				i++;
			while ((InstructionCode[i] != ' ') && (InstructionCode[i] != ':'))
			{
				*lable += InstructionCode[i];
				i++;
			}
		}
		while ((InstructionCode[i] == ' ') || (InstructionCode[i] == ',') || (InstructionCode[i] == ':'))
			i++;
		while ((InstructionCode[i] != ' ') && (InstructionCode[i] != ','))
		{
			op += InstructionCode[i];
			i++;
		}
		while ((InstructionCode[i] == ' ') || (InstructionCode[i] == ','))
			i++;
		if (type == 1)																//1做RFormat
		{
			while ((InstructionCode[i] != ' ') && (InstructionCode[i] != ','))
			{
				rd += InstructionCode[i];
				i++;
			}
			while ((InstructionCode[i] == ' ') || (InstructionCode[i] == ','))
				i++;
			while ((InstructionCode[i] != ' ') && (InstructionCode[i] != ','))
			{
				rs += InstructionCode[i];
				i++;
			}
			while ((InstructionCode[i] == ' ') || (InstructionCode[i] == ','))
				i++;
			while ((InstructionCode[i] != ' ') && (InstructionCode[i] != ','))
			{
				rt += InstructionCode[i];
				i++;
				if (i >= int(InstructionCode.size()))
					break;
			}
		}

		else																		//2做RFormat
		{
			while ((InstructionCode[i] != ' ') && (InstructionCode[i] != ','))
			{
				rt += InstructionCode[i];
				i++;
			}
			while ((InstructionCode[i] == ' ') || (InstructionCode[i] == ','))
				i++;

			if (JSwitch == 0)
			{
				while ((InstructionCode[i] != '('))
				{
					adress += InstructionCode[i];
					i++;
					if (i >= int(InstructionCode.size()))
						break;
				}

				while ((InstructionCode[i] == ' ') || (InstructionCode[i] == '('))
					i++;
					
				while ((InstructionCode[i] != ' ') && (InstructionCode[i] != ')'))
				{
					rs += InstructionCode[i];
					i++;
					if (i >= int(InstructionCode.size()))
						break;
				}
				
			}
			else
			{	
				Jlable = new string;
				while ((InstructionCode[i] == ' ') || (InstructionCode[i] == ','))
					i++;
				while ((InstructionCode[i] != ' ') && (InstructionCode[i] != ','))
				{
					rs += InstructionCode[i];
					i++;
				}
				while ((InstructionCode[i] == ' ') || (InstructionCode[i] == ','))
					i++;
				while ((InstructionCode[i] != ' ') && (InstructionCode[i] != ','))
				{
					*Jlable += InstructionCode[i];
					i++;
					if (i >= int(InstructionCode.size()))
						break;
				}
			}
		
		}

	}
	return;
}

void Instruction::SpecialTreatment(int IN)
{
	InstructionGap = abs(InstructionNumber - IN) * 4;
	return;
}

void Instruction::output()
{
	switch (type)
	{
	case 1:
		if (op == "add")
			funct = 32;
		else
			funct = 34;
		cout << "op = " << op << ", rs = " << rs << " , rt = " << rt << " , rd = " << rd << " , funct = " << funct << endl;
		break;
	case 2:
		cout << "op = " << op << ", rs = " << rs << " , rt = " << rt << " , adress = " << adress << endl;
		break;
	}
	return;
}

void Instruction::change_and_output()			//依類型轉碼
{
	string Reg[] = { "$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$t8","$t9" , "$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7" };
	int    RegN[] = { 8,9,10,11,12,13,14,15,24,25,16,17,18,19,20,21,22,23 };
	bool   test1 = 0, test2 = 0, test3 = 0;
	Instruction_conversion OP;


	if (type == 1)
	{
		RFormat = new MachineCode_RFormat;
		if (op == "add")
		{
			Decimal_to_Binary(RFormat->op, add);
			funct = 32;
		}
			
		else if (op == "sub")
		{
			Decimal_to_Binary(RFormat->op, sub);
			funct = 34;
		}
			

		for (int i = 0; i<int(sizeof(Reg)/sizeof(Reg[0])); i++)
		{
			if (rs == Reg[i])
			{
				Decimal_to_Binary(RFormat->rs, RegN[i]);
				test1 = 1;
			}
			if (rt == Reg[i])
			{
				Decimal_to_Binary(RFormat->rt, RegN[i]);
				test2 = 1;
			}
			if (rd == Reg[i])
			{
				Decimal_to_Binary(RFormat->rd, RegN[i]);
				test3 = 1;
			}
			if (test1 == 1 && test2 == 1 && test3 == 1)
				break;
		}
		//以下錯誤判斷
		if (test1 == 0)
		{
			cout << "rs format is error\n";
			return;
		}

		else if (test2 == 0)
		{
			cout << "rt format is error\n";
			return;
		}

		else if (test3 == 0)
		{
			cout << "rd format is error\n";
			return;
		}
		
		Decimal_to_Binary(RFormat->funct, funct);

		MIPSmachineCode = MIPSmachineCode + RFormat->op + RFormat->rs + RFormat->rt + RFormat->rd + RFormat->shamt + RFormat->funct;

		for (int i = 0; i < int(MIPSmachineCode.size()); i++)
		{
			cout << MIPSmachineCode[i];
			if (i % 4 == 3)
				cout << " ";
		}
		cout << endl;
			
		RFormat = NULL;
		delete RFormat;
		return;
	}

	else if (type == 2)
	{
		IFormat = new MachineCode_IFormat;
		if (op == "lw")
			Decimal_to_Binary(IFormat->op, lw);
		else if (op == "sw")
			Decimal_to_Binary(IFormat->op, sw);
		else if (op == "beq")
			Decimal_to_Binary(IFormat->op, beq);
		else if (op == "bne")
			Decimal_to_Binary(IFormat->op, bne);

		for (int i = 0; i<int(sizeof(Reg) / sizeof(Reg[0])); i++)
		{
			if (rs == Reg[i])
			{
				Decimal_to_Binary(IFormat->rs, RegN[i]);
				test1 = 1;
			}
			if (rt == Reg[i])
			{
				Decimal_to_Binary(IFormat->rt, RegN[i]);
				test2 = 1;
			}
			
			if (test1 == 1 && test2 == 1 )
				break;
		}
		//以下錯誤判斷
		if (test1 != 1)
		{
			cout << "rs format is error\n";
			return;
		}

		else if (test2 != 1)
		{
			cout << "rt format is error\n";
			return;
		}

		if( JSwitch == 0 )
			Decimal_to_Binary(IFormat->adress, string_to_int(adress));
		else
			Decimal_to_Binary(IFormat->adress, InstructionGap);

		MIPSmachineCode = MIPSmachineCode + IFormat->op + IFormat->rs + IFormat->rt + IFormat->adress;
		
		for (int i = 0; i < int(MIPSmachineCode.size()); i++)
		{
			cout << MIPSmachineCode[i];
			if (i % 4 == 3)
				cout << " ";
		}
		cout << endl;

		IFormat = NULL;
		delete IFormat;
		return;
	}
	else
		return;
}

void Instruction::Preprocessing()
{
	Format();
	StringProcessing();
}

void Instruction::MediumProcessing(Instruction *IS)
{
	if (type == 2 && JSwitch == 1 && IS->lable != NULL)
	{
		if (*Jlable == *IS->lable)
			SpecialTreatment(IS->InstructionNumber);
	}
	
	return;
}


void Instruction::PostProcessing()
{
	cout << "--------------------------------------" << endl;
	change_and_output();
	cout << "--------------------------------------" << endl;
	return;
}

Instruction::~Instruction()
{
	if (lable != NULL) 
	{
		lable = NULL;
		delete lable;
	}
	if (Jlable != NULL)
	{
		Jlable = NULL;
		delete Jlable;
	}
}


