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
      double amount;
      double fee;
      int signature;

      long calculate_hash(string input_public_key, string output_public_key, double amount);
  };
}
