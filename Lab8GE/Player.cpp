#include "Player.h"

Player::Player() :
	m_window{ sf::VideoMode{ 400, 400, 32}, "Lab 8 GE"}
{
	srand(time(NULL));
	m_flying = false;

	m_window.setActive(false);

	m_data = std::ostringstream();

	m_numThreads = 0;
	m_number = 1;
	m_next = 1;
	for (int i = 0; i < n; i++)
	{
		m_turn[i] = 0;
	}

	m_playerWidth = 25;
	m_position = sf::Vector2f(sf::Vector2f(0, 350));
	m_player.setPosition(m_position);
	m_player.setSize(sf::Vector2f(m_playerWidth, m_playerWidth));
	m_player.setFillColor(sf::Color::Red);

	m_floor.setPosition(sf::Vector2f(0, 375));
	m_floor.setSize(sf::Vector2f(400, 25));
	m_floor.setFillColor(sf::Color::Green);
}

void Player::Update()
{
	int i = m_numThreads++;  

	m_mutex.lock();
	std::cout << "Update Thread Activated" << std::endl;
	m_mutex.unlock();

	std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 50));

	while (true)
	{
		m_turn[i] = m_number.fetch_add(1);

		m_mutex.lock();
		std::cout << "Update Thread Turn: " << m_turn[i] << std::endl;
		m_mutex.unlock();

		//std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 50));

		while (m_turn[i] != m_next)
		{
			continue;
		}

		m_mutex.lock();
		std::cout << "Update Thread"<< std::endl;
		m_mutex.unlock();

		//critical section
		//m_data << " data_t" << i << " ";
		m_mutex.lock();
		std::cout << "Update Thread:: Current Position " << m_position.x << " " << m_position.y << std::endl;
		if (m_position.x < 0)
		{
			m_position.x = 0;
		}
		else if (m_position.x > 375)
		{
			m_position.x = 375;
		}

		if (m_flying == false)
		{
			if (m_position.y < 350)
			{
				m_position.y += 9;
			}

			if (m_position.y > 350)
			{
				m_position.y = 350;
			}
			else if (m_position.y < 0)
			{
				m_position.y = 0;
			}
		}

		std::cout << "Update Thread:: Updated Position " << m_position.x << " " << m_position.y << std::endl;
		m_mutex.unlock();
		//exit protocol
		m_next += 1;

		m_mutex.lock();
		std::cout << m_data.str() << std::endl;
		std::cout << "Update Thread Next Turn " << m_next << std::endl;
		m_mutex.unlock();
	}
}

void Player::Input()
{
	int i = m_numThreads++;  //Intentional post-increment

	m_mutex.lock();
	std::cout << "Input Thread Activated" << std::endl;
	m_mutex.unlock();

	std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 50));

	while (true)
	{
		m_turn[i] = m_number.fetch_add(1);

		m_mutex.lock();
		std::cout << "Input Thread Turn: " << m_turn[i] << std::endl;
		m_mutex.unlock();

		//Slow down the program so that we can read the console.
//		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 500));

		while (m_turn[i] != m_next)
		{
			continue;
		}

		m_mutex.lock();
		std::cout << "Input Thread " << std::endl;
		m_mutex.unlock();

		//critical section
		//m_data << " data_t" << i << " ";
		m_mutex.lock();
		std::cout << "Input Thread::Current Position " << m_position.x << " " << m_position.y << std::endl;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_position.x -= 3;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_position.x += 3;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_position.y -= 1;
			m_flying = true;
		}
		else {
			m_flying = false;
		}
		std::cout << "Input Thread:: Updated Position " << m_position.x << " " << m_position.y << std::endl;
		m_mutex.unlock();
		//exit protocol
		m_next += 1;

		m_mutex.lock();
		std::cout << m_data.str() << std::endl;
		std::cout << "Input Thread Next Turn " << m_next << std::endl;
		m_mutex.unlock();
	}
}

void Player::Render()
{
	int i = m_numThreads++;  

	m_mutex.lock();
	std::cout << "Render Thread Activated" << std::endl;
	m_mutex.unlock();

	std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 500));

	while (true)
	{
		m_turn[i] = m_number.fetch_add(1);

		m_mutex.lock();
		std::cout << "Render Thread Turn: " << m_turn[i] << std::endl;
		m_mutex.unlock();

		//Slow down the program so that we can read the console.
//		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 1500));

		while (m_turn[i] != m_next)
		{
			continue;
		}

		m_mutex.lock();
		std::cout << "Render Thread" << std::endl;
		m_mutex.unlock();

		//critical section
		//m_data << " data_t" << i << " ";
		m_mutex.lock();
		std::cout << "Render Thread:: Player Position " << m_position.x << " " << m_position.y << std::endl;
		m_player.setPosition(m_position);

		m_window.clear(sf::Color::Black);

		m_window.draw(m_player);
		m_window.draw(m_floor);

		m_window.display();
		m_mutex.unlock();
		//exit protocol
		m_next += 1;

		m_mutex.lock();
		std::cout << m_data.str() << std::endl;
		std::cout << "Render Thread Next Turn " << m_next << std::endl;
		m_mutex.unlock();
	}
}