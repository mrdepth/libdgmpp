#pragma once
#include "types.h"
#include "Item.h"
#include "Type.hpp"

namespace dgmpp {
	
	class Charge : public Item
	{
	public:
		Charge(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Item> const& owner);
		virtual ~Charge(void);
		std::shared_ptr<Charge> shared_from_this() {
			return std::static_pointer_cast<Charge>(Item::shared_from_this());
		}
		bool isAssistance();
		bool isOffensive();
		bool canBeActive();

		virtual Item* ship();
		virtual Item* character();
		virtual Item* other();
	protected:
		virtual void lazyLoad();
	private:
		bool canBeActive_;
	};
	
}

namespace dgmpp2 {
	class Charge: public Type {
	public:
		static std::unique_ptr<Charge> Create (TypeID typeID) { return std::unique_ptr<Charge>(new Charge(typeID)); }
		
	protected:
		virtual Type* domain(MetaInfo::Modifier::Domain domain) override;
		bool canBeActive() const	{ return flags_.canBeActive; }
		bool requireTarget() const	{ return flags_.requireTarget; }
		
	private:
		friend class Module;
		
		struct {
			bool canBeActive : 1;
			bool requireTarget : 1;
		} flags_;
		
		Charge(TypeID typeID);
	};
}
