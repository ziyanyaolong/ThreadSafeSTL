#pragma once

#include <vector>

#include "../../STL_Bass/STL_Bass.h"

namespace FLThreadSafeSTL
{
	template <typename T>
	class FLVector : public STL_Basic<T, typename std::vector<T>::iterator>
	{
	private:
		std::vector<T> list;

	public:
		FLVector() : STL_Basic<T, typename std::vector<T>::iterator>() {}
		virtual ~FLVector() {}

		virtual void c_push_back(const T& data)
		{
			list.push_back(data);
		}

		virtual std::size_t c_size()
		{
			return list.size();
		}

		virtual void c_clear()
		{
			list.clear();
		}

		virtual bool c_empty()
		{
			return list.empty();
		}

		virtual typename std::vector<T>::iterator c_begin()
		{
			return list.begin();
		}

		virtual typename std::vector<T>::iterator c_end()
		{
			return list.end();
		}
	};
}
