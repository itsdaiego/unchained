#include "blockchain.h"
#include <time.h>
#include <string>
#include <map>


using namespace BC;
using namespace BL;
using namespace UT;

int main()
{
  
  struct Issuer issuerA;
  
  issuerA.pub_key = "-----BEGIN PUBLIC KEY-----"
    "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDHSpu3Aq53hkHqjVP7OcntZV0f"
    "Ji2Uf8+9oDl+sU0/52/jhVdNZx8MhC4Q1X8SRl7mGdtakXomPGIziCXvzrW+TO1R"
    "3kUNqM75lvASzXAt8eAvNlikv7zuOeIHcW9jw4xIWZ9WcEK/gEGKSdzUmjrkUP07"
    "hrFMsdedVoU/5RWWlQIDAQAB"
    "-----END PUBLIC KEY-----";

  issuerA.pvt_key = "-----BEGIN RSA PRIVATE KEY-----"
    "MIICXgIBAAKBgQDHSpu3Aq53hkHqjVP7OcntZV0fJi2Uf8+9oDl+sU0/52/jhVdN"
    "Zx8MhC4Q1X8SRl7mGdtakXomPGIziCXvzrW+TO1R3kUNqM75lvASzXAt8eAvNlik"
    "v7zuOeIHcW9jw4xIWZ9WcEK/gEGKSdzUmjrkUP07hrFMsdedVoU/5RWWlQIDAQAB"
    "AoGBALA8PxWJDoXuOS5VSnX4taP0pnPcTCRtHmWfYhiybBDd9mkqSnjNf3yPCzmh"
    "wxyDFHrBVORzj6Ruc50Egh/eGYKfP3s6+i9UTcngRF63cbH/suFKbAC6QLzoR9o5"
    "h0lcB4QhHOPFxwLMnwXIvxpGw/0OIXiaSvTUWU11FKdLa8QhAkEA6iBOzhM0JfZm"
    "KQx8qn+l8WXW+BzTSDnHT2CRDcXhu0gf+G2PSfBcay8r2xHqP+Rq4P5lFADlt7rF"
    "xjXy8b9GLQJBANnpJKQU2EbMO79HlWUsiYhsPZV2sLZHaa6nR8yYae4369xohoS1"
    "vtWCPNPdEfMNnPSw23VK8m6E4tf2BKCG+wkCQA9fRa1UJ3ViozyIvFq5fNzHsgCi"
    "a+DvIj38+iksV/DjAG5gSyswo/DJrRh6KaY+SiIxsdNJZ8vTcI7eFfB3fZUCQQC2"
    "0mvzXam2fFMEQEKPB7a7xlREube4tmFsLtyGQrldK32vBeMWJIVfDE2MUsVkbd9p"
    "S5hT5/VN1B+doMJxC85BAkEAuUuWJsF0tGYBKvzlT9DDaWJUzAtiu04BnFhV3MUC"
    "QjT3fA/rmJ6UT92OM6cysm9NzcWr4KIv07YNXPABK+nXZQ=="
    "-----END RSA PRIVATE KEY-----";

  struct Issuer issuerB;

  issuerB.pub_key = "-----BEGIN PUBLIC KEY-----"
    "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQC33jDbSQgxI6OJjgcFkHZG1/eS"
    "kcbz6rPsD2sS1jIa/sT6JEFgmRS6gHtTyruNxUu7JT4qfQWnAMI1IaUsyfFDbgyV"
    "HnkhnwZBcempv3mAJtf9agm1IFHrpBLrru+XWJt17ZB3LwiWyzjmJl/Ug/sQuX99"
    "haRS+TdCFNVyjIrXZwIDAQAB"
    "-----END PUBLIC KEY-----";
  issuerB.pvt_key = "-----BEGIN RSA PRIVATE KEY-----"
    "MIICXQIBAAKBgQC33jDbSQgxI6OJjgcFkHZG1/eSkcbz6rPsD2sS1jIa/sT6JEFg"
    "mRS6gHtTyruNxUu7JT4qfQWnAMI1IaUsyfFDbgyVHnkhnwZBcempv3mAJtf9agm1"
    "IFHrpBLrru+XWJt17ZB3LwiWyzjmJl/Ug/sQuX99haRS+TdCFNVyjIrXZwIDAQAB"
    "AoGBAJWKuwW+klEVAU9BGmjmI6xevlaRBdUgUJFvwNAjMcFO8HnZvuqH1poRITz3"
    "KC+YBY4CLlt0L4KyVUHNSX/yBqxGDYRT1WT5s+LcFAw9P0WaXyr6+wniPbepHebv"
    "zLPovMaQwEcLgZ1VhZn/wPOo8ujjHHlABDFrLd8irZNrfOHRAkEA2VmxOEpPyk2+"
    "xeJQFkv49oW9EblmAZ+ofqSzDoJV8as40ktdT5Wn6r+SRQHdbYMKaLxpIVMgh7F3"
    "OFScee8nMwJBANiQTGljQMLhAVAeGEnJWzm2P8v3LwpfagGzHNRRdUjtV1ULN+ub"
    "RdTO5aO0MDGclaQkX5x+YAZ2JyZULdqCfv0CQDfYgt+KwHujhDwGDTvdY2e8LztJ"
    "nrsWEc4QdW1p8bk5nEz0TlJvioiXlnaipwlHXTpSBtUoLbiP0akonFf8Kd8CQFZJ"
    "KCjVYvhCrkM9um+ryq0z8DdURWncmmAS/WmbCyADcMhxr9YwB6LCzLxtDsa1nOnJ"
    "lE7GC3yHlxGueJaXaAECQQCj3RHHzGEqvE3JRn93TPmbLGG5G0U9GM1Ss8I021ZK"
    "Wa9uQQTB68hT+Pz7DIk8BagcREufjwJHfHdVgEP/UUbI"
    "-----END RSA PRIVATE KEY-----";




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
    { issuerA.pub_key, 0 },
    { issuerB.pub_key, 0 }
  };

  vector<Transaction> transactions;

  

  bl.append_block(bc.blocks, issuerA.pub_key);

  Transaction transaction1;
  transaction1.input_public_key = issuerA.pub_key;
  transaction1.output_public_key = issuerB.pub_key;
  transaction1.amount = 15;

  Transaction transaction2;
  transaction2.input_public_key = issuerA.pub_key;
  transaction2.output_public_key = issuerB.pub_key;
  transaction2.amount = 5;

  transactions.push_back(transaction1);
  transactions.push_back(transaction2);

  bl.append_block(bc.blocks, issuerA.pub_key, transactions);

  bl.append_block(bc.blocks, issuerB.pub_key);

  bc.list_blocks(bc.blocks);

  std::cout << "IssuerA balance: " << bl.utxo.utxopool.find(issuerA.pub_key)->second << std::endl;

  std::cout << "IssuerB balance: " << bl.utxo.utxopool.find(issuerB.pub_key)->second << std::endl;

  return 0;
}
