#pragma once

template <typename T>
class KDeque;

template <typename T>

class KDIter {

private:

	KDeque<T>* D;
	mutable int index;

	KDIter(KDeque<T>* deque, int i) : D(deque), index(i) { }
	KDIter(KDeque<T> const* deque, int i) : D((KDeque<T>*)deque), index(i) { }


public:
	friend KDeque<T>;

	KDIter() : D(nullptr) {}

	inline KDIter& operator++ ();
	inline KDIter const& operator++() const;
	inline KDIter operator++ (int);
	inline KDIter const operator++ (int) const;

	T& operator * ();
	T const& operator * () const;

	bool operator == (KDIter const& it) const {	return index == it.index; }
	bool operator != (KDIter const& it) const {	return !(*this == it); }

};

template <typename T>
T& KDIter<T>::operator * () { return D->Memory_for_Deque[index]; }

template <typename T>
const T& KDIter<T>::operator * () const { return D->Memory_for_Deque[index]; }

template <typename T>
inline KDIter<T>& KDIter<T>::operator ++() { 
	index = (index + 1) % (D->Cells_Amount);
	return *this; 
}

template <typename T>
inline KDIter<T> const& KDIter<T>::operator ++() const { 
	index = (index + 1) % D->Cells_Amount; 
	return *this;
}

template <typename T>
inline KDIter<T>  KDIter<T>::operator ++(int)
{
	KDIter DC(*this);
	++ *this;
	return DC;
}

template <typename T>
inline KDIter<T> const KDIter<T>::operator ++(int) const
{
	KDIter DC(*this);
	++ *this;
	return DC;
}