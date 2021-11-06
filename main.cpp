#include "blockchain.h"
#include <time.h>
#include <string>
#include <map>
#include <stdexcept>


using namespace BC;
using namespace BL;
using namespace UT;

struct Issuer {
  string key;
  string secret;
};

int main()
{
  if (!getenv("SECRET")) {
    throw invalid_argument("MISSING SECRET: export SECRET=something");
  } // shared secret among identities (not ideal ofc :P)

  struct Issuer issuerA;

  issuerA.key = "somekeyforissuera";
  issuerA.secret = getenv("SECRET");

  struct Issuer issuerB;

  issuerB.key = "anotherkeyforuserb";
  issuerB.secret = getenv("SECRET");

  // initialized time before compilation to random number generation
  srand(time(0));

  Blockchain bc;
  Block bl;

  bc.create_blockchain();

  Block root_block;

  root_block = bc.create_root_block();

  bc.blocks.push_back(root_block);

  Block first_block, second_block, third_block;

  bl.utxo.utxopool = {
    { issuerA.key, 0 },
    { issuerB.key, 0 }
  };

  vector<Transaction> transactions;

  bl.append_block(bc.blocks, issuerA.key);

  Transaction transaction1;
  transaction1.input_public_key = issuerA.key;
  transaction1.output_public_key = issuerB.key;
  transaction1.amount = 5;

  Transaction transaction2;
  transaction2.input_public_key = issuerB.key;
  transaction2.output_public_key = issuerA.key;
  transaction2.amount = 2;

  transactions.push_back(transaction1);
  transactions.push_back(transaction2);

  bl.append_block(bc.blocks, issuerA.key, transactions);

  bl.append_block(bc.blocks, issuerB.key);

  bc.list_blocks(bc.blocks);

  std::cout << "IssuerA balance: " << bl.utxo.utxopool.find(issuerA.key)->second << std::endl;

  std::cout << "IssuerB balance: " << bl.utxo.utxopool.find(issuerB.key)->second << std::endl;

  return 0;
}
