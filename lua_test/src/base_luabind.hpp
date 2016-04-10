#pragma once


#define OPEN_LUABIND


#include <array>
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <fstream>


#include <iostream>
#include <list>
#include <map>
#include <memory>

#include <set>
#include <vector>
#include <utility>

#ifdef OPEN_LUABIND


#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <luabind/function.hpp>


//需要包含的库文件
#pragma comment (lib, "vs_lua_bind.lib")
#pragma comment (lib, "lua51.lib")


void testFunc()
{
	std::cout<<"helo there, i am a cpp fun"<<std::endl;
}


class testclass
{
public:
    testclass(const std::string& s): m_string(s) {}
    void print_string() { std::cout << m_string << "\n"; }
    std::string m_string;
};

void luabind_test()
{
	using namespace luabind;//首先声明luaState环境
	lua_State* L = lua_open();	//也可以用luaL_newState()函数
	luaL_openlibs(L);	//注意将lua默认库打开，要不会出现N多错误的，比如print函数都没有
	luabind::open(L);

	//将c++ 类 注册到 lua中
	module(L)
		[
		class_<testclass>("testclass")
			.def(constructor<const std::string&>())
			.def("print_string", &testclass::print_string)
			.def_readwrite("m_string", &testclass::m_string)
		];

	//将c++中的函数到 lua中
	module(L, "cppapi")
		[
			def("testFunc", (void(*)(void))testFunc)
		];

	luaL_dofile(L, "server.lua");

	try
	{
		//调用lua中的整形全局变量
		int nLuaGlobal = luabind::object_cast<int>(luabind::globals(L)["nGlobal"]) ;
		//调用lua中的字符串变量
		std::string strLuaGlobal = luabind::object_cast<std::string>(luabind::globals(L)["strGlobal"]);

		//循环获取全局变量
		for (luabind::iterator i(globals(L)["t"]), end; i != end; ++i)//遍历某个区域
		{
			auto type_ = luabind::type(*i );//获取对象类型
			std::string v_str("nll");
			int v_num= 0;
			if(type_ == 3){//int类型的对象
				v_num = luabind::object_cast<int>(*i) ;//获取value
				auto key_o = i.key();//获取key的对象
				auto key_str = luabind::object_cast<std::string>(key_o) ;//获取key的字符串
			}
			else if(type_ == 4){//字符串 类型的对象
				v_str = luabind::object_cast<std::string>(*i) ;
			}
		}

		//获取table,方法一，通过luabind::object 固有方法
		luabind::object luaTable = luabind::globals(L)["t"] ;
		std::string name=luabind::object_cast<std::string>(luaTable["name"]) ;
		int age = luabind::object_cast<int>(luaTable["age"]) ;


		//获取table，方法二，通过gettable
		std::string desc = luabind::object_cast<std::string>(luabind::gettable(luaTable,"desc"));

		//调用lua中函数
		//参数: c++ 自定义  类
		testclass _testclass("hbb");
		std::string strEchoRes2 = luabind::call_function<std::string>(L, "strEcho2", &_testclass) ;
		_testclass.print_string();//这个时候 输出: zhou

		//调用lua中函数 
		int nAddRes = luabind::call_function<int>(L, "add", 3, 4) ;
		std::string strEchoRes = luabind::call_function<std::string>(L, "strEcho", "c++参数") ;
	}
	catch(std::exception& e)
	{
		std::cout<<"error:"<<e.what()<<std::endl;
	}

}








#endif
