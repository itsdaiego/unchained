#include <string>
#include <iostream>
#include "transaction.h"
#include "utxo.h"
#include <vector>

using namespace std;
using namespace UT;
using namespace TRX;

struct Issuer {
  string pub_key;
  string pvt_key; 
};

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
      Transaction transactions;

      void append_block(vector<Block> &last_block, Issuer issuer);
      long mine_block(long parent_hash);
  };
}
