#include "resizableArray.h"

using std::ostream;

namespace rarr
{
	// increases the size of the array by a power of 2
	template<class T>
	void ResizableArray<T>::resize()
	{
		T** temp;
		temp = new T * [size * size];

		for (int i = 0; i < size; i++)
		{
			temp[i] = arr[i];
		}

		delete[] arr;
		arr = temp;
		size = size * size;
	}

	template<class T>
	ResizableArray<T>::ResizableArray()
	{
		size = MIN_SIZE;
		num_elems = 0;
		arr = new T*[size];

		for (int i = 0; i < size; i++)
		{
			arr[i] = nullptr;
		}
	}

	template<class T>
	ResizableArray<T>::~ResizableArray()
	{
		for (int i = 0; i < size; i++)
		{
			delete arr[i];
		}

		delete arr;
	}

	// inserts an element to first available spot in the array
	template<class T>
	void ResizableArray<T>::insert(T elem)
	{
		bool found = false;

		if ((num_elems + 1) > size)
			resize();

		for (int i = 0; i < size && !found; i++)
		{
			if (!arr[i])
			{
				*arr[i] = elem;
				found = true;
			}
		}
	}

	// removes the element from the array if it exists
	// returns the index from where it was removed or -1 if it could not be found
	template<class T>
	int ResizableArray<T>::remove(T elem)
	{
		int idx = find(elem);

		if (idx >= 0)
		{
			delete arr[idx];
			arr[idx] = nullptr;
		}

		return idx;
	}

	// searches for the element in the array
	// returns the index from where it was found or -1 if it could not be found
	template<class T>
	int ResizableArray<T>::find(T elem) const
	{
		bool found = false;
		int idx = -1;

		for (int i = 0; i < size && !found; i++)
		{
			if (*arr[i] == elem)
			{
				idx = i;
				found = true;
			}
		}

		return idx;
	}

	// displays
	template<class T>
	std::ostream& ResizableArray<T>::display(std::ostream& os) const
	{
		for (int i = 0; i < size; i++)
		{
			arr[i] ? (os << "[" << *arr[i] << "]") : (os << "[]");
 		}

		return os;
	}
}
