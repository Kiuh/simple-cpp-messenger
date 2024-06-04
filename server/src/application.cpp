#include <boost/asio.hpp>
#include <thread>
#include <atomic>
#include <memory>
#include <iostream>

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace std;

namespace server
{
	class Service
	{
	public:
		Service() {}
		void HandleClient(tcp::socket &sock)
		{
			cout << "Handle client." << endl;
			asio::streambuf request;
			asio::read_until(sock, request, '\n');

			this_thread::sleep_for(std::chrono::milliseconds(500));

			std::string response = "Response " + to_string(request.data().size()) + "\n";
			cout << "Write response to client:\n|" << response << "|" << endl;
			asio::write(sock, asio::buffer(response));
		}
	};

	class Acceptor
	{
	public:
		Acceptor(asio::io_service &ios, unsigned short port_num)
			: m_ios(ios),
			  m_acceptor(m_ios, tcp::endpoint(address_v4::any(), port_num))
		{
			cout << "Start listening..." << endl;
			m_acceptor.listen();
		}

		void Accept()
		{
			tcp::socket sock(m_ios);
			cout << "Server start accepting..." << endl;
			m_acceptor.accept(sock);
			Service service;
			service.HandleClient(sock);
		}

	private:
		asio::io_service &m_ios;
		asio::ip::tcp::acceptor m_acceptor;
	};

	class Server
	{
	public:
		Server(unsigned short port_num)
		{
			this->port_num = port_num;
			m_stop = false;
		}

		void Start()
		{
			cout << "Server starting..." << endl;
			auto action = [this]
			{
				this->Run();
			};
			auto thread = new std::thread(action);
			m_thread.reset(thread);
		}

		void Stop()
		{
			cout << "Server stopped!" << endl;
			m_stop = true;
			m_thread->join();
		}

	private:
		void Run()
		{
			cout << "Server running..." << endl;
			Acceptor acceptor(m_ios, port_num);
			while (!m_stop)
			{
				acceptor.Accept();
			}
		}

		unique_ptr<thread> m_thread;
		bool m_stop = false;
		io_service m_ios;
		unsigned short port_num;
	};
}