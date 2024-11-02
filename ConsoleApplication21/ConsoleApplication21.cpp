#include <iostream>

template<typename T>
class UniquePtr
{
public:
	UniquePtr() {
		this->ptr = nullptr;
	}

	UniquePtr(T* ptr)
	{
		this->ptr = ptr;
		
	};

	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator=(const UniquePtr&) = delete;

	T& operator*()
	{
		return *ptr;
	}

	UniquePtr(UniquePtr&& other) {
		this->ptr = other.ptr;
		other.ptr = nullptr;
	}

	~UniquePtr()
	{
		delete ptr;
	}
	;

private:
	T* ptr;
};

template<typename T>
class SharedPtr
{
public:
	SharedPtr(T* ptr)
	{
		this->ptr = ptr;
		counter = new int(1);
	};

	SharedPtr(const SharedPtr& other) {
		this->ptr = other.ptr;
		this->counter = other.counter
		(*counter)++;
	}

	SharedPtr& operator=(const SharedPtr& other) {
		if (this != &other) {
			memoryChecker();
			ptr = other.ptr;
			counter = other.counter;
			(*counter)++;
		}
		return *this;
	}

	T& operator*()
	{
		return *ptr;
	}

	~SharedPtr() 
	{
		memoryChecker();
	};

private:
	T* ptr;
	int* counter;

	void memoryChecker() {
		if (counter && (*counter)-- == 0)
		{
			delete ptr;
			delete counter;
		}
	}
};



int main()
{
	UniquePtr<int> u_ptr1(new int(5));
	std::cout << *u_ptr1 << "\n";

	SharedPtr<int> s_ptr1(new int(3));
	std::cout << *s_ptr1;

	
}

