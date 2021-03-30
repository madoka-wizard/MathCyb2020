#pragma once

#include <string>
#include <ctime>
#include <cstdint>

namespace blockchain {
class Block {
public:
    Block();

    Block(std::string message, std::uint64_t nounce, std::uint64_t hash);

    Block(const Block &block);

private:
    ~Block();

    /**
     * Parameter for proof-of-work
     */
    std::uint64_t nounce;

    /**
     * Hash of previouse block, 0 for the first block
     */
    std::uint64_t hash;

    /**
     * Timestamp when block was created
     */
    std::time_t timestamp;

    /**
     * Data stored in one block of blockchain
     */
    std::string message;
};
}
