#include "entityHits.hpp"

    entity_Hits::entity_Hits():
        hitsChannel(this, "hitsChannel")
    {}

    void addHits(unsigned int plrID, unsigned int data){
        hit.plrID = plrID;
        hit.data = data;
        hitsChannel.write(hit);
    }

    void getHits(){
        unsigned int hits = hitsChannel.read()
    }