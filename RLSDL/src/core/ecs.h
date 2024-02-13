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
    void InsertData(Entity entity, T component);
    void RemoveData(Entity entity);
    T& GetData(Entity entity);
    void EntityDestroyed(Entity entity) override;
private:
    std::array<T, MAX_ENTITIES> mComponentArray;
    std::unordered_map<Entity, size_t> mEntityToIndexMap;
    std::unordered_map<size_t, Entity> mIndexToEntityMap;
    size_t mSize;
};

class ComponentManager {
public:
    template<typename T>
    void RegisterComponent();
    template<typename T>
    ComponentType GetComponentType();
    template<typename T>
    void AddComponent(Entity entity, T component);
    template<typename T>
    void RemoveComponent(Entity entity);
    template<typename T>
    T& GetComponent(Entity entity);
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
    template<typename T>
    std::shared_ptr<T> RegisterSystem();
    template<typename T>
    void SetSignature(Signature signature);
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
    template<typename T>
    void RegisterComponent();
    template<typename T>
    void AddComponent(Entity entity, T component);
    template<typename T>
    void RemoveComponent(Entity entity);
    template<typename T>
    T& GetComponent(Entity entity);
    template<typename T>
    ComponentType GetComponentType();
    template<typename T>
    std::shared_ptr<T> RegisterSystem();
    template<typename T>
    void SetSystemSignature(Signature signature);

private:
    std::unique_ptr<ComponentManager> mComponentManager;
    std::unique_ptr<EntityManger> mEntityManager;
    std::unique_ptr<SystemManger> mSystemManager;
};

#endif


