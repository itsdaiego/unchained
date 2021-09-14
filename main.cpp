#include "blockchain.h"


using namespace BC;
using namespace BL;

int main()
{
    Blockchain bc;

    std::vector<Block> blocks;

    bc.create(blocks);

    return 0;
}
