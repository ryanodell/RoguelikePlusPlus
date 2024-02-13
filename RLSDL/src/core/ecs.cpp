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

 //////////////////////////////////////COMPONENT ARRAY////////////////////////////////////
 ///NOTES: Guard clauses commented out until time to finish testing
template <typename T>
void ComponentArray<T>::InsertData(Entity entity, T component) {
    // if(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) {
    //     Logger::LogError("Component Added to the same entity more than once: EntityID: %u", entity);
    //     CRASH_PROGRAM;
    // }
    size_t newIndex = mSize;
    mEntityToIndexMap[entity] = newIndex;
    mIndexToEntityMap[newIndex] = entity;
    mComponentArray[newIndex] = component;
    ++mSize;
}

template <typename T>
void ComponentArray<T>::RemoveData(Entity entity) {
    // if(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end()) {
    //     Logger::LogError("Component Added to the same entity more than once: EntityID: %u", entity);
    //     CRASH_PROGRAM;
    // }
    size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
    size_t indexOfLastElement = mSize - 1;
    mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];
    Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
	mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
	mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;
	mEntityToIndexMap.erase(entity);
	mIndexToEntityMap.erase(indexOfLastElement);
	--mSize;
}

template <typename T>
T &ComponentArray<T>::GetData(Entity entity) {
    // if(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end()) {
    //     Logger::LogError("Retrieving non-existent component.");
    // }
    return mComponentArray[mEntityToIndexMap[entity]];
}

template <typename T>
void ComponentArray<T>::EntityDestroyed(Entity entity) {
    if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) {
        RemoveData(entity);
	}
}
//////////////////////////////////////COMPONENT ARRAY////////////////////////////////////

//////////////////////////////////////COMPONENT MANAGER////////////////////////////////////
template <typename T>
void ComponentManager::RegisterComponent() {
    const char* typeName = typeid(T).name();
    //assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");
     mComponentTypes.insert({typeName, mNextComponentType});
     mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
    ++mNextComponentType;
}

template <typename T>
ComponentType ComponentManager::GetComponentType() {
    const char* typeName = typeid(T).name();
    //assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");	
	return mComponentTypes[typeName];
}

template <typename T>
void ComponentManager::AddComponent(Entity entity, T component) {
    GetComponentArray<T>()->InsertData(entity, component);
}

template <typename T>
void ComponentManager::RemoveComponent(Entity entity) {
    GetComponentArray<T>()->RemoveData(entity);
}

template <typename T>
T &ComponentManager::GetComponent(Entity entity) {
    return GetComponentArray<T>()->GetData(entity);
}

void ComponentManager::EntityDestroyed(Entity entity) {
    for(auto const& pair : mComponentArrays) {        
        auto const& component = pair.second;        
        component->EntityDestroyed(entity);
    }
}
//////////////////////////////////////COMPONENT MANAGER////////////////////////////////////

//////////////////////////////////////////SYSTEM///////////////////////////////////////////
template <typename T>
std::shared_ptr<T> SystemManger::RegisterSystem() {
    const char* typeName = typeid(T).name();
	//assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");
	auto system = std::make_shared<T>();
	mSystems.insert({typeName, system});
	return system;
}

template <typename T>
void SystemManger::SetSignature(Signature signature) {
    const char* typeName = typeid(T).name();
	//assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");
	mSignatures.insert({typeName, signature});
}

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

void Coordinator::Init() {

}

Entity Coordinator::CreateEntity() {
    return Entity();
}

void Coordinator::DestroyEntity(Entity entity) {

}

template <typename T>
void Coordinator::RegisterComponent() {

}

template <typename T>
void Coordinator::AddComponent(Entity entity, T component) {

}

template <typename T>
void Coordinator::RemoveComponent(Entity entity) {

}

template <typename T>
T &Coordinator::GetComponent(Entity entity) {

}

template <typename T>
ComponentType Coordinator::GetComponentType() {
    return ComponentType();
}

template <typename T>
std::shared_ptr<T> Coordinator::RegisterSystem() {
    return std::shared_ptr<T>();
}

template <typename T>
void Coordinator::SetSystemSignature(Signature signature) {

}
