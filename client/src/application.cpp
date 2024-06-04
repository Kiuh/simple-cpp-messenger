#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace std;
using namespace system;

namespace client
{
    class SyncTCPClient
    {
    public:
        SyncTCPClient(const string &raw_ip_address, unsigned short port_num)
            : m_ep(address::from_string(raw_ip_address), port_num),
              m_sock(m_ios)
        {
            m_sock.open(m_ep.protocol());
        }

        void connect()
        {
            m_sock.connect(m_ep);
        }

        void close()
        {
            m_sock.shutdown(tcp::socket::shutdown_both);
            m_sock.close();
        }

        string emulateLongComputationOp(unsigned int duration_sec)
        {
            std::string request = "EMULATE_LONG_COMP_OP " + std::to_string(duration_sec) + "\n";
            sendRequest(request);
            return receiveResponse();
        };

    private:
        void sendRequest(const std::string &request)
        {
            asio::write(m_sock, asio::buffer(request));
        }
        std::string receiveResponse()
        {
            asio::streambuf buf;
            asio::read_until(m_sock, buf, '\n');
            std::istream input(&buf);
            std::string response;
            std::getline(input, response);
            return response;
        }

    private:
        asio::io_service m_ios;
        asio::ip::tcp::endpoint m_ep;
        asio::ip::tcp::socket m_sock;
    };
}