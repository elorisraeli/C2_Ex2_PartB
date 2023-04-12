#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "card.hpp"
#include <vector>

using namespace std;

namespace ariel
{
    class Player
    {
    private:
        string mName;
        vector<Card> myStack;
        int cardsTaken;
        int wins;
        int loses;

    public:
        Player(string name);

        int stacksize();
        int cardesTaken();
        Card playCard();
        string getName();
        int getWins();
        int getloses();
        void addWin();
        void addLose();
        void increaseCardsTaken();
        void addCardToStack(Card card);
    };
}
#endif
