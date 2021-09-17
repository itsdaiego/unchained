#include <string>
#include <iostream>
#include "transaction.h"
#include "utxo.h"
#include <vector>

using namespace std;
using namespace UT;
using namespace TRX;

namespace BL
{
  class Block
  {
    public:
      unsigned long hash;
      unsigned long parent_hash;
      int height;
      int coinbaseBeneficiary;
      int nonce;
      UTXO utxoPool;
      Transaction transactions;

      void append_block(vector<Block> &last_block);

      private:
        long mine_block(long parent_hash);
  };
}
