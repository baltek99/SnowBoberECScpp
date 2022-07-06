#include "Util.h"
#include <cmath>

using namespace std;

float Util::lerp(float start_value, float end_value, float pct) {
    return (start_value + (end_value - start_value) * pct);
}

float Util::easeOut(float x) {
    return 1 - (float)pow(1 - x, 3);
}

float Util::flip(float x) {
    return 1 - x;
}

float Util::spike(float x) {
    if (x <= 0.5) {
        return easeOut(x / 0.5f);
    }
    return easeOut(flip(x) / 0.5f);
}

float Util::easeInOutCubic(float x) {
    return x < 0.5 ? 4 * x * x * x : 1 - (float)pow(-2 * x + 2, 3) / 2;
}

float Util::easeInQuint(float x) {
    return (float)pow(x, 5);
}
