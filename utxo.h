#include <string>
#include <iostream>


using namespace std;

namespace UT
{
  class UTXO
  {
    public:
      string public_key;
      int amount;

      void add_transaction_to_pool(string input_public_key, string output_public_key, int amount);
  };
}
