#include <iostream>
#include <coroutine>
#include <vector>
#include <atomic>
#include <mutex>
#include <thread>
#include <chrono>
#include <future>

// A simple coroutine task class
class MyTask {
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    MyTask(handle_type h) : coro(h) {}
    ~MyTask() { if (coro) coro.destroy(); }

    void resume() {
        if (coro && !coro.done()) {
            coro.resume();
        }
    }

    bool is_done() const { 
        return coro.done(); 
    }

    struct promise_type {
        MyTask get_return_object() { return MyTask{handle_type::from_promise(*this)}; }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::exit(1); }
    };

private:
    handle_type coro;
};

// Simulating an async task with a delay and thread-safe access to a shared counter
MyTask async_task(int id, std::mutex& mtx, std::atomic<int>& counter) {
    std::cout << "Task " << id << " started.\n";
    
    // Simulate work with a sleep (delay)
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Safely update the shared counter using a mutex
    {
        std::lock_guard<std::mutex> lock(mtx);
        counter++;
        std::cout << "Task " << id << " finished.\n";
    }

    co_return;
}

int main() {
    std::mutex mtx;  // Mutex to protect shared resources
    std::atomic<int> counter{0};  // Atomic counter to track completed tasks
    std::vector<std::future<void>> futures;

    // Launch multiple tasks concurrently using std::async (to simulate parallel execution)
    for (int i = 1; i <= 99; ++i) {
        futures.push_back(std::async(std::launch::async, [i, &mtx, &counter]() {
            MyTask task = async_task(i, mtx, counter);
            task.resume();  // Start the coroutine
            while (!task.is_done()) {  // Use the public is_done() method to check coroutine status
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate yielding
            }
        }));
    }

    // Wait for all futures to finish (i.e., all coroutines to complete)
    for (auto& future : futures) {
        future.get();
    }

    std::cout << "All tasks completed.\n";
    return 0;
}
