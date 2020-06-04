#include "semaphore.h"
// #include <mutex>
// #include <condition_variable>

void semaphore::down() {

	std::unique_lock<std::mutex> lck(m_mux);

	if(--m_value < 0) {
		m_waitcond.wait(lck);
	}
}

void semaphore::up() {

	std::unique_lock<std::mutex> lck(m_mux);

	if(++m_value <= 0)
		m_waitcond.notify_one();
}