#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include "game.hpp"
#include "player.hpp"
#include "card.hpp"

using namespace std;

namespace ariel
{

    Game::Game(Player &player1, Player &player2) : player_1(player1), player_2(player2)
    {
        turns = 0;
        draws = 0;
        vector<Card> shuffledDeck;
        for (int i = static_cast<int>(Card::Series::HEARTS); i <= static_cast<int>(Card::Series::SPADES); i++)
        {
            for (int j = static_cast<int>(Card::Rank::ACE); j <= static_cast<int>(Card::Rank::KING); j++)
            {
                Card::Series series = static_cast<Card::Series>(i);
                Card::Rank rank = static_cast<Card::Rank>(j);
                Card card(series, rank);
                shuffledDeck.push_back(card);
            }
        }

        // shuffle the deck of cards
        auto seed = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
        default_random_engine rng(static_cast<unsigned int>(seed));
        shuffle(shuffledDeck.begin(), shuffledDeck.end(), rng);

        // Deal shuffled deck of cards
        bool even = true;
        for (const auto &card : shuffledDeck)
        {
            if (even)
            {
                player_1.addCardToStack(card);
            }
            else
            {
                player_2.addCardToStack(card);
            }
            even = !even;
        }
    }

    bool Game::isGameEnd()
    {
        if ((player_1.stacksize() != 0) && (player_2.stacksize() != 0))
        {
            return false;
        }
        return true;
    }

    void Game::addToLog(string str)
    {
        log.push_back(str);
    }

    void Game::playTurn()
    {
        turns++;

        if (&player_1 == &player_2)
        {
            throw runtime_error("Cannot play turn, same player accured.");
        }
        if (player_1.stacksize() == 0 && player_2.stacksize() == 0)
        {
            throw runtime_error("Cannot play turn, stacks are empty, Game over.");
        }

        int countCardsInTurn = 0;

        Card p1Card = player_1.playCard();
        Card p2Card = player_2.playCard();
        countCardsInTurn += 2;

        string turnString = player_1.getName() + " played " + p1Card.getRank() + " of " + p1Card.getSeries() + " " + player_2.getName() + " played " + p2Card.getRank() + " of " + p2Card.getSeries() + ". ";

        bool draw = false;
        if (p1Card.getRankValue() == p2Card.getRankValue())
        {
            draw = true;
        }

        // while draw
        while (draw == true)
        {
            turnString.append("Draw. ");
            draws++;
            // first option out of cards
            if (player_1.stacksize() == 0 || player_2.stacksize() == 0)
            {
                break;
            }
            // if not out of cards: continue the draw breakdown
            // simulate of opposite down cards - go inside the cards deck of turn without consider their value
            Card p1AnotherCard = player_1.playCard();
            Card p2AnotherCard = player_2.playCard();
            countCardsInTurn += 2;

            // second option out of cards while the card are "opposite down"
            if (player_1.stacksize() == 0 || player_2.stacksize() == 0)
            {
                // return each player his cards (each got on)
                break;
            }

            p1AnotherCard = player_1.playCard();
            p2AnotherCard = player_2.playCard();
            countCardsInTurn += 2;

            turnString.append(player_1.getName() + " played " + p1AnotherCard.getRank() + " of " + p1AnotherCard.getSeries() + " " + player_2.getName() + " played " + p2AnotherCard.getRank() + " of " + p2AnotherCard.getSeries() + ". ");

            if (p1AnotherCard.getRankValue() != p2AnotherCard.getRankValue())
            {
                draw = false;
            }
        }

        // ----- by ivgeni (teacher) rules --> 2 wins Ace but Ace wins all others -----

        if (p1Card.getRankValue() > p2Card.getRankValue())
        {

            if (p1Card.getRankValue() != 2 && p2Card.getRankValue() == 1)
            {
                // player 2 wins
                turnString.append(player_2.getName() + " wins.");
                player_2.addWin();
                player_1.addLose();
                while (countCardsInTurn > 0)
                {
                    player_2.increaseCardsTaken();
                    countCardsInTurn--;
                }
            }
            else
            {
                // player 1 wins
                turnString.append(player_1.getName() + " wins.");
                player_1.addWin();
                player_2.addLose();
                while (countCardsInTurn > 0)
                {
                    player_1.increaseCardsTaken();
                    countCardsInTurn--;
                }
            }
        }
        else if (p1Card.getRankValue() < p2Card.getRankValue()) // could be just else
        {
            if (p1Card.getRankValue() == 1 && p2Card.getRankValue() != 2)
            {
                // player 1 wins
                turnString.append(player_1.getName() + " wins.");
                player_1.addWin();
                player_2.addLose();
                while (countCardsInTurn > 0)
                {
                    player_1.increaseCardsTaken();
                    countCardsInTurn--;
                }
            }
            else
            {
                // player 2 wins
                turnString.append(player_2.getName() + " wins.");
                player_2.addWin();
                player_1.addLose();
                while (countCardsInTurn > 0)
                {
                    player_2.increaseCardsTaken();
                    countCardsInTurn--;
                }
            }
        }
        else // no one win and out of cards
        {
            while (countCardsInTurn > 0)
            {
                player_1.increaseCardsTaken();
                player_2.increaseCardsTaken();
                countCardsInTurn -= 2;
            }
        }

        addToLog(turnString);
    }

    void Game::printLastTurn()
    {
        cout << log.back() << endl;
    }

    void Game::playAll()
    {
        while (isGameEnd() == false)
        {
            playTurn();
        }
    }

    void Game::printWiner()
    {
        if ((player_1.stacksize() > 0) && (player_2.stacksize() > 0))
        {
            cout << "Game not over yet." << endl;
            return;
        }
        if (player_1.cardesTaken() > player_2.cardesTaken())
        {
            cout << "The winner is: " << player_1.getName() << "!" << endl;
        }
        else if (player_1.cardesTaken() < player_2.cardesTaken())
        {
            cout << "The winner is: " << player_2.getName() << "!" << endl;
        }
        else if (player_1.cardesTaken() == player_2.cardesTaken())
        {
            cout << "Game end with draw, no winner." << endl;
        }
        else
        {
            cout << "No winner." << endl;
        }
    }

    void Game::printLog()
    {
        for (const auto &line : log)
        {
            cout << line << endl;
        }
    }

    void Game::printStats()
    {
        int p1Rate = -1;
        int p2Rate = -1;
        int drawRate = -1;
        try
        {
            p1Rate = static_cast<double>(player_1.getWins()) / static_cast<double>(turns) * 100.0;
            p2Rate = static_cast<double>(player_2.getWins()) / static_cast<double>(turns) * 100.0;
            drawRate = static_cast<double>(draws) / static_cast<double>(turns) * 100.0;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        string p1String = "\nPlayer1: win rate=" + to_string(p1Rate) + "%, cards won=" + to_string(player_1.cardesTaken());
        string p2String = "\nPlayer2: win rate=" + to_string(p2Rate) + "%, cards won=" + to_string(player_2.cardesTaken());
        string drawsString = "\nDraws: draws=" + to_string(draws) + ", draw rate=" + to_string(drawRate) + "%";
        cout << p1String + p2String + drawsString << endl;
    }

    string Game::getDrawsString()
    {
        return to_string(draws);
    }

    string Game::getTurnsPlayedString()
    {
        return to_string(turns);
    }

}