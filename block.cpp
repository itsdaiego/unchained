#include "block.h"
#include <iostream>
#include <functional>
#include <string>

using namespace BL;
using namespace std;

Block Block::append_block(Block last_block)
{
  std::hash<string> hash;

  string nonce = to_string(rand());
  long long_hash = hash(nonce);

  Block bl;

  bl.hash = long_hash;
  bl.parent_hash = last_block.hash;
  bl.height = last_block.height + 1;
  bl.coinbaseBeneficiary = 0;

  return bl;
}
