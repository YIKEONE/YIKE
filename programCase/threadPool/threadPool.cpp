/*
    因为程序边运行边创建线程是比较耗时的，所以我们通过池化的思想：在程序开始运行前创建多个线程，这样，程序在运行时，
    只需要从线程池中拿来用就可以了．大大提高了程s序运行效率．一般线程池都会有以下几个部分构成：
    1. 线程池管理器（ThreadPoolManager）: 用于创建并管理线程池，也就是线程池类
    2. 工作线程（WorkThread）: 线程池中线程
    3. 任务队列task: 用于存放没有处理的任务。提供一种缓冲机制。
    4. append：用于添加任务的接口
*/

#include <condition_variable>
#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>

const int MAX_THREADS = 100;

template <typename T>
class ThreadPool {
private:
    std::mutex queueMutex_;
    std::condition_variable conditon_;
    bool stop_;
    std::vector<std::thread> workThreads_;

    static void *worker(void);
    void run();
public:
    ThreadPool(int threadNum = 1);
    ~ThreadPool();

    bool Append(T *request);
    
    std::queue<T> taskQueues_;
};

template <typename T>
ThreadPool<T>::ThreadPool(int num) : stop_(false)
{
    if(num <= 0 || num > MAX_THREADS) {
        throw std::exception();
    }
    for(int i = 0; i < num; i++) {
        std::cout << "create thread num is: " << num << std::endl;
        workThreads_.emplace_back(worker, this);
    }
}

template <typename T>
inline ThreadPool<T>::~ThreadPool()
{
    std::unique_lock<std::mutex> lock(queueMutex_);
    stop_ = true;
    conditon_.notify_all();
    for(auto &thread : workThreads_) {
        if(thread.joinable()) {
            thread.join();
        }
    }
}

template <typename T>
bool ThreadPool<T>::Append(T *request)
{
    std::lock_guard<std::mutex> lock(queueMutex_);
    // queueMutex_.lock();
    taskQueues_.push(request);
    conditon_.notify_one();
    return true;
}

template <typename T>
void ThreadPool<T>::run()
{
    while (!stop_) {
        std::unique_lock<std::mutex> lock(this->queueMutex_);
        this->conditon_.wait(lock, [this] { return !taskQueues_.empty(); });
        if(this->taskQueues_.empty()) {
            std::cout << "没有任务~" << std::endl;
            continue;
        } else {
            T *request = taskQueues_.front();
            taskQueues_.pop();
            if(request) {
                request->process();
            }
        }
    }

}

class Task
{
private:
    
public:
    void process()
    {
        int num = 100;
        std::cout << "num is: " << num * num << std::endl;
    }
};


int main() {
    ThreadPool<Task> threadPool(6);

    while (1) {
        Task *task = new Task();
        threadPool.Append(task);
        std::cout << "添加任务数量: " << threadPool.taskQueues_.size() << std::endl;
        delete task;
    }
}
