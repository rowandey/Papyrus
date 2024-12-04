#include <iostream>
#include <coroutine>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>

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

    bool is_done() const { return coro.done(); }

    struct promise_type {
        MyTask get_return_object() {
            return MyTask{handle_type::from_promise(*this)};
        }

        std::suspend_always initial_suspend() { return {}; }   // Suspend at the start of the coroutine
        std::suspend_always final_suspend() noexcept { return {}; } // Suspend at the end of the coroutine
        void return_void() {}  // No return value
        void unhandled_exception() { std::exit(1); }  // Handle exceptions (abort if any occur)
    };

private:
    handle_type coro;
};

// Coroutine that simulates a task by sleeping for a given number of seconds
MyTask async_task(int id, int delay_seconds) {
    std::cout << "Task " << id << " started.\n";

    // Simulate work by sleeping for the specified delay
    std::this_thread::sleep_for(std::chrono::seconds(delay_seconds));

    std::cout << "Task " << id << " finished.\n";

    co_return;  // Return control to the caller (coroutine is done)
}

int main() {
    const int num_tasks = 5;  // Number of concurrent tasks
    std::vector<std::thread> threads;  // Threads to execute the coroutines
    std::vector<MyTask> tasks;  // Store coroutines

    // Launch several coroutines concurrently, each with a different sleep duration
    for (int i = 0; i < num_tasks; ++i) {
        tasks.push_back(async_task(i, i + 1));  // Task i will sleep for (i + 1) seconds

        // Launch a thread for each task to simulate concurrent execution
        threads.push_back(std::thread([&tasks, i]() {
            tasks[i].resume();  // Start the coroutine
            while (!tasks[i].is_done()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate yielding
            }
        }));
    }

    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "All tasks completed.\n";
    return 0;
}
