// testSerialization.cpp : Defines the entry point for the console application.
//
 
#include "core/serialization.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include "core/serialization.h"
using namespace std;
static const  char * buffer_txt = "buffer.txt";

struct ss{
	int a;
	int b;
};
ostream& operator<< (ostream& o, ss& s)
{
 o << s.a << " " << s.b << "\n";
return o;
};
 


class Obj :public  serialize::I
{

public:
	vector<int>             ints;
	vector<Obj*>            p_objs;
	map<int, string>		string_map;
	int a;
	Obj(){}
	Obj(int aa) :a(aa)   {
		ints.push_back(1);
		ints.push_back(2);
		ints.push_back(3);
		p_objs.push_back(new Obj());
		p_objs[0]->a = 9999;
        
		string_map[1] = "hello,nesting";
		string_map[2] = "hello,nesting2";
	}
	ostream& write(ostream& s)
	{
		serialize::write(s, string_map);
		serialize::write(s, a);
		serialize::write(s, ints);
		serialize::write(s, p_objs);

		return s;
	}
	istream& read(istream& s)
	{
		serialize::read(s, string_map);
		serialize::read(s, a);
		serialize::read(s, ints);
		serialize::read(s, p_objs);

		return s;
	}
    
    //not complete ==,just for a demo :)
    bool operator==(const  Obj& s)
    {

        for (int i =0;i <ints.size();++i)if (ints[i]!=ints[i])return false;
        for (auto a: s.string_map) if(a.second!=string_map[a.first])return  false;
        for (int i =0;i <p_objs.size();++i)
        {
            if (p_objs[i] && p_objs[i]!=p_objs[i])
                return false;
   
        }
        return  true;
        
    }
	friend ostream& operator<< (ostream& o, Obj& s)
	{

		o << s.a;
		return o;
	};

};






template<typename T>
void testVectorPrimtives(vector<T> v)
{
 	  
	ofstream file(buffer_txt, std::ios::out | std::ios::binary | std::ios::trunc);
	serialize::write(file, v);
	file.flush();
	file.close();

	vector<T>  a2;
	ifstream  file2(buffer_txt, std::ios::in | std::ios::binary);
	serialize::read(file2, a2);
	 for (int i=0;i <a2.size(); ++i)
	 {
         assert(v[i]==a2[i]);
	 }
    cout<<"vector<"<<typeid(T).name()<<">  passed\n";

}
template<typename T>
void testVectorObjectsPointer(vector<T> v)
{
    
    ofstream file(buffer_txt, std::ios::out | std::ios::binary | std::ios::trunc);
    serialize::write(file, v);
    file.flush();
    file.close();
    
    vector<T>  a2;
    ifstream  file2(buffer_txt, std::ios::in | std::ios::binary);
    serialize::read(file2, a2);
    for (int i=0;i <a2.size(); ++i)
    {
        
    }
   
}


 
void testString(string s)
{


	ofstream file(buffer_txt, std::ios::out | std::ios::binary | std::ios::trunc);
	serialize::write(file, s);
	file.flush();
	file.close();

	string  s2;
	ifstream  file2(buffer_txt, std::ios::in | std::ios::binary);
	serialize::read(file2, s2);
	 
    assert(s2==s);
cout<<"string"<<"  passed\n";
}

bool testMapObjectsPointer(map<int, Obj*> v)
{
 
	ofstream file(buffer_txt, std::ios::out | std::ios::binary | std::ios::trunc);
	serialize::write(file, v);
	file.flush();
	file.close();

	map<int, Obj*>   a2;
	ifstream  file2(buffer_txt, std::ios::in | std::ios::binary);
	serialize::read(file2, a2);
	   for (auto& a: a2) {
           if(a.second)
           assert(*v[a.first]==*a.second);
           else
           assert(NULL==v[a.first] && NULL==a.second);
       }

    printf("map<%s, %s*> passed\n",typeid(int).name(),typeid(Obj).name());
    return true;
}

template<typename K, typename  V>
void testMapPrimtives(map<K, V> v)
{
 
	ofstream file(buffer_txt, std::ios::out | std::ios::binary | std::ios::trunc);
	serialize::write(file, v);
	file.flush();
	file.close();

	map<K, V>   a2;
	ifstream  file2(buffer_txt, std::ios::in | std::ios::binary);
	serialize::read(file2, a2);
    for (auto& a: a2) {
        assert(v[a.first]==a.second);
    }
   printf("map<%s, %s> passed\n",typeid(K).name(),typeid(V).name());
    
}

template<typename K>
void testSetPrimtives(set<K> v)
{
 

	ofstream file(buffer_txt, std::ios::out | std::ios::binary | std::ios::trunc);
	serialize::write(file, v);
	file.flush();
	file.close();

	set<K>  a2;
	ifstream  file2(buffer_txt, std::ios::in | std::ios::binary);
	serialize::read(file2, a2);
    assert(v==a2);
    printf("set<%s> passed\n",typeid(K).name());
}


void testVectorPointPrimtives(vector<Obj*> v)
{
  
	ofstream file(buffer_txt, std::ios::out | std::ios::binary | std::ios::trunc);
	serialize::write(file, v);
	file.flush();
	file.close();

	vector<Obj*>  a2;
	ifstream  file2(buffer_txt, std::ios::in | std::ios::binary);
	serialize::read(file2, a2);
	 for (int i = 0; i < a2.size(); ++i)
	{
        if(a2[i])
            assert(*a2[i]==*v[i]);
        else
            assert(NULL==v[i] && NULL==a2[i]);
	}
     printf("vector<%s*> passed\n",typeid(Obj).name());
}


template<typename T>
void testListPrimtives(list<T> v)
{
 
	ofstream file(buffer_txt, std::ios::out | std::ios::binary | std::ios::trunc);
	serialize::write(file, v);
	file.flush();
	file.close();

	list<T>  a2;
	ifstream  file2(buffer_txt, std::ios::in | std::ios::binary);
	serialize::read(file2, a2);
    assert(v==a2);
     printf("list<%s> passed\n",typeid(T).name());
}

template<typename T>
void testPointerListObjects(list<T*> v)
{
 	 
	ofstream file(buffer_txt, std::ios::out | std::ios::binary | std::ios::trunc);
	serialize::write(file, v);
	file.flush();
	file.close();

	list<T*>  a2;
	ifstream  file2(buffer_txt, std::ios::in | std::ios::binary);
	serialize::read(file2, a2);

    printf("vector<%s*> passed\n",typeid(Obj).name());
    
}




int main( )
{
	 
 	testVectorPrimtives<bool>({ false, true,false });
	testVectorPrimtives<int>({ 1,2, 3, 4 });
	testVectorPrimtives<double>({ 1.3, 2.3, 3.3, 4.3 });
	testVectorPrimtives<float>({ 1.3f, 2.3f, 3.3f, 4.3f });
	testVectorPrimtives<char>({  'b', 'd' });
	testVectorPrimtives<long long >({1111111111,222222222});
	testVectorPrimtives<long>({ 1111111111, 222222222 });


	testString("hello,world");
	testString("你好，世界");
	 
	{
		vector<Obj*>   ints;
		ints.push_back(new Obj(4));
		ints.push_back(new Obj(5));
		ints.push_back(NULL);
		ints.push_back(new Obj(7));
		testVectorPointPrimtives(ints);
	}
	map<int, Obj*> ms;
	ms[2] = new Obj(22);
	ms[4] = NULL;
	ms[3] = new Obj(33);
	ms[5] = NULL;
	ms[6] = new Obj(66);
	testMapObjectsPointer(ms);

	{
		map<int, string>  m2 = { { 1, "hello" }, { 2, "world" } };
		testMapPrimtives(m2);
	}
	{
		map<string, string>  m2 = { { "ho", "hello" }, {"wd", "world" } };
		testMapPrimtives(m2);
	}
	{
		map<int, int>  m2 = { { 1, 1 }, { 2, 2 } };
		testMapPrimtives(m2);
	}

	{
		map<int, double>  m2 = { { 1, 1111.11 }, { 2, 1111.11 } };
		testMapPrimtives(m2);
	}

	{
		map<int, float>  m2 = { { 1, 1111.11f }, { 2, 1111.11f } };
		testMapPrimtives(m2);
	}


	{
		set<int> sets = { 1, 2, 3, 4   };
		testSetPrimtives(sets);
	}
	{
		set<double> sets = { 1.111, 2, 3,   };
		testSetPrimtives(sets);
	}
	{
		set<string> sets = { "hello","world"};
		testSetPrimtives(sets);
	}

	{
		list <int>  lists = { 1, 2, 31, 1, 1, 0, 0, 0, 0, 1 };
		testListPrimtives(lists);
	}
	{
		list <double>  lists = { 1, 2, 31, 1, 1, 0, 0.12321, 0, 0, 1 };
		testListPrimtives(lists);
	}
	{
		list <string>  lists = {"hello","list" };
		testListPrimtives(lists);
	}
	list <Obj*>  ints;
	ints.push_back(new Obj(11));
	ints.push_back(NULL);
	ints.push_back(new Obj(22));
	ints.push_back(NULL);
	testPointerListObjects(ints);



	{
	vector<map<int, Obj*> >  intss = { { { 1, new Obj(3) }, { 4, new Obj(4) } }, { { 2, new Obj(3) }, { 4, new Obj(6) } } };
	testVectorObjectsPointer(intss);

	}

    {
        vector<Obj>  as;
        
        as.resize(3);
        as[0].string_map[1]="world";
        ofstream file(buffer_txt, std::ios::out | std::ios::binary | std::ios::trunc);
        serialize::write(file, as);
        file.flush();
        file.close();
        
        vector<Obj>  a2;
        ifstream  file2(buffer_txt, std::ios::in | std::ios::binary);
        serialize::read(file2, a2);
        assert(as[0]==a2[0]);
        cout<<"vector<Obj>: pass\n";
        
    }
    {
        
    struct AAA
    {
    public:
        void hello(){
            printf("s");
        }
        
        int a,b,c;
    };
     
        AAA a={1,2,3};
        ofstream file(buffer_txt, std::ios::out | std::ios::binary | std::ios::trunc);
        serialize::write(file, a);
        file.flush();
        file.close();
        
        AAA  a2;
        ifstream  file2(buffer_txt, std::ios::in | std::ios::binary);
        serialize::read(file2, a2);
        //be careful when you do this! because the memory layout is just right only if you don`t use polymorphism! So , the best practice would be: Implement serialize::I :)
        getchar();
    }
    
    
    
       
	 
	return 0;
}

