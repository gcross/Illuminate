//@+leo-ver=5-thin
//@+node:gcross.20110809112154.2492: * @file tests-slave.cpp
//@@language cplusplus

//@+<< Includes >>
//@+node:gcross.20110809112154.2498: ** << Includes >>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/assign.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>

#include "illuminate.hpp"
#include "illuminate/slave.hpp"

using Illuminate::Slave;
using Illuminate::slave_sentinel;
using Illuminate::TestResult;

using boost::archive::text_iarchive;
using boost::archive::text_oarchive;
using boost::assign::list_of;

using std::endl;
using std::istringstream;
using std::string;
using std::stringstream;
using std::vector;
//@-<< Includes >>

//@+others
//@+node:gcross.20110809112154.2493: ** construct slave without using it
TEST_CASE(construct_slave_without_using_it) {
    struct : public Slave {
        virtual void initiateConnection() {
            FAIL("initiateConnection() called!");
        }
        virtual boost::optional<int> terminateConnection() {
            FAIL("terminateConnection() called!");
            return boost::none;
        }
        virtual std::istream& getInput() {
            FATALLY_FAIL("getInput() called!");
        }
        virtual std::ostream& getOutput() {
            FATALLY_FAIL("getOutput() called!");
        }
    } slave;
}
//@+node:gcross.20110809112154.2497: ** run test in slave with empty input
TEST_CASE(run_test_in_slave_with_empty_input) {
    struct SlaveHarness: public Slave {
        SlaveHarness() : initiateConnection_called(false) {}
        bool initiateConnection_called;
        stringstream stream;
        virtual void initiateConnection() {
            if(initiateConnection_called) FAIL("initiateConnection() called twice!");
            initiateConnection_called = true;
        }
        virtual boost::optional<int> terminateConnection() {
            FAIL("terminateConnection() called!");
            return boost::none;
        }
        virtual std::istream& getInput() {
            return stream;
        }
        virtual std::ostream& getOutput() {
            return stream;
        }
    } slave;
    try {
        slave(0);
        FAIL("Exception not thrown!");
    } catch(stringstream::failure const& _) {}
    EXPECT_TRUE(slave.stream.eof());
}
//@+node:gcross.20110809112154.2500: ** run test in slave with crashing test
TEST_CASE(run_test_in_slave_with_crashing_test) {
    struct SlaveHarness: public Slave {
        SlaveHarness()
          : initiateConnection_called(false)
          , terminateConnection_called(false)
        {
            stream1 << slave_sentinel << endl
                    << "Hello, world!" << endl
            ;
        }
        bool initiateConnection_called, terminateConnection_called;
        stringstream stream1, stream2;
        virtual void initiateConnection() {
            if(initiateConnection_called) FAIL("initiateConnection() called twice!");
            initiateConnection_called = true;
        }
        virtual boost::optional<int> terminateConnection() {
            if(terminateConnection_called) FAIL("terminateConnection() called twice!");
            terminateConnection_called = true;
            return boost::make_optional(24);
        }
        virtual std::istream& getInput() {
            return stream1;
        }
        virtual std::ostream& getOutput() {
            return stream2;
        }
    } slave;
    TestResult result = slave(42);
    EXPECT_TRUE(slave.stream1.eof());
    EXPECT_TRUE(slave.initiateConnection_called);
    EXPECT_TRUE(slave.terminateConnection_called);
    unsigned int test_id = 0;
    slave.stream2 >> test_id;
    EXPECT_EQ_VAL(test_id,42);
    EXPECT_EQ_VAL(result->size(),1);
    istringstream stream((*result)[0]);
    string s;
    getline(stream,s);
    EXPECT_EQ_VAL("Test caused a crash with error code 24!",s);
    getline(stream,s);
    getline(stream,s);
    getline(stream,s);
    getline(stream,s);
    EXPECT_EQ_VAL("Hello, world!",s);
}
//@+node:gcross.20110809112154.2502: ** run test in slave
TEST_CASE(run_test_in_slave) {
    vector<string> expected_result = list_of("A")("B");
    struct SlaveHarness: public Slave {
        SlaveHarness(vector<string> const& expected_result)
          : initiateConnection_called(false)
          , terminateConnection_called(false)
        {
            stream1 << slave_sentinel << endl
                    << "Hello, world!" << endl
                    << slave_sentinel << endl
            ;
            text_oarchive(stream1) << expected_result;
            stream1 << endl << slave_sentinel << endl;
        }
        bool initiateConnection_called, terminateConnection_called;
        stringstream stream1, stream2;
        virtual void initiateConnection() {
            if(initiateConnection_called) FAIL("initiateConnection() called twice!");
            initiateConnection_called = true;
        }
        virtual boost::optional<int> terminateConnection() {
            if(terminateConnection_called) FAIL("terminateConnection() called twice!");
            terminateConnection_called = true;
            return boost::none;
        }
        virtual std::istream& getInput() {
            return stream1;
        }
        virtual std::ostream& getOutput() {
            return stream2;
        }
    } slave(expected_result);
    TestResult actual_results = slave(42);
    EXPECT_TRUE(slave.initiateConnection_called);
    EXPECT_FALSE(slave.terminateConnection_called);
    unsigned int test_id = 0;
    slave.stream2 >> test_id;
    EXPECT_EQ_VAL(test_id,42);
    EXPECT_TRUE(*actual_results == expected_result);
}
//@-others
//@-leo
