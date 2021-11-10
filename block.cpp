#include "block.h"
#include <iostream>
#include <functional>
#include <string>
#include "include/easy-encrypt/encrypt.h"
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace BL;
using namespace std;
using namespace UT;

void Block::append_block(int &shm_id, string &key, const vector<Transaction> &transactions)
{
  // access shared memory in order to access latest block in chain
  // ofc might cause some concurrency problems #eita
  vector<Block> *blocks = (vector<class Block>*) shmat(shm_id, NULL, 0);

  Block *last_block = &blocks->back();

  std::cout << "shared" << std::endl;
  string  transactions_combined_hash = "";
  transactions_combined_hash = utxo.compute_transactions(transactions, utxo, key);
  std::cout << "shared1" << std::endl;

  string hash_input = last_block->parent_hash + key + transactions_combined_hash;

  string mined_block = to_string(mine_block(hash_input));
  string encrypted_hash = encrypt(mined_block, key);

  Block bl;

  bl.hash = encrypted_hash;
  bl.parent_hash = last_block->hash;
  bl.height = last_block->height + 1;
  bl.coinbaseBeneficiary = key;
  bl.transactions = transactions;

  blocks->push_back(bl);

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
