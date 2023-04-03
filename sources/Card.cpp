#include <iostream>
#include <cstdlib>
#include "card.hpp"

using namespace std;

namespace ariel
{

    const char *const CARDS_AS_STRINGS[] = {
        "", "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};

    const char *const SERIES_AS_STRINGS[] = {
        "", "Hearts", "Diamonds", "Clubs", "Spades"};

    Card::Card(Series series, Rank rank) : mySeries(series), myRank(rank)
    {
        rankString = CARDS_AS_STRINGS[static_cast<int>(myRank)];
        seriesString = SERIES_AS_STRINGS[static_cast<int>(mySeries)];
    }

    Card::Card()
    {
    }

    string Card::getRank()
    {
        return rankString;
    }

    string Card::getSeries()
    {
        return seriesString;
    }

    int Card::getRankValue()
    {
        return static_cast<int>(myRank);
    }

}