#include "blockchain.h"


using namespace BC;
using namespace BL;

int main()
{
    Blockchain bc;

    std::vector<Block> blocks;

    Block root = bc.create_root_block(blocks);

    return 0;
}
