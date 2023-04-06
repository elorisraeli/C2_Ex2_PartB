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
        int numCardsWon;
        int wins;
        int loses;

    public:
        Player(string name);

        int stacksize();
        int cardesTaken();
        Card playCard();
        void addCardWon(Card wonCards);
        string getName();
        void decreaseNumOfCardsWon();
        int getWins();
        int getloses();
        void addWin();
        void addLose();
        int getNumCardsWon();
    };
}
#endif
