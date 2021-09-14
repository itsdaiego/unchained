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
      string hash;
      string parent_hash;
      int height;
      int coinbaseBeneficiary;
      int nonce;
      UTXO utxoPool;
      Transaction transactions;

      void create();
  };
}
