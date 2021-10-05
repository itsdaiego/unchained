#include "transaction.h"
#include <iostream>

using namespace TRX;
using namespace std;

long Transaction::calculate_hash(string input_public_key, string output_public_key, double amount)
{
  string hash_input = input_public_key + output_public_key + to_string(amount);

  std::hash<string> hash;
  unsigned hash_result = hash(hash_input);

  return hash_result;
}
