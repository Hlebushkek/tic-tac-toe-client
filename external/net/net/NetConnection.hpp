#pragma once

#include "NetCommon.hpp"
#include "NetThreadsafeQueue.hpp"

namespace net
{

template<typename T>
class Connection : public std::enable_shared_from_this<Connection<T>>
{
public:
    enum class Owner
    {
        server,
        client
    };
    
    Connection(Owner parent, boost::asio::io_context& asioContext, boost::asio::ip::tcp::socket socket, TSQueue<OwnedMessage<T>>& qIn)
        : m_asioContext(asioContext), m_socket(std::move(socket)), m_qMessagesIn(qIn)
    {
        m_nOwnerType = parent;
    }

    virtual ~Connection() {}

    void connectToServer(const boost::asio::ip::tcp::resolver::results_type& endpoints)
    {
        if (m_nOwnerType == Owner::client)
        {
            boost::asio::async_connect(m_socket, endpoints,
                [this](std::error_code ec, boost::asio::ip::tcp::endpoint endpoint)
            {
                if (!ec)
                {
                    std::cout << "Connected to server, read header" << std::endl;
                    readHeader();
                }
                else
                {
                    std::cout << ec.message() << std::endl;
                }
            });
        }
    }

    void connectToClient(uint32_t uid = 0)
    {
        if (m_nOwnerType == Owner::server)
        {
            if (m_socket.is_open())
            {
                id = uid;
                std::cout << "Connected to client, read header" << std::endl;
                readHeader();
            }
        }
    }

    void disconnect()
    {
        if (isConnected())
            boost::asio::post(m_asioContext, [this]() { m_socket.close(); });
    }

    bool isConnected() const
    {
        return m_socket.is_open();
    }

    void send(const Message<T>& msg)
    {
        boost::asio::post(m_asioContext,
            [this, msg]()
        {
            bool bWritingMessage = !m_qMessagesOut.empty();
            m_qMessagesOut.push_back(msg);
            if (!bWritingMessage)
            {
                writeHeader();
            }
        });
    }

    uint32_t getID() const
    {
        return id;
    }

private:
    void readHeader()
    {
        boost::asio::async_read(m_socket, boost::asio::buffer(&m_msgTemporaryIn.header, sizeof(MessageHeader<T>)),
            [this](std::error_code ec, std::size_t length)
        {
            std::cout << "sizeof " << sizeof(MessageHeader<T>) << std::endl;    
            if (!ec)
            {
                if (m_msgTemporaryIn.header.size > 0)
                {
                    m_msgTemporaryIn.body.resize(m_msgTemporaryIn.header.size);
                    std::cout << "readHeader readBody" << std::endl;
                    std::cout << "size: " << this->m_msgTemporaryIn.header.size << std::endl;
                    readBody();
                }
                else
                {
                    std::cout << "readHeader else" << std::endl;
                    addToIncomingMessageQueue();
                }
            }
            else
            {
                std::cout << "[" << id << "] Read Header Fail.\n";
                m_socket.close();
            }
        });
    }

    void readBody()
    {
        boost::asio::async_read(m_socket, boost::asio::buffer(m_msgTemporaryIn.body.data(), m_msgTemporaryIn.body.size()),
            [this](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::cout << "readBody addToIncomingMessageQueue" << std::endl;
                addToIncomingMessageQueue();
            }
            else
            {
                std::cout << "[" << id << "] Read Body Fail.\n";
                std::cout << ec.message() << std::endl;
                m_socket.close();
            }
        });
    }

    void addToIncomingMessageQueue()
    {
        if(m_nOwnerType == Owner::server)
            m_qMessagesIn.push_back({ this->shared_from_this(), m_msgTemporaryIn });
        else
            m_qMessagesIn.push_back({ nullptr, m_msgTemporaryIn });

        readHeader();
    }

    void writeHeader()
    {
        boost::asio::async_write(m_socket, boost::asio::buffer(&m_qMessagesOut.front().header, sizeof(MessageHeader<T>)),
            [this](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                if (m_qMessagesOut.front().body.size() > 0)
                {
                    writeBody();
                }
                else
                {
                    m_qMessagesOut.pop_front();

                    if (!m_qMessagesOut.empty())
                    {
                        writeHeader();
                    }
                }
            }
            else
            {
                std::cout << "[" << id << "] Write Header Fail.\n";
                m_socket.close();
            }
        });
    }

    void writeBody()
    {
        boost::asio::async_write(m_socket, boost::asio::buffer(m_qMessagesOut.front().body.data(), m_qMessagesOut.front().body.size()),
            [this](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                m_qMessagesOut.pop_front();

                if (!m_qMessagesOut.empty())
                {
                    writeHeader();
                }
            }
            else
            {
                std::cout << "[" << id << "] Write Body Fail.\n";
                m_socket.close();
            }
        });
    }

protected:
    boost::asio::ip::tcp::socket m_socket;

    boost::asio::io_context& m_asioContext;

    TSQueue<Message<T>> m_qMessagesOut;
    TSQueue<OwnedMessage<T>>& m_qMessagesIn;
    Message<T> m_msgTemporaryIn;

    Owner m_nOwnerType = Owner::server;

    uint32_t id = 0;
};

}