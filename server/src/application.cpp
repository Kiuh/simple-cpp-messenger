#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;
using ip::tcp;

namespace server
{
	class Application
	{
	public:
		void run()
		{
			io_service io_service;
			tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 12345));

			while (true)
			{
				tcp::socket socket(io_service);
				acceptor.accept(socket);

				std::string message = "Hello from server!";
				boost::system::error_code ignored_error;
				boost::asio::write(socket, buffer(message), ignored_error);
			}
		}
	};
}