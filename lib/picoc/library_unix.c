#include "interpreter.h"
#include <stdbool.h>

const int DefaultTimes  = 5;

void UnixSetupFunc(Picoc *pc)
{
	//定义不可更改全局变量，当做常数宏定义使用
	VariableDefinePlatformVar(pc, NULL, "DefaultTimes", &pc->IntType, (union AnyValue *)&DefaultTimes, false);
}

//函数原型
void sayhello_src(int time)
{
	int i=0;
	if(time<0)
	{
		printf("ERROR!\n");
		return;
	}
	for(i=0;i<time;i++)
	{
		printf("Hello! %d\n",i);
	}
}

//函数封装成可解析模式
void Ctest (struct ParseState *Parser, struct Value *ReturnValue,struct Value **Param, int NumArgs)
{
    printf("test(%d)\n", Param[0]->Val->Integer);
    Param[0]->Val->Integer = 1234;
}

void Clineno (struct ParseState *Parser, struct Value *ReturnValue,struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = Parser->Line;
}

void Csayhello (struct ParseState *Parser, struct Value *ReturnValue,struct Value **Param, int NumArgs)
{
	sayhello_src(Param[0]->Val->Integer);
}

/* 函数列表 */
struct LibraryFunction UnixFunctions[] =
{
	{Csayhello,		"void sayhello(int);"},
    {Ctest,			"void test(int);"},
    {Clineno,		"int lineno();"},
    {NULL, NULL}
};

void PlatformLibraryInit(Picoc *pc)
{
	//把函数列表和全局宏定义变量定义到解析器中
    IncludeRegister(pc, "picoc_unix.h", &UnixSetupFunc, &UnixFunctions[0], NULL);
}
