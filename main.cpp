#include "blockchain.h"
#include <time.h>


using namespace BC;
using namespace BL;

int main()
{
    // initialized time before compilation
    srand(time(0));

    // Init classes on stack
    Blockchain bc;
    Block bl;

    // Create blockchain
    bc.create_blockchain();

    Block root_block;

    // Create initial blockchain (root) block
    root_block = bc.create_root_block();

    bc.blocks.push_back(root_block);

    // Create a block
    Block first_block;

    first_block = bl.append_block(bc.blocks.back());

    bc.blocks.push_back(first_block);

    // List all existing blocks
    bc.list_blocks(bc.blocks);


    return 0;
}
