#include<SFML\Network.hpp>
#include<string>
#include<iostream>
#include<windows.h>

using namespace std;

int main() { 
	sf::TcpSocket socket;
	sf::IpAddress ip, curentIp = sf::IpAddress::getLocalAddress();
	sf::Packet packet;
	char mode;
	string name, mailForSend, text, getName, mail;
	cout << "Input your name: ";
	cin >> name;
	cout << "\n";
	cout << "Input mode (s for server and c for client)";
	cin >> mode;
	if (mode == 's') {
		sf::TcpListener listener;

		cout << "Your IP is: " << curentIp << "\n";
		if (listener.listen(2000) != sf::Socket::Done)
		{
			cout << "Listener error\n";
		}

		// accept a new connection
		if (listener.accept(socket) != sf::Socket::Done)
		{
			cout << "Acept error\n";
		}

	}
	else {
		cout << "Input the IP of server: ";
		cin >> ip;
		cout << "\n";
		sf::Socket::Status status = socket.connect(ip, 2000);
		if (status != sf::Socket::Done)
		{
			cout << "Conection error\n";
		}
		text = " was conected!\n";
		packet << name << text;
		socket.send(packet);
	}
	socket.setBlocking(false);

	
	
	while (true) {
		if (GetAsyncKeyState(VK_LCONTROL)) {
			getline(cin, mailForSend);
			if (mailForSend != "") {
				packet << name << mailForSend;
				socket.send(packet);
			}
		}		
		else if (socket.receive(packet) == sf::Socket::Done) {
			string ;
			packet >> getName >> mail;
			cout << getName << ": " << mail << "\n";
			packet.clear();
		}
	}
	system("pause");
	return 0;
}