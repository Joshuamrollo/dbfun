#ifndef REWRITER_H
#define REWRITER_H

#include "klikedb/common/LogicalOperator.h"

namespace klikedb {

class Rewriter {
public:
    Rewriter();
    void rewrite(std::unique_ptr<LogicalOperator>& logical_plan_head);

private:

};
    
}

#endif