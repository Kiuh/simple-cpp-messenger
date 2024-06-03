#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <iostream>
#include <string>

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace std;

namespace server
{
	class Application
	{
	public:
		void run()
		{
			string addr = "";
			cout << "Enter addr: ";
			cin >> addr;
			int port = 0;
			cout << "Enter port: ";
			cin >> port;

			system::error_code ec;

			io_context context;
			tcp::endpoint endpoint(make_address_v4(addr, ec), port);

			tcp::socket socket(context);

			socket.connect(endpoint, ec);

			if (!ec)
			{
				cout << "Connected";
			}
			else
			{
				cout << "Failed to connect! " << ec.message() << endl;
			}
		}
	};
}