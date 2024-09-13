// String Class.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstring>
using namespace std;
class String
{
public:
	String() :string(nullptr), len(0) {}//default
	String(const char * str) {// parameterised cotr
		len = strlen(str);
		string = new char[len + 1];
		strcpy_s(string,len+1,str);
	}
	String(const String& str) {
		len = str.len;
		string = new char[len + 1];
		strcpy_s(string,len+1, str.string);
	}
	String(String&& str) {
		len = str.len;
		string = str.string;
		str.string = nullptr;
		str.len = 0;
	}
	String& operator=( String&& str) {
		if (this != &str) {
			delete[] string;
			len = str.len;
			string = str.string;
			str.string = nullptr;
			str.len = 0;
		}
		return *this;
	}
	String& operator=(const String& str) {
		if (this != &str) {
			delete[] string;
			len = str.len;
			string = new(char[len + 1]);
			strcpy_s(string,len+1, str.string);
		}
		return *this;
	}
	int length() {
		return len;
	}

	~String() {
		delete[] string;
	}
	friend ostream& operator<<(ostream& str1, String& str2);
	friend istream& operator>>(istream& str1, String& str2);
private:
	char* string;
	int len;
};
// we are writing here outside the class because we don't want to implement inside the cout class 
// so function structure will be like <<(cout,str2)
ostream& operator<<(ostream& out, String& str2) {
	out << str2.string;
	return out;
}
istream& operator>>(istream& in, String& str2) {
	char temp[1000];  // Assuming maximum input size of 1000 characters for simplicity
	in >> temp;
	delete[] str2.string;  // Free existing memory
	str2.len = strlen(temp);
	str2.string = new char[str2.len + 1];
	strcpy_s(str2.string,str2.len+1, temp);
	return in;
}

int main()
{
	String str1;//default cotr
	String str2 = "hello";//parameterised cotr
	String str3 = str2;//copy cotr
	String str4;
	str4 = str2;//copy assignment oper because its already  str4 is calling = function where str2 is parameter
	int len = str4.length();
	cout << str2;//cout is calling ,str2 is going as parameter to function <<; if we are calling inside the class
	cin >> str1;
	String str6 = std::move(str3);//move copy cotr
	str6 = std::move(str2);//move copy assignment cotr

}

