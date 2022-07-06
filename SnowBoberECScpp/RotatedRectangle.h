#pragma once
#include <SFML/Graphics.hpp>

class RotatedRectangle {
public:
    sf::FloatRect collisionRectangle;
    float rotation;
    sf::Vector2f origin;

    RotatedRectangle(sf::FloatRect rectangle, float theInitialRotation);

    /// <summary>
    /// Used for changing the X and Y position of the RotatedRectangle
    /// </summary>
    /// <param name="theXPositionAdjustment"></param>
    /// <param name="theYPositionAdjustment"></param>
    void changePosition(int theXPositionAdjustment, int theYPositionAdjustment);

    /// <summary>
    /// Check to see if two Rotated Rectangls have collided
    /// </summary>
    /// <param name="rectangle"></param>
    /// <returns></returns>
    bool intersects(RotatedRectangle rectangle);

    /// <summary>
    /// Determines if a collision has occurred on an Axis of one of the
    /// planes parallel to the Rectangle
    /// </summary>
    /// <param name="rectangle"></param>
    /// <param name="axis"></param>
    /// <returns></returns>
    bool isAxisCollision(RotatedRectangle rectangle, sf::Vector2f axis);

    /// <summary>
    /// Generates a scalar value that can be used to compare where corners of 
    /// a rectangle have been projected onto a particular axis. 
    /// </summary>
    /// <param name="rectangleCorner"></param>
    /// <param name="axis"></param>
    /// <returns></returns>
    int generateScalar(sf::Vector2f rectangleCorner, sf::Vector2f axis);

    /// <summary>
    /// Rotate a point from a given location and adjust using the Origin we
    /// are rotating around
    /// </summary>
    /// <param name="point"></param>
    /// <param name="originV"></param>
    /// <param name="rotationVal"></param>
    /// <returns></returns>
    sf::Vector2f rotatePoint(sf::Vector2f point, sf::Vector2f originV, float rotationVal);

    sf::Vector2f upperLeftCorner();

    sf::Vector2f upperRightCorner();

    sf::Vector2f lowerLeftCorner();

    sf::Vector2f lowerRightCorner();

    int getX();

    int getY();

    int getWidth();

    int getHeight();
};
