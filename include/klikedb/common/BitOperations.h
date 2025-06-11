#ifndef BIT_OPERATIONS_H
#define BIT_OPERATIONS_H

#include <cstddef>
#include <cstdint>

inline void set_bit(std::uint8_t* bitmap, std::size_t i);
inline void clear_bit(std::uint8_t* bitmap, std::size_t i);
inline bool is_set(const std::uint8_t* bitmap, std::size_t i);

#endif
