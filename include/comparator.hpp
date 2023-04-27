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
    // Print summary of trajectories (priority: index)
    void summary(bool verbose = false);
    // Print summary of trajectories (priority: length)
    void summaryLength(bool verbose = false);
    // Print summary of trajectories (priority: speed)
    void summarySpeed(bool verbose = false);

    // Get trajectory given an index
    TrajectoryPtr trajectory(int index);

    // Fetch trajectory from file and compute their metrics
    bool fetchFromFile(fs::path path);

    // Add a trajectory to the comparator
    void addTrajectory(TrajectoryPtr trajectory);

    // Get closest trajectories given metric
    std::vector<TrajectoryPtr> getClosestTrajectoryInLength(TrajectoryPtr refTrajectory, int n = 3) const;
    std::vector<TrajectoryPtr> getClosestTrajectoryInSpeed(TrajectoryPtr refTrajectory, int n = 3) const;
private:
    // Get N trajectories from the map whose keys are closer to a given key value (excluding the refTrajectory)
    std::vector<TrajectoryPtr> getClosestTrajectories(const std::multimap<double, TrajectoryPtr>& trajectoryMap, TrajectoryPtr refTrajectory, double keyValue, int n = 3) const;

    std::vector<TrajectoryPtr> m_trajectories;
    std::multimap<double, TrajectoryPtr> m_lengthTrajectoryMap;
    std::multimap<double, TrajectoryPtr> m_speedTrajectoryMap;
};