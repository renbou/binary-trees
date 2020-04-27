#ifndef VECTOR_H
#define VECTOR_H

#include "algorithms.h"
#include "stdexcept"

typedef unsigned int sizeT;

template<typename T>
class vector {
private:
	unsigned int roundToNextPowerOfTwo(unsigned int v)
	{
		v--;
		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		v++;
		return v;
	}
protected:
	T * _baseArray = nullptr;
	unsigned int _defaultStartSize = 32;
        unsigned int _currentMaxSize = 0;
	unsigned int _currentSize = 0;
public:
	vector()
			: _defaultStartSize(32),
                          _currentMaxSize(_defaultStartSize),
                          _currentSize(0)
	{
		_baseArray = new T[_currentMaxSize];
	}

	template <sizeT n> vector(const T (&arr)[n])
	{
		_currentSize = n;
		_currentMaxSize = (n&(-n)) == n ? n : roundToNextPowerOfTwo(n);
		_baseArray = new T[_currentMaxSize];
                Algorithms::copy(arr, _baseArray, n);
	}

	vector(sizeT t_vectorSize)
			: _currentMaxSize((t_vectorSize&(-t_vectorSize)) == t_vectorSize ? t_vectorSize : roundToNextPowerOfTwo(t_vectorSize)),
			  _currentSize(t_vectorSize)
	{
		_baseArray = new T[_currentMaxSize];
	}

	vector(sizeT t_vectorSize, T t_default)
			: _currentMaxSize((t_vectorSize&(-t_vectorSize)) == t_vectorSize ? t_vectorSize : roundToNextPowerOfTwo(t_vectorSize)),
			  _currentSize(t_vectorSize)
	{
		_baseArray = new T[_currentMaxSize];
		fill(_baseArray, _currentMaxSize, t_default);
	}

	~vector()
	{
		if (_baseArray != nullptr) {
			_currentSize = 0;
			_currentMaxSize = 0;
			delete[] _baseArray;
		}
	}

	vector(const vector & other)
			: _currentMaxSize(other._currentMaxSize),
			  _currentSize(other._currentSize)
	{
		if (_baseArray != nullptr)
			delete [] _baseArray;
		_baseArray = new T[_currentMaxSize];
                Algorithms::copy(other._baseArray, _baseArray, _currentSize);
	}

	vector& operator=(const vector & other)
	{
		_currentMaxSize = other._currentMaxSize;
		_currentSize = other._currentSize;
		if (_baseArray != nullptr)
			delete [] _baseArray;
		_baseArray = new T[_currentMaxSize];
                Algorithms::copy(other._baseArray, _baseArray, _currentSize);
		return *this;
	}

        T& operator[](unsigned int index)
	{
		if (index < 0 || index >= _currentSize) throw std::runtime_error("Accessing element at invalid location in vector.");
		return _baseArray[index];
	}

        T at(unsigned int index) const
	{
		if (index < 0 || index >= _currentSize) throw std::runtime_error("Accessing element at invalid location in vector.");
		return _baseArray[index];
	}

	vector operator+(const vector & other)
	{
		vector result(_currentSize+other._currentSize);
                Algorithms::copy(_baseArray, result._baseArray, _currentSize);
                Algorithms::copy(other._baseArray, result._baseArray+_currentSize, other._currentSize);
		return result;
	}

	vector& operator+=(const vector &other)
	{
		vector result = *this+other;
		*this = result;
		return *this;
	}

	bool operator==(const vector &other)
	{
		if (_currentSize != other._currentSize) return false;
		for (int i = 0; i < _currentSize; i++)
			if (_baseArray[i] != other._baseArray[i]) return false;
		return true;
	}

	unsigned int size() const
	{
		return _currentSize;
	}

	bool empty() const
	{
		return _currentSize;
	}

        void resize(sizeT t_n)
	{
		vector result(t_n);
		if (t_n < _currentSize)
                        Algorithms::copy(_baseArray, result._baseArray, t_n);
		else
                        Algorithms::copy(_baseArray, result._baseArray, _currentSize);
		result._currentSize = t_n;
		*this = result;
	}

	void clear()
	{
		if (_baseArray != nullptr) {
			_currentSize = 0;
			_currentMaxSize = 0;
			delete[] _baseArray;
		}
	}

	void push(T t_value)
	{
		if (_currentMaxSize == 0)
			vector();
		if (_currentSize == _currentMaxSize)
			resize(_currentMaxSize*2);
		_baseArray[_currentSize++] = t_value;
	}

	void pop()
	{
		if (_currentSize == 0) throw std::runtime_error("Trying to pop element from empty vector.");
		_currentSize--;
		_baseArray[_currentSize] = T();
	}
};

#endif // VECTOR_H
