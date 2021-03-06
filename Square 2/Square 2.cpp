// Square 2.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Slider.h"
#include <SFML/Graphics.hpp>
#include <SFML\Network.hpp>
#include <sstream>
sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
Slider slider(window, sf::Vector2f(300, 100), sf::Vector2f(20, 20), 8);
sf::CircleShape player1, player2;
const unsigned short PORT = 5000;
const std::string IPADDRESS("192.168.0.101");//change to suit your needs

std::string Value;
sf::TcpSocket socket;
sf::Mutex globalMutex;

std::string intToString(int i)
{
	std::ostringstream ss;
	ss << i;
	std::string str = ss.str();
	return str;
}

void Server(void)
{
	sf::TcpListener listener;
	listener.listen(PORT);
	listener.accept(socket);
	std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
}

bool Client(void)
{
	if (socket.connect(IPADDRESS, PORT) == sf::Socket::Done)
	{
		std::cout << "Connected\n";
		return true;
	}
	return false;
}

int cut(std::string test)
{
	std::string newstring;
	for (int i = 1; i < test.length(); i++)
	{
		newstring += test[i];
	}
	return atoi(newstring.c_str());
}

void Send(void)
{
	static std::string Value;
	while (1)
	{
		sf::Packet packetSendX;
		Value = "X" + intToString(player1.getPosition().x);
		packetSendX << Value;
		socket.send(packetSendX);
		sf::Packet packetSendY;
		Value = "Y" + intToString(player1.getPosition().y);
		packetSendY << Value;
		socket.send(packetSendY);
	}
}

void Recive(void)
{
	static std::string oldValueX, oldValueY;
	while (1)
	{
		std::string value;
		sf::Packet packetReceive;
		socket.receive(packetReceive);
		packetReceive >> value;
		if (value[0] == 'X')
		{
			if (cut(value) != player2.getPosition().x)
			{
				oldValueX = value;
				player2.setPosition(sf::Vector2f(cut(value),player2.getPosition().y));
			}
		}
		if (value[0] == 'Y')
		{

			if (cut(value) != player2.getPosition().y)
			{
				oldValueY = value;
				player2.setPosition(sf::Vector2f(player2.getPosition().x,cut(value)));
			}
		}
	}
}

int main()
{
	sf::Thread* recive = 0;
	sf::Thread* send = 0;
	player1.setFillColor(sf::Color::Red);
	player2.setFillColor(sf::Color::Blue);
	player1.setRadius(20);
	player2.setRadius(20);
	player1.setPosition(sf::Vector2f(0, 0));
	player2.setPosition(sf::Vector2f(100, 100));
	send = new sf::Thread(&Send);
	recive = new sf::Thread(&Recive);
	char who;
	std::cout << "Do you want to be a server (s) or a client (c) ? ";
	std::cin >> who;

	if (who == 's')
	{
		send->launch();
		recive->launch();
		Server();
	}
	else
	{
		send->launch();
		recive->launch();
		Client();
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					player1.setPosition(sf::Vector2f(player1.getPosition().x, player1.getPosition().y-10));
				}

				if (event.key.code == sf::Keyboard::S)
				{
					player1.setPosition(sf::Vector2f(player1.getPosition().x, player1.getPosition().y + 10));
				}

				if (event.key.code == sf::Keyboard::A)
				{
					player1.setPosition(sf::Vector2f(player1.getPosition().x-10, player1.getPosition().y ));
				}

				if (event.key.code == sf::Keyboard::D)
				{
					player1.setPosition(sf::Vector2f(player1.getPosition().x+10, player1.getPosition().y ));
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(player1);
		window.draw(player2);
		window.display();
	}

	return 0;
}

