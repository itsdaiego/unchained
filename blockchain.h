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
     string name;
     vector<Block> blocks;

     public:
       Block create_root_block(vector<Block> blocks);
       int get_longest_chain_size();
   };
}
