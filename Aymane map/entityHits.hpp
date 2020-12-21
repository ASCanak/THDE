#ifndef ENTITYHITS_HPP
#define ENTITYHITS_HPP

#include "rtos.hpp"

struct hitStruct{unsigned int plrID; unsigned int data;};

class entity_Hits{
private:
    rtos::channel < hit > hitsChannel;
public:
    hitStruct hit;

    entity_Hits();

    void addHits(unsigned int plrID, unsigned int data);

    void getHits();
};

#endif