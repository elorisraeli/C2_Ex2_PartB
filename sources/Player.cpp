#include "player.hpp"
#include "card.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace ariel
{
    Player::Player(string name) : mName(name), numCardsWon(0), myStack(), wins(0), loses(0)
    {
    }

    int Player::stacksize()
    {
        return myStack.size();
    }

    int Player::cardesTaken()
    {
        return numCardsWon;
    }

    void Player::addCardWon(Card wonCard)
    {
        myStack.push_back(wonCard);
        numCardsWon++;
    }

    Card Player::playCard()
    {
        // Card currentTopCard = myStack.front();
        // myStack.erase(myStack.begin());
        numCardsWon = 0;
        Card currentTopCard = myStack.back();
        myStack.pop_back();
        return currentTopCard;
    }

    string Player::getName()
    {
        return mName;
    }

    void Player::decreaseNumOfCardsWon()
    {
        numCardsWon--;
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
    int Player::getNumCardsWon()
    {
        return numCardsWon;
    }

}