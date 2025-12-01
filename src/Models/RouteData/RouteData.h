#ifndef ROUTEDATA_H
#define ROUTEDATA_H

#include <string>
using namespace std;

class RouteData {
public:
    string origin;
    string destination;
    string date;
    string departureTime;
    string arrivalTime;
    int cost;
    string company;

    RouteData(const string& orig,
              const string& dest,
              const string& d,
              const string& dep,
              const string& arr,
              int c,
              const string& comp);

    RouteData();
};

#endif
