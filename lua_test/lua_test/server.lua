

nGlobal = 10 --一个全局的整形变量 
strGlobal = "hello i am in lua" --一个全局的字符串变量 



t={	name='ettan',	age=23,	desc='正值花季年龄'}



--一个返回值为int类型的函数 
function add(a, b) 
    return a+b 
end


--形参为c++ 自定义类
function strEcho2(a) 
	a:print_string();
	a.m_string = "zhou";
	a:print_string();
    return 'haha i have print your input param' 
end 



--形参为 字符串
function strEcho(a) 
    print(a)
    return 'haha i have print your input param' 
end 

cppapi.testFunc() --调用c++暴露的一个测试函数 

