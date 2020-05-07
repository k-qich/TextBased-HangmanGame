#ifndef RESIZABLEARR_H
#define RESIZABLEARR_H
#include <iostream>

const int MIN_SIZE = 2;

namespace rarr
{
	template<class T>
	class ResizableArray
	{
		T** arr;
		int size;
		int num_elems;

		protected:
			void resize();

		public:
			ResizableArray();
			~ResizableArray();
			void insert(T elem);
			int remove(T elem);
			int find(T elem) const;
			std::ostream& display(std::ostream& os = std::cout) const;
	};
}
#endif
