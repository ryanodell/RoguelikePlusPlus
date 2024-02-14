#ifndef ECS_H
#define ECS_H

#include <set>
#include <bitset>
#include <cstdint>
#include <array>
#include <queue>
#include <unordered_map>
#include <memory>
#include "logger.h"
#include "macros.h"
#include "../components.h"

//Butterfly wings or Swallow Tail Plant - Note Don't lose.

const int MAX_ENTITIES = 5000;
const int MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;
using ComponentType = std::uint8_t;
using Entity = std::uint32_t;

class EntityManger {
public:
    EntityManger();
    Entity CreateEntity();
    void DestroyEntity(Entity entity);
    void SetSignature(Entity entity, Signature signature);
    Signature GetSignature(Entity entity);

private:
    std::queue<Entity> mAvailableEntities;
    std::array<Signature, MAX_ENTITIES> mSignatures;
    uint32_t mLivingEntityCount;
};

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:
    void InsertData(Entity entity, T component) {
        // if(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) {
        //     Logger::LogError("Component Added to the same entity more than once: EntityID: %u", entity);
        //     CRASH_PROGRAM;
        // }
        size_t newIndex = mSize;
        mEntityToIndexMap[entity] = newIndex;
        mIndexToEntityMap[newIndex] = entity;
        mComponentArray[newIndex] = component;
        ++mSize;
    };
    void RemoveData(Entity entity) {
        size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
        size_t indexOfLastElement = mSize - 1;
        mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];
        Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
	    mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
	    mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;
	    mEntityToIndexMap.erase(entity);
	    mIndexToEntityMap.erase(indexOfLastElement);
	    --mSize;
    };
    T& GetData(Entity entity) {
        // if(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end()) {
        //     Logger::LogError("Retrieving non-existent component.");
        // }
        return mComponentArray[mEntityToIndexMap[entity]];
    };
    void EntityDestroyed(Entity entity) override {
    if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) {
        RemoveData(entity);
	};
}
private:
    std::array<T, MAX_ENTITIES> mComponentArray;
    std::unordered_map<Entity, size_t> mEntityToIndexMap;
    std::unordered_map<size_t, Entity> mIndexToEntityMap;
    size_t mSize;
};

class ComponentManager {
public:
    template <typename T>
    void RegisterComponent() {
        const char* typeName = typeid(T).name();
        //assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");
         mComponentTypes.insert({typeName, mNextComponentType});
         mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
        ++mNextComponentType;
    };
    template <typename T>
    ComponentType GetComponentType() {
        const char* typeName = typeid(T).name();
        //assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");	
    	return mComponentTypes[typeName];
    };

    template <typename T>
    void AddComponent(Entity entity, T component) {
        GetComponentArray<T>()->InsertData(entity, component);
    };

    template <typename T>
    void RemoveComponent(Entity entity) {
        GetComponentArray<T>()->RemoveData(entity);
    };

    template <typename T>
    T& GetComponent(Entity entity) {
        return GetComponentArray<T>()->GetData(entity);
    };
    void EntityDestroyed(Entity entity);

private:
    std::unordered_map<const char*, ComponentType> mComponentTypes;
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> mComponentArrays;
    ComponentType mNextComponentType;    
    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray() {
        const char* typeName = typeid(T).name();
        if(mComponentTypes.find(typeName) == mComponentTypes.end()){
             Logger::LogError("Component not registered before use.");
        }
		return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
    }
};

class System {
public:
    std::set<Entity> mEntities;
};

class SystemManger {
public:
    template <typename T>
    std::shared_ptr<T> RegisterSystem() {
        const char* typeName = typeid(T).name();
    	//assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");
    	auto system = std::make_shared<T>();
    	mSystems.insert({typeName, system});
    	return system;
    };
    template <typename T>
    void SetSignature(Signature signature) {
        const char* typeName = typeid(T).name();
    	//assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");
    	mSignatures.insert({typeName, signature});
    };
    void EntityDestroyed(Entity entity);
    void EntitySignatureChanged(Entity entity, Signature entitySignature);
private:
    std::unordered_map<const char*, Signature> mSignatures;
    std::unordered_map<const char*, std::shared_ptr<System>> mSystems;
};

class Coordinator {
public:
    void Init();
    Entity CreateEntity();
    void DestroyEntity(Entity entity);
    template <typename T>
    void RegisterComponent() {
        mComponentManager->RegisterComponent<T>();
    };
    template <typename T>
    void AddComponent(Entity entity, T component) {
        mComponentManager->AddComponent<T>(entity, component);
        auto signature = mEntityManager->GetSignature(entity);
        signature.set(mComponentManager->GetComponentType<T>(), true);
        mEntityManager->SetSignature(entity, signature);
        mSystemManager->EntitySignatureChanged(entity, signature);
    };

    template <typename T>
    void RemoveComponent(Entity entity) {
        mComponentManager->RemoveComponent<T>(entity);
        auto signature = mEntityManager->GetSignature(entity);
        signature.set(mComponentManager->GetComponentType<T>(), false);
    	mEntityManager->SetSignature(entity, signature);
    	mSystemManager->EntitySignatureChanged(entity, signature);
    };

    template <typename T>
    T& GetComponent(Entity entity) {
        return mComponentManager->GetComponent<T>(entity);
    };

    template <typename T>
    ComponentType GetComponentType() {
        return mComponentManager->GetComponentType<T>();
    };

    template <typename T>
    std::shared_ptr<T> RegisterSystem() {
        return mSystemManager->RegisterSystem<T>();
    };

    template <typename T>
    void SetSystemSignature(Signature signature) {
        mSystemManager->SetSignature<T>(signature);
    };

private:
    std::unique_ptr<ComponentManager> mComponentManager;
    std::unique_ptr<EntityManger> mEntityManager;
    std::unique_ptr<SystemManger> mSystemManager;
};

#endif


