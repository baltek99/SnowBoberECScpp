#include "TextField.h"

TextField::TextField() : Component(CmpId::TEXT_FIELD) {
}

TextField::TextField(std::string text_) : Component(CmpId::TEXT_FIELD), text(text_) {
}
