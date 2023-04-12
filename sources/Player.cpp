#include "player.hpp"
#include "card.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace ariel
{
    Player::Player(string name) : mName(name), myStack(), myCardsTaken(), cardsTaken(0), wins(0), loses(0)
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

    void Player::addCardWon(Card wonCard)
    {
        myCardsTaken.push_back(wonCard);
    }

    Card Player::playCard()
    {
        if (myStack.size() == 0)
        {
            throw runtime_error("Cannot play card, stack is empty.");
        }
        Card currentTopCard = myStack.front();
        myStack.erase(myStack.begin());
        return currentTopCard;
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
    void Player::increaseCardsTaken()
    {
        cardsTaken++;
    }

    void Player::endGame()
    {
        // clear the deck
        myStack.clear();
        // release any unused memory
        myStack.shrink_to_fit();

        // reset data
        wins = 0;
        loses = 0;
        cardsTaken = 0;
    }

    void Player::getCard(Card card)
    {
        myStack.push_back(card);
    }

}