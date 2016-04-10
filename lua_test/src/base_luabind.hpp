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


//��Ҫ�����Ŀ��ļ�
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
	using namespace luabind;//��������luaState����
	lua_State* L = lua_open();	//Ҳ������luaL_newState()����
	luaL_openlibs(L);	//ע�⽫luaĬ�Ͽ�򿪣�Ҫ�������N�����ģ�����print������û��
	luabind::open(L);

	//��c++ �� ע�ᵽ lua��
	module(L)
		[
		class_<testclass>("testclass")
			.def(constructor<const std::string&>())
			.def("print_string", &testclass::print_string)
			.def_readwrite("m_string", &testclass::m_string)
		];

	//��c++�еĺ����� lua��
	module(L, "cppapi")
		[
			def("testFunc", (void(*)(void))testFunc)
		];

	luaL_dofile(L, "server.lua");

	try
	{
		//����lua�е�����ȫ�ֱ���
		int nLuaGlobal = luabind::object_cast<int>(luabind::globals(L)["nGlobal"]) ;
		//����lua�е��ַ�������
		std::string strLuaGlobal = luabind::object_cast<std::string>(luabind::globals(L)["strGlobal"]);

		//ѭ����ȡȫ�ֱ���
		for (luabind::iterator i(globals(L)["t"]), end; i != end; ++i)//����ĳ������
		{
			auto type_ = luabind::type(*i );//��ȡ��������
			std::string v_str("nll");
			int v_num= 0;
			if(type_ == 3){//int���͵Ķ���
				v_num = luabind::object_cast<int>(*i) ;//��ȡvalue
				auto key_o = i.key();//��ȡkey�Ķ���
				auto key_str = luabind::object_cast<std::string>(key_o) ;//��ȡkey���ַ���
			}
			else if(type_ == 4){//�ַ��� ���͵Ķ���
				v_str = luabind::object_cast<std::string>(*i) ;
			}
		}

		//��ȡtable,����һ��ͨ��luabind::object ���з���
		luabind::object luaTable = luabind::globals(L)["t"] ;
		std::string name=luabind::object_cast<std::string>(luaTable["name"]) ;
		int age = luabind::object_cast<int>(luaTable["age"]) ;


		//��ȡtable����������ͨ��gettable
		std::string desc = luabind::object_cast<std::string>(luabind::gettable(luaTable,"desc"));

		//����lua�к���
		//����: c++ �Զ���  ��
		testclass _testclass("hbb");
		std::string strEchoRes2 = luabind::call_function<std::string>(L, "strEcho2", &_testclass) ;
		_testclass.print_string();//���ʱ�� ���: zhou

		//����lua�к��� 
		int nAddRes = luabind::call_function<int>(L, "add", 3, 4) ;
		std::string strEchoRes = luabind::call_function<std::string>(L, "strEcho", "c++����") ;
	}
	catch(std::exception& e)
	{
		std::cout<<"error:"<<e.what()<<std::endl;
	}

}








#endif
