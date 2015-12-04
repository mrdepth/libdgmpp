#pragma once
#include "types.h"
#include "Module.h"
#include <vector>

namespace eufe {
	
	class HeatSimulator
	{
	public:
		struct State {
			int tNow;
			int duration;
			int reloadTime;
			int shot;
			int clipSize;
			int moduleIndex;
			float heatDamage;
		};

		
		HeatSimulator(std::shared_ptr<Ship> const& ship);
		virtual ~HeatSimulator(void);
		void simulate();
		void reset();
	private:
		std::weak_ptr<Ship> ship_;
		bool isCalculated_;
		typedef std::vector<std::shared_ptr<State>> StatesVector;
		typedef std::vector<std::shared_ptr<Module>> ModulesVector;
		StatesVector states_;

		void simulate(const ModulesVector& modules);
		float heat(float t, float heatCapacity, float heatGeneration);
		float damageProbability(float h, int range, int numberOfOnlineModules, int numberOfSlots, float heatAttenuation);
	};
	
}