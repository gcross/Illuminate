//@+leo-ver=5-thin
//@+node:gcross.20101206161648.1606: * @file main.cpp
//@@language cplusplus
//@+<< License >>
//@+node:gcross.20110222175650.1654: ** << License >>
//@+at
// ISC License (http://www.opensource.org/licenses/isc-license)
// 
// Copyright (c) 2011, Gregory Crosswhite <gcrosswhite@gmail.com>
// 
// Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.
// 
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//@@c
//@-<< License >>

//@+<< Includes >>
//@+node:gcross.20101206161648.1607: ** << Includes >>
#include <boost/lambda/lambda.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

#include "illuminate.hpp"
#include "illuminate/runners.hpp"
#include "illuminate/slave.hpp"

namespace lambda = boost::lambda;
using boost::none;
namespace po = boost::program_options;

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios_base;
using std::max;
using std::ofstream;
using std::ostream;
using std::string;
using std::vector;

using namespace Illuminate;
//@-<< Includes >>

//@+others
//@+node:gcross.20101206161648.1609: ** main
int main(int argc, char** argv) {
    getRoot().sort();
    string const slave_mode("--slave-mode");
    if(find_if(argv,argv+argc,slave_mode == lambda::_1) != argv+argc) {
        std::cerr << "Running in slave mode!" << std::endl;
        runInSlaveMode();
        return 0;
    }

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message and then exit\n")
        ("list,l", "output the list of tests and then exit\n")
        ("color,c", po::value<Coloring>(),
            "coloring style\n"
            "\n"
            "The possible values of this option are:\n"
            "    ansi:  ansi color codes (default for console output)\n"
            "    plain: no coloring, plain text (default for file output)\n"
            "\n"
        )
        ("fatal,f", po::value<AbortMode>(),
            "fatality mode\n"
            "\n"
            "The possible values of this option are:\n"
            "    none:       no problems are fatal (default)\n"
            "    exceptions: exceptions are fatal\n"
            "    all:        all problems are fatal\n"
            "\n"
            "The purpose of this option is to allow you cause the test program to die when it encounters a particular type of problem so that you can more easily examine the stack trace in a debugger.\n"
        )
        ("workers,n", po::value<int>()->default_value(1),
            "number of parallel workers\n\n"
            "If this value is positive, then it specifies the number of processes (outside of the main process) to use for running tests.  Using separate processes involves slightly more overhead, but it is safer in the case where either your code is not thread-safe or where bugs cause tests to crash the process with something like a segmentation fault rather than merely throwing an exception or failing a test invariant.\n\n"
            "If this value is zero then it is equivalent to having specified +N (that is, use N processes) where N is the detected number of hardware capabilities.\n\n"
            "If this value is negative, then it specifies the number of threads (within the main process) to use for running tests.  Note that using multiple threads rather than multiple processes can cause problems if your code (or a library on which it relies) is not thread-safe.\n\n"
            "In the special case where this value is -1, then no threads are spawned but rather the tests are run in the main thread in order to make life easier when using a debugger.\n\n"
            "This value defaults to +1 (that is, a single process outside the main process) if not otherwise specified.\n"
        )
        ("output,o", po::value<string>(),
            "output file\n\n"
            "This option causes the output of running the tests to be written to the specified file rather than to standard output.  (It also automatically disables the use of ANSI color codes unless you explicitly enable them.)\n"
        )
        ("id,i", po::value<vector<unsigned int> >()->composing(),
            "test ids to run\n\n"
            "If this value is specified one or more times, then instead of running the whole suite the tests with the given numbers will be run.\n\n"
        )
    ;

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        ifstream config_file("test.cfg");
        po::store(po::parse_config_file(config_file, desc), vm);
    } catch(...) {
        cout << desc << "\n";
        cout << "Options may also be specified in 'test.cfg'" << endl;
        return 1;
    }

    if (vm.count("help")) {
        cout << desc << "\n";
        cout << "Options may also be specified in 'test.cfg'" << endl;
        return 1;
    }

    ColorCodes const& color_codes
        = (vm.count("color") == 0
            ? (vm.count("output") == 0
                ? ColorCodes::ANSI
                : ColorCodes::plain
              )
            : (vm["color"].as<Coloring>() == ANSI_COLORING
                ? ColorCodes::ANSI
                : ColorCodes::plain
              )
          );

    ofstream file;
    if(vm.count("output") > 0) {
        string filename = vm["output"].as<string>();
        file.open(filename.c_str(),ios_base::out | ios_base::trunc);
    }

    ostream& out =
        vm.count("output") == 0
            ? cout
            : file
    ;

    if(vm.count("list")) {
        printTestTree(color_codes,out);
        return 1;
    }

    if (vm.count("fatal")) {
        Test::abort_mode = vm["fatal"].as<AbortMode>();
    }

    if(vm.count("id")) {
        runTestsWithIdsAndPrintResults(vm["id"].as<vector<unsigned int> >(),color_codes,out);
        return 0;
    }

    int number_of_workers = vm["workers"].as<int>();

    TestResultFetcher fetchResult;

    if(number_of_workers < 0) {
        number_of_workers = -number_of_workers;
        fetchResult = Test::run;
    } else {
        fetchResult = SlaveProcess(argv[0]);
    }

    if(0 == number_of_workers) number_of_workers = max(boost::thread::hardware_concurrency(),1u);

    if(1 == number_of_workers)
        runTestsAndPrintResults(color_codes,out,fetchResult);
    else
        runTestsInWorkersAndPrintResults(number_of_workers,color_codes,out,fetchResult);

    return 0;
}
//@-others
//@-leo
