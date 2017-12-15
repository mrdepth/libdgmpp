#pragma once
#include "types.h"
#include "Modifier.h"
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include "MetaInfo.hpp"

namespace dgmpp {

	class EffectPrototype;
	
	class Effect
	{

	public:
		enum class Category
		{
			generic = 0,
			active = 1, //also online effect
			target = 2,
			passive = 4,
			overloaded = 5,
			dungeon = 6,
			system = 7
		};
		
		static std::shared_ptr<Effect> getEffect(std::shared_ptr<Engine> const& engine, EffectID effectID, std::shared_ptr<Item> const& owner);
		
		Effect(std::shared_ptr<Engine> const& engine, std::shared_ptr<EffectPrototype> const& prototype, std::shared_ptr<Item> const& owner);
		virtual ~Effect(void);
		virtual bool addEffect(Environment* environment);
		virtual bool removeEffect(Environment* environment);
		EffectID getEffectID() const;
		Category getCategory() const;
		const char* getEffectName() const;
		friend std::ostream& operator<<(std::ostream& os, Effect& effect);
		bool isAssistance() const;
		bool isOffensive() const;
	private:
		std::weak_ptr<Engine> engine_;
		std::weak_ptr<Item> owner_;
		std::shared_ptr<EffectPrototype> prototype_;
		std::map<Modifier::Type, ModifiersList> modifiers_;
	};
}


