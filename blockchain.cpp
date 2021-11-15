#include "blockchain.h"
#include <iostream>
#include <functional>
#include <string>
#include <sys/shm.h>
#include <sys/ipc.h>

using namespace BC;
using namespace std;

Blockchain Blockchain::create_blockchain()
{
  Blockchain bc;
  vector<Block> blocks;

  bc.name = "Unchained";
  bc.blocks = blocks;

  std::cout << "Blockchain: " << bc.name << std::endl;

  return bc;
}

Block Blockchain::create_root_block()
{
  Block root_block;

  root_block.hash = "000";
  root_block.parent_hash = "000";
  root_block.height = 0;

  return root_block;
}


void Blockchain::list_blocks(int shm_id)
{
  const vector<Block> *blocks = (vector<class Block>*) shmat(shm_id, NULL, 0);

  std::cout << "Created blocks:" << std::endl;

  for(const auto &block : *blocks){
    cout << "------------" << endl;
    cout << "------------" << endl;
    cout << "Hash: " << block.hash << endl;
    cout << "Parent Hash: " << block.parent_hash << endl;
    cout << "Coinbase Beneficiary: " << block.coinbaseBeneficiary << endl;
    cout << "Height: " << block.height << endl;
    for (Transaction trx : block.transactions) {
      std::cout << "........................" << std::endl; 
      std::cout << "Transaction sender key: " << trx.input_public_key << std::endl; 
      std::cout << "Transaction receiver key: " << trx.output_public_key << std::endl; 
      std::cout << "Transaction amount: " << trx.amount << std::endl; 
    }
  }
}
