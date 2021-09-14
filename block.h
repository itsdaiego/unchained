#include <string>
#include <iostream>
#include "transaction.h"
#include "utxo.h"

using namespace std;
using namespace UT;
using namespace TRX;

namespace BL
{
  class Block
  {
    public:
      long hash;
      long parent_hash;
      int height;
      int coinbaseBeneficiary;
      int nonce;
      UTXO utxoPool;
      Transaction transactions;

      Block append_block(Block last_block);
  };
}
