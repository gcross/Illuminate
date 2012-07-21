// Includes {{{
#include <boost/make_shared.hpp>

#include "illuminate/runners.hpp"
#include "illuminate/test_worker_group.hpp"
// }}}

// Usings {{{
using boost::make_shared;
using boost::mutex;
using boost::optional;
using boost::unordered_map;

using std::vector;
// }}}

namespace Illuminate {

// class TestWorkerGroup {{{
TestWorkerGroup::TestWorkerGroup( // {{{
    unsigned int const number_of_workers,
    TestResultFetcher fetchResult,
    optional<vector<unsigned int> const&> maybe_test_ids
)
    : queue(new std::queue<TestTask>)
    , queue_mutex(new mutex)
    , futures(make_shared<unordered_map<unsigned int,TestFuture> >())
{
    if(maybe_test_ids) {
        enqueueSelectedTests(queue,futures,*maybe_test_ids);
    } else {
        enqueueAllTests(queue,futures);
    }
    for(unsigned int i = 0; i < number_of_workers; ++i) {
        workers.create_thread(TestWorker(queue,queue_mutex,fetchResult));
    }
} // }}}
TestWorkerGroup::~TestWorkerGroup() { // {{{
    workers.interrupt_all(); 
} // }}}
// }}}

}
