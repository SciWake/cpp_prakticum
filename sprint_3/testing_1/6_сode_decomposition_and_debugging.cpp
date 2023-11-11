/* ЗАГОТОВКА КОДА
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    int q;
    cin >> q;

    map<string, vector<string>> buses_to_stops, stops_to_buses;

    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "NEW_BUS"s) {
            string bus;
            cin >> bus;
            int stop_count;
            cin >> stop_count;
            vector<string>& stops = buses_to_stops[bus];
            stops.resize(stop_count);
            for (string& stop : stops) {
                cin >> stop;
                stops_to_buses[stop].push_back(bus);
            }

        } else if (operation_code == "BUSES_FOR_STOP"s) {
            string stop;
            cin >> stop;
            if (stops_to_buses.count(stop) == 0) {
                cout << "No stop"s << endl;
            } else {
                bool is_first = true;
                for (const string& bus : stops_to_buses[stop]) {
                    if (!is_first) {
                        cout << " "s;
                    }
                    is_first = false;
                    cout << bus;
                }
                cout << endl;
            }

        } else if (operation_code == "STOPS_FOR_BUS"s) {
            string bus;
            cin >> bus;
            if (buses_to_stops.count(bus) == 0) {
                cout << "No bus"s << endl;
            } else {
                for (const string& stop : buses_to_stops[bus]) {
                    cout << "Stop "s << stop << ":"s;
                    if (stops_to_buses[stop].size() == 1) {
                        cout << " no interchange"s;
                    } else {
                        for (const string& other_bus : stops_to_buses[stop]) {
                            if (bus != other_bus) {
                                cout << " "s << other_bus;
                            }
                        }
                    }
                    cout << endl;
                }
            }

        } else if (operation_code == "ALL_BUSES"s) {
            if (buses_to_stops.empty()) {
                cout << "No buses"s << endl;
            } else {
                for (const auto& bus_item : buses_to_stops) {
                    cout << "Bus "s << bus_item.first << ":"s;
                    for (const string& stop : bus_item.second) {
                        cout << " "s << stop;
                    }
                    cout << endl;
                }
            }
        }
    }

    return 0;
}
*/


#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};


istream& operator>>(istream& is, Query& q) {
    string operation_code;
    is >> operation_code;
    if (operation_code == "NEW_BUS"s) {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int count_stops = 0;
        is >> count_stops;
        q.stops.resize(count_stops);
        for (string& stop : q.stops) {
            is >> stop;
        } 
    } else if (operation_code == "BUSES_FOR_STOP"s) {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    } else if (operation_code == "STOPS_FOR_BUS"s) {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    } else if (operation_code == "ALL_BUSES"s) {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    // Наполните полями эту структуру
    vector<string> buses;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    if (r.buses.empty()) {
        os << "No stop"s << endl;
    } else {
        bool is_first = true;
        for (const string& bus : r.buses) {
            if (!is_first) {
                os << " "s;
            }
            is_first = false;
            os << bus;
        }
        os << endl;
    }
    return os;
}

struct StopsForBusResponse {
    // Наполните полями эту структуру
    vector<string> stops;
    string bus;
    map<string, vector<string>> stops_to_buses;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    if (r.stops.empty()) {
        os << "No bus"s << endl;
    } else {
        for (const string& stop : r.stops) {
            os << "Stop "s << stop << ":"s;
            if (r.stops_to_buses.at(stop).size() == 1) {
                os << " no interchange"s;
            } else {
                for (const string& other_bus : r.stops_to_buses.at(stop)) {
                    if (r.bus != other_bus) {
                        os << " "s << other_bus;
                    }
                }
            }
            os << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    // Наполните полями эту структуру
    map<string, vector<string>> buses_to_stops;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    if (r.buses_to_stops.empty()) {
        os << "No buses"s << endl;
    } else {
        for (const auto& bus_item : r.buses_to_stops) {
            os << "Bus "s << bus_item.first << ":"s;
            for (const string& stop : bus_item.second) {
                os << " "s << stop;
            }
            os << endl;
        }
        }
    return os;
}

class BusManager {
private:
    map<string, vector<string>> buses_to_stops_, stops_to_buses_;
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // Реализуйте этот метод
        buses_to_stops_[bus] = stops;
        for (const string& stop: stops) {
            stops_to_buses_[stop].push_back(bus);
        }
    }
    // BusesForStopResponse - от данной структуры можно избавиться, 
    // просто занимает память. Можно использовать перегрузку для вывода.
    // для этого можно вернуть stops_to_buses_.at(stop)
    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Реализуйте этот метод
        BusesForStopResponse response;
        if (stops_to_buses_.count(stop) != 0) {
            response.buses = stops_to_buses_.at(stop);
        }
        return response;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Реализуйте этот метод
        StopsForBusResponse response;
        if (buses_to_stops_.count(bus) != 0) {
            response.stops = buses_to_stops_.at(bus);
            response.bus = bus;
            response.stops_to_buses = stops_to_buses_;
        }
        return response;
    }

    AllBusesResponse GetAllBuses() const {
        // Реализуйте этот метод
        AllBusesResponse response;
        response.buses_to_stops = buses_to_stops_;
        return response;
    }
};

// Реализуйте функции и классы, объявленные выше, чтобы эта функция main
// решала задачу "Автобусные остановки"

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
        
    }
}