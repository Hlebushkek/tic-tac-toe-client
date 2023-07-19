#pragma once

#include <net/NetClient.hpp>
#include "Types.hpp"

class TicTacToeClient : public net::ClientInterface<TicTacToeMessage>
{
public:
    void pingServer();

    void loginIn(std::string login, std::string password);

private:

};