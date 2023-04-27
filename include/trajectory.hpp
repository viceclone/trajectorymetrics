#pragma once

#include <map>
#include <string>

using PointType = std::pair<int, int>;

class Trajectory
{
public:
    // Init from CLI
    void initFromCLI();
    std::string toString(bool verbose = false);

    //Setters
    void setIndex(int index);
    
    // Getters
    int index() const;
    const std::map<int, PointType>& points() const;
    double length() const;
    double speed() const;

    void addPoint(int t, int x, int y);

    // Compute metrics and save to internal buffer
    void computeLengthAndSpeed();

private:
    int m_index{-1};
    std::map<int, PointType> m_points;
    double m_length{0};
    double m_speed{0.0};
};