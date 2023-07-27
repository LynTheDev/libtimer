#include <timer.hpp>

Timer::Timer(bool running, int time, std::function<void()> timer_callback) : running(running), time(time), timed_out(timer_callback) 
{
    if (this->running.load())
    {
        this->timer_thread = std::thread(&Timer::thread_body, this);
    }
}

Timer::~Timer()
{
    this->stop();
}

// Stop the timer and quit the thread
void Timer::stop()
{
    if (this->running.load())
    {
        this->running = false;
        this->timer_notifier.notify_one();
        if (this->timer_thread.joinable())
        {
            this->timer_thread.join();
        }
    }
}

// Start the timer and begin a new thread
void Timer::start()
{
    if(!this->running.load())
    {
        this->running = true;
        this->timer_thread = std::thread(&Timer::thread_body, this);
    }
}

// Use mutex and lock to block the thread until the timer reaches 0
// We do this beause we can stop the time using a notify call
void Timer::thread_body()
{
    std::mutex mtx;
    std::unique_lock<std::mutex> timer_lock(mtx);

    while (this->running.load())
    {
        this->timer_notifier.wait_for(timer_lock, std::chrono::seconds(this->time));
        if (this->running.load() && this->timed_out)
        {
            this->timed_out();
        }
    }
}