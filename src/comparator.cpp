#include "comparator.hpp"
#include <iostream>
#include <fstream>

TrajectoryPtr TrajectoryComparator::trajectory(int index)
{
    if (index < 0 || index > m_trajectories.size())
    {
        return nullptr;
    }

    return m_trajectories.at(index);
}

void TrajectoryComparator::summary(bool verbose)
{
    std::cout << "Number of trajectories: " << m_trajectories.size() << std::endl;
    for (auto trajectory : m_trajectories)
    {
        std::cout << trajectory->toString(verbose) << std::endl;
    }
}

void TrajectoryComparator::summaryLength(bool verbose)
{
    std::cout << "Number of trajectories: " << m_trajectories.size() << std::endl;
    for (auto [length, trajectory] : m_lengthTrajectoryMap)
    {
        std::cout << trajectory->toString(verbose) << std::endl;
    }
}

void TrajectoryComparator::summarySpeed(bool verbose)
{
    std::cout << "Number of trajectories: " << m_trajectories.size() << std::endl;
    for (auto [speed, trajectory] : m_speedTrajectoryMap)
    {
        std::cout << trajectory->toString(verbose) << std::endl;
    }
}

bool TrajectoryComparator::fetchFromFile(fs::path path)
{
    if (!fs::exists(path) || !fs::is_regular_file(path))
    {
        std::cerr << "File does not exist!" << std::endl;
        return false;
    }

    std::ifstream is{path};
    int numTrajectories;
    is >> numTrajectories;
    for (auto i = 0; i < numTrajectories; i++)
    {
        auto trajectory = std::make_shared<Trajectory>();
        int numPoints;
        is >> numPoints;
        for (auto j = 0; j < numPoints; j++)
        {
            int x, y, t;
            is >> x >> y >> t;
            trajectory->addPoint(t, x, y);
        }
        trajectory->setIndex(i);
        trajectory->computeLengthAndSpeed();
        addTrajectory(trajectory);
    }
    return true;
}

void TrajectoryComparator::addTrajectory(TrajectoryPtr trajectory)
{
    if (!trajectory)
    {
        return;
    }
    m_trajectories.push_back(trajectory);
    m_lengthTrajectoryMap.emplace(trajectory->length(), trajectory);
    m_speedTrajectoryMap.emplace(trajectory->speed(), trajectory);
}

std::vector<TrajectoryPtr> 
TrajectoryComparator::getClosestTrajectories(const std::multimap<double, TrajectoryPtr>& trajectoryMap, TrajectoryPtr refTrajectory, double keyValue, int n) const
{
    std::vector<TrajectoryPtr> results;
    auto iter = trajectoryMap.lower_bound(keyValue);
    auto riter = std::make_reverse_iterator(iter);
    // ++riter;

    if (iter != trajectoryMap.end() && iter->second == refTrajectory)
    {
        ++iter;
    }

    while (!(iter == trajectoryMap.end() && riter == trajectoryMap.rend()) && results.size() < n)
    {
        if (iter == trajectoryMap.end())
        {
            results.push_back(riter->second);
            ++riter;
            continue;
        }

        if (riter == trajectoryMap.rend())
        {
            results.push_back(iter->second);
            ++iter;
            continue;
        }

        if (iter->first - keyValue < keyValue - riter->first)
        {
            results.push_back(iter->second);
            ++iter;
        }
        else
        {
            results.push_back(riter->second);
            ++riter;
        }
    }
    return std::move(results);
}

std::vector<TrajectoryPtr> TrajectoryComparator::getClosestTrajectoryLength(TrajectoryPtr refTrajectory, int n) const
{
    return getClosestTrajectories(m_lengthTrajectoryMap, refTrajectory, refTrajectory->length(), n);
}

std::vector<TrajectoryPtr> TrajectoryComparator::getClosestTrajectorySpeed(TrajectoryPtr refTrajectory, int n) const
{
    return getClosestTrajectories(m_speedTrajectoryMap, refTrajectory, refTrajectory->speed(), n);
}
