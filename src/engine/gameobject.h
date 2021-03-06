#pragma once

#include <algorithm>
#include <memory>
#include <typeinfo>
#include <vector>

#include <SFML/Graphics.hpp>

#include "engine/component.h"
#include "engine/config.h"

#include "util/type.h"

namespace engine {

class GameObject {
   public:
    GameObject() = default;
    virtual ~GameObject() = default;

    template <typename ComponentType, typename... ConstructorArgs>
    ComponentType& createComponent(const ConstructorArgs&... constructorArgs);
    template <typename ComponentType>
    ComponentType* getComponent();

    virtual void draw(sf::RenderWindow& window);
    virtual void update(const sf::Time& frameTime);
    virtual void fixedUpdate(const sf::Time& frameTime);

   private:
    std::vector<std::unique_ptr<Component>> componentPtrs;
};

template <typename ComponentType, typename... ConstructorArgs>
inline ComponentType& GameObject::createComponent(const ConstructorArgs&... constructorArgs) {
    static_assert(std::is_base_of<Component, ComponentType>::value, "Class not subclass of Component");
    componentPtrs.push_back(std::make_unique<ComponentType>(*this, constructorArgs...));
    return static_cast<ComponentType&>(*componentPtrs.back());
}

template <typename ComponentType>
inline ComponentType* GameObject::getComponent() {
    auto componentPtrIt = std::find_if(componentPtrs.begin(), componentPtrs.end(),
                                       [](auto& componentPtr) { return util::isType<ComponentType>(*componentPtr); });
    if (componentPtrIt == componentPtrs.end()) {
        return nullptr;
    } else {
        return static_cast<ComponentType*>(componentPtrIt->get());
    }
}

}  // namespace engine
