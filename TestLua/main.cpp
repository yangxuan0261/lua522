#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

//读取lua脚本文件的函数（此处作为一个配置文件）  
void LoadLua(lua_State* L, const char* filename, int * arg1, int * arg2)
{
	if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
		printf("loadfile failed! %s\n", lua_tostring(L, -1));//如果失败，栈顶为错误信息  
	//获得全局变量，压入栈中  
	lua_getglobal(L, "arg1");
	lua_getglobal(L, "arg2");
	//判断一下素不素想要的类型  
	if (!lua_isnumber(L, -2))
		printf("arg1 is not number\n");
	if (!lua_isnumber(L, -1))
		printf("arg2 is not number\n");
	//提取栈中的参数值  
	*arg1 = lua_tointeger(L, -2);
	*arg2 = lua_tointeger(L, -1);
}

void openLuaFile()
{
	//打开lua  
	lua_State* L = luaL_newstate();
	//加载lib文件  
	luaL_openlibs(L);

	int i, j = 0;
	LoadLua(L, "test.lua", &i, &j);
	printf("i = %d, j = %d\n", i, j);

	//结束  
	lua_close(L);
}

int main()
{
	openLuaFile();
	system("pause");
	return 0;
}