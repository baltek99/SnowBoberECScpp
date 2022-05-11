#include "HighScores.h"
#include <algorithm>

HighScores::HighScores() : maxNumberOfResults(10) {
}

void HighScores::addResult(std::string name, int score) {
    scores.push_back(ResultBind(name, score));

    std::sort(scores.begin(), scores.end(), compare);

    if (scores.size() > maxNumberOfResults) {
        scores.erase(scores.begin());
    }
}

int HighScores::compare(const ResultBind& bind1, const ResultBind& bind2) {
    return bind1.score < bind2.score;
}