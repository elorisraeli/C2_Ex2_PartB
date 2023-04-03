#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include "game.hpp"
#include "player.hpp"

using namespace std;

namespace ariel
{

    int turns;
    int draws;
    vector<string> log;

    Game::Game(Player player1, Player player2) : player1(player1), player2(player2)
    {
        cout << "Player1 " + player1.getName() << endl;
        cout << "Player2 " + player2.getName() << endl;
        turns = 0;
        draws = 0;

        bool even = true;
        for (int i = static_cast<int>(Card::Series::HEARTS); i <= static_cast<int>(Card::Series::SPADES); i++)
        {
            for (int j = static_cast<int>(Card::Rank::ACE); j <= static_cast<int>(Card::Rank::KING); j++)
            {
                Card::Series series = static_cast<Card::Series>(i);
                Card::Rank rank = static_cast<Card::Rank>(j);
                Card card(series, rank);

                if (even)
                {
                    player1.addCardWon(card);
                    player1.decreaseNumOfCardsWon();
                    cout << ("Player1 " + player1.getName() + ": stackSize=" + to_string(player1.stacksize()) + ", numCardWon=" + to_string(player1.cardesTaken())) << endl;
                }
                else
                {
                    player2.addCardWon(card);
                    player2.decreaseNumOfCardsWon();
                    cout << ("Player2 " + player2.getName() + ": stackSize=" + to_string(player2.stacksize()) + ", numCardWon=" + to_string(player2.cardesTaken())) << endl;
                }
                even = !even;
            }
        }
    }

    bool Game::isWinner()
    {
        if (player1.stacksize() == 52 || player2.stacksize() == 52)
        {
            return true;
        }
        return false;
    }

    void Game::addToLog(string str)
    {
        log.push_back(str);
    }

    void Game::playTurn()
    {
        vector<Card> turnCards;

        Card p1Card = player1.playCard();
        Card p2Card = player2.playCard();

        turnCards.push_back(p1Card);
        turnCards.push_back(p2Card);

        string turnString = player1.getName() + " played " + p1Card.getRank() + " of " + p1Card.getSeries() + " " + player2.getName() + " played " + p2Card.getRank() + " of " + p2Card.getSeries() + ". ";

        bool draw = false;
        if (p1Card.getRankValue() == p2Card.getRankValue())
        {
            draw = true;
        }
        // while draw
        while (draw == true)
        {
            turnString.append("Draw. ");
            // first option out of cards
            if (player1.stacksize() == 0 || player2.stacksize() == 0)
            {
                break;
            }
            // if not out of cards: continue the draw breakdown
            // simulate of opposite down cards - go inside the cards deck of turn without consider their value
            Card p1AnotherCard = player1.playCard();
            Card p2AnotherCard = player2.playCard();
            turnCards.push_back(p1AnotherCard);
            turnCards.push_back(p2AnotherCard);

            // second option out of cards while the card are "opposite down"
            if (player1.stacksize() == 0 || player2.stacksize() == 0)
            {
                // return each player his cards (each got on)
                break;
            }
            // if their both left cards in stack, then start the loop until winner accur or out of cards

            turnString.append(player1.getName() + " played " + p1AnotherCard.getRank() + " of " + p1AnotherCard.getSeries() + " " + player2.getName() + " played " + p2AnotherCard.getRank() + " of " + p2AnotherCard.getSeries() + ". ");

            if (p1AnotherCard.getRankValue() != p2AnotherCard.getRankValue())
            {
                draw = false;
            }
        }

        if (p1Card.getRankValue() > p2Card.getRankValue())
        {
            turnString.append(player1.getName() + " wins.");
            while (turnCards.empty() == false)
            {
                Card currentTopCard = turnCards.front();
                turnCards.erase(turnCards.begin());
                player1.addCardWon(currentTopCard);
                player2.decreaseNumOfCardsWon();
            }
        }
        else if (p1Card.getRankValue() < p2Card.getRankValue()) // could be just else
        {
            turnString.append(player2.getName() + " wins.");
            while (turnCards.empty() == false)
            {
                Card currentTopCard = turnCards.front();
                turnCards.erase(turnCards.begin());
                player2.addCardWon(currentTopCard);
                player1.decreaseNumOfCardsWon();
            }
        }
        else // no one win and out of cards
        {
            bool even = true;
            while (turnCards.empty() == false)
            {
                Card currentTopCard = turnCards.front();
                turnCards.erase(turnCards.begin());
                if (even)
                {
                    player1.addCardWon(currentTopCard);
                    player2.decreaseNumOfCardsWon();
                }
                else
                {
                    player2.addCardWon(currentTopCard);
                    player1.decreaseNumOfCardsWon();
                }
                even = !even;
            }
        }

        addToLog(turnString);
    }

    void Game::printLastTurn()
    {
        cout << log.back();
    }

    void Game::playAll()
    {
        while (isWinner() == false)
        {
            playTurn();
        }
    }

    void Game::printWiner()
    {
        if (player1.stacksize() == 0)
        {
            cout << player1.getName() << endl;
        }
        else if (player2.stacksize() == 0)
        {
            cout << player2.getName() << endl;
        }
        else
        {
            cout << "No winner yet" << endl;
        }
    }
    void Game::printLog()
    {
        for (const auto &line : log)
        {
            cout << line << endl;
        }
    }

    // ------------------------------------------------------NEED TO FILL----------------------------------------------------------
    void Game::printStats()
    {
    }
    // ------------------------------------------------------NEED TO FILL----------------------------------------------------------

    string Game::getDrawsString()
    {
        return to_string(draws);
    }

    string Game::getTurnsPlayedString()
    {
        return to_string(turns);
    }

}