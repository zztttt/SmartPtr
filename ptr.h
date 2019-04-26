#ifndef PTR_H_
#define PTR_H_
template<class T>
class sharedPtr {
private:
	T* ptr;
	int* count;
public:
	sharedPtr();// : ptr(nullptr), count(nullptr) {}
	sharedPtr(T*);
	~sharedPtr();
	sharedPtr(const sharedPtr<T>& t);
	sharedPtr<T>& operator=(const sharedPtr<T>& right);
};
#endif // DEBUG


