#include "player.hpp"
#include "card.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace ariel
{
    Player::Player(string name) : mName(name), myStack(), cardsTaken(0), wins(0), loses(0)
    {
    }

    int Player::stacksize()
    {
        return myStack.size();
    }

    int Player::cardesTaken()
    {
        return cardsTaken;
    }

    void Player::increaseCardsTaken()
    {
        cardsTaken++;
    }

    Card Player::playCard()
    {
        if (myStack.size() != 0)
        {
            Card currentTopCard = myStack.front();
            myStack.erase(myStack.begin());
            return currentTopCard;
        }
        throw runtime_error("Cannot play card, stack is empty.");
    }

    string Player::getName()
    {
        return mName;
    }

    int Player::getWins()
    {
        return wins;
    }
    int Player::getloses()
    {
        return loses;
    }
    void Player::addWin()
    {
        wins++;
    }
    void Player::addLose()
    {
        loses++;
    }

    void Player::addCardToStack(Card card)
    {
        myStack.push_back(card);
    }

}