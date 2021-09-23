#include "utxo.h"
#include <iostream>
#include <map>
#include <stdexcept>

using namespace UT;
using namespace std;

void UTXO::verify_transaction(string pub_key, double amount)
{
  UTXO utxo;

  auto issuer_pool = utxo.utxopool.find(pub_key);
  long issuer_balance = issuer_pool->second;

  if (issuer_balance < amount)
  {
    throw invalid_argument("insufficient funds");
  }

  issuer_balance -= amount;

  if (issuer_balance == 0)
  {
    utxo.utxopool.erase(pub_key);
  }
}
