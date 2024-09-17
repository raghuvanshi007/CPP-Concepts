
#include <iostream>
using namespace std;
template<typename T>
class uniqueptr {
private:
	T* mem;

public:
	uniqueptr(T* a = nullptr) :mem(a) {//default contructor
		cout << "cotr" << endl;
	}
	uniqueptr(const uniqueptr<T>& temp) = delete;//copy constr will not be used we dont want to copy
	uniqueptr& operator=(const uniqueptr<T>& temp) = delete;//copy assignment will not be used we dont want to assign any object to other
	uniqueptr( uniqueptr<T>&& temp) {//move constructor it will R value as ptr1 obj and transfer owner ship to ptr3
		mem = temp.mem;
		temp.mem = nullptr;
	}
	uniqueptr& operator=(uniqueptr<T>&& temp) {
		if (this != &temp) {//this check for they are not same pt4=ptr4
			if (mem) {//this check if suppose already created pt4 mem so delete first then allocate
				delete mem;
			}
			mem = temp.mem;
			temp.mem = nullptr;
		}
		return *this;
	}
	T* operator->() {
		return mem;
	}
	T& operator*() {
		return *mem;
	}
	void reset(T* a=nullptr)//if I am not paasing anything 
	{
		if (mem) delete mem;
		mem = a;
	}
	~uniqueptr() {
		if (mem) { delete mem; mem = nullptr; };
		cout << "dctor" << endl;
	}

};

int main()
{
	uniqueptr<int> ptr1(new int(10));
	//uniqueptr<int>ptr2(ptr1);//compilation error copy constructor
	//uniqueptr<int>ptr3 = ptr2;//compilation error
	uniqueptr<int>ptr4(new int(2));
	//ptr4 = ptr3;//compilation error copy assignment operator
	uniqueptr<int>ptr3 = std::move(ptr1);//move constructor
	ptr4 = move(ptr3);
	cout << *ptr4;//* operator overloading will return value of that pointer 
	//ptr1->func();//means it will return pointer
	ptr1.reset(new int(20));//no return type and it will delete previous one as ptr1 and then allocate to new


}
