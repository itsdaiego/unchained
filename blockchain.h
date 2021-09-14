#include <string>
#include <iostream>
#include <vector>
#include "block.h"

using namespace std;
using namespace BL;

namespace BC
{
   class Blockchain
   {
     public:
       string name;
       vector<Block> blocks;

       Blockchain create_blockchain();
       Block create_root_block();
       int get_longest_chain_size();
       void list_blocks(vector<Block> &blocks);
   };
}
