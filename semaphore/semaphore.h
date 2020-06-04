#pragma once 
#ifndef GUARD_semaphore_h
#define GUARD_semaphore_h

#include <mutex>
#include <condition_variable>

class semaphore {
public:
	semaphore(int init): m_value(init){}

	void wait();

	void signal();

private:
	int m_value;
	std::mutex m_mux;
	std::condition_variable m_waitcond;
}