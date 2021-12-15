#pragma once

#include <assert.h>
#include <iostream>

template <class T>

class TStack
{
private:
	T* Data;
	int Num;
	int TopIndex;
public:
	TStack(size_t num = 10) {
		assert(num > 0);
		Data = new T[num];
		Num = num;
		TopIndex = -1;
	}

	TStack(const TStack& st) {
		Data = new T[st.Num];
		Num = st.Num;
		TopIndex = st.TopIndex;
		for (int i = 0; i <= TopIndex ; i++) {
			Data[i] = st.Data[i];
		}
	}

	~TStack() {
		delete[] Data;
	}

	TStack reverse() {
		TStack<T>* tmp = new TStack<T>(*this);
		for (int i = 0; i <=TopIndex; i++) tmp->Data[i] = this->Data[TopIndex - i];		
		return *tmp;
		
	}

	TStack& operator=(const TStack& st) {
		Data = new T[st.Num];
		Num = st.Num;
		TopIndex = st.TopIndex;
		for (int i = 0; i <TopIndex + 1; i++) {
			Data[i] = st.Data[i];
		}
		return *this;
	}

	bool IsEmpty() { return TopIndex == -1; }

	bool IsFull() { return TopIndex + 1 == Num; }

	void Push(T elem) {
		if (IsFull()) {
			T* tmp = Data;
			Data = new T[Num + 1];
			for (int i = 0; i < Num; i++) {
				Data[i] = tmp[i];
			}
			Num++;
			delete[] tmp;
		}
		
		TopIndex++;
		Data[TopIndex] = elem;
	}

	T Pop() {
		if (!IsEmpty()) {
			T popElem = Data[TopIndex];
			TopIndex--;
			return popElem;
		}
		return 0;
	}

	void print() {
		if (!IsEmpty()) {
			for (int i = 0; i <= TopIndex; i++) {
				std::cout << Data[i] << ' ';
			}
		}
	}

	T Top() {
		assert(!IsEmpty());

		return  Data[TopIndex]  ;
	}

};

