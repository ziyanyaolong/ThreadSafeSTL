#pragma once

#include "../AtomicLock.h"

namespace FLThreadSafeSTL
{
	class FLAtomicLock_Bool : public FLAtomicLock<bool>
	{
	public:
		FLAtomicLock_Bool() : FLAtomicLock<bool>(false) {}
		virtual ~FLAtomicLock_Bool() {}
		enum class LockWay
		{
			Wait,
			Direct
		};

		bool lock(LockWay way = LockWay::Wait, std::size_t number = 0)
		{
			switch (way)
			{
			case FLThreadSafeSTL::FLAtomicLock_Bool::LockWay::Wait:
				return this->wait(true, number);
				break;

			case FLThreadSafeSTL::FLAtomicLock_Bool::LockWay::Direct:
				this->direct(true);
				return true;
				break;

			default:
				return false;
				break;
			}
			return false;
		}

		bool unlock(LockWay way = LockWay::Wait, std::size_t number = 0)
		{
			switch (way)
			{
			case FLThreadSafeSTL::FLAtomicLock_Bool::LockWay::Wait:
				return this->wait(false, number);
				break;

			case FLThreadSafeSTL::FLAtomicLock_Bool::LockWay::Direct:
				this->direct(false);
				return true;
				break;

			default:
				return false;
				break;
			}
			return false;
		}
	};
}
