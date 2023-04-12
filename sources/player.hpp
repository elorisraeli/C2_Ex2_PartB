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
        vector<Card> myCardsTaken;
        int wins;
        int loses;
        int cardsTaken;

    public:
        Player(string name);

        int stacksize();
        int cardesTaken();
        Card playCard();
        void addCardWon(Card wonCards);
        string getName();
        int getWins();
        int getloses();
        void addWin();
        void addLose();
        void increaseCardsTaken();
        void endGame();
        void getCard(Card card);
    };
}
#endif
