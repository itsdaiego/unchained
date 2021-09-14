#include <string>
#include <iostream>

using namespace std;

namespace TRX
{
  class Transaction
  {
    public:
      string input_public_key;
      string output_public_key;
      int amount;
      int fee;
      int signature;

      void perform_transaction(string input_public_key, string output_public_key, int amount);
  };
}
