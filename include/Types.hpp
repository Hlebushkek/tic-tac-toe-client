#pragma once

#include <stdint.h>

enum class TicTacToeMessage : uint32_t
{
    ServerPing,
    MessageAll,
    ServerMessage,
    LoginIn,
    LoginAccept,
    LoginDenied,
    Place
};