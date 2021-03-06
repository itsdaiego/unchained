#include "utxo.h"
#include <iostream>
#include <map>
#include <stdexcept>

using namespace UT;
using namespace std;


const int FEE = 2;
const int REWARD = 20;

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

string UTXO::compute_transactions(vector<Transaction> transactions, UTXO &utxo, string id)
{
  string transactions_combined_hash = "";

  for (Transaction trx : transactions)
  {
    Transaction transaction;

    transactions_combined_hash += to_string(transaction.calculate_hash(trx.input_public_key, trx.output_public_key, trx.amount));

    double issuer_balance = utxo.utxopool.find(id)->second;
    utxo.verify_transaction(issuer_balance, trx.amount);

    auto issuer = utxo.utxopool.find(trx.input_public_key);
    issuer->second = issuer->second - trx.amount;
    auto receiver = utxo.utxopool.find(trx.output_public_key);
    receiver->second = receiver->second + trx.amount;
  }

  return transactions_combined_hash;
}

void UTXO::set_issuer_reward(UTXO &utxo, string id)
{
  auto curr_utxopool = utxo.utxopool.find(id);
  curr_utxopool->second = curr_utxopool->second + REWARD;
}
