#include "illuminate/visitors/result.hpp"

namespace Illuminate {

ResultVisitor::ResultVisitor(TestResultFetcher const& fetchTestResult)
  : fetchTestResult(fetchTestResult)
  , number_of_failed_tests(0)
{}

void ResultVisitor::test(Test const& test) {
    if(test.skipped) {
        testSkipped(test);
    } else {
        testStarted(test);
        TestResult result = fetchTestResult(test.id);
        if(result->size() == 0) {
            testPassed(test);
        } else {
            ++number_of_failed_tests;
            testFailed(test,*result);
        }
    }
}

}
