#pragma once

#include "NetCommon.hpp"
#include "NetThreadsafeQueue.hpp"
#include "NetMessage.hpp"
#include "NetConnection.hpp"

namespace net
{

template<typename T>
class ClientInterface
{
public:
    ClientInterface() {}

    virtual ~ClientInterface()
    {
        disconnect();
    }

    bool connect(const std::string& host, const uint16_t port)
    {
        try
        {
            boost::asio::ip::tcp::resolver resolver(m_context);
            boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));
            
            m_connection = std::make_unique<Connection<T>>(Connection<T>::Owner::client, m_context, boost::asio::ip::tcp::socket(m_context), m_qMessagesIn);
            
            m_connection->connectToServer(endpoints);

            thrContext = std::thread([this]() { m_context.run(); });
        }
        catch (std::exception& e)
        {
            std::cerr << "Client Exception: " << e.what() << "\n";
            return false;
        }

        return true;
    }

    void send(const Message<T>& msg)
    {
        if (isConnected())
            m_connection->send(msg);
        else
            std::cout << "Client is not connected to server" << std::endl;
    }

    void disconnect()
    {
        if (isConnected())
            m_connection->disconnect();

        m_context.stop();

        if (thrContext.joinable())
            thrContext.join();

        m_connection.release();
    }

    bool isConnected()
    {
        if (m_connection)
            return m_connection->isConnected();
        else
            return false;
    }

    TSQueue<OwnedMessage<T>>& incoming()
    { 
        return m_qMessagesIn;
    }

protected:
    boost::asio::io_context m_context;
    std::thread thrContext;
    std::unique_ptr<Connection<T>> m_connection;
    
private:
    TSQueue<OwnedMessage<T>> m_qMessagesIn;
};

}