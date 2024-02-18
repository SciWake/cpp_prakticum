#pragma once

#include <chrono>
#include <iostream>
#include <string>

class LogDuration {
public:
    // заменим имя типа std::chrono::steady_clock
    // с помощью using для удобства
    using Clock = std::chrono::steady_clock;

    LogDuration() {
    }

    LogDuration(const std::string& message) 
        :message_(message)
    {
    }

    ~LogDuration() {
        using namespace std::chrono;
        using namespace std::literals;

        const auto end_time = Clock::now();
        const auto dur = end_time - start_time_;
        std::cerr << message_ << ": "s << duration_cast<milliseconds>(dur).count() << " ms"s << std::endl;
    }

private:
    const Clock::time_point start_time_ = Clock::now();
    std::string message_;
};


#define PROFILE_CONCAT_INTERNAL(X, Y) X ## Y
#define PROFILE_CONCAT(X, Y) PROFILE_CONCAT_INTERNAL(X, Y)
#define UNIQUE_VAR_NAME_PROFILE PROFILE_CONCAT(profileGuard, __LINE__)
#define LOG_DURATION(x) LogDuration UNIQUE_VAR_NAME_PROFILE(x)

// 1] LOG_DURATION("Total"s);
// Макроc LOG_DURATION раскрывается в LogDuration UNIQUE_VAR_NAME_PROFILE("Total"s). 

// 2] UNIQUE_VAR_NAME_PROFILE раскрывается в PROFILE_CONCAT(profileGuard, __LINE__)
// и в итоге у нас получается LogDuration PROFILE_CONCAT(profileGuard, __LINE__)("Total"s)

// 3] PROFILE_CONCAT раскрывается в PROFILE_CONCAT_INTERNAL(X, Y) 
// и в итоге получается LogDuration PROFILE_CONCAT_INTERNAL(profileGuard, 67)("Total"s)

// 4] Затем макрос PROFILE_CONCAT_INTERNAL раскрывается 
// и просто склеивает переданные ему строки profileGuard и 67

// В итоге после всех подстановок у нас получается LogDuration profileGuard67("Total"s)
// То есть мы создали переменную с уникальным именем profileGuard67 типа LogDuration 
// и передали ей в конструктор строку "Total"s

/*
Такого трюка для определения UNIQUE_VAR_NAME_PROFILE — макроса, 
генерирующего уникальное имя переменной — требуют довольно запутанные правила раскрытия в C++. 
Параметры макроса при склеивании заменяются на то, что в них было подставлено без изменения. 
Те параметры, которые не склеиваются, раскрываются, то есть полностью подставляются до того момента, 
пока в них не останется макросов. Чтобы достичь желаемого, нужно, 
чтобы __LINE__ побывал параметром два раза: в первый раз он раскроется в номер строки, 
во второй раз номер строки приклеится к имени переменной.
*/