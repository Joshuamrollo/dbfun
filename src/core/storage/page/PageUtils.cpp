#include <klikedb/common/DataType.h>

inline bool isMinMaxSupported(DataType type) {
    switch (type) {
        case DataType::INT32:
        case DataType::INT64:
            return true;
        default:
            return false;
    }
}
