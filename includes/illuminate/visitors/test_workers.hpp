//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1827: * @thin test_workers.hpp
//@@language cplusplus

#ifndef ILLUMINATE_VISITORS_TEST_WORKERS_HPP
#define ILLUMINATE_VISITORS_TEST_WORKERS_HPP

//@+<< Includes >>
//@+node:gcross.20101206161648.1828: ** << Includes >>
#include <boost/thread.hpp>
#include <iostream>

#include "illuminate.hpp"
//@-<< Includes >>

namespace Illuminate {

//@+<< Usings >>
//@+node:gcross.20101206161648.1829: ** << Usings >>
using namespace std;
//@-<< Usings >>

//@+others
//@+node:gcross.20101206161648.1830: ** class TestWorkers
class TestWorkers {
public:
    TestWorkers(int number_of_workers, Suite& suite=getRoot());
protected:
    thread_group workers;
};
//@-others

}

#endif
//@-leo
