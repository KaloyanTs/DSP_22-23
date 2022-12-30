#ifndef __TASK_SOLVER_HPP
#define __TASK_SOLVER_HPP

#include "TrainMap.hpp"
#include "CityMap.hpp"
#include "Box.hpp"

class TaskSolver
{
    void optimize(std::list<Box> &boxes);

public:
    static void a();
    static void b();
    static void c();
    static void total();
};

#endif