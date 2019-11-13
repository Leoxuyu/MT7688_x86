#include "interpreter.h"
#include <stdio.h>

struct complex {int i; int j;};  /* make this C declaration match the picoc one */

void Crandom(struct ParseState *Parser,
			 struct Value *ReturnValue,
			 struct Value **Param,
			 int NumArgs)
{
    ReturnValue->Val->Integer = random() % Param[0]->Val->Integer;
}

struct LibraryFunction PlatformLibrary[] =
{
    {Crandom, "int random(int)"},
    {NULL, NULL}
};
