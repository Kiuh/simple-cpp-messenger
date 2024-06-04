#include "application.cpp"
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <cstdio>

using namespace client;

int main()
{
    const std::string raw_ip_address = "127.0.0.1";
    const unsigned short port_num = 3333;
    try
    {
        SyncTCPClient client(raw_ip_address, port_num);

        // Sync connect.
        client.connect();
        std::cout << "Sending request to the server... " << std::endl;
        std::string response = client.emulateLongComputationOp(10);
        std::cout << "Response received: " << response << std::endl;
        // Close the connection and free resources.
        client.close();
    }
    catch (system::system_error &e)
    {
        std::cout << "Error occurred!\nError code = " << e.code()
                  << ".\nMessage: " << e.what();
        getchar();
        return e.code().value();
    }
    getchar();
    return 0;
}
