

nGlobal = 10 --һ��ȫ�ֵ����α��� 
strGlobal = "hello i am in lua" --һ��ȫ�ֵ��ַ������� 



t={	name='ettan',	age=23,	desc='��ֵ��������'}



--һ������ֵΪint���͵ĺ��� 
function add(a, b) 
    return a+b 
end


--�β�Ϊc++ �Զ�����
function strEcho2(a) 
	a:print_string();
	a.m_string = "zhou";
	a:print_string();
    return 'haha i have print your input param' 
end 



--�β�Ϊ �ַ���
function strEcho(a) 
    print(a)
    return 'haha i have print your input param' 
end 

cppapi.testFunc() --����c++��¶��һ�����Ժ��� 

