//Source:Functions For WrongQuestionManagementSystem

//Headers
#include <time.h>
#include "Includes.h"

//Functions
	//Command
		int DisplayHelp(int, char* []);
		int ClearScreen(int, char* []);
		int Browse(int, char* []);
		int Add(int, char* []);
		int Delete(int, char* []);
		int Alter(int, char* []);
	//Normal
		void Greet(void);
		int Explain(char*, char*, char* []);
		int ToNum(char[]);
		int Run(int, int, char* []);
		extern void Destroy(char*, char*, char* [4]);
		extern int WriteLog(FILE*, char*);
	//Change
		extern Subject STRToSubject(char*);
		extern Type STRToType(char*);
		extern char* SubjectToSTR(Subject);
		extern char* TypeToSTR(Type);
	//Read && Write
		extern WrongQuestionLL* Read(unsigned int, FILE*);
		extern int Print(WrongQuestionLL*, Subject);
		extern void LLFree(WrongQuestionLL*);
	//Just for fun
		extern void PrintLine(void);
		extern void DoSomething(void);
		extern void DoSomethingElse(void);
//Functions Pointer
extern int(*(func_p[6]))(int, char* []);
char* Command[6] = { "help","cls","browse","add","delete","alter" };

//All WrongQuestions
Infomation AllWQ;

void Greet(void)
//Greet the user
{
	//time
	time_t rawtime;
	struct tm* ptminfo;
	time(&rawtime);
	ptminfo = localtime(&rawtime);
	char weekday[10];
	switch (ptminfo->tm_wday)
	{
	case 0:
		strcpy(weekday, "Sunday");
		break;
	case 1:
		strcpy(weekday, "Monday");
		break;
	case 2:
		strcpy(weekday, "Tuesday");
		break;
	case 3:
		strcpy(weekday, "Wednesday");
		break;
	case 4:
		strcpy(weekday, "Thursday");
		break;
	case 5:
		strcpy(weekday, "Friday");
		break;
	case 6:
		strcpy(weekday, "Saturday");
		break;
	default:
		strcpy(weekday, "ERROR");
	}
	//user_name
	char name[20];
	FILE* fp;
	fp = fopen("WQMS-DATA\\User-Info\\Name", "r+");
	fscanf(fp, "%[^\n]", name);
	fclose(fp);
	//output
	printf("***************************************\n");
	printf("|  Welcome, %-26s|\n", name);
	printf("|  Time:%4d-%2d-%2d %9s %2d:%2d:%2d |\n",
		ptminfo->tm_year + 1900,
		ptminfo->tm_mon + 1,
		ptminfo->tm_mday,
		weekday,
		ptminfo->tm_hour,
		ptminfo->tm_min,
		ptminfo->tm_sec);
	//year-month-day weekday hour:minute:second
	printf("|  Have a good day!                   |\n");
	printf("***************************************\n");
}

int DisplayHelp(int argc, char* argv[]) 
{
	if (argc > 0)
		return ERR_TOOMANYARG;
	else if (argc < 0)
		return ERR_TOOFEWARG;
	else
	{
		printf("\
Special  :exit\n\
          Exit this program\n\
Command-0:help\n\
          Show this list\n\
Command-1:cls [-\"g\"|-\"n\"]\n\
          Clear screen[show greet or not]\n\
Command-2:browse [-\"all\"|-\"chinese\"|-\"math\"|-\"english\"|-\"politics\"|-\"history\"|-\"geography\"|-\"biology\"|-\"physics\"|-\"chemistry\"] [-\"n\"|-\"p\"]\n\
          Show the wrong questions[subject], print or not\n\
Command-3:add \n\
          Add a new wrong question\n\
Command-4:delete [-number]\n\
          Delete a wrong question[question-number]\n\
Command-5:alter [-number]\n\
          Alter a wrong question[question-number](Including subject|question|answer|etc.)\n");
		return ERR_NO;
	}
}

