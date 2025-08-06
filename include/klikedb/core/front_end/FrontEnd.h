#ifndef FRONT_END_H
#define FRONT_END_H

#include "klikedb/core/query_planner/QueryPlanner.h"
#include <string>

namespace klikedb {

class FrontEnd {
public:
    FrontEnd(QueryPlanner& planner);
    // validates SQL -> sends statements to planner -> gets results back and prints
    void processQuery(std::string input);

private:
    void displayResults();
    QueryPlanner& _planner;
};

}

#endif