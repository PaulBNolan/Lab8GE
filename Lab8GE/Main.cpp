#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <sstream>

//using namespace std;

const int n = 10;
std::atomic_int m_number;
std::atomic_int m_next;
std::atomic_int m_turn[n];
int m_numThreads;
std::mutex m_coutMutex;

std::ostringstream m_data;

void func() {
	int i = m_numThreads++;  //Intentional post-increment

	m_coutMutex.lock();
	std::cout << "Thread " << i << " reporting in." << std::endl;
	m_coutMutex.unlock();

	std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 500));

	while (true)
	{
		//Take a ticket
		m_turn[i] = m_number.fetch_add(1);

		//Using a mutex for output so that threads don't uppercut each other on the console.
		m_coutMutex.lock();
		std::cout << "Thread " << i << " Turn: " << m_turn[i] << std::endl;
		m_coutMutex.unlock();

		//Slow down the program so that we can read the console.
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 1500));

		while (m_turn[i] != m_next)
		{
			continue;
		}

		m_coutMutex.lock();
		std::cout << "Thread " << i << std::endl;
		m_coutMutex.unlock();

		//critical section
		m_data << " data_t" << i << std::endl;

		//exit protocol
		m_next += 1;

		m_coutMutex.lock();
		std::cout << m_data.str() << std::endl;
		std::cout << "Thread " << i << " Next Turn " << m_next << std::endl;
		m_coutMutex.unlock();
	}
}


int main()
{
	srand(time(NULL));

	m_data = std::ostringstream();

	m_numThreads = 0;
	m_number = 1;
	m_next = 1;
	for (int i = 0; i < n; i++)
	{
		m_turn[i] = 0;
	}

	std::thread t1 = std::thread(func);
	std::thread t2 = std::thread(func);
	std::thread t3 = std::thread(func);  //Add as many threads as you like
	//std::thread t4 = std::thread(func);
	//std::thread t5 = std::thread(func);

	t1.join();
	t2.join();
	t3.join();
	//t4.join();
	//t5.join();

	return 0;
}