/*##############################MAGIC_PROTECT##############################*/
/**/int Explain(char* full_command, char* command, char* args[])
//Don't touch, magic!
//If you try to edit this function, you'll be in PRISON, and this program will NOT be running!!!
{
	char* i_p, * o_p;
	for (i_p = full_command, o_p = command; *i_p != '\0' && *i_p != ' '; i_p++, o_p++)
		*o_p = *i_p;
	*o_p = '\0';
	if (*i_p == '\0')
		return 0;
	i_p++;
	int n = 0;
	for (; *i_p != '\0'; n++)
	{
		if (n != 0)
			i_p++;
		o_p = args[n + 1];
		for (; *i_p != ' ' && *i_p != '\0'; i_p++, o_p++)
			*o_p = *i_p;
		*o_p = '\0';
	}
	return n;
}
/*##############################MAGIC_PROTECT##############################*/

int ToNum(char command[])
{
	int i;
	for (i = 0; i < 6; i++)
		if (strcmp(command,Command[i]) == 0)
			return i;
	//Function usually ends here
//No this function
	return ERR_NOFUNC;
}

int Run(int num, int arg_num, char* args[])
{
	return (*(func_p[num]))(arg_num, args);
}

int ClearScreen(int argc, char* argv[])
{
	if (argc == 0)
		return ERR_TOOFEWARG;
	else if (argc > 1)
		return ERR_TOOMANYARG;
	else if (strcmp(argv[1], "-g") == 0)
	{
		system("cls");
		Greet();
		return ERR_NO;
	}
	else if (strcmp(argv[1], "-n") == 0)
	{
		system("cls");
		return ERR_NO;
	}
	else
		return ERR_NOTHISARG;
}

int Browse(int argc, char* argv[])
{
	if (argc < 2)
		return ERR_TOOFEWARG;
	else if (argc > 2)
		return ERR_TOOMANYARG;
	else if ((STRToSubject(argv[1] + 1/*Jump '-'*/) != 0 || strcmp(argv[1], "-all") == 0) && (strcmp(argv[2], "-p") == 0 || strcmp(argv[2], "-n") == 0))
	{
		if (AllWQ.head != NULL)
			LLFree(AllWQ.head);
			//WrongQuestionLL* bptr = AllWQ.head;
			//WrongQuestionLL* ptr = bptr->next;
			//while (ptr != NULL)
			//{
			//	free(bptr);
			//	bptr = ptr;
			//	ptr = ptr->next;
			//}
			//free(bptr);
		AllWQ.head = NULL;
		AllWQ.Number = 0;
		FILE* num_fp;
		if((num_fp = fopen("WQMS-DATA\\Wrong-Questions\\Number.lst", "r")) == NULL)
			return ERR_CANNOTOPENFILE;
		fscanf(num_fp, "WrongQuestionsNumber=%d", &AllWQ.Number);
		fclose(num_fp);
		FILE* lst_fp;
		if ((lst_fp = fopen("WQMS-DATA\\Wrong-Questions\\WrongQuestions.lst", "r")) == NULL)
			return ERR_CANNOTOPENFILE;
		AllWQ.head = Read(AllWQ.Number, lst_fp);
		if (strcmp(argv[2], "-p") == 0)
		{
			if (strcmp(argv[1], "-all") == 0)
				Print(AllWQ.head, 0);
			else
				Print(AllWQ.head, STRToSubject(argv[1] + 1));
		}
		return ERR_NO;
	}
	else
		return ERR_NOTHISARG;
}

