#include "blockchain.h"
#include <time.h>


using namespace BC;
using namespace BL;

int main()
{
    // initialized time before compilation to random number generation
    srand(time(0));

    Blockchain bc;
    Block bl;

    bc.create_blockchain();

    Block root_block;

    root_block = bc.create_root_block();

    bc.blocks.push_back(root_block);

    Block first_block, second_block, third_block;


    bl.append_block(bc.blocks);

    bl.append_block(bc.blocks);

    bl.append_block(bc.blocks);
    cout << bc.blocks.size() << endl;

    return 0;
}
