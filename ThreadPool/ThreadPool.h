//
// Created by loohan on 2019/2/14.
//

#ifndef RECIPES_THREADPOOL_H
#define RECIPES_THREADPOOL_H

#include <iostream>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

#include "boost/asio.hpp"


class ThreadPool
{
public:

    ThreadPool(int threadNums)
        : work_guard_(boost::asio::executor_work_guard(io_context_))
    {
            workers_.resize(threadNums);
            for (int i = 0; i < threadNums; ++i)
            {
                    workers_.emplace_back(boost::asio::io_service::run(), &io_context_);
            }
    }

    ~ThreadPool()
    {
            io_context_.stop();

            for (auto worker : workers_)
            {
                    worker.join();
            }
    }

    template <typename T>
    void enqueueTask(T task)
    {
            boost::asio::post(task);
    }


private:
    std::vector<std::thread> workers_;
    boost::asio::io_context io_context_;

    typedef boost::asio::io_context::executor_type ExecutorType;
    boost::asio::executor_work_guard<ExecutorType> work_guard_;
};


std::mutex mtx;
int main(int argc, int argv*[])
{
        ThreadPool pool(4);

        for (int i = 0; i < 8; ++i)
        {
               pool.enqueueTask([]
               {
                        {
                                std::lock_guard<std::mutex> lk(mtx);
                                std::cout << "i is: " << i << std::endl;
                        }

                        std::this_thread::sleep_for(std::chrono::seconds(1)); // sleep 1 s

                        {
                        std::lock_guard<std::mutex> lk(mtx);
                        std::cout << "i is: " << i << std::endl;
                        }

                });
        }


}

#endif //RECIPES_THREADPOOL_H
