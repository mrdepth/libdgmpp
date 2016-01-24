#pragma once
#include "types.h"
#include "Commodity.h"
#include "Cycle.h"
#include <iterator>

namespace dgmpp {
	class Facility : public std::enable_shared_from_this<Facility> {
	public:
		Facility(TypeID typeID, const std::string& typeName, double capacity, std::shared_ptr<Planet> const& owner = std::shared_ptr<Planet>(nullptr), int64_t identifier = 0);
		void addInput(const std::shared_ptr<const Route>& route);
		void addOutput(const std::shared_ptr<const Route>& route);
		void removeInput(const std::shared_ptr<const Route>& route);
		void removeOutput(const std::shared_ptr<const Route>& route);
		TypeID getTypeID() const {return typeID_;};
		const std::string& getTypeName() const  {return typeName_;};
		virtual TypeID getGroupID() const {return 0;};
		double getCapacity() const {return capacity_;};
		int64_t getIdentifier() const {return identifier_;};
		std::shared_ptr<Planet> getOwner() const {return owner_.lock();};

		const std::list<std::shared_ptr<const Route>>& getInputs() const {return inputs_;};
		const std::list<std::shared_ptr<const Route>>& getOutputs() const {return outputs_;};

		virtual double getLaunchTime() const {return 0;};
		virtual double getInstallTime() const {return 0;};
		virtual double getExpiryTime() const {return 0;};
		virtual double getCycleTime() const {return 0;};
		
		size_t numberOfCycles() const {return cycles_.size();};
		std::shared_ptr<const Cycle> getCycle(double timeStamp) const;
		const std::list<std::shared_ptr<Cycle>>& getCycles() const {return cycles_;};

		
		virtual void addCommodity(const Commodity& commodity);
		virtual void addCommodity(TypeID typeID, uint32_t quantity);
		virtual void extractCommodity(const Commodity& commodity);
		virtual void clear();
		std::list<std::shared_ptr<const Commodity>> getCommodities() const;
		const Commodity& getCommodity(const Commodity& commodity) const;
		
		virtual int32_t getFreeStorage(const Commodity& commodity) const;
		virtual double getFreeVolume() const;
		virtual double getVolume() const;

		virtual std::string toJSONString() const;
		friend std::ostream& operator<<(std::ostream& os, const Facility& facility);
		
		virtual bool routed() const {return true;};

	protected:
		std::list<std::shared_ptr<const Route>> inputs_;
		std::list<std::shared_ptr<const Route>> outputs_;
		std::list<std::shared_ptr<Cycle>> cycles_;
		mutable std::map<TypeID, std::shared_ptr<Commodity>> commodities_;
		
		virtual double getCycleEndTime() const;
		virtual double getNextUpdateTime() const;
		virtual void finishCycle(double cycleTime) {};
		virtual void startCycle(double cycleTime) {};
		virtual int priority() const {return 0;};
		virtual void update(double time) {};
		
		friend class Planet;
		double nextUpdateTime_;
	private:
		std::weak_ptr<Planet> owner_;
		TypeID typeID_;
		std::string typeName_;
		double capacity_;
		int64_t identifier_;
	};
}