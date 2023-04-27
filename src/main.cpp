#include "comparator.hpp"
#include <iostream>

TrajectoryComparator comparator;
TrajectoryPtr referenceTrajectory;

void printSummary()
{
    int selection;
    std::cout << "------> Priority (1. Index | 2. Length | 3. Speed) ";
    std::cin >> selection;

    char c = 0;
    std::cout << "------> Verbose (Y=yes / otherwise=No) ";
    std::cin >> c;
    c = std::toupper(c);
    bool verbose = (c == 'Y');

    switch (selection)
    {
        case 1:
            comparator.summary(verbose);
            break;
        case 2:
            comparator.summaryLength(verbose);
            break;
        case 3:
            comparator.summarySpeed(verbose);
            break;
        default:
            comparator.summary(verbose);
            break;
    }
}

void printReferenceTrajectory()
{
    if (!referenceTrajectory)
    {
        std::cerr << "No reference trajectory available!" << std::endl;
    }
    else
    {
        std::cout << "---------REFERENCE---------" << std::endl;
        std::cout << referenceTrajectory->toString(true) << std::endl;
    }
}

void getReferenceFromList()
{
    int index;
    std::cout << "Index? ";
    std::cin >> index;
    referenceTrajectory = comparator.trajectory(index);
    if (!referenceTrajectory)
    {
        std::cerr << "Invalid index!" << std::endl;
    }
}

void getReferenceFromManualInput()
{
    referenceTrajectory = std::make_shared<Trajectory>();
    referenceTrajectory->initFromCLI();
}

void getClosestTrajectoriesInLengthToReference()
{
    if (!referenceTrajectory)
    {
        std::cerr << "No reference trajectory available!" << std::endl;
    }
    else
    {
        int n;
        std::cout << "N? ";
        std::cin >> n;
        auto closest = comparator.getClosestTrajectoryLength(referenceTrajectory, n);
        std::cout << "---------RESULT---------" << std::endl;
        int count = 0;
        for (auto closeTrajectory : closest)
        {
            std::cout << "--- Trajectory " << count << " ---" << std::endl;
            std::cout << closeTrajectory->toString() << std::endl;
            ++count;
        }
    }
}

void getClosestTrajectoriesInSpeedToReference()
{
    if (!referenceTrajectory)
    {
        std::cerr << "No reference trajectory available!" << std::endl;
    }
    else
    {
        int n;
        std::cout << "N? ";
        std::cin >> n;
        auto closest = comparator.getClosestTrajectorySpeed(referenceTrajectory, n);
        std::cout << "---------RESULT---------" << std::endl;
        int count = 0;
        for (auto closeTrajectory : closest)
        {
            std::cout << "--- Trajectory " << count << " ---" << std::endl;
            std::cout << closeTrajectory->toString() << std::endl;
            ++count;
        }
    }
}

int main()
{
    std::string pathString;
    
    bool isValid = false;
    do
    {
        std::cout << "Import from file. Path? ";
        std::cin >> pathString;
    } while (!comparator.fetchFromFile(pathString));
    
    bool isTerminated{false};
    do
    {
        int input;
        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
        std::cout << "----------------- Command list -----------------" << std::endl;
        std::cout << "0. QUIT." << std::endl;
        std::cout << "1. Print summary of the trajectory list." << std::endl;
        std::cout << "2. Print summary of the reference trajectory." << std::endl;
        std::cout << "3. Select a reference trajectory from the list." << std::endl;
        std::cout << "4. Select a reference trajectory from manual input." << std::endl;
        std::cout << "5. Get N closest trajectories in length compared to the reference trajectory" << std::endl;
        std::cout << "6. Get N closest trajectories in speed compared to the reference trajectory" << std::endl;
        std::cout << ">> What do you want to do? Enter command index: ";
        std::cin >> input;
        std::cout << ">>>> COMMAND RESULT <<<<" << std::endl;
        switch (input)
        {
        case 1:
            printSummary();
            break;
        case 2:
            printReferenceTrajectory();
            break;
        case 3:
            getReferenceFromList();
            break;
        case 4:
            getReferenceFromManualInput();
            break;
        case 5:
            getClosestTrajectoriesInLengthToReference();
            break;
        case 6:
            getClosestTrajectoriesInSpeedToReference();
            break;
        default:
            isTerminated = true;
            break;
        }

        std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    } while (!isTerminated);
    
    return 0;
}