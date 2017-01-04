#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

//��ȡlua�ű��ļ��ĺ������˴���Ϊһ�������ļ���  
void LoadLua(lua_State* L, const char* filename, int * arg1, int * arg2)
{
	if (luaL_loadfile(L, filename) || lua_pcall(L, 0, 0, 0))
		printf("loadfile failed! %s\n", lua_tostring(L, -1));//���ʧ�ܣ�ջ��Ϊ������Ϣ  
	//���ȫ�ֱ�����ѹ��ջ��  
	lua_getglobal(L, "arg1");
	lua_getglobal(L, "arg2");
	//�ж�һ���ز�����Ҫ������  
	if (!lua_isnumber(L, -2))
		printf("arg1 is not number\n");
	if (!lua_isnumber(L, -1))
		printf("arg2 is not number\n");
	//��ȡջ�еĲ���ֵ  
	*arg1 = lua_tointeger(L, -2);
	*arg2 = lua_tointeger(L, -1);
}

void openLuaFile()
{
	//��lua  
	lua_State* L = luaL_newstate();
	//����lib�ļ�  
	luaL_openlibs(L);

	int i, j = 0;
	LoadLua(L, "test.lua", &i, &j);
	printf("i = %d, j = %d\n", i, j);

	//����  
	lua_close(L);
}

int main()
{
	openLuaFile();
	system("pause");
	return 0;
}