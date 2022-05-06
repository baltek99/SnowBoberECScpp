#pragma once
#include "Component.h"
#include <string>

struct TextField : public Component {
public:
	std::string text;

	TextField();

	TextField(std::string text_);
};

