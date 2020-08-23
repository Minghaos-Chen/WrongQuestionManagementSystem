//Source:Functions'Helper For WrongQuestionManagementSystem

//Custom Headers
#include "Includes.h"

//Lists
char* SubPtr[] = { NULL,"chinese","math","english","politics","history","geography","biology","physics","chemistry" };
//chinese = 1, math, english, politics, history, geography, biology, physics, chemistry
char* TypePtr[] = { NULL/*Useless*/,"text_only","pict_only","text_with_pict" };
//text_only = 1, pict_only, text_with_pict

//Functions
	//Normal
		void Destroy(char*, char*, char* [4]);
		int WriteLog(FILE*, char*);
	//Change
		Subject STRToSubject(char*);
		Type STRToType(char*);
		char* SubjectToSTR(Subject);
		char* TypeToSTR(Type);
	//Read && Write
		WrongQuestionLL* Read(unsigned int, FILE*);
		int Print(WrongQuestionLL*, Subject);
		void LLFree(WrongQuestionLL*);
	//Just for fun
		void PrintLine(void);
		void DoSomething(void);
		void DoSomethingElse(void);

extern Infomation AllWQ;

Subject STRToSubject(char* str)
//TODO:Change String into Subject and return. Return 0 if str is not a subject.
{
	int i;
	for (i = 1/*No NULL*/; i < 10; i++)
		if (strcmp(str, SubPtr[i]) == 0)
			return i;
			//Function usually ends here
	//str is not a subject
	return 0;
}

Type STRToType(char* str)
//Change String into Type and return. Return 0 if str is not a type.
{
	int i;
	for (i = 1/*No NULL*/; i < 4; i++)
		if (strcmp(str, TypePtr[i]) == 0)
			return i;
			//Function usually ends here
	//str is not a type
	return 0;
}

char* SubjectToSTR(Subject subject)
//Change Subject into String and return the first address. Return NULL if there's any error.
{
	return SubPtr[subject];
}

char* TypeToSTR(Type type)
//Change Type into String and return the first address. Return NULL if there's any error.
{
	return TypePtr[type];
}

WrongQuestionLL* Read(unsigned int number, FILE* fp)
{
	WrongQuestionLL* head = (WrongQuestionLL*)malloc(sizeof(WrongQuestionLL)), * ptr = head;
	unsigned int SVS = 1;//Stupid Visual Studio, SVS, 'i' before
	//Read lines number
	unsigned int num = 1;//Number
	while (num <= number)
	{
		if (num != 1)
		{
			ptr->next = (WrongQuestionLL*)malloc(sizeof(WrongQuestionLL));
			ptr = ptr->next;
		}
		//---------------------------------------------------------------------
		fscanf(fp, "{");
	bool is_deleted;
	int tpm_bool;
		fscanf(fp, "{is_deleted=\"%d\";}", &tpm_bool);
			is_deleted = (bool)tpm_bool;
			if (is_deleted == true)
			{
				fscanf(fp, "%*[^\n]\n");
				//Read this line and throw them into the dustbin
				continue;
			}
		fscanf(fp, "{subject=\"%d\";", &ptr->WrongQuestion.BasedInfo.subject);
		fscanf(fp, "title=\"%[^\"]\";}", ptr->WrongQuestion.BasedInfo.title);
		fscanf(fp, "{question_type=\"%d\";}", &ptr->WrongQuestion.Question);
		fscanf(fp, "{answer_type=\"%d\";}", &ptr->WrongQuestion.Answer);
		fscanf(fp, "{explain_type=\"%d\";}", &ptr->WrongQuestion.Explain);
		fscanf(fp, "{is_blank=\"%d\";}", &tpm_bool);
			ptr->WrongQuestion.PrintInfo.is_blank_area = (bool)tpm_bool;
			ptr->WrongQuestion.BasedInfo.number = num;
		fscanf(fp, "}\n");
		//---------------------------------------------------------------------
		num++;
	}
	ptr->next = NULL;
	return head;
}

int Print(WrongQuestionLL* head, Subject subject)
{
	PrintLine();
	printf("%-6s %16s %32s\n", "Number", "Subject", "Title");
	WrongQuestionLL* ptr = head;
	int i = 0;
	for (ptr = head; ptr != NULL; ptr = ptr->next, i++)
		if(subject==0||ptr->WrongQuestion.BasedInfo.subject==subject)
		printf("%-6d %16s %32s\n",
			ptr->WrongQuestion.BasedInfo.number,
			SubjectToSTR(ptr->WrongQuestion.BasedInfo.subject),
			ptr->WrongQuestion.BasedInfo.title);
	return i;
}

void LLFree(WrongQuestionLL* head)
{
	WrongQuestionLL* bptr = head;
	WrongQuestionLL* ptr = bptr->next;
	while (ptr != NULL)
	{
		free(bptr);
		bptr = ptr;
		ptr = ptr->next;
	}
	free(bptr);
}

void PrintLine(void)
{
	printf("------------------------------------------------------------\n");
}

void DoSomething() {
	//Do your ass
	printf("Have already done something.\n");
}

void DoSomethingElse() {
	//Also, do your ass
	printf("Have already done something else.\n");
}

void Destroy(char* full_command, char* command, char* args[4])
{
	*full_command = '\0';
	*command = '\0';
	*args[0] = '\0';
	*args[1] = '\0';
	*args[2] = '\0';
	*args[3] = '\0';
}