#pragma once
#include "Effect.h"

namespace dgmpp {
	class GangBoost;
	
	class GangBoostEffect: public Effect {
	public:
		GangBoostEffect(std::shared_ptr<Engine> const& engine, std::shared_ptr<EffectPrototype> const& prototype, std::shared_ptr<Item> const& owner);
		
		virtual bool addEffect(Environment* environment);
		virtual bool removeEffect(Environment* environment);
	private:
		std::list<std::shared_ptr<GangBoost>> boosts_;
	};
}
