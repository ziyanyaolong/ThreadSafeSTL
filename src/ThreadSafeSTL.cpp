#include <iostream>

#include <thread>
#include "SafeSTL/FLVector/FLVector.h"
using namespace FLThreadSafeSTL;

FLVector<int> lllp;
std::vector<int> ve;

void thread_add()
{
	while (true)
	{
		lllp.pushBack(rand());
		lllp.pushBack(rand());
		lllp.pushBack(rand());
		//lllp.lock();
		////auto i = lllp.begin();
		////i != lllp.end();
		//for (auto i = lllp.begin(); i != lllp.end(); ++i)
		//{
		//	//std::cout << *i << std::endl;
		//}
		//lllp.unLook();
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void thread_add2()
{
	while (true)
	{
		ve.push_back(rand());
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main()
{
	//std::thread* tempThread = new std::thread(thread_add2);
	//tempThread->detach();
	for (std::size_t i = 0; i < 8; i++)
	{
		std::thread* tempThread = new std::thread(thread_add);
		tempThread->detach();
	}
	std::size_t speed1 = 1;
	std::size_t speed2 = 1;
	std::size_t speed1_ = 1;
	std::size_t speed2_ = 1;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	while (true)
	{
		speed1_ = lllp.size();
		speed2_ = ve.size();
		std::cout << (speed1_ - speed1) << " | " << (speed2_ - speed2) << std::endl;
		speed1 = speed1_;
		speed2 = speed2_;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}