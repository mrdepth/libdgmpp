//
//  Effect.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//
#pragma once
#include "MetaInfo.hpp"
#include "Modifier.hpp"

namespace dgmpp2 {
	
	class Effect {
	public:
		Effect (const Effect& other) = delete;
		Effect (Effect&& other) = delete;
		Effect& operator= (const Effect& other) = delete;
		Effect& operator= (Effect&& other) = delete;
		~Effect() = default;
		
		const MetaInfo::Effect& metaInfo() const			{ return metaInfo_; }
		const std::list<const Modifier>& modifiers() const	{ return modifiers_; };
		
		bool active() const { return active_; }
		
	private:
		friend class Type;
		
		bool active_ = false;
		const MetaInfo::Effect&		metaInfo_;
		std::list<const Modifier>	modifiers_;
		
		Effect (const MetaInfo::Effect& metaInfo, Type& owner);
		void active (bool active) { active_ = active; }
	};
	
}

