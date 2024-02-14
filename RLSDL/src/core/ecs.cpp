#include "ecs.h"

//////////////////////////////////////ENTITY MANAGER////////////////////////////////////
EntityManger::EntityManger() {
    for(Entity entity = 0; entity < MAX_ENTITIES; entity++) {
        mAvailableEntities.push(entity);
    }
}

Entity EntityManger::CreateEntity(){
    if(mLivingEntityCount > MAX_ENTITIES) {
        Logger::LogError("Too many entities. Increase MAX_ENTITIES");
        CRASH_PROGRAM;
    }
    Entity entity = mAvailableEntities.front();
    mAvailableEntities.pop();
    ++mLivingEntityCount;
    return entity;
}

void EntityManger::DestroyEntity(Entity entity) {
     if(entity > MAX_ENTITIES) {
         Logger::LogError("Entity %u is out of range.", entity);
     }
     mSignatures[entity].reset();
     mAvailableEntities.push(entity);
     --mLivingEntityCount;
 }

 void EntityManger::SetSignature(Entity entity, Signature signature) {
     if(entity > MAX_ENTITIES) {
         Logger::LogError("Entity %u is out of range.", entity);
     }
     mSignatures[entity] = signature;
 }

 Signature EntityManger::GetSignature(Entity entity) {
     if(entity > MAX_ENTITIES) {
         Logger::LogError("Entity %u is out of range.", entity);
     }
     return mSignatures[entity];
 }

 //////////////////////////////////////ENTITY MANAGER////////////////////////////////////

//////////////////////////////////////COMPONENT MANAGER////////////////////////////////////
void ComponentManager::EntityDestroyed(Entity entity) {
    for(auto const& pair : mComponentArrays) {        
        auto const& component = pair.second;        
        component->EntityDestroyed(entity);
    }
}
//////////////////////////////////////COMPONENT MANAGER////////////////////////////////////

//////////////////////////////////////////SYSTEM///////////////////////////////////////////
void SystemManger::EntityDestroyed(Entity entity) {
    for (auto const& pair : mSystems) {
		auto const& system = pair.second;
		system->mEntities.erase(entity);
	}
}

void SystemManger::EntitySignatureChanged(Entity entity, Signature entitySignature) {
    for (auto const& pair : mSystems) {
		auto const& type = pair.first;
		auto const& system = pair.second;
		auto const& systemSignature = mSignatures[type];
		if ((entitySignature & systemSignature) == systemSignature) {
			system->mEntities.insert(entity);
		} else {
			system->mEntities.erase(entity);
		}
	}
}
//////////////////////////////////////////SYSTEM///////////////////////////////////////////

//////////////////////////////////////COORDINATOR//////////////////////////////////////////
void Coordinator::Init() {
    mEntityManager = std::make_unique<EntityManger>();
    mComponentManager = std::make_unique<ComponentManager>();
    mSystemManager = std::make_unique<SystemManger>();
}

Entity Coordinator::CreateEntity() {
    return mEntityManager->CreateEntity();
}

void Coordinator::DestroyEntity(Entity entity) {
    mEntityManager->DestroyEntity(entity);
    mComponentManager->EntityDestroyed(entity);
    mSystemManager->EntityDestroyed(entity);
}
//////////////////////////////////////COORDINATOR//////////////////////////////////////////