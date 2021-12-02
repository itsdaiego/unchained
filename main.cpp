#include "blockchain.h"
#include <time.h>
#include <string>
#include <map>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"


using namespace BC;
using namespace BL;
using namespace UT;
using namespace rapidjson;


struct Issuer {
  string key;
  string secret;
};


int main(int argc, char **argv)
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

  // set initial chain' s state
  bc.create_blockchain();

  Block root_block;

  root_block = bc.create_root_block();

  bc.blocks.push_back(root_block);

  bl.utxo.utxopool = {
    { issuerA.key, 20 },
    { issuerB.key, 20 }
  };

  vector<Transaction> transactions;

  /// create shared memory 
  int shm_key = 342; // value will be shared by multiple processes

  int shm_id = shmget(shm_key, sizeof(class Block) * 100, IPC_CREAT | 0666);

  // insert root_block into shared memory 
  vector<Block> *blocks = (vector<class Block>*) shmat(shm_id, NULL, 0);
  blocks->push_back(root_block);

  std::cout << "shared memory id: " << shm_id << std::endl;

  Document d;

  for (std::string line; std::getline(std::cin, line);) {
    std::cout << "transaction to compute: "<< line << std::endl;

    char json[line.length() + 1];
    strcpy(json, line.c_str());

    d.Parse(json);

    Transaction transaction;
    transaction.input_public_key = d["input_public_key"].GetString();
    transaction.output_public_key = d["output_public_key"].GetString();
    transaction.amount = d["amount"].GetInt();

    transactions.push_back(transaction);
    bl.append_block(shm_id, issuerA.key, transactions);
  }


  bc.list_blocks(shm_id);

  std::cout << "IssuerA balance: " << bl.utxo.utxopool.find(issuerA.key)->second << std::endl;

  std::cout << "IssuerB balance: " << bl.utxo.utxopool.find(issuerB.key)->second << std::endl;

  // destroys shared memory 
  std::cout << "SHARED_MEM_ID: " << shm_id << std::endl;
  int r_detach = shmdt(blocks);
  std::cout << "success detaching" << r_detach << std::endl;
  int r_destroy = shmctl(shm_id, IPC_RMID, 0);
  std::cout << "success destroying?" << r_destroy << std::endl;


  return 0;
}
