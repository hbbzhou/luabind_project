// lua_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../src/base_luabind.hpp"

int _tmain(int argc, _TCHAR* argv[])
{
	luabind_test();//它 介绍了, 如何 在 lua 函数里, 处理 c++ 自定义的 类
	return 0;
}

