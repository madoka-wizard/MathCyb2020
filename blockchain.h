#pragma once

#include <cstddef>

#include <list>
#include <string>

#include "block.h"

namespace blockchain {
class BlockChain {
public:
    BlockChain();

    /**
     * Add new block to tail of chain
     */
    int push(Block new_tail);

    /**
     * Delete tail block from chain and return it
     */
    Block pop();

    int save_to_file(std::string filename);

    int load_from_file(std::string filename);

    /**
     * Print to console messages from n tail blocks
     *
     * @param n tail of blocks length
     * @return number of printed messages
     */
    int print_last_messages(std::size_t n);

private:
    ~BlockChain();

    std::list<Block> chain;
};
}
