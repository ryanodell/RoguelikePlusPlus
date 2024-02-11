#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <cstdint>
#include <array>
#include <queue>
#include "logger.h"
#include "macros.h"

//Butterfly wings or Swallow Tail Plant - Note Don't lose.

const int MAX_ENTITIES = 5000;
const int MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;
using ComponentType = std::uint8_t;
using Entity = std::uint32_t;

class EntityManger {
public:
    EntityManger() {
        for(Entity entity = 0; entity < MAX_ENTITIES; entity++) {
            mAvailableEntities.push(entity);
        }
    }    
    Entity CreateEntity() {
        if(mLivingEntityCount > MAX_ENTITIES) {
            Logger::LogError("Too many entities. Increase MAX_ENTITIES");
            CRASH_PROGRAM;
        }
    }

    void DestroyEntity(Entity entity) {
        if(entity > MAX_ENTITIES) {
            Logger::LogError("Entity %u is out of range.", entity);
        }
    }

    void SetSignature(Entity entity, Signature signature) {
        if(entity > MAX_ENTITIES) {
            Logger::LogError("Entity %u is out of range.", entity);
        }
        
    }

private:
    std::queue<Entity> mAvailableEntities;
    std::array<Signature, MAX_ENTITIES> mSignatures;
    uint32_t mLivingEntityCount;
};

#endif