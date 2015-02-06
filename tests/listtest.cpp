#include <iostream>
#include <memory>
#include "DList.hpp"
using namespace std;

bool testCreateIsEmpty();
bool testStore();
bool testStorePtr();
bool testRemove();
bool testNavigate();
bool testRemoveAddInTheMiddle();
int main()
{
	if(!testCreateIsEmpty())
	{
		cerr << "Failed 1" << endl;
		return 1;	
	}
	cout << "1 Ok"<< endl;

	if(!testCreateIsEmpty())
	{
		cerr << "Failed 2" << endl;
		return 2;	
	}
	cout << "2 Ok"<< endl;

	if(!testStore())
	{
		cerr << "Failed 3" << endl;
		return 3;
	}
	cout << "3 Ok"<< endl;
	
	if(!testRemove())
	{
		cerr << "Failed 4" << endl;
		return 4;
	}
	cout << "4 Ok"<< endl;

	if(!testNavigate())
	{
		cerr << "Failed 5" << endl;
		return 5;
	}
	cout << "5 Ok "<< endl;
	if(!testRemoveAddInTheMiddle())
	{
		cerr << "Failed 6" << endl;
		return 6;
	}
	cout << "6 Ok "<< endl;
}

bool testCreateIsEmpty()
{
	DList<int> l = DList<int>();
	if(!l.isEmpty()){return false;}
	return true;
}

bool testStore()
{
	DList<int> l = DList<int>();
	
	int count  = 10;
	for(int i = 0; i<count; i++){
		l.insert(i);
		int nr = *l.inspect().lock();
		if( nr != i) return false;
	}
	
	return true;
}

bool testStorePtr()
{
	DList<int> l = DList<int>();
	
	int count  = 10;
	for(int i = 0; i<count; i++){
		std::shared_ptr<int> iptr = std::shared_ptr<int>(new int);
		*iptr = i;
		l.insert(iptr);
		int nr = *l.inspect().lock();
		if( nr != i) return false;
	}
	
	return true;
}

bool testRemove()
{
	DList<int> l = DList<int>();
	int count  = 10;
	for(int i = 0; i<count; i++){
		l.insert(i);
		int nr = *l.inspect().lock();
		if( nr != i) return false;
	}

	for(int i = 0; i<count; i++){
		int nr = *l.inspect().lock();
		if( nr!=count-1-i) return false;
		l.remove();
	}	

	if(!l.isEmpty()) return false;

	return true;
}

bool testNavigate()
{
	DList<int> l = DList<int>();
	int count  = 10;
	for(int i = 0; i<count; i++){
		l.insert(i);
		int nr = *l.inspect().lock();
		if( nr != i) return false;
		l.next();
	}

	l.first();
	int num = 0;
	while(!l.isEnd())
	{
		int i= *l.inspect().lock();
		if(i!=num) return false;
		l.next();
		num++;
	}

	return true;
}

bool testRemoveAddInTheMiddle()
{
	DList<int> l = DList<int>();
	int count  = 30;  //Must be 3*int
	for(int i = 0; i<count; i++){
		l.insert(i);
		l.next();
	}

	l.first();
	for(int i = 0; i<count/3; i++)
	{
		l.next();	
	} 

	for(int i = 0; i<count/3; i++)
	{
		l.remove();
	}

	for(int i = 10*count+count/3; i<10*count+2*count/3; i++)
	{
		l.insert(i);
		l.next();
	}
	
	l.first();
	int j = count /3;
	int k = 2*j;
	for(int i = 0; i<count; i++){
		int num = *l.inspect().lock();
		
		if( (i>=0 && i<j) || (i>=k && i<count) )
		{
			if(num != i) return false;	
		}

		if(i>=j && i<k)
		{
			if(num != 10*count+i) return false;
		}

		l.next();
	}
	return true;
}

