#include <cstddef>
#include <cstdint>

// set bit at position i to 1
inline void set_bit(std::uint8_t* bitmap, std::size_t i) {
    bitmap[i / 8] |= (1 << (i % 8));
}

// set bit at position i to 0
inline void clear_bit(std::uint8_t* bitmap, std::size_t i) {
    bitmap[i / 8] &= ~(1 << (i % 8));
}

// if bit at position i is 1 return true else return false
inline bool is_set(const std::uint8_t* bitmap, std::size_t i) {
    return bitmap[i / 8] & (1 << (i % 8));
}
