#pragma once
class Util
{
public:
    /**
     * Linearly interpolates a value between two floats
     *
     * @param start_value Start value
     * @param end_value   End value
     * @param pct         Our progress or percentage. [0,1]
     * @return Interpolated value between two floats
     */
    static float lerp(float start_value, float end_value, float pct);

    static float easeOut(float x);

    static float flip(float x);

    static float spike(float x);

    static float easeInOutCubic(float x);

    static float easeInQuint(float x);
};

