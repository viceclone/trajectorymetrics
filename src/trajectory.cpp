#include "trajectory.hpp"
#include <cmath>
#include <sstream>
#include <iostream>

void Trajectory::initFromCLI()
{   
    int n;
    std::cout << "N points: ";
    std::cin >> n;
    for (int i=0; i<n; i++)
    {
        int t, x, y;

        std::cout << "--- Point " << i << " ---  " << std::endl;
        std::cout << ">> t? ";
        std::cin >> t;

        std::cout << ">> x? ";
        std::cin >> x;

        std::cout << ">> y? ";
        std::cin >> y;
        addPoint(t, x, y);
    }
    computeLengthAndSpeed();
}

std::string Trajectory::toString(bool verbose)
{
    std::stringstream ss;
    ss << ">> INDEX: " << m_index << std::endl;
    ss << ">> Trajectory length: " << m_length << std::endl;
    ss << ">> Trajectory speed : " << m_speed << std::endl;
    if (verbose)
    {
        for (auto [t, point] : m_points)
        {
            ss << "  - T: " << t << ".  Point: (" << point.first << " | " << point.second << ")" << std::endl;
        }
    }
    return ss.str();
}

void Trajectory::setIndex(int index)
{
    m_index = index;
}

int Trajectory::index() const
{
    return m_index;
}

const std::map<int, PointType>& Trajectory::points() const
{
    return m_points;
}

double Trajectory::length() const
{
    return m_length;
}

double Trajectory::speed() const
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