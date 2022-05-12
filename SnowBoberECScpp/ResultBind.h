#pragma once
#include "Component.h"
#include <string>
struct ResultBind : public Component {
public:
	std::string name;
	int score;

	ResultBind();

	ResultBind(std::string name_, int score_);

	friend std::ostream& operator << (std::ostream& out, const ResultBind& obj);

	friend std::istream& operator >> (std::istream& in, ResultBind& obj);
};

