#include <string>
#include <iostream>
#include <map>

using namespace std;

namespace UT
{
  class UTXO
  {
    public:
      string public_key;
      double balance;
      double amount; 
      map<string, double> utxopool;


      static void verify_transaction(string input_public_key, double amount);
  };
}
