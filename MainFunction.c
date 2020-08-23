//Wrong Question Management system 
//Version 0.0.1 Beta[Release]
//             -By Mr.Minghao Chen
//                   Aug.8th, 2020
//Copyright(c)2020-[inf] Mr.Minghao Chen. All rights reserved.
//
//Source:Main-Function For WrongQuestionManagementSystem

//Custom Headers
#include "Includes.h"

//Functions In Function.c
	//Command
		extern int DisplayHelp(int, char* []);
		extern int ClearScreen(int, char* []);
		extern int Browse(int, char* []);
		extern int Add(int, char* []);
		extern int Delete(int, char* []);
		extern int Alter(int, char* []);
	//Normal
		extern void Greet(void);
		extern int Explain(char*, char*, char* []);
		extern int ToNum(char[]);
		extern int Run(int, int, char*[]);
		extern int WriteLog(FILE*, char*);
		extern void Destroy(char*, char*, char*[4]);
	//Just For Fun
		extern void DoSomething();
		extern void DoSomethingElse();
//Function Pointer
int(*(func_p[6]))(int, char* []) = { DisplayHelp, ClearScreen, Browse, Add, Delete, Alter };
//All WrongQuestions Number 
extern unsigned int AllWQNumber;
extern WrongQuestionLL* head;

int main(void)
{
	system("color 70");
	system("title Wrong Question Management System - By Mr.Minghao Chen");
	Greet();
	while (true)
	{
		int arg_num, func_num;
		char dust_ch, full_command[128], command[32], * args[4] = { ROOM };
		Destroy(full_command, command, args);
		const char* br_args[] = { "3","-all","-n" };
		Run(ToNum("browse"), 2, br_args);
	INPUT:
		printf("Manage>>>");
		scanf("%[^\n]", full_command);
		while ((dust_ch = getchar()) != '\n' && dust_ch != EOF);
		if (*full_command == '\0')
		{
			printf("No command.\n");
			goto INPUT;
		}
		arg_num = Explain(full_command, command, args);
#ifdef DEBUG
		printf("Command:%s\n", command);
		printf("Arguments:");
		if (arg_num == 0)
			printf("None");
		else
			for (int i = 1; i <= arg_num; i++)
			{
				printf("%s ", args[i]);
			}
		putchar('\n');
#endif
		if (strcmp(command, "version") == 0)
		{
			printf("Wrong Question Management System\n\
Version 0.0.1 Beta[Release]\n\
-By Mr.Minghao Chen\n\
Aug.8th, 2020\n\
Copyright(c)2020-[inf] Mr.Minghao Chen. All rights reserved.\n");
			goto INPUT;
		}
		else if (strcmp(command, "exit") == 0)
		{
		EXIT:
			printf("Continue to exit?<y/n>");
			char answer = getchar();
			getchar();
			if ((int)answer == (int)'y' || (int)answer == (int)'Y')
				exit(0);
			else if ((int)answer == (int)'n' || (int)answer == (int)'N')
				goto INPUT;//Restart
			else
			{
				printf("Unknown Answer, please check and try again.\n");
				goto EXIT;
			}
		}
		else if ((func_num = ToNum(command)) != -1)
		{
			itoa(func_num, args[0], 10);//func_num->args[0]
			switch (Run(func_num, arg_num, args))
			{
			case ERR_NOFUNC:
				printf("Unknown command, please check and try again.\n");
				break;
			case ERR_TOOFEWARG:
				printf("Too few argument, please check and try again.\n");
				break;
			case ERR_TOOMANYARG:
				printf("Too many arguments, please check and try again.\n");
				break;
			case ERR_NOTHISARG:
				printf("Unknown argument, please check and try again.\n");
				break;
			case ERR_NO:
				break;
			default:
				DoSomething();
			}
		}
		else
			printf("Unknown command, please check and try again.\n");
	}
}