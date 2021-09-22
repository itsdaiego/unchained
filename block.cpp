#include "block.h"
#include <iostream>
#include <functional>
#include <string>

using namespace BL;
using namespace std;
using namespace UT;

void Block::append_block(vector<Block> &blocks, Issuer issuer)
{

  Block last_block = blocks.back();

  string hash_input = to_string(last_block.parent_hash) + issuer.pub_key;
  long long_hash = mine_block(hash_input);

  Block bl;

  bl.hash = long_hash;
  bl.parent_hash = last_block.hash;
  bl.height = last_block.height + 1;
  bl.coinbaseBeneficiary = issuer.pub_key;

  blocks.push_back(bl);

  // TODO: create a separate function for this instruction
  auto curr_utxpool = utxo.utxopool.find(issuer.pub_key);
  curr_utxpool->second = curr_utxpool->second + 20.5;
}

long Block::mine_block(string hash_input)
{
  std::hash<string> hash;

  unsigned long long_hash = 111;

  while (long_hash % 1000 != 000)
  {
    unsigned long MAX_LONG = -1;
    unsigned long rand_n = rand() + MAX_LONG;
    string nonce = to_string(rand_n);
    long_hash = hash(nonce + hash_input);
    cout << "Mining: " << long_hash << endl;
  }

  cout <<  "Mining completed"  << endl;
  return long_hash;
}
