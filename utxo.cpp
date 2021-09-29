#include "utxo.h"
#include <iostream>
#include <map>
#include <stdexcept>

using namespace UT;
using namespace std;

void UTXO::verify_transaction(double issuer_balance, double amount)
{
  std::cout << "pool: " << issuer_balance << std::endl;
  std::cout << "amount: " << amount << std::endl;

  if (issuer_balance < amount)
  {
    throw invalid_argument("insufficient funds");
  }

  issuer_balance -= amount;
}
