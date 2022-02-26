#pragma once

#include "../AtomicLock/AtomicLock_Bool/AtomicLock_Bool.h"

namespace FLThreadSafeSTL
{
	template <typename T, typename IT>
	class STL_Basic
	{
	private:
		friend class iterator;
		FLAtomicLock_Bool isLookingAtAlgorithm;
		FLAtomicLock_Bool isLookingAtWrite;
		FLAtomicLock_Bool isLookingAtRead;

		void setWrite()
		{
			while (true)
			{
				if (isLookingAtAlgorithm.get() || isLookingAtRead.get())
				{
					continue;
				}
				isLookingAtWrite.lock(FLAtomicLock_Bool::LockWay::Wait);
				if (isLookingAtAlgorithm.get() || isLookingAtRead.get())
				{
					isLookingAtWrite.unlock(FLAtomicLock_Bool::LockWay::Direct);
					continue;
				}
				break;
			}
		}

		void resetWrite()
		{
			isLookingAtWrite.unlock(FLAtomicLock_Bool::LockWay::Direct);
		}

		void setRead()
		{
			if (isLookingAtRead.get())
			{
				return;
			}

			while (true)
			{
				if (isLookingAtAlgorithm.get() || isLookingAtWrite.get())
				{
					continue;
				}
				isLookingAtRead.lock(FLAtomicLock_Bool::LockWay::Wait);
				if (isLookingAtAlgorithm.get() || isLookingAtWrite.get())
				{
					isLookingAtRead.unlock(FLAtomicLock_Bool::LockWay::Direct);
					continue;
				}
				break;
			}
		}

		void resetRead()
		{
			isLookingAtRead.unlock(FLAtomicLock_Bool::LockWay::Direct);
		}

		void setAlgorithm()
		{
			while (true)
			{
				if (isLookingAtRead.get() || isLookingAtWrite.get())
				{
					continue;
				}
				isLookingAtAlgorithm.lock(FLAtomicLock_Bool::LockWay::Wait);
				if (isLookingAtRead.get() || isLookingAtWrite.get())
				{
					isLookingAtAlgorithm.unlock(FLAtomicLock_Bool::LockWay::Direct);
					continue;
				}
				break;
			}
		}

		void resetAlgorithm()
		{
			isLookingAtAlgorithm.unlock(FLAtomicLock_Bool::LockWay::Direct);
		}

	protected:
		virtual void c_push_back(const T&) = 0;
		virtual std::size_t c_size() = 0;
		virtual void c_clear() = 0;
		virtual bool c_empty() = 0;
		virtual IT c_begin() = 0;
		virtual IT c_end() = 0;

	public:
		STL_Basic<T, IT>() {}
		virtual ~STL_Basic<T, IT>() {}

		void lock()
		{
			setAlgorithm();
			isLookingAtAlgorithm.lock(FLAtomicLock_Bool::LockWay::Direct);
		}

		void unLook()
		{
			resetAlgorithm();
			isLookingAtAlgorithm.unlock(FLAtomicLock_Bool::LockWay::Direct);
		}

		void pushBack(T data)
		{
			setWrite();
			c_push_back(data);
			resetWrite();
		}

		std::size_t size()
		{
			setRead();
			auto tempData = c_size();
			resetRead();
			return tempData;
		}

		void clear()
		{
			setWrite();
			c_clear();
			resetWrite();
		}

		bool empty()
		{
			setRead();
			auto tempData = c_empty();
			resetRead();
			return tempData;
		}

		IT begin()
		{
			return c_begin();
		}

		IT end()
		{
			return c_end();
		}
	};
}


