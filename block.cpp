#include "block.h"
#include <iostream>
#include <functional>
#include <string>

using namespace BL;
using namespace std;
using namespace UT;

void Block::append_block(vector<Block> &blocks, string pub_key, vector<Transaction> transactions)
{
  Block last_block = blocks.back();
  Transaction transaction;

  string transaction_hash = "";
  long total_amount = 0;


  for (Transaction trx : transactions)
  {
    transaction_hash += to_string(transaction.calculate_hash(trx.input_public_key, trx.output_public_key, trx.amount));

    double issuer_balance = utxo.utxopool.find(pub_key)->second;
    utxo.verify_transaction(issuer_balance, trx.amount);

    // update issuer and receiver balances
    auto issuer = utxo.utxopool.find(trx.input_public_key);
    issuer->second = issuer->second - trx.amount;

    auto receiver = utxo.utxopool.find(trx.output_public_key);
    receiver->second = receiver->second + trx.amount;
  }

  string hash_input = to_string(last_block.parent_hash) + pub_key + transaction_hash;

  long long_hash = mine_block(hash_input);

  Block bl;

  bl.hash = long_hash;
  bl.parent_hash = last_block.hash;
  bl.height = last_block.height + 1;
  bl.coinbaseBeneficiary = pub_key;
  bl.transactions = transactions;

  blocks.push_back(bl);


  auto curr_utxopool = utxo.utxopool.find(pub_key);
  curr_utxopool->second = curr_utxopool->second + 20.5;
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
