#include "block.h"
#include <iostream>
#include <functional>
#include <string>

using namespace BL;
using namespace std;
using namespace UT;

void Block::append_block(vector<Block> &blocks, string key, vector<Transaction> transactions)
{
  Block last_block = blocks.back();


  string transactions_combined_hash = utxo.compute_transactions(transactions, utxo, key);
  string hash_input = to_string(last_block.parent_hash) + key + transactions_combined_hash;

  long long_hash = mine_block(hash_input);

  Block bl;

  bl.hash = long_hash;
  bl.parent_hash = last_block.hash;
  bl.height = last_block.height + 1;
  bl.coinbaseBeneficiary = key;
  bl.transactions = transactions;

  blocks.push_back(bl);

  utxo.set_issuer_reward(utxo, key);
}

long Block::mine_block(string hash_input)
{
  unsigned long long_hash = 1; // just a initial value before first iteration

  // random simple condition to enforce some sort of computation power 
  // in order to mine blocks
  while(long_hash % 1000 != 00)
  {
    unsigned long MAX_LONG = -1;
    unsigned long rand_n = rand() + MAX_LONG;
    string nonce = to_string(rand_n);

    std::hash<string> hash;

    long_hash = hash(nonce + hash_input);

    cout << "Mining: " << long_hash << endl;
  }

  cout <<  "Mining completed"  << endl;
  return long_hash;
}
