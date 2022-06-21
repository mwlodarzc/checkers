#ifndef BOT_HH
#define BOT_HH
#include <limits>
#include "CheckerBoard.hh"
namespace Bot
{
    int minimax(CheckerBoard &position, int depth, int alfa, int beta, bool whitePov);
    void make_best_move(CheckerBoard &position, int depth, bool whitePov);
}
#endif