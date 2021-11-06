#include "blockchain.h"
#include <iostream>
#include <functional>
#include <string>

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


void Blockchain::list_blocks(vector<Block> &blocks)
{
  std::cout << "Created blocks:" << std::endl;
  for (int i = 0; i < blocks.size(); ++i) {
    cout << "------------" << endl;
    cout << "------------" << endl;
    cout << "Hash: " << blocks[i].hash << endl;
    cout << "Parent Hash: " << blocks[i].parent_hash << endl;
    cout << "Coinbase Beneficiary: " << blocks[i].coinbaseBeneficiary << endl;
    cout << "Height: " << blocks[i].height << endl;
    for (Transaction trx : blocks[i].transactions) {
      std::cout << "........................" << std::endl; 
      std::cout << "Transaction sender key: " << trx.input_public_key << std::endl; 
      std::cout << "Transaction receiver key: " << trx.output_public_key << std::endl; 
      std::cout << "Transaction amount: " << trx.amount << std::endl; 
    }
  }
}
