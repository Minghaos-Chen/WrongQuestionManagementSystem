//Header:Includes For WrongQuestionManagementSystem
//Windows
//#include <windows.h>
//Standad
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <direct.h>
//Custom
#include "ErrorsDef.h"
//Disable
#pragma warning(disable:4996)
#pragma warning(disable:6031)
//Flag
#pragma once
//#define DEBUG
//Defines
#define MAX_ARG 3
#define LEN sizeof(char[16])
#define RAM_ROOM (char*)malloc(LEN)
#define ROOM RAM_ROOM##,##RAM_ROOM##,##RAM_ROOM##,##RAM_ROOM
//Structures
typedef enum {
	chinese = 1, math, english, politics, history, geography, biology, physics, chemistry
}Subject;
typedef struct {
	unsigned int number;
	Subject subject;
	char title[256];
}BasedInfo;
typedef enum {
	text_only = 1, pict_only, text_with_pict
}Type;
typedef struct {
	bool is_blank_area;
}PrintInfo;
typedef struct {
	BasedInfo BasedInfo;
	Type Question;
	Type Answer;
	Type Explain;
	PrintInfo PrintInfo;
}WrongQuestion;
typedef struct LinkedList{
	WrongQuestion WrongQuestion;
	struct LinkedList* next;
	//Notice:CANNOT use "WrongQuestionLL* next;"
	//Unknown Reason
}WrongQuestionLL;

typedef struct {
	unsigned int Number;
	WrongQuestionLL* head;
}Infomation;

//Comments

//Argument
/*
   0----------->1---------->2
args[0]		 args[1]		args[2]
   |            |           |
argv[0](str) argv[1]     argv[2]
   |            |           |
func_num    argument[1] argument[2]
*/
//Function-Number Relationship
/*
command-number  0           1        2       3       4       5
                |           |        |       |       |       |
command-name   help        cls     browse   add    delete  alter
(Command)   	|           |        |       |       |       |
func-name  DisplayHelp ClearScreen Browse   Add    Delete  Alter
                |           |        |       |       |       |
func_p        func[0]     func[1]  func[2] func[3] func[4] func[5]
*/