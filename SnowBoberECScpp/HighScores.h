#pragma once
#include <vector>
#include "ResultBind.h"

class HighScores {
public :
    std::vector<ResultBind> scores;
    int maxNumberOfResults;

    HighScores();

    void addResult(std::string name, int score);

    void readHighScores();

    void writeHighScores();
private:
    static int compare(const ResultBind& bind1, const ResultBind& bind2);
};
