#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

int main()
{
	printf("hello world\n");
	system("pause");
	return 0;
}