#include "application.cpp"
#include <SDKDDKVer.h>

using namespace server;

int main()
{
	unsigned short port_num = 3333;
	unsigned int sleep_time = 120;
	try
	{
		Server server(port_num);
		server.Start();
		std::this_thread::sleep_for(std::chrono::seconds(sleep_time));
		server.Stop();
	}
	catch (system::system_error &e)
	{
		cout << "Error occurred! Error code = "
			 << e.code() << ". Message: "
			 << e.what();
	}
	return 0;
}
