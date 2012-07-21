#include "illuminate/test_result_fetchers/future.hpp"

namespace Illuminate {

FutureTestResultFetcher::FutureTestResultFetcher(TestFutures const& futures)
    : futures(futures)
{ }

TestResult FutureTestResultFetcher::operator()(unsigned int test_id) const {
    return (*futures)[test_id]->get();
}

}