int Add(int argc, char* argv[])
{
	if (argc < 0)
		return ERR_TOOFEWARG;
	else if (argc > 0)
		return ERR_TOOMANYARG;
	else if (argc == 0)
	{
		//Single WrongQuestion
		WrongQuestion WQ;
		char tpm_subject[16];
		int tpm_type;
		printf("Information\n");
		PrintLine();
		printf("Number:%d\n", AllWQ.Number + 1);
	SUBJECT:
		printf("Subject:");
		scanf("%s", tpm_subject);
		getchar();
		if (STRToSubject(tpm_subject) != 0)
			WQ.BasedInfo.subject = STRToSubject(tpm_subject);
		else
		{
			printf("Unknown subject, we support\n\
chinese, math, english, politics, history, geography, biology.\n\
please check and try again.\n");
			goto SUBJECT;
		}
		printf("Title:");
		scanf("%[^\n]", WQ.BasedInfo.title);
		getchar();
		printf("Types:1 for texture-only, 2 for picture-only, 3 for both-of-them\n");
	Question:
		printf("Question Type:");
		scanf("%d", &tpm_type);
		getchar();
		if (tpm_type == 1 || tpm_type == 2 || tpm_type == 3)
			WQ.Question = tpm_type;
		else
		{
			printf("Unknown number of type, please check and try again.\n");
			goto Question;
		}
	Answer:
		printf("Answer Type:");
		scanf("%d", &tpm_type);
		getchar();
		if (tpm_type == 1 || tpm_type == 2 || tpm_type == 3)
			WQ.Answer = tpm_type;
		else
		{
			printf("Unknown number of type, please check and try again.\n");
			goto Answer;
		}
	Explain:
		printf("Explain Type:");
		scanf("%d", &tpm_type);
		getchar();
		if (tpm_type == 1 || tpm_type == 2 || tpm_type == 3)
			WQ.Explain = tpm_type;
		else
		{
			printf("Unknown number of type, please check and try again.\n");
			goto Explain;
		}
	IF:
		printf("Needs blank to answer(when print)?<y/n>");
		char answer = getchar();
		getchar();
		if ((int)answer == (int)'y'|| (int)answer == (int)'Y')
			WQ.PrintInfo.is_blank_area = true;
		else if ((int)answer == (int)'n'|| (int)answer == (int)'N')
			WQ.PrintInfo.is_blank_area = false;
		else
		{
			printf("Unknown answer, please input again.\n");
			goto IF;
		}
		FILE* lst_fp, *num_fp;
		num_fp = fopen("WQMS-DATA\\Wrong-Questions\\Number.lst","w");
		fprintf(num_fp, "WrongQuestionsNumber=%d", AllWQ.Number + 1);
		fclose(num_fp);
		lst_fp = fopen("WQMS-DATA\\Wrong-Questions\\WrongQuestions.lst", "a");
		fprintf(lst_fp, "{\
{is_deleted=\"0\";}\
{subject=\"%d\";title=\"%s\";}\
{question_type=\"%d\";}\
{answer_type=\"%d\";}\
{explain_type=\"%d\";}\
{is_blank=\"%d\";}\
}\n",
			WQ.BasedInfo.subject, WQ.BasedInfo.title,
			WQ.Question,
			WQ.Answer,
			WQ.Explain,
			WQ.PrintInfo.is_blank_area
			);
		fclose(lst_fp);
		return ERR_NO;
	}
	else
		return ERR_NOTHISARG;
}

int Delete(int argc, char* argv[])
{
	unsigned int del_number;
	if (argc < 1)
		return ERR_TOOFEWARG;
	else if (argc > 1)
		return ERR_TOOMANYARG;
	else if (((del_number = atoi(argv[1])) != 0) && del_number <= AllWQ.Number)
	{
		PrintLine();
	ANSWER:
		printf("Really want to delete?<y/n>");
		char answer = getchar();
		if (answer == 'y' || answer == 'Y')
		{
			unsigned int i = 1;
			int tmp_del;
			bool is_deleted;
			FILE* lst_fp;
			if ((lst_fp = fopen("WQMS-DATA\\Wrong-Questions\\WrongQuestions.lst", "r+")) == NULL)
				return ERR_CANNOTOPENFILE;
			while (i < del_number)
			{
				fscanf(lst_fp, "{{is_deleted=\"%d\";}%*[^\n]\n", &tmp_del);
				is_deleted = (bool)tmp_del;
				if (is_deleted == true)
					continue;
				i++;
			}//Read all line before 
			fseek(lst_fp, 14L, SEEK_CUR);
			fprintf(lst_fp, "1");
			fclose(lst_fp);
			FILE* num_fp;
			if ((num_fp = fopen("WQMS-DATA\\Wrong-Questions\\Number.lst", "w")) == NULL)
				return ERR_CANNOTOPENFILE;
			fprintf(num_fp, "WrongQuestionsNumber=%d", AllWQ.Number - 1);
			fclose(num_fp);
		}
		else if (answer == 'n' || answer == 'N')
			return ERR_NO;
		else
		{
			printf("Unknown answer, please check and try again.\n");
			goto ANSWER;
		}
	}
	else
		return ERR_NOTHISARG;
}

int Alter(int argc, char* argv[])
{
	;
}