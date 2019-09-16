//
// Created by looperX on 2019-06-24.
//

#ifndef RECIPES_TIMERCPP_H
#define RECIPES_TIMERCPP_H

#include <iostream>
#include <thread>
#include <chrono>

class Timer {
    bool clear = false;

public:
    template<typename Function>
    void setTimeout(Function function, int delay);

    template<typename Function>
    void setInterval(Function function, int interval);
    void stop();
    std::time_t getTimeStamp();
};


std::time_t getTimeStamp()
{
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now());
    auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
    std::time_t timestamp = tmp.count();
    //std::time_t timestamp = std::chrono::system_clock::to_time_t(tp);
    return timestamp;
}

template<typename Function>
void Timer::setTimeout(Function function, int delay) {
    this->clear = false;
    std::thread t([=]() {
        if(this->clear) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if(this->clear) return;
        function();
    });
    t.detach();
}

template<typename Function>
void Timer::setInterval(Function function, int interval) {
    this->clear = false;
    std::thread t([=]() {
        while(true) {
            if(this->clear) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if(this->clear) return;
            function();
        }
    });
    t.detach();
}

void Timer::stop() {
    this->clear = true;
}
//
//#include <iostream>
//#include <string>
//#include <thread>
//#include <mutex>
//#include <condition_variable>
//#include "timer/timercpp.h"
//
//using namespace std;
//
//std::mutex m;
//std::condition_variable cv;
//std::string data;
//bool ready = false;
//bool processed = false;
//
//void worker_thread()
//{
//    // 等待直至 main() 发送数据
//    std::unique_lock<std::mutex> lk(m);
////    cv.wait(lk, []{return ready;}); 等值于以下：
//    while (!ready)
//    {
//        cv.wait(lk);
//    }
//
//    // 等待后，我们占有锁。
//    std::cout << "Worker thread is processing data\n";
//    data += " after processing";
//
//    // 发送数据回 main()
//    processed = true;
//    std::cout << "Worker thread signals data processing completed\n";
//
//    // 通知前完成手动解锁，以避免等待线程才被唤醒就阻塞（细节见 notify_one ）
//    lk.unlock();
//    cv.notify_one();
//}
//
//int main()
//{
//    Timer t = Timer();
//
//    t.setInterval([&]() {
//        cout << "Hey.. After each 1s..." << endl;
//    }, 1000);
//
//    t.setTimeout([&]() {
//        cout << "Hey.. After 5.2s. But I will stop the timer!" << endl;
//        t.stop();
//    }, 5200);
//
//    cout << "I am Timer" <<endl;
//    cout << getTimeStamp() << endl;
//    while(true); // Keep main thread active
//}


#endif //RECIPES_TIMERCPP_H
