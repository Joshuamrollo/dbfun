#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "klikedb/common/LogicalOperator.h"
#include <memory>

namespace klikedb {

// ill fill out this class eventually :p
class Optimizer {
public:
    Optimizer();
    void optimize(std::unique_ptr<LogicalOperator>& logical_plan_head);

private:

};

}

#endif