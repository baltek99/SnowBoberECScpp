#include "RotatedRectangle.h"

RotatedRectangle::RotatedRectangle(sf::FloatRect rectangle, float theInitialRotation)
{
    collisionRectangle = rectangle;
    rotation = theInitialRotation;

    //Calculate the Rectangles origin. We assume the center of the Rectangle will
    //be the point that we will be rotating around and we use that for the origin
    origin = sf::Vector2f((int)rectangle.width / 2, (int)rectangle.height / 2);
}

/// <summary>
/// Used for changing the X and Y position of the RotatedRectangle
/// </summary>
/// <param name="theXPositionAdjustment"></param>
/// <param name="theYPositionAdjustment"></param>
void RotatedRectangle::changePosition(int theXPositionAdjustment, int theYPositionAdjustment)
{
    collisionRectangle.left += theXPositionAdjustment;
    collisionRectangle.top += theYPositionAdjustment;
}

/// <summary>
/// Check to see if two Rotated Rectangls have collided
/// </summary>
/// <param name="rectangle"></param>
/// <returns></returns>
bool RotatedRectangle::intersects(RotatedRectangle rectangle)
{
    //Calculate the Axis we will use to determine if a collision has occurred
    //Since the objects are rectangles, we only have to generate 4 Axis (2 for
    //each rectangle) since we know the other 2 on a rectangle are parallel.
    std::vector<sf::Vector2f> rectangleAxis;
    rectangleAxis.resize(4);
    rectangleAxis[0] = (upperRightCorner() - upperLeftCorner());
    rectangleAxis[1] = (upperRightCorner() - lowerRightCorner());
    rectangleAxis[2] = (rectangle.upperLeftCorner() - rectangle.lowerLeftCorner());
    rectangleAxis[3] = (rectangle.upperLeftCorner() - rectangle.upperRightCorner());

    //Cycle through all of the Axis we need to check. If a collision does not occur
    //on ALL of the Axis, then a collision is NOT occurring. We can then exit out 
    //immediately and notify the calling function that no collision was detected. If
    //a collision DOES occur on ALL of the Axis, then there is a collision occurring
    //between the rotated rectangles. We know this to be true by the Seperating Axis Theorem
    for (sf::Vector2f axis : rectangleAxis)
    {
        if (!isAxisCollision(rectangle, axis))
        {
            return false;
        }
    }

    return true;
}

/// <summary>
/// Determines if a collision has occurred on an Axis of one of the
/// planes parallel to the Rectangle
/// </summary>
/// <param name="rectangle"></param>
/// <param name="axis"></param>
/// <returns></returns>
bool RotatedRectangle::isAxisCollision(RotatedRectangle rectangle, sf::Vector2f axis)
{
    //Project the corners of the Rectangle we are checking on to the Axis and
    //get a scalar value of that project we can then use for comparison
    std::vector<int> rectangleAScalars;
    rectangleAScalars.resize(4);
    rectangleAScalars[0] = (generateScalar(rectangle.upperLeftCorner(), axis));
    rectangleAScalars[1] = (generateScalar(rectangle.upperRightCorner(), axis));
    rectangleAScalars[2] = (generateScalar(rectangle.lowerLeftCorner(), axis));
    rectangleAScalars[3] = (generateScalar(rectangle.lowerRightCorner(), axis));

    //Project the corners of the current Rectangle on to the Axis and
    //get a scalar value of that project we can then use for comparison
    std::vector<int>  rectangleBScalars;
    rectangleBScalars.resize(4);
    rectangleBScalars[0] = (generateScalar(upperLeftCorner(), axis));
    rectangleBScalars[1] = (generateScalar(upperRightCorner(), axis));
    rectangleBScalars[2] = (generateScalar(lowerLeftCorner(), axis));
    rectangleBScalars[3] = (generateScalar(lowerRightCorner(), axis));

    //Get the Maximum and Minium Scalar values for each of the Rectangles
    int rectangleAMinimum = *min_element(rectangleAScalars.begin(), rectangleAScalars.end());
    int rectangleAMaximum = *max_element(rectangleAScalars.begin(), rectangleAScalars.end());
    int rectangleBMinimum = *min_element(rectangleBScalars.begin(), rectangleBScalars.end());;
    int rectangleBMaximum = *max_element(rectangleBScalars.begin(), rectangleBScalars.end());;

    //If we have overlaps between the Rectangles (i.e. Min of B is less than Max of A)
    //then we are detecting a collision between the rectangles on this Axis
    if (rectangleBMinimum <= rectangleAMaximum && rectangleBMaximum >= rectangleAMaximum)
    {
        return true;
    }
    else if (rectangleAMinimum <= rectangleBMaximum && rectangleAMaximum >= rectangleBMaximum)
    {
        return true;
    }

    return false;
}

/// <summary>
/// Generates a scalar value that can be used to compare where corners of 
/// a rectangle have been projected onto a particular axis. 
/// </summary>
/// <param name="rectangleCorner"></param>
/// <param name="axis"></param>
/// <returns></returns>
int RotatedRectangle::generateScalar(sf::Vector2f rectangleCorner, sf::Vector2f axis)
{
    //Using the formula for Vector projection. Take the corner being passed in
    //and project it onto the given Axis
    float numerator = (rectangleCorner.x * axis.x) + (rectangleCorner.y * axis.y);
    float denominator = (axis.x * axis.x) + (axis.y * axis.y);
    float divisionResult = numerator / denominator;
    sf::Vector2f cornerProjected = sf::Vector2f(divisionResult * axis.x, divisionResult * axis.y);

    //Now that we have our projected Vector, calculate a scalar of that projection
    //that can be used to more easily do comparisons
    float scalar = (axis.x * cornerProjected.x) + (axis.y * cornerProjected.y);
    return (int)scalar;
}

/// <summary>
/// Rotate a point from a given location and adjust using the Origin we
/// are rotating around
/// </summary>
/// <param name="point"></param>
/// <param name="originV"></param>
/// <param name="rotationVal"></param>
/// <returns></returns>
sf::Vector2f RotatedRectangle::rotatePoint(sf::Vector2f point, sf::Vector2f originV, float rotationVal)
{
    return sf::Vector2f(
        (float)(originV.x + (point.x - originV.x) * cos(rotationVal)
            - (point.y - originV.y) * sin(rotationVal)),

        (float)(originV.y + (point.y - originV.y) * cos(rotationVal)
            + (point.x - originV.x) * sin(rotationVal))
    );
}

sf::Vector2f RotatedRectangle::upperLeftCorner()
{
    sf::Vector2f upperLeft = sf::Vector2f(collisionRectangle.left, collisionRectangle.top);
    upperLeft = rotatePoint(upperLeft, upperLeft + origin, rotation);
    return upperLeft;
}

sf::Vector2f RotatedRectangle::upperRightCorner()
{
    sf::Vector2f upperRight = sf::Vector2f(collisionRectangle.left + collisionRectangle.width, collisionRectangle.top);
    upperRight = rotatePoint(upperRight, upperRight + sf::Vector2f(-origin.x, origin.y), rotation);
    return upperRight;
}

sf::Vector2f RotatedRectangle::lowerLeftCorner()
{
    sf::Vector2f lowerLeft = sf::Vector2f(collisionRectangle.left, collisionRectangle.top + collisionRectangle.height);
    lowerLeft = rotatePoint(lowerLeft, lowerLeft + sf::Vector2f(origin.x, -origin.y), rotation);
    return lowerLeft;
}

sf::Vector2f RotatedRectangle::lowerRightCorner()
{
    sf::Vector2f lowerRight = sf::Vector2f(collisionRectangle.left + collisionRectangle.width, collisionRectangle.top + collisionRectangle.height);
    lowerRight = rotatePoint(lowerRight, lowerRight + sf::Vector2f(-origin.x, -origin.y), rotation);
    return lowerRight;
}

int RotatedRectangle::getX() { return collisionRectangle.left; }

int RotatedRectangle::getY() { return collisionRectangle.top; }

int RotatedRectangle::getWidth() { return collisionRectangle.width; }

int RotatedRectangle::getHeight() { return collisionRectangle.height; }
