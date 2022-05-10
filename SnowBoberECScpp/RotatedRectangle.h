#pragma once

#include <SFML/Graphics.hpp>

class RotatedRectangle
{
public:
    sf::FloatRect CollisionRectangle;
    float Rotation;
    sf::Vector2f Origin;

    RotatedRectangle(sf::FloatRect theRectangle, float theInitialRotation)
    {
        CollisionRectangle = theRectangle;
        Rotation = theInitialRotation;

        //Calculate the Rectangles origin. We assume the center of the Rectangle will
        //be the point that we will be rotating around and we use that for the origin
        Origin = sf::Vector2f((int)theRectangle.width / 2, (int)theRectangle.height / 2);
    }

    /// <summary>
    /// Used for changing the X and Y position of the RotatedRectangle
    /// </summary>
    /// <param name="theXPositionAdjustment"></param>
    /// <param name="theYPositionAdjustment"></param>
    void ChangePosition(int theXPositionAdjustment, int theYPositionAdjustment)
    {
        CollisionRectangle.left += theXPositionAdjustment;
        CollisionRectangle.top += theYPositionAdjustment;
    }


    /// <summary>
    /// Check to see if two Rotated Rectangls have collided
    /// </summary>
    /// <param name="theRectangle"></param>
    /// <returns></returns>
    bool Intersects(RotatedRectangle theRectangle)
    {
        //Calculate the Axis we will use to determine if a collision has occurred
        //Since the objects are rectangles, we only have to generate 4 Axis (2 for
        //each rectangle) since we know the other 2 on a rectangle are parallel.
        std::vector<sf::Vector2f> aRectangleAxis;
        aRectangleAxis.resize(4);
        aRectangleAxis[0] = (UpperRightCorner() - UpperLeftCorner());
        aRectangleAxis[1] = (UpperRightCorner() - LowerRightCorner());
        aRectangleAxis[2] = (theRectangle.UpperLeftCorner() - theRectangle.LowerLeftCorner());
        aRectangleAxis[3] = (theRectangle.UpperLeftCorner() - theRectangle.UpperRightCorner());

        //Cycle through all of the Axis we need to check. If a collision does not occur
        //on ALL of the Axis, then a collision is NOT occurring. We can then exit out 
        //immediately and notify the calling function that no collision was detected. If
        //a collision DOES occur on ALL of the Axis, then there is a collision occurring
        //between the rotated rectangles. We know this to be true by the Seperating Axis Theorem
        for (sf::Vector2f aAxis : aRectangleAxis)
        {
            if (!IsAxisCollision(theRectangle, aAxis))
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
    /// <param name="theRectangle"></param>
    /// <param name="aAxis"></param>
    /// <returns></returns>
    bool IsAxisCollision(RotatedRectangle theRectangle, sf::Vector2f aAxis)
    {
        //Project the corners of the Rectangle we are checking on to the Axis and
        //get a scalar value of that project we can then use for comparison
        std::vector<int> aRectangleAScalars;
        aRectangleAScalars.resize(4);
        aRectangleAScalars[0] = (GenerateScalar(theRectangle.UpperLeftCorner(), aAxis));
        aRectangleAScalars[1] = (GenerateScalar(theRectangle.UpperRightCorner(), aAxis));
        aRectangleAScalars[2] = (GenerateScalar(theRectangle.LowerLeftCorner(), aAxis));
        aRectangleAScalars[3] = (GenerateScalar(theRectangle.LowerRightCorner(), aAxis));

        //Project the corners of the current Rectangle on to the Axis and
        //get a scalar value of that project we can then use for comparison
        std::vector<int>  aRectangleBScalars;
        aRectangleBScalars.resize(4);
        aRectangleBScalars[0] = (GenerateScalar(UpperLeftCorner(), aAxis));
        aRectangleBScalars[1] = (GenerateScalar(UpperRightCorner(), aAxis));
        aRectangleBScalars[2] = (GenerateScalar(LowerLeftCorner(), aAxis));
        aRectangleBScalars[3] = (GenerateScalar(LowerRightCorner(), aAxis));

        //Get the Maximum and Minium Scalar values for each of the Rectangles
        int aRectangleAMinimum = *min_element(aRectangleAScalars.begin(), aRectangleAScalars.end());
        int aRectangleAMaximum = *max_element(aRectangleAScalars.begin(), aRectangleAScalars.end());
        int aRectangleBMinimum = *min_element(aRectangleBScalars.begin(), aRectangleBScalars.end());;
        int aRectangleBMaximum = *max_element(aRectangleBScalars.begin(), aRectangleBScalars.end());;

        //If we have overlaps between the Rectangles (i.e. Min of B is less than Max of A)
        //then we are detecting a collision between the rectangles on this Axis
        if (aRectangleBMinimum <= aRectangleAMaximum && aRectangleBMaximum >= aRectangleAMaximum)
        {
            return true;
        }
        else if (aRectangleAMinimum <= aRectangleBMaximum && aRectangleAMaximum >= aRectangleBMaximum)
        {
            return true;
        }

        return false;
    }

    /// <summary>
    /// Generates a scalar value that can be used to compare where corners of 
    /// a rectangle have been projected onto a particular axis. 
    /// </summary>
    /// <param name="theRectangleCorner"></param>
    /// <param name="theAxis"></param>
    /// <returns></returns>
    int GenerateScalar(sf::Vector2f theRectangleCorner, sf::Vector2f theAxis)
    {
        //Using the formula for Vector projection. Take the corner being passed in
        //and project it onto the given Axis
        float aNumerator = (theRectangleCorner.x * theAxis.x) + (theRectangleCorner.y * theAxis.y);
        float aDenominator = (theAxis.x * theAxis.x) + (theAxis.y * theAxis.y);
        float aDivisionResult = aNumerator / aDenominator;
        sf::Vector2f aCornerProjected = sf::Vector2f(aDivisionResult * theAxis.x, aDivisionResult * theAxis.y);

        //Now that we have our projected Vector, calculate a scalar of that projection
        //that can be used to more easily do comparisons
        float aScalar = (theAxis.x * aCornerProjected.x) + (theAxis.y * aCornerProjected.y);
        return (int)aScalar;
    }

    /// <summary>
    /// Rotate a point from a given location and adjust using the Origin we
    /// are rotating around
    /// </summary>
    /// <param name="thePoint"></param>
    /// <param name="theOrigin"></param>
    /// <param name="theRotation"></param>
    /// <returns></returns>
    sf::Vector2f RotatePoint(sf::Vector2f thePoint, sf::Vector2f theOrigin, float theRotation)
    {
        return sf::Vector2f(
            (float)(theOrigin.x + (thePoint.x - theOrigin.x) * cos(theRotation)
                - (thePoint.y - theOrigin.y) * sin(theRotation)),

            (float)(theOrigin.y + (thePoint.y - theOrigin.y) * cos(theRotation)
                + (thePoint.x - theOrigin.x) * sin(theRotation))
        );
    }

    sf::Vector2f UpperLeftCorner()
    {
        sf::Vector2f aUpperLeft = sf::Vector2f(CollisionRectangle.left, CollisionRectangle.top);
        aUpperLeft = RotatePoint(aUpperLeft, aUpperLeft + Origin, Rotation);
        return aUpperLeft;
    }

    sf::Vector2f UpperRightCorner()
    {
        sf::Vector2f aUpperRight = sf::Vector2f(CollisionRectangle.left + CollisionRectangle.width, CollisionRectangle.top);
        aUpperRight = RotatePoint(aUpperRight, aUpperRight + sf::Vector2f(-Origin.x, Origin.y), Rotation);
        return aUpperRight;
    }

    sf::Vector2f LowerLeftCorner()
    {
        sf::Vector2f aLowerLeft = sf::Vector2f(CollisionRectangle.left, CollisionRectangle.top + CollisionRectangle.height);
        aLowerLeft = RotatePoint(aLowerLeft, aLowerLeft + sf::Vector2f(Origin.x, -Origin.y), Rotation);
        return aLowerLeft;
    }

    sf::Vector2f LowerRightCorner()
    {
        sf::Vector2f aLowerRight = sf::Vector2f(CollisionRectangle.left + CollisionRectangle.width, CollisionRectangle.top + CollisionRectangle.height);
        aLowerRight = RotatePoint(aLowerRight, aLowerRight + sf::Vector2f(-Origin.x, -Origin.y), Rotation);
        return aLowerRight;
    }

    int getX() { return CollisionRectangle.left; }

    int getY() { return CollisionRectangle.top; }

    int getWidth() { return CollisionRectangle.width; }

    int getHeight() { return CollisionRectangle.height; }
};

