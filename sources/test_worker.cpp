// Includes {{{
#include <sstream>

#include "illuminate/test_worker.hpp"
// }}}

// Usings {{{
using boost::lock_guard;
using boost::mutex;
namespace this_thread = boost::this_thread;
using boost::shared_ptr;
// }}}

namespace Illuminate {

// class TestWorker {{{
TestWorker::TestWorker( // {{{
    TestQueue const& queue,
    shared_ptr<mutex> const& queue_mutex,
    TestResultFetcher fetchResult
)
    : queue(queue)
    , queue_mutex(queue_mutex)
    , fetchResult(fetchResult)
{} // }}}
void TestWorker::operator()() { // {{{
    while(!this_thread::interruption_requested()) {
        TestTask task;
        {
            lock_guard<mutex> guard(*queue_mutex);
            if(queue->empty()) {
                return;
            } else {
                task = queue->front();
                queue->pop();
            }
        }
        TestResult result;
        task.second->set_value(fetchResult(task.first));
    }
} // }}}
// }}}

}
