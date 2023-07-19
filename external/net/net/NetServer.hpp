#pragma once

#include "NetCommon.hpp"
#include "NetMessage.hpp"
#include "NetConnection.hpp"
#include "NetThreadsafeQueue.hpp"

namespace net
{

template<typename T>
class ServerInterface
{
public:
    ServerInterface(uint16_t port)
        : m_asioAcceptor(m_asioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {

    }

    virtual ~ServerInterface()
    {
        stop();
    }

    bool start()
    {
        try
        {
            waitForClientConnection();

            m_threadContext = std::thread([this]() { m_asioContext.run(); });
        }
        catch (std::exception& e)
        {
            std::cerr << "[SERVER] Exception: " << e.what() << "\n";
            return false;
        }

        std::cout << "[SERVER] Started!\n";
        return true;
    }

    void stop()
    {
        m_asioContext.stop();

        if (m_threadContext.joinable())
            m_threadContext.join();

        std::cout << "[SERVER] Stopped!\n";
    }

    #pragma mark - Async

    void waitForClientConnection()
    {
        m_asioAcceptor.async_accept(
            [this](std::error_code ec, boost::asio::ip::tcp::socket socket)
            {
                if (!ec)
                {
                    std::cout << "[SERVER] New Connection: " << socket.remote_endpoint() << "\n";

                    std::shared_ptr<Connection<T>> newconn =
                        std::make_shared<Connection<T>>(Connection<T>::Owner::server,
                            m_asioContext, std::move(socket), m_qMessagesIn);

                    if (onClientConnect(newconn))
                    {
                        m_deqConnections.push_back(std::move(newconn));
                        m_deqConnections.back()->connectToClient(nIDCounter++);

                        std::cout << "[" << m_deqConnections.back()->getID() << "] Connection Approved\n";
                    }
                    else
                    {
                        std::cout << "[-----] Connection Denied\n";
                    }
                }
                else
                {
                    std::cout << "[SERVER] New Connection Error: " << ec.message() << "\n";
                }

                waitForClientConnection();
            }
        );
    }

    void messageClient(std::shared_ptr<Connection<T>> client, const Message<T>& msg)
    {
        if (client && client->isConnected())
        {
            client->send(msg);
        }
        else
        {
            onClientDisconnect(client);

            client.reset();
            m_deqConnections.erase(
                std::remove(m_deqConnections.begin(), m_deqConnections.end(), client), m_deqConnections.end()
            );
        }
    }

    void messageAllClients(const Message<T>& msg, std::shared_ptr<Connection<T>> pIgnoreClient = nullptr)
    {
        bool bInvalidClientExists = false;

        for (auto& client : m_deqConnections)
        {
            if (client && client->isConnected())
            {
                if(client != pIgnoreClient)
                    client->send(msg);
            }
            else
            {
                onClientDisconnect(client);
                client.reset();

                bInvalidClientExists = true;
            }
        }

        if (bInvalidClientExists)
            m_deqConnections.erase(
				std::remove(m_deqConnections.begin(), m_deqConnections.end(), nullptr), m_deqConnections.end()
            );
    }

    void update(size_t nMaxMessages = -1, bool bWait = false)
    {
        if (bWait) m_qMessagesIn.wait();

        size_t nMessageCount = 0;
        while (nMessageCount < nMaxMessages && !m_qMessagesIn.empty())
        {
            auto msg = m_qMessagesIn.pop_front();

            onMessage(msg.remote, msg.msg);

            nMessageCount++;
        }
    }

protected:
    virtual bool onClientConnect(std::shared_ptr<Connection<T>> client)
    {
        return false;
    }

    virtual void onClientDisconnect(std::shared_ptr<Connection<T>> client)
    {

    }

    virtual void onMessage(std::shared_ptr<Connection<T>> client, Message<T>& msg)
    {

    }

protected:
    TSQueue<OwnedMessage<T>> m_qMessagesIn;

    std::deque<std::shared_ptr<Connection<T>>> m_deqConnections;

    boost::asio::io_context m_asioContext;
    std::thread m_threadContext;

    boost::asio::ip::tcp::acceptor m_asioAcceptor;

    uint32_t nIDCounter = 10000;
};
   
}
