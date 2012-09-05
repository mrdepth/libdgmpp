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

		
		HeatSimulator(Ship* ship);
		virtual ~HeatSimulator(void);
		void simulate();
		void reset();
	private:
		Ship* ship_;
		bool isCalculated_;
		typedef std::vector<State*> StatesVector;
		typedef std::vector<Module*> ModulesVector;
		StatesVector states_;

		void simulate(const ModulesVector& modules);
		float heat(float t, float heatCapacity, float heatGeneration);
		float damageProbability(float h, int range, int numberOfOnlineModules, int numberOfSlots, float heatAttenuation);
	};
	
}