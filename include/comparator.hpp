#pragma once

#include <filesystem>
#include <memory>
#include <set>
#include <map>
#include "trajectory.hpp"

namespace fs = std::filesystem;
using TrajectoryPtr = std::shared_ptr<Trajectory>;

class TrajectoryComparator
{
public:
    void summary(bool verbose = false);
    void summaryLength(bool verbose = false);
    void summarySpeed(bool verbose = false);

    TrajectoryPtr trajectory(int index);

    bool fetchFromFile(fs::path path);
    void addTrajectory(TrajectoryPtr trajectory);

    std::vector<TrajectoryPtr> getClosestTrajectoryLength(TrajectoryPtr refTrajectory, int n = 3) const;
    std::vector<TrajectoryPtr> getClosestTrajectorySpeed(TrajectoryPtr refTrajectory, int n = 3) const;
private:
    // Get N trajectories from the map whose keys are closer to the value
    std::vector<TrajectoryPtr> getClosestTrajectories(const std::multimap<double, TrajectoryPtr>& trajectoryMap, TrajectoryPtr refTrajectory, double keyValue, int n = 3) const;

    std::vector<TrajectoryPtr> m_trajectories;
    std::multimap<double, TrajectoryPtr> m_lengthTrajectoryMap;
    std::multimap<double, TrajectoryPtr> m_speedTrajectoryMap;
};