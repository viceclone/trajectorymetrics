#pragma once

#include <map>

using PointType = std::pair<int, int>;

class Trajectory
{
public:

    // Getters
    double length();
    double speed();

    void addPoint(int t, int x, int y);

    // Compute metrics and save to internal buffer
    void computeLengthAndSpeed();

private:
    std::map<int, PointType> m_points;
    double m_length{0};
    double m_speed{0.0};
};