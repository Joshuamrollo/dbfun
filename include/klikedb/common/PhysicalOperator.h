#ifndef PHYSICAL_OPERATOR_H
#define PHYSICAL_OPERATOR_H

namespace klikedb {

enum class PhysicalOperatorType {
    PHYSICAL_TABLE_SCAN,
    PHYSICAL_PROJECTION,
    PHYSICAL_INSERT,
    PHYSICAL_CREATE
};

class PhysicalOperator {

};

class PhysicalTableScan : public PhysicalOperator {

};

class PhysicalProjection : public PhysicalOperator {

};

class PhysicalInsert : public PhysicalOperator {

};

class PhysicalCreate : public PhysicalOperator {

};


}

#endif