#pragma once

// internal code
#include "Entity.hpp"
#include "Events/Event.hpp"

// standard libraries
#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>

// external libraries
#include <glm/glm.hpp>

/*
Code for implementing template functions for components is taken from:
https://stackoverflow.com/questions/44105058/how-does-unitys-getcomponent-work
*/

#define TO_STRING( x ) #x

// CLASS_DECLARATION
// This macro must be included in the declaration of any subclass of component. It declares variables used in type checking.


#define CLASS_DECLARATION( classname )                                                      \
public:                                                                                     \
    static const std::size_t Type;                                                          \
    virtual bool IsClassType( const std::size_t classType ) const override;                 \

// CLASS_DEFINITION
// This macro must be included in the class definition to properly initialize variables used in type checking.
// Take special care to ensure that the proper parentclass is indicated or the run-time type information will be
// incorrect. Only works on single-inheritance RTTI.

#define CLASS_DEFINITION( parentclass, childclass )                                         \
const std::size_t childclass::Type = std::hash< std::string >()( TO_STRING( childclass ) ); \
bool childclass::IsClassType( const std::size_t classType ) const {                         \
        if ( classType == childclass::Type )                                                \
            return true;                                                                    \
        return parentclass::IsClassType( classType );                                       \
}   

// Components make up Entities and give them Data and Functionality
// Add a component to the Entity and it will be updated, receive events
// and render; called from the Application
// A Component does not need to implement all functions and can implement only those it needs
// When creating a new type of component the CLASS_DEFINITION needs to be added in the ComponentClasses.cpp
class Component
{
public:
	static const std::size_t Type;
	virtual bool IsClassType(const std::size_t classType) const
	{
		return classType == Type;
	}

	Component(Entity* entity, bool enabled = true) : m_Entity(entity), m_Enabled(enabled) {}
	Component(const Component&) = default;

	virtual void OnUpdate(float deltaTime) {}
	virtual void OnEvent(Event& event) {}
	virtual void Draw(const glm::mat4& view, const glm::mat4& projection) {}

	inline Entity& GetEntity() { return *m_Entity; }

	bool GetEnabled() const { return m_Enabled; }
	void SetEnabled(bool enabled) { m_Enabled = enabled; }

protected:
	Entity* m_Entity;
	bool m_Enabled;

};