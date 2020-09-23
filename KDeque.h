#pragma once
#include <iostream>
#include <string>
#include "KDIter.h"
using namespace std;

template <typename T> class KDeque;
template <typename T> ostream& operator << (ostream& out_deque, KDeque<T> const& deque);
template <typename T> istream& operator >> (istream& input_deque, KDeque<T>& deque);

//-------------------------------------------------------------

template <typename T>

class KDIter;


template <typename T>

class KDeque {

public:

	friend KDIter<T>;
	typedef KDIter<T> iter;

	typedef const KDIter <T> const_iter;

	iter begin() { return iter(this, ibegin); }
	iter   end() { return iter(this, iend); }

	const_iter begin() const { return const_iter(this, ibegin); }
	const_iter   end() const { return const_iter(this, iend); }

	const_iter c_begin() { return const_iter(this, ibegin); }
	const_iter с_begin() const { return const_iter(this, ibegin); }

	const_iter   с_end() { return const_iter(this, iend); }
	const_iter   с_end() const { return const_iter(this, iend); }



private:

	T* Memory_for_Deque;

	int ibegin;
	int iend;
	int Cells_Amount;
	int fpSize;

	//================================================

	//void Expand() {
	//	int* p = new T[2 * Cells_Amount - 1];
	//	int b1 = 0, e1 = 0;
	//	for (int i = ibegin; i != iend; i = (i + 1) % Cells_Amount)
	//	{
	//		p[e1++] = Memory_for_Deque[i];
	//	}
	//	delete[]Memory_for_Deque;
	//	Memory_for_Deque = p;
	//	Cells_Amount = 2 * Cells_Amount - 1;
	//	ibegin = b1; iend = e1;
	//}

public:


	KDeque(int Input_Size = 10);
	KDeque(KDeque const& deque); // Copy Constructor
	inline KDeque(KDeque&& deque);  // Перемещающий конструктор  

	KDeque(initializer_list<T> iList);


	~KDeque();

	// FUNC'S -------------------------------------------



	template <typename ... Args>
	void emplace_front(Args&&... val) {

		if (!IsFull()) {
			ibegin = (ibegin - 1 + Cells_Amount) % Cells_Amount;
			fpSize++;
			new (Memory_for_Deque + ibegin) T(forward<Args>(val)...);
		}

		else return;
	}

	template <typename ... Args>
	void emplace_back(Args&&... val) {

		if (!IsFull()) {
			new (Memory_for_Deque + iend) T(forward<Args>(val)...);
			iend = (iend + 1) % Cells_Amount;
			fpSize++;
		}

		else return;
	}


	bool PushFront(T data); // Add new element to the front
	bool PopFront(); // delete element from the front;
	T& Front(); // get front element value
	const T& Front() const; // get front element value CONST

	bool PushBack(T data); // Add new element to the end
	bool PopBack(); //delete element from the end;

	T& Back(); //get element's value from the back
	const T& Back() const; //get element's value from back if deque is CONST

	void ShowDeque(); //Show deque

	//bool IsEmpty();
	bool IsEmpty() const;

	//bool IsFull();
	bool IsFull() const;


	int Size(); //Size of Deque


	bool Clear(); //удалить все элементы дека,

	friend ostream& operator << <T> (ostream& out_deque, KDeque const& deque);

	friend istream& operator >> <T> (istream& input_deque, KDeque& deque);

	KDeque operator + (KDeque const& deque);
	KDeque operator += (KDeque const& deque);

	KDeque& operator = (KDeque const& deque);
	KDeque& operator = (KDeque&& deque);

	bool operator == (KDeque const& deque);
	bool operator != (KDeque const& deque);

	void Swap(KDeque& deque) {

		swap(Memory_for_Deque, deque.Memory_for_Deque);
		swap(ibegin, deque.ibegin);
		swap(iend, deque.iend);
		swap(fpSize, deque.fpSize);
		swap(Cells_Amount, deque.Cells_Amount);
	}

};

//-------------------------------------------------------------

template <typename T>
KDeque<T>::KDeque(int Input_Size) {

	Memory_for_Deque = new T[Input_Size + 1];
	Cells_Amount = Input_Size + 1;
	fpSize = 0;

	ibegin = Cells_Amount / 2 - 1;

	iend = ibegin;

}

//-------------------------------------------------------------

template <typename T>
KDeque<T>::KDeque(KDeque<T> const& deque) {

	Memory_for_Deque = new T[deque.Cells_Amount];

	for (int i = 0; i < deque.Cells_Amount; i++) {
		*(Memory_for_Deque + i) = *(deque.Memory_for_Deque + i);
	}

	ibegin = deque.ibegin;
	//	begin = Memory_for_Deque + ibegin;

	iend = deque.iend;

	fpSize = deque.fpSize;
	Cells_Amount = deque.Cells_Amount;

}

template <typename T>
inline KDeque<T>::KDeque(KDeque<T>&& deque) :Memory_for_Deque(deque.Memory_for_Deque), Cells_Amount(deque.Cells_Amount), ibegin(deque.ibegin), iend(deque.iend), fpSize(deque.fpSize) {
	deque.Memory_for_Deque = nullptr;
	deque.Cells_Amount = deque.fpSize = deque.ibegin = deque.iend = 0;
}

//-------------------------------------------------------------

template <typename T>
//template <typename U>
KDeque<T>::KDeque(initializer_list<T> iList) : fpSize(0), ibegin(0), iend(0) {
	Cells_Amount = 2 * iList.size() - 1;
	Memory_for_Deque = new T[Cells_Amount];
	for (auto& x : iList)
		PushBack(x);
}

template <typename T>
KDeque<T>::~KDeque() { Clear(); }

//-------------------------------------------------------------

template <typename T>
bool KDeque<T>::PushFront(T data) {

	if (IsFull())
		return false;

	else {
		ibegin = (ibegin - 1 + Cells_Amount) % Cells_Amount;
		//begin = Memory_for_Deque + ibegin;
		*(Memory_for_Deque + ibegin) = data;
		fpSize++;
		return true;
	}

}

//-------------------------------------------------------------

template <typename T>
bool KDeque<T>::PopFront() {
	if (IsEmpty())
		return false;

	else {
		ibegin = (ibegin + 1) % Cells_Amount;
		fpSize--;
		return true;
	}
}

//-------------------------------------------------------------

template <typename T>
T& KDeque<T>::Front() {

	if (IsEmpty()) throw -1;
	
	else 
		return *(Memory_for_Deque + ibegin);
}

template <typename T>
const T& KDeque<T>::Front() const {

	if (IsEmpty()) throw -1;
	
	else return *(Memory_for_Deque + ibegin);
}

//-------------------------------------------------------------

template <typename T>
bool KDeque<T>::PushBack(T data) {
	if (IsFull())
		return false;

	else {
		*(Memory_for_Deque + iend) = data;
		iend = (iend + 1) % Cells_Amount;
		fpSize++;
		return true;
	}
}

//-------------------------------------------------------------

template <typename T>
bool KDeque<T>::PopBack() {
	if (IsEmpty())
		return false;

	else {
		iend = (iend - 1 + Cells_Amount) % Cells_Amount;
		fpSize--;
		return true;
	}
}

//-------------------------------------------------------------

template <typename T>
T& KDeque<T>::Back() {

	if (IsEmpty()) throw - 1;

	return *(Memory_for_Deque + (iend - 1 + Cells_Amount) % Cells_Amount);
}

template <typename T>
const T& KDeque<T>::Back() const {

	if (IsEmpty()) throw - 1;

	return *(Memory_for_Deque + (iend - 1 + Cells_Amount) % Cells_Amount);
}

//-------------------------------------------------------------

template <typename T>
void KDeque<T>::ShowDeque() {

	for (int i = 0; i < Cells_Amount; i++) {
		printf("%d ", *(Memory_for_Deque + i));
	}
	printf("\n");
}

//-------------------------------------------------------------

template <typename T>
int KDeque<T>::Size() {
	return fpSize;
}

//-------------------------------------------------------------

template <typename T>
bool KDeque<T>::IsFull() const {
	if ((iend + 1) % Cells_Amount == ibegin) return true;
	else return false;
}

//-------------------------------------------------------------

template <typename T>
bool KDeque<T>::IsEmpty() const {
	if (ibegin == iend) return true;
	else return false;
}


//-------------------------------------------------------------

template <typename T>
bool KDeque<T>::Clear() {
	if (!IsEmpty()) {
		while (fpSize) PopFront();
		return true;
	}

	else return false;
}

//-------------------------------------------------------------

template <typename T>
ostream& operator << (ostream& out_deque, KDeque<T> const& deque) {

	for (int i = deque.ibegin; i != deque.iend; i = (i + 1) % deque.Cells_Amount) {
		out_deque << *(deque.Memory_for_Deque + i) << " ";
	}

	return out_deque;
}

//-------------------------------------------------------------

template <typename T>
istream& operator >> (istream& input_deque, KDeque<T>& deque) {

	deque.ibegin = 0;

	deque.iend = deque.Cells_Amount - 1;

	deque.fpSize = deque.Cells_Amount - 1;


	while (deque.Memory_for_Deque + deque.iend != deque.Memory_for_Deque + deque.Cells_Amount - 1) {
		input_deque >> *(deque.Memory_for_Deque + deque.iend);
		deque.iend++;
	}
	return input_deque;
}

//-------------------------------------------------------------

template <typename T>
KDeque<T> KDeque<T> :: operator + (KDeque<T> const& deque) {

	KDeque<T> L_deque(*this);

	return L_deque += deque;

}

//-------------------------------------------------------------

template <typename T>
KDeque<T> KDeque<T>::operator += (KDeque<T> const& deque) {


	int SizeCheck;
	if (fpSize + deque.fpSize >= Cells_Amount)
		SizeCheck = Cells_Amount + deque.Cells_Amount - 2;

	else SizeCheck = Cells_Amount - 1;

	KDeque <T> deque_sum(SizeCheck);

	int index;

	if (ibegin <= iend) { deque_sum.ibegin = ibegin; }
	else deque_sum.ibegin = deque_sum.Cells_Amount - (Cells_Amount - ibegin);

	deque_sum.iend = ibegin;

	for (int i = 0; i < fpSize; i++) {
		index = (ibegin + i) % Cells_Amount;
		deque_sum.PushBack(*(Memory_for_Deque + index));
	}

	for (int i = 0; i < deque.fpSize; i++) {
		index = (deque.ibegin + i) % deque.Cells_Amount;
		deque_sum.PushBack(*(deque.Memory_for_Deque + index));
	}


	Swap(deque_sum);

	return *this;
}

//-------------------------------------------------------------

template <typename T>
bool KDeque<T>::operator == (KDeque const& deque) {

	if (fpSize == deque.fpSize) {

		int dplace, tdplace;

		for (int i = 0; i < fpSize; i++) {

			dplace = (ibegin + i) % Cells_Amount;
			tdplace = (deque.ibegin + i) % deque.Cells_Amount;

			if (*(Memory_for_Deque + dplace) != *(deque.Memory_for_Deque + tdplace)) return false;
		}
	}

	else return false;

	return true;
}

//-------------------------------------------------------------

template <typename T>
bool KDeque<T>::operator != (KDeque const& deque) {

	return !(*this == deque);
}

//-------------------------------------------------------------

template <typename T>
KDeque<T>& KDeque<T>::operator = (KDeque const& deque) {

	if (this != &deque) {
		KDeque t(deque);
		Swap(t);
	}
	return *this;
}

//-------------------------------------------------------------

template <typename T>
inline KDeque<T>& KDeque<T> :: operator = (KDeque&& deque) {

	if (this != &deque) {
		KDeque DC(forward<KDeque<T>>(deque));
		Swap(DC);
	}
	return *this;
}


//-------------------------------------------------------------
