#include "transaction.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using namespace TRX;
namespace UT
{
  class UTXO
  {
    public:
      string public_key;
      double balance;
      double amount; 
      map<string, double> utxopool;


      static void verify_transaction(double issuer_balance, double amount);
      string compute_transactions(const vector<Transaction> transaction, UTXO &utxo, string id);
      void set_issuer_reward(UTXO &utxo, string id);
  };
}
