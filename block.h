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
      vector<Transaction> transactions;

      void append_block(vector<Block> &last_block, string pub_key, vector<Transaction> transactions);
      long mine_block(string hash_input);
  };
}
