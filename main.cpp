#include <streambuf>
#include <fstream>
#include <cassert>
#include <random>
#include <cstdint>
#include <numeric>

#include "blockchain.h"
#include "block.h"

namespace {
using namespace blockchain;

std::uint64_t rand_nonce() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<std::uint64_t> dist(0, std::numeric_limits<std::uint64_t>::max());

    return dist(mt);
}

bool compare_blockchains(const BlockChain &blockchain1, const BlockChain &blockchain2) {
    blockchain1.save_to_file("blockchain1.json");
    std::ifstream blockchain1_json("blockchain1.json");
    std::string str1((std::istreambuf_iterator<char>(blockchain1_json)),
                     std::istreambuf_iterator<char>());

    blockchain2.save_to_file("blockchain2.json");
    std::ifstream blockchain2_json("blockchain2.json");
    std::string str2((std::istreambuf_iterator<char>(blockchain2_json)),
                     std::istreambuf_iterator<char>());

    return str1 == str2;
}

void test_read_write_blockchain() {
    BlockChain blockchain1;

    Block first_block("A->B:300$", rand_nonce());
    blockchain1.push(first_block);

    Block second_block("B->C:400$", rand_nonce(), first_block);
    blockchain1.push(second_block);

    blockchain1.save_to_file("test1.json");

    BlockChain blockchain2;
    blockchain2.load_from_file("test1.json");
    assert(compare_blockchains(blockchain1, blockchain2));
}

void test_sync_blockchains() {
    Block block1("A->B:300$", rand_nonce());
    Block block2("B->C:400$", rand_nonce(), block1);
    Block block3("C->D:100$", rand_nonce(), block2);

    Block block4("D->E:200$", rand_nonce(), block3);
    Block block5("E->F:300$", rand_nonce(), block4);
    Block block6("B->A:340$", rand_nonce(), block5);

    Block block7("G->H:310$", rand_nonce(), block3);

    BlockChain blockchain1;
    blockchain1.push(block1);
    blockchain1.push(block2);
    blockchain1.push(block3);
    blockchain1.push(block4);
    blockchain1.push(block5);
    blockchain1.push(block6);

    BlockChain blockchain2;
    blockchain2.push(block1);
    blockchain2.push(block2);
    blockchain2.push(block3);
    blockchain2.push(block7);

    BlockChain blockchain1_copy = blockchain1;
    assert(BlockChain::synchronize(blockchain1, blockchain2));

    assert(compare_blockchains(blockchain1, blockchain2));
    assert(compare_blockchains(blockchain1, blockchain1_copy));
}
}

int main() {
    test_read_write_blockchain();
    test_sync_blockchains();

    return 0;
}
