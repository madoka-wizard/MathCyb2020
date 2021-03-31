#include "block.h"
#include "utils.h"

#include <functional>
#include <utility>
#include "json.h"


namespace blockchain {
Block::Block(std::string message, const std::uint64_t nonce)
        : nonce_{nonce}, hash_{0}, timestamp_{std::time(nullptr)}, message_{std::move(message)} {
}

Block::Block(std::string message, const std::uint64_t nonce, const blockchain::Block &block)
        : nonce_{block.nonce_}, timestamp_{std::time(nullptr)}, message_{std::move(message)} {
    hash_ = std::hash<std::string>{}(message);
    hash_combine(hash_, std::hash<std::time_t>{}(timestamp_));
    hash_combine(hash_, std::hash<std::uint64_t>{}(nonce));
    hash_combine(hash_, block.hash());
}

nlohmann::json Block::serialize() const {
    return nlohmann::json{
            {"message",   message_},
            {"nonce",     nonce_},
            {"hash",      hash_},
            {"timestamp", timestamp_}
    };
}

Block::Block(std::string message, std::uint64_t nonce, std::uint64_t hash, std::time_t timestamp)
        : message_{std::move(message)}, nonce_{nonce}, hash_{hash}, timestamp_{timestamp} {
}

Block Block::deserialize(const nlohmann::json &j) {
    std::string message;
    std::uint64_t nonce;
    std::uint64_t hash;
    std::time_t timestamp;

    j.at("message").get_to(message);
    j.at("nonce").get_to(nonce);
    j.at("hash").get_to(hash);
    j.at("timestamp").get_to(timestamp);
    return Block(message, nonce, hash, timestamp);
}

std::string Block::message() const {
    return message_;
}

std::uint64_t Block::hash() const {
    return hash_;
}
}
