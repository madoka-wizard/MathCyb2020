#pragma once

#include <cstddef>

#include <list>
#include <string>

#include "block.h"

namespace blockchain {
class BlockChain final {
public:
    /**
     * Add new block to tail of chain
     */
    void push(const Block &new_tail);

    std::size_t size() const;

    /**
     * Delete tail block from the chain and return it
     */
    Block pop();

    void save_to_file(const std::string &filename) const;

    void load_from_file(const std::string &filename);

    /**
     * Print to console messages from n tail blocks
     *
     * @param n tail of blocks length
     * @return number of printed messages
     */
    int print_last_messages(std::size_t n);

    static bool synchronize(BlockChain &lhs, BlockChain &rhs);

private:
    BlockChain fork(std::size_t index) const;

    void mend(std::size_t last_correct, const BlockChain &other);

    std::list<Block> chain;
};
}
