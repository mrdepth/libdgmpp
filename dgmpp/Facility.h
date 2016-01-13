#pragma once
#include "types.h"

namespace dgmpp {
	class Facility {
	public:
		Facility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		void addInput(const Route* route);
		void addOutput(const Route* route);
		void removeInput(const Route* route);
		void removeOutput(const Route* route);
		TypeID getTypeID() const {return typeID_;};
		const std::string& getTypeName() const  {return typeName_;};
		virtual TypeID getGroupID() const {return 0;};
		double getCapacity() const {return capacity_;};
		int64_t getIdentifier() const {return identifier_;};
	protected:
		std::list<const Route*> inputs_;
		std::list<const Route*> outputs_;
	private:
		std::weak_ptr<Planet> owner_;
		TypeID typeID_;
		std::string typeName_;
		double capacity_;
		int64_t identifier_;
	};
}