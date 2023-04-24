#include "trajectory.hpp"
#include <cmath>

double Trajectory::length()
{
    return m_length;
}

double Trajectory::speed()
{
    return m_speed;
}

void Trajectory::addPoint(int t, int x, int y)
{
    m_points.emplace(t, std::make_pair(x, y));
}

void Trajectory::computeLengthAndSpeed()
{
    m_length = 0;
    if (m_points.size() < 2)
    {
        return;
    }

    // Computing length
    for (auto it = m_points.begin(); it != std::prev(m_points.end(), 1); ++it)
    {
        double x1 = static_cast<double>((it->second).first);
        double y1 = static_cast<double>((it->second).second);

        auto nextIt = std::next(it);
        double x2 = static_cast<double>((nextIt->second).first);
        double y2 = static_cast<double>((nextIt->second).second);

        m_length += std::sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    }
    
    // Compute speed (length / t)
    auto firstPointIter = m_points.begin();
    auto lastPointIter = m_points.rbegin();
    m_speed = m_length / (lastPointIter->first - firstPointIter->first);
}