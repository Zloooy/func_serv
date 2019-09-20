#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H
#include <queue>
#include <iostream>
#include <mutex>
#include <condition_variable>
template <typename T>
class ThreadSafeQueue
{
    std::queue<T> queue;
    std::condition_variable data_ready;
    std::mutex m;
    public:
    ThreadSafeQueue();
    T wait_and_get_front();
    void push(T);
    void clear();
};
template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue()
{
    std::cout << "Creating queue" << std::endl;
    std::cout << "notifying" << std::endl;
}
template <typename T>
void ThreadSafeQueue<T>::push(T element)
{
    std::cout << "start pushing element" << std::endl;
    auto lk = std::unique_lock<std::mutex>(m);
    std::cout << "took lock" << std::endl;
    bool was_empty = queue.empty();
    queue.push(element);
    std::cout << "notifying" << std::endl;
    lk.unlock();
    if (was_empty) data_ready.notify_one();
    std::cout << "end pushing element" << std::endl;
}
template <typename T>
T ThreadSafeQueue<T>::wait_and_get_front()
{
    T result;
    std::cout << "start waiting and getting front" << std::endl;
    auto lk = std::unique_lock<std::mutex>(m);
    std::cout << "acqured lock" << std::endl;
    while(queue.empty()){
    data_ready.wait(lk);
    } 
    result = queue.front();
    queue.pop();
    lk.unlock();
    std::cout << "end waiting and getting front" << std::endl;
    return result;
}
template <typename T>
void ThreadSafeQueue<T>::clear()
{
    auto lk = std::unique_lock<std::mutex>(m);
    std::queue<T> q;
    std::swap(queue, q);
}
#endif
