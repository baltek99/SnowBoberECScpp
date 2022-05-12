#include "HighScores.h"
#include <fstream>
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

void HighScores::readHighScores() {
	std::ifstream in("highscores.txt");

	int number_of_lines = 0;
	std::string line;

	while (std::getline(in, line))
		++number_of_lines;
	in.close();

	std::ifstream in2("highscores.txt");
	if (number_of_lines % 2 == 0) {
		for (int i = 0; i < number_of_lines / 2; i++) {
			ResultBind rb;
			in2 >> rb;
			scores.push_back(rb);
		}
	}
	in2.close();

	std::sort(scores.begin(), scores.end(), compare);
}

void HighScores::writeHighScores() {
	std::ofstream out;
	out.open("highscores.txt", std::ofstream::out | std::ofstream::trunc);

	for (int i = 0; i < scores.size(); i++) {
		out << scores.at(i);
	}
	out.close();
}