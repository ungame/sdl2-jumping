#ifndef TIME_H
#define TIME_H

#include <chrono>
#include <string>
#include <ctime>

class Time
{
    public:
        Time() { _time = now(); };

        inline std::chrono::time_point<std::chrono::system_clock> time() { return _time; }

        inline static std::chrono::time_point<std::chrono::system_clock> now() 
        { 
            return std::chrono::system_clock::now(); 
        }

        inline static double since(Time* t) 
        {
            std::chrono::duration<double> elapsed = now() - t->time();
            
            return elapsed.count();
        }

        inline std::string toString() const
        {
            std::time_t t = std::chrono::system_clock::to_time_t(_time);
            auto lc = localtime(&t);
            char t_str[] = {0};
            strftime(t_str, 100, "%Y-%m-%d %H:%M:%S", lc);
            return std::string(t_str);
        }

    private:
        std::chrono::time_point<std::chrono::system_clock> _time;
};

#endif