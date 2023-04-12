#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
#include "player.hpp"
using namespace std;

namespace ariel
{
    class Game
    {
    private:
        Player& player_1;
        Player& player_2;
        int turns;
        int draws;
        vector <string> log;

    public:
        Game(Player& player1, Player& player2);

        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();

        void addToLog(string str);

        string getDrawsString();
        string getTurnsPlayedString();

        bool isWinner();
    };
}
#endif // GAME_HPP
