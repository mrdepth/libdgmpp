//
//  Effect.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//
#pragma once
#include "MetaInfo.hpp"
#include "Modifier.hpp"
#include "WarfareBuff.hpp"

namespace dgmpp {
	
	class Effect {
	public:
		Effect (const Effect& other) = delete;
		Effect (Effect&& other) = delete;
		Effect& operator= (const Effect& other) = delete;
		Effect& operator= (Effect&& other) = delete;
		virtual ~Effect() = default;
		
		const MetaInfo::Effect& metaInfo() const noexcept			{ return metaInfo_; }
		const std::list<Modifier>& modifiers() const noexcept		{ return modifiers_; };
		const std::list<WarfareBuff>& warfareBuffs() const noexcept	{ return warfareBuffs_; };
		Type& owner() const noexcept { return owner_; }
		
		bool isActive() const noexcept { return active_; }

	protected:
		std::list<Modifier>	modifiers_;
		std::list<WarfareBuff> warfareBuffs_;
		
		Effect (const MetaInfo::Effect& metaInfo, Type& owner);
		virtual void setActive (bool active) { active_ = active; }

	private:
		friend class Type;
		
		bool active_ = false;
		Type& owner_;
		const MetaInfo::Effect& metaInfo_;
		
	};
	
	class WarfareBuffEffect: public Effect {
	private:
		friend class Type;
		
		WarfareBuffEffect (const MetaInfo::Effect& metaInfo, Type& owner) : Effect(metaInfo, owner) {}
		
		virtual void setActive (bool active) override;
	};
}

