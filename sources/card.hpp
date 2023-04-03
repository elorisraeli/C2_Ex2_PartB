#ifndef CARD_HPP
#define CARD_HPP

#include <string>
using namespace std;

namespace ariel
{
    class Card
    {
    public:
        enum class Series
        {
            HEARTS = 1,
            DIAMONDS,
            CLUBS,
            SPADES
        };

        enum class Rank
        {
            ACE = 1,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            NINE,
            TEN,
            JACK,
            QUEEN,
            KING
        };

        Card(Series series, Rank rank); // my own constructor
        Card();                         // empty constructor

        string getRank();
        string getSeries();
        int getRankValue();

    private:
        Series mySeries;
        Rank myRank;
        string seriesString;
        string rankString;
    };
}
#endif // CARD_HPP
