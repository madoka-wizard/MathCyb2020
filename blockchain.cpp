#include "blockchain.h"
#include "json.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

namespace blockchain {
void BlockChain::push(const blockchain::Block &new_tail) {
    chain.push_back(new_tail);
}

Block blockchain::BlockChain::pop() {
    const auto res = chain.back();
    chain.pop_back();
    return res;
}

void BlockChain::save_to_file(const std::string &filename) const {
    std::ofstream output(filename);
    nlohmann::json j;
    for (auto &block : chain) {
        j.push_back(block.serialize());
    }
    output << std::setw(4) << j;
}

void BlockChain::load_from_file(const std::string &filename) {
    std::ifstream input(filename);
    nlohmann::json j;
    input >> j;
    for (const auto &current : j) {
        push(Block::deserialize(current));
    }
}

int BlockChain::print_last_messages(std::size_t n) {
    n = std::min(n, size());
    auto counter = 0;
    for (auto it = chain.rbegin(); counter != n; ++it, ++counter) {
        std::cout << it->message() << std::endl;
    }
    return n;
}

std::size_t BlockChain::size() const {
    return chain.size();
}

BlockChain BlockChain::fork(std::size_t index) const {
    BlockChain res;
    if (index < size()) {
        auto it = chain.begin();
        std::advance(it, index);
        for (; it != chain.cend(); ++it) {
            res.push(*it);
        }
    }
    return res;
}

void BlockChain::mend(std::size_t last_correct, const BlockChain &other) {
    ++last_correct;

    for (auto i = last_correct, old_size = chain.size(); i < old_size; ++i) {
        pop();
    }
    for (auto &block : other.chain) {
        push(block);
    }
}

bool BlockChain::synchronize(BlockChain &lhs, BlockChain &rhs) {
    if (lhs.size() < rhs.size()) {
        std::swap(lhs, rhs);
    }

    auto index = static_cast<int>(lhs.size()) - 1;
    for (auto it = lhs.chain.rbegin(); index != -1; --index, ++it) {
        auto rhs_it = rhs.chain.begin();
        for (auto i = 0; i < rhs.size(); ++i, ++rhs_it) {
            if (rhs_it->hash() == it->hash()) {
                auto tail = lhs.fork(index + 1);
                rhs.mend(i, tail);
                return true;
            }
        }
    }

    return false;
}
}
