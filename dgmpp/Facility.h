#pragma once
#include "types.h"
#include "Commodity.h"
#include "Cycle.h"
#include "State.h"
#include <iterator>

namespace dgmpp {
	extern bool operator == (const std::list<std::shared_ptr<const Commodity>>& left, const std::list<std::shared_ptr<const Commodity>>& right);
	extern bool operator != (const std::list<std::shared_ptr<const Commodity>>& left, const std::list<std::shared_ptr<const Commodity>>& right);

	class Facility : public std::enable_shared_from_this<Facility> {
	public:
		Facility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);

		TypeID getTypeID() const {return typeID_;};
		const std::string& getTypeName() const  {return typeName_;};
		virtual TypeID getGroupID() const {return 0;};
		int64_t getIdentifier() const {return identifier_;};
		std::string getFacilityName() const;
		std::shared_ptr<Planet> getOwner() const {return owner_.lock();};

		void addInput(const std::shared_ptr<const Route>& route);
		void addOutput(const std::shared_ptr<const Route>& route);
		void removeInput(const std::shared_ptr<const Route>& route);
		void removeOutput(const std::shared_ptr<const Route>& route);
		
		const std::list<std::shared_ptr<const Route>>& getInputs() const {return inputs_;};
		const std::list<std::shared_ptr<const Route>>& getOutputs() const {return outputs_;};

		double getCapacity() const {return capacity_;};

		size_t numberOfStates() const {return states_.size();};
		std::shared_ptr<const State> getState(double timestamp) const;
		const std::list<std::shared_ptr<State>>& getStates() const {return states_;};

		virtual void addCommodity(const Commodity& commodity);
		virtual void addCommodity(TypeID typeID, uint32_t quantity);
		virtual void extractCommodity(const Commodity& commodity);
		virtual void clear();
		std::list<const Commodity> getCommodities() const;
		const Commodity& getCommodity(const Commodity& commodity) const;
		const Commodity& getIncomming(const Commodity& commodity) const;
		
		virtual uint32_t getFreeStorage(const Commodity& commodity) const;
		virtual double getFreeVolume() const;
		virtual double getVolume() const;

		virtual std::string toJSONString() const;
		friend std::ostream& operator<<(std::ostream& os, const Facility& facility);
		
		virtual bool routed() const {return true;};

		virtual void update(double time);

	protected:
		std::list<std::shared_ptr<const Route>> inputs_;
		std::list<std::shared_ptr<const Route>> outputs_;
		std::list<std::shared_ptr<State>> states_;

		mutable std::map<TypeID, std::shared_ptr<Commodity>> commodities_;
		mutable std::map<TypeID, std::shared_ptr<Commodity>> incomming_;
		
		virtual double getNextUpdateTime() const;
		virtual int priority() const {return 0;};
		
		
		friend class Planet;
		friend class Route;
	private:
		std::weak_ptr<Planet> owner_;
		TypeID typeID_;
		std::string typeName_;
		mutable std::string facilityName_;
		double capacity_;
		int64_t identifier_;
	};
}