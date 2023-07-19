#include "TicTacToeClient.hpp"

void TicTacToeClient::pingServer()
{
    net::Message<TicTacToeMessage> msg;
    msg.header.id = TicTacToeMessage::ServerPing;
    std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();		
    msg << timeNow;

    std::chrono::seconds duration = std::chrono::duration_cast<std::chrono::seconds>(timeNow.time_since_epoch());
    std::cout << "try ping server with msg: " << duration.count() << std::endl;
    
    this->send(msg);
}

void TicTacToeClient::loginIn(std::string login, std::string password)
{
    net::Message<TicTacToeMessage> msg;
    msg.header.id = TicTacToeMessage::LoginIn;	
    std::cout << "try login in " << login << " " << password << std::endl;
    
    msg << login << password;

    this->send(msg);
}
