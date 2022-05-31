#include<iostream>
#include<cmath>
#include<string>
using namespace std;

enum	Instruction_conversion
{
	add = 0,
	sub = 0,
	lw = 35,
	sw = 43,
	beq = 4,
	bne = 5
};              //OP


struct MachineCode_RFormat
{
	string op = { "000000" };
	string rs = { "00000" };
	string rt = { "00000" };
	string rd = { "00000" };
	string shamt = { "00000" };
	string funct = { "000000" };
};                  //RFormat

struct MachineCode_IFormat
{
	string op = { "000000" };
	string rs = { "00000" };
	string rt = { "00000" };
	string adress = { "0000000000000000" };			//16bit
};					//IFormat


class Instruction {
private:
	string InstructionCode;
	string MIPSmachineCode;
	string op;
	string rs;
	string rt;
	string rd;
	string adress;
	string *lable;
	string *Jlable;
	int InstructionNumber;
	int InstructionGap;
	int funct;
	int type;  //0表無,1表R,2表I,3表J
	int JSwitch; //0表無須跳,1表跳
	MachineCode_RFormat *RFormat;
	MachineCode_IFormat *IFormat;
public:
	Instruction* link;
	Instruction* top;
	Instruction(string* str, int i) { InstructionCode = *str; type = 0; JSwitch = 0; funct = 0; InstructionNumber = i; lable = NULL; Jlable = NULL; InstructionGap = NULL; RFormat = NULL; IFormat = NULL; link = NULL; top = NULL; };
	Instruction() { type = 0; JSwitch = 0; funct = 0; InstructionNumber = 0; lable = NULL; Jlable = NULL; InstructionGap = NULL; RFormat = NULL; IFormat = NULL; link = NULL; top = NULL; };
	void  Format();
	void  StringProcessing();
	void  SpecialTreatment(int IN);
	void  output();
	void  change_and_output();
	void  Preprocessing();
	void  MediumProcessing(Instruction *IS);
	void  PostProcessing();
	~Instruction();
};
