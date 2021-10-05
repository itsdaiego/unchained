#include <string>
#include <iostream>
#include "utxo.h"
#include <vector>

using namespace std;
using namespace UT;

namespace BL
{
  class Block
  {
    public:
      unsigned long hash;
      unsigned long parent_hash;
      int height;
      string coinbaseBeneficiary;
      int nonce;
      UTXO utxo;
      vector<Transaction> transactions;

      void append_block(vector<Block> &last_block, string id, const vector<Transaction> transactions = vector<Transaction>());
      long mine_block(string hash_input);
  };
}
