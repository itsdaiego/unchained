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
  };
}
