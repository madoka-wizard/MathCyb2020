#pragma once

#include <string>
#include <ctime>
#include <cstdint>
#include <iostream>

namespace blockchain {
class Block final {
public:
    Block(std::string message, std::uint64_t nonce);

    Block(std::string message, std::uint64_t nonce, const Block &block);

    void serialize(std::ostream &input) const;

    static Block deserialize(std::istream &input);

    std::string message() const;

    std::uint64_t hash() const;

    ~Block();

private:
    Block(std::string message, std::uint64_t nonce, std::uint64_t hash, std::time_t timestamp);

    /**
     * Parameter for the Proof of Work
     */
    std::uint64_t nonce_;

    /**
     * Hash of previous block, 0 for the first block
     */
    std::uint64_t hash_;

    /**
     * Timestamp when block was created
     */
    std::time_t timestamp_;

    /**
     * Data stored in one block of blockchain
     */
    std::string message_;
};
}
