#include "RouteData.h"
using namespace std;

RouteData::RouteData(const string& orig,
                     const string& dest,
                     const string& d,
                     const string& dep,
                     const string& arr,
                     int c,
                     const string& comp)
    : origin(orig), destination(dest), date(d), departureTime(dep),
      arrivalTime(arr), cost(c), company(comp) {}

RouteData::RouteData()
    : origin(""), destination(""), date(""), departureTime(""),
      arrivalTime(""), cost(0), company("") {}
