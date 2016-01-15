#pragma once
#include "types.h"
#include "Commodity.h"

namespace dgmpp {
	class Facility : public std::enable_shared_from_this<Facility> {
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
		std::shared_ptr<Planet> getOwner() const {return owner_.lock();};

		const std::list<const Route*>& getInputs() const {return inputs_;};
		const std::list<const Route*>& getOutputs() const {return outputs_;};

		virtual double getLastLaunchTime() const {return 0;};
		virtual double getInstallTime() const {return 0;};
		virtual double getExpiryTime() const {return 0;};
		virtual double getCycleTime() const {return 0;};
		
		virtual double getCycleEndTime() const;
		virtual void finishCycle(double cycleTime) {};
		virtual void startCycle(double cycleTime) {};
		
		virtual int priority() const {return 0;};
		
		virtual void addCommodity(const Commodity& commodity);
		virtual void addCommodity(TypeID typeID, int32_t quantity);
		virtual void extractCommodity(const Commodity& commodity);
		virtual void clear();
		std::list<std::shared_ptr<const Commodity>> getCommodities() const;
		const Commodity& getCommodity(const Commodity& commodity) const;
		
		virtual int32_t getFreeStorage(const Commodity& commodity) const;
		virtual double getFreeVolume() const;

		virtual std::string toJSONString() const;
		friend std::ostream& operator<<(std::ostream& os, const Facility& facility);

	protected:
		std::list<const Route*> inputs_;
		std::list<const Route*> outputs_;
		mutable std::map<TypeID, std::shared_ptr<Commodity>> commodities_;
	private:
		std::weak_ptr<Planet> owner_;
		TypeID typeID_;
		std::string typeName_;
		double capacity_;
		int64_t identifier_;
	};
}