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
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

#include "illuminate.hpp"
#include "illuminate/runners.hpp"

using boost::none;
namespace po = boost::program_options;

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios_base;
using std::ofstream;
using std::ostream;
using std::string;
using std::vector;

using namespace Illuminate;
//@-<< Includes >>

//@+others
//@+node:gcross.20101206161648.1609: ** main
int main(int argc, char** argv) {
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
        ("threads,n", po::value<unsigned int>()->default_value(1),
            "number of threads\n\n"
            "If this value is zero, then the number of threads is equal to the detected number of hardware capabilities.\n\n"
            "If this value is one (the default), then no threads are spawned but rather the tests are run in the main thread (which can make it easier to analyze stack traces).\n\n"
            "Note that using multiple threads can cause problems if your code (or a library on which it relies) is not thread-safe.\n"
        )
        ("output,o", po::value<string>(),
            "number of threads\n\n"
            "If this value is zero, then the number of threads is equal to the detected number of hardware capabilities.\n\n"
            "If this value is one (the default), then no threads are spawned but rather the tests are run in the main thread (which can make it easier to analyze stack traces).\n\n"
            "Note that using multiple threads can cause problems if your code (or a library on which it relies) is not thread-safe.\n"
        )
        ("id,i", po::value<vector<unsigned int> >()->composing(),
            "test ids to run\n\n"
            "If this value is specified one or more times, then instead of running the whole suite the tests with the given numbers will be run in the main thread.\n\n"
            "Note that if this value is present then the value of -n is ignored.\n"
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

    unsigned int const number_of_threads = vm["threads"].as<unsigned int>();

    switch(number_of_threads) {
        case 0:  runTestsInThreadsAndPrintResults(none,color_codes,out); break;
        case 1:  runTestsAndPrintResults(color_codes,out); break;
        default: runTestsInThreadsAndPrintResults(number_of_threads,color_codes,out); break;
    }

    return 0;
}
//@-others
//@-leo
