#include<iostream>
#include "ptr.h"
using namespace std;

template<class T>
sharedPtr<T>::sharedPtr(T* _t){
	ptr = _t;
	count = new int(1);
	cout << "constructor ponter:" << this << endl;
}
template<class T>
sharedPtr<T>::~sharedPtr()
{	//release when count == 1
	cout << "willing to release:" << this << endl;
	if (--(*count) == 0) {
		delete ptr;
		delete count;
		ptr = nullptr;
		count = nullptr;
		cout << "destructor pointer:" << this << endl;
	}
	else
		cout << this << " still has more than 1 reference" << endl;
}
/*
* eg. p(t)
*/
template<class T>
sharedPtr<T>::sharedPtr(const sharedPtr<T>& t)
{
	ptr = t.ptr;
	count = t.count;
	(*count)++;
	cout << "copy from " << &t << "to" << this << endl;
}
/*
* decrease the left's count, then increase the right's count
* avoid to desctruct when a = a; 
*/
template<class T>
sharedPtr<T>& sharedPtr<T>::operator=(const sharedPtr<T>& right)
{
	(*right.count)++;
	(*count)--;
	if (*count == 0) {
		delete ptr;
		delete count;
		ptr = nullptr;
		count = nullptr;
		cout << "delete left element:" << this << endl;
	}
	ptr = right.ptr;
	count = right.count;
	cout << "copy right to left" << endl;
	return *this;
}
//static sharedPtr<double> p1 = NULL;
//static sharedPtr<double> p2 = NULL;
//static sharedPtr<double> p3 = NULL;
void test() {
	sharedPtr<double> p1 = sharedPtr<double>(new double(1.1));
	sharedPtr<double> p2 = sharedPtr<double>(new double(2.2));
	sharedPtr<double> p3 = sharedPtr<double>(p2);
	cout << "test p1 = p1" << endl;// test whether destructor itself
	/*
	* before: p1: ptr p1, count 1
	* after:  p1: ptr p1, count 1
	*/
	p1 = p1;
	cout << "test p3 = p1" << endl;
	/*
	* before:
	*		p1: ptr addr1, count 1
	*		p2: ptr addr2, count 2
	*		p3: ptr addr2, count 2
	* after:
	*		p1: ptr addr1, count 2
	*		p2: ptr addr2, count 1
	*		p3: ptr addr1, count 2
	*/
	p3 = p1;
	cout << "test p3 = p2" << endl;
	/*
	* before:
	*		p1: ptr addr1, count 2
	*		p2: ptr addr2, count 1
	*		p3: ptr addr1, count 2
	* after:
	*		p1: ptr addr1, count 1
	*		p2: ptr addr2, count 2
	*		p3: ptr addr2, count 2
	*/
	p3 = p2;
}
int main() {
	test();
	system("pause");
	return 0;
}