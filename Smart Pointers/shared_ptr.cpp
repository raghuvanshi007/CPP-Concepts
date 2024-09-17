// shared_ptr.cpp : Defines the entry point for the application.
//

#include <iostream>
#include<stdio.h>
using namespace std;
template<typename T>
class sharedptr {
private:
	T* res;
	int* counter;//we cant take simple count then per object value will be 1
	//we can't take static because then whole class value be incresed but that should be per resource means particualr resource how many
	// pointers pointing so we are taking int * 
	void increament() {
		if(counter)
		*(counter)++;
	}
	void decrement() {
		if (counter) {
			*(counter)--;
			if ((*counter) == 0) {
				if (res) {
					delete res;
					delete counter; 
					res = nullptr;
					counter = nullptr;
				}
			}
		}
	}
public:
	sharedptr(T* a = nullptr)  {
		res = a;
		counter=new int(1); 
		cout << "cotr" << endl;
	}
	sharedptr(const sharedptr& ptr) {
		res = ptr.res;
		counter = ptr.counter;
		increament();
	}
	sharedptr& operator=(const sharedptr& ptr) {
		if (this != &ptr) { 
			decrement();
			res = ptr.res;
			counter = ptr.counter;
			increament();
		}
		return *this;
	}
	sharedptr(sharedptr&& ptr) {
		res = ptr.res;
		counter = ptr.counter;
			ptr.res = nullptr;
		ptr.counter=nullptr;
	}
	sharedptr& operator=(sharedptr&& ptr) {
		if (this != &ptr){
			decrement();
		res = ptr.res;
		counter = ptr.counter;
		ptr.res = nullptr;
		ptr.counter = nullptr;
	}
	return *this;

	}
	void reset(T *a=nullptr) {
		decrement();
		res = a;
		counter = new int(1);
	}
	int get_count() {
		if (counter) {
			return *counter;
		}
		return -1;
	}
	T& operator*() {
		return *res;
	}
	~sharedptr() {
		if (counter) {
			decrement();
			cout << "dtor" << endl;
		}
	}
};

int main()
{
	sharedptr<int> ptr1;//default cotr
	sharedptr<int> ptr2(new int(20));//parameterised
	sharedptr<int> ptr3(ptr2);
	ptr3 = ptr2;//copy assignment operator
	//ptr3 releasing the own resource means counter decreses
	//ptr3 getting resource of ptr2 so increase ptr2 counter;
	sharedptr<int> ptr4(move(ptr3));// move constructor
	// which means we don't need to increament cause pt4 pointing from one to other 
	ptr4 = move(ptr3);//move assignment
	
	ptr1.reset();
	ptr1.reset(new int (10));
	cout << *ptr2;
	ptr1.get_count();//total no. of object pointing to same resource
}
