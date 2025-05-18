#include <iostream>
using namespace std;

// Константы
const int SECONDS_IN_MINUTE = 60;
const int MINUTES_IN_HOUR = 60;
const int SECONDS_IN_HOUR = SECONDS_IN_MINUTE * MINUTES_IN_HOUR;
const int SECONDS_IN_DAY = 24 * SECONDS_IN_HOUR;

// Преобразует смещение из формата чч:мм:сс в секунды
int GetTimeOffset(int hours, int minutes, int seconds) {
    return (hours * MINUTES_IN_HOUR + minutes) * SECONDS_IN_MINUTE + seconds;
}

class Time {
public:
    // Устанавливает начальное время
    void SetTime(int hours, int minutes, int seconds) {
        hours_ = hours;
        minutes_ = minutes;
        seconds_ = seconds;
    }

    // Увеличиваем время на заданное смещение
    void Add(int hours, int minutes, int seconds) {
        int current_timestamp = GetTimestamp();
        int offset = GetTimeOffset(hours, minutes, seconds);
        SetTimestamp(current_timestamp + offset);
    }

    // Уменьшаем время на заданное смещение
    void Sub(int hours, int minutes, int seconds) {
        int current_timestamp = GetTimestamp();
        int offset = GetTimeOffset(hours, minutes, seconds);
        SetTimestamp(current_timestamp - offset);
    }

    int GetHours() const { return hours_; }
    int GetMinutes() const { return minutes_; }
    int GetSeconds() const { return seconds_; }

private:

    // Если поля класса имеют примитивный тип, например, int, bool, double или float, их изначальные значения будут неопределёнными. Поэтому лучше задать этим полям некоторое ожидаемое начальное значение. Для класса Time подходящим значением по умолчанию будет полночь (00:00:00).
    int hours_ = 0;
    int minutes_ = 0;
    int seconds_ = 0;

    // Возвращает текущее время в секундах относительно полуночи
    int GetTimestamp() const {
        return GetTimeOffset(hours_, minutes_, seconds_);
    }

    // Задаёт время, используя смещение в секундах с начала суток
    void SetTimestamp(int timestamp) {
        timestamp = ((timestamp % SECONDS_IN_DAY) + SECONDS_IN_DAY) % SECONDS_IN_DAY;

        hours_ = timestamp / SECONDS_IN_HOUR;
        minutes_ = (timestamp / SECONDS_IN_MINUTE) % MINUTES_IN_HOUR;
        seconds_ = timestamp % SECONDS_IN_MINUTE;
    }
};

int main() {
    Time t;
    t.SetTime(23, 59, 45);
    t.Add(0, 0, 15); // прибавит 15 секунд
    // Ожидаемый вывод: 0:0:0
    cout << t.GetHours() << ':' << t.GetMinutes() << ':' << t.GetSeconds() << endl;
    return 0;
}
