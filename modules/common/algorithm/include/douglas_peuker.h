/**
  ******************************************************************************
  * @file           : douglas_peuker.h
  * @author         : lxy
  * @brief          : extract sparse control points;
  * @attention      : Input Point:Eigen::Vector2d;
  * @date           : 1/28/24
  ******************************************************************************
  */


#ifndef MONOLANEMAPPINGINTERFACE_DOUGLAS_PEUKER_H
#define MONOLANEMAPPINGINTERFACE_DOUGLAS_PEUKER_H

#pragma once
#include <vector>
#include <iostream>
#include <math.h>

#include<Eigen/Dense>

typedef Eigen::Vector2d Point;

double PerpendicularDistance(const Point& pt, const Point& lineStart, const Point& lineEnd)
{
    double dx = lineEnd[0] - lineStart[0];
    double dy = lineEnd[1] - lineStart[1];

    //Normalise
    double mag = sqrt(pow(dx, 2) + pow(dy, 2));
    if (mag > 0.0)
    {
        dx /= mag;
        dy /= mag;
    }

    double pvx = pt[0] - lineStart[0];
    double pvy = pt[1] - lineStart[1];

    //Get dot product (project pv onto normalized direction)
    double pvdot = dx * pvx + dy * pvy;

    //Scale line direction vector
    double dsx = pvdot * dx;
    double dsy = pvdot * dy;

    //Subtract this from pv
    double ax = pvx - dsx;
    double ay = pvy - dsy;

    return sqrt(pow(ax, 2.0) + pow(ay, 2.0));
};

void DouglasPeucker(const std::vector<Point>& polyLine, double epsilon, std::vector<Point>& simplifiedPolyLine)
{
    if (polyLine.size() < 2)
    {
        std::cout << "Not enough points to simplify" << std::endl;
        return;
    }

    // Find the point with the maximum distance from line between start and end
    double maxDistance = 0.0;
    int index = 0;
    int end = polyLine.size() - 1;
    for (int i = 1; i < end; i++)
    {
        double d = PerpendicularDistance(polyLine[i], polyLine[0], polyLine[end]);
        if (d > maxDistance)
        {
            index = i;
            maxDistance = d;
        }
    }

    // If max distance is greater than epsilon, recursively simplify
    if (maxDistance > epsilon)
    {
        // Recursive call
        std::vector<Point> recResults1;
        std::vector<Point> recResults2;
        std::vector<Point> firstLine(polyLine.begin(), polyLine.begin() + index + 1);
        std::vector<Point> lastLine(polyLine.begin() + index, polyLine.end());
        DouglasPeucker(firstLine, epsilon, recResults1);
        DouglasPeucker(lastLine, epsilon, recResults2);

        // Build the result list
        simplifiedPolyLine.assign(recResults1.begin(), recResults1.end() - 1);
        simplifiedPolyLine.insert(simplifiedPolyLine.end(), recResults2.begin(), recResults2.end());
    }
    else
    {
        //Just return start and end points
        simplifiedPolyLine.push_back(polyLine[0]);
        simplifiedPolyLine.push_back(polyLine[end]);
    }
};



#endif //MONOLANEMAPPINGINTERFACE_DOUGLAS_PEUKER_H
