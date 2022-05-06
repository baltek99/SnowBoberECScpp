#pragma once
#include "Component.h"
#include <string>
struct ResultBind : public Component {
public:
	std::string name;
	int score;

	ResultBind(std::string name_, int score_);
};

