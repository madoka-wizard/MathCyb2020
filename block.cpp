#include "block.h"
#include <functional>
#include <utility>

namespace blockchain {
Block::Block(std::string message, const std::uint64_t nonce)
        : nonce_{nonce}, hash_{0}, timestamp_{std::time(nullptr)}, message_{std::move(message)} {
}

Block::Block(std::string message, const std::uint64_t nonce, const blockchain::Block &block)
        : nonce_{block.nonce_}, timestamp_{std::time(nullptr)}, message_{std::move(message)} {
    hash_ = std::hash<std::string>{}(std::to_string(nonce) + std::to_string(block.hash_));
}

Block::~Block() {
}

void Block::serialize(std::ostream &input) const {
    input << message_ << " "
          << nonce_ << " "
          << hash_ << " "
          << timestamp_ << std::endl;
}

Block::Block(std::string message, std::uint64_t nonce, std::uint64_t hash, std::time_t timestamp)
        : message_{std::move(message)}, nonce_{nonce}, hash_{hash}, timestamp_{timestamp} {
}

Block Block::deserialize(std::istream &in) {
    std::string message;
    std::uint64_t nonce;
    std::uint64_t hash;
    std::time_t timestamp;

    in >> message >> nonce >> hash >> timestamp;
    return Block(message, nonce, hash, timestamp);
}

std::string Block::message() const {
    return message_;
}

std::uint64_t Block::hash() const {
    return hash_;
}
}
