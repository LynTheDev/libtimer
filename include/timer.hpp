#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <functional>

// Base timer class
class Timer
{
private:
    std::thread timer_thread;
    std::atomic_bool running; // Using an atomic bool to avoid bad threading communication
    std::function<void()> timed_out;
    std::condition_variable timer_notifier;

    int time;

    void thread_body();
public:
    Timer(bool running, int time, std::function<void()> timer_callback);
    ~Timer();

    void start();
    void stop();
};