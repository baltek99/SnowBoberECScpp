#include "ResultBind.h"
#include <fstream>
#include <iostream>
#include <cassert>

ResultBind::ResultBind() : Component(CmpId::RESULT_BIND), name(""), score(0) {}

ResultBind::ResultBind(std::string name_, int score_) : Component(CmpId::RESULT_BIND), name(name_), score(score_) {
}

std::ostream& operator << (std::ostream& out, const ResultBind& obj) {
	out << obj.name << "\n" << obj.score << std::endl;
	return out;
}

std::istream& operator >> (std::istream& in, ResultBind& obj) {
	in >> obj.name;
	in >> obj.score;

	return in;
}