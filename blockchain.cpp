#include "blockchain.h"
#include <iostream>

using namespace BC;
using namespace std;

Block Blockchain::create_root_block(vector<Block> blocks)
{
  Block root_block;

  root_block.hash = "123";

  cout << "Blockchain root block" << endl;
  cout << root_block.hash << endl;
  
  return root_block;
}
