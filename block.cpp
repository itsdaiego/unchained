#include "block.h"
#include <iostream>
#include <functional>
#include <string>

using namespace BL;
using namespace std;

void Block::append_block(vector<Block> &blocks)
{

  Block last_block = blocks.back();
  long long_hash = mine_block(last_block.hash);

  Block bl;


  bl.hash = long_hash;
  bl.parent_hash = last_block.hash;
  bl.height = last_block.height + 1;
  bl.coinbaseBeneficiary = 0;

  blocks.push_back(bl);
}

long Block::mine_block(long parent_hash)
{
  std::hash<string> hash;

  unsigned long long_hash = 111;

  while (long_hash % 1000 != 000)
  {
    unsigned long MAX_LONG = -1;
    unsigned long rand_n = rand() + MAX_LONG;
    string nonce = to_string(rand_n);
    long_hash = hash(nonce);
    /* std::cout << "Mining: " << long_hash << std::endl; */
  }

  return long_hash;
}
