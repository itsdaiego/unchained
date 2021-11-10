#include "blockchain.h"
#include <time.h>
#include <string>
#include <map>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <sys/ipc.h>
#include <sys/shm.h>


using namespace BC;
using namespace BL;
using namespace UT;

struct Issuer {
  string key;
  string secret;
};

int main()
{
  // current approach is to create multiple processes instead of using threads, in that way we will be able to broadcast transactions and validate them using multiple nodes. Leaving that here just for reference
  /* std::mutex mtx; */
  /* mtx.lock(); */
  /* std::thread th1(&Block::append_block, bl, std::ref(shm_id), std::ref(issuerA.key), std::ref(transactions)); */
  /* mtx.unlock(); */
  /* th1.join(); */

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

  bl.utxo.utxopool = {
    { issuerA.key, 0 },
    { issuerB.key, 0 }
  };

  vector<Transaction> transactions;

  int shm_key = 1234; // value will be shared by multiple processes

  int shm_id = shmget(shm_key, sizeof(class Block) * 100, IPC_CREAT | 0666);

  // insert root_block into shared memory 
  vector<Block> *blocks = (vector<class Block>*) shmat(shm_id, NULL, 0);
  blocks->push_back(root_block);

  std::cout << "block 1" << std::endl;
  bl.append_block(shm_id, issuerA.key);

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

  std::cout << "block 2" << std::endl;
  bl.append_block(shm_id, issuerA.key, transactions);
  std::cout << "block 3" << std::endl;
  bl.append_block(shm_id, issuerB.key);

  bc.list_blocks(shm_id);

  std::cout << "IssuerA balance: " << bl.utxo.utxopool.find(issuerA.key)->second << std::endl;

  std::cout << "IssuerB balance: " << bl.utxo.utxopool.find(issuerB.key)->second << std::endl;

  // destroys shared memory 
  std::cout << "SHARED_MEM_ID: " << shm_id << std::endl;
  int r_detach = shmdt(blocks);
  std::cout << "success detaching" << r_detach << std::endl;
  int r_destroy = shmctl(shm_key, IPC_RMID, NULL);
  std::cout << "success destroying?" << r_destroy << std::endl;
  return 0;
}
