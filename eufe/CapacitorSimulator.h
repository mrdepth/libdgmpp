#pragma once
#include "types.h"
#include <vector>

namespace eufe {
	
	class CapacitorSimulator
	{
	public:
		
		class Drain
		{
		public:
			Drain(std::shared_ptr<Module> module, float cycleTime = 0, float capacitorNeed = 0, float clipSize = 0, float reloadTime = 0) : cycleTime_(cycleTime), capacitorNeed_(capacitorNeed), clipSize_(clipSize), reloadTime_(reloadTime), module_(module) {};
			
			bool operator == (const Drain& other)
			{
				return module_.lock() == other.module_.lock();
			}

			float cycleTime_;
			float capacitorNeed_;
			float clipSize_;
			float reloadTime_;
		private:
			std::weak_ptr<Module> module_;
		};
		
		struct State {
			int tNow;
			int duration;
			float capNeed;
			int reloadTime;
			int shot;
			int clipSize;
		};

		
		CapacitorSimulator(std::shared_ptr<Ship> ship, bool reload, int maxTime);
		virtual ~CapacitorSimulator(void);
		
		void reset();
		
		void setReload(bool reload);
		void setMaxTime(int maxTime);
		
		bool getReload();
		int getMaxTime();
		int getIterations();
		bool isCapStable();
		float getCapLastsTime();
		float getCapStableLevel();
		float getCapUsed();
		float getCapRecharge();
		
		
	private:
		typedef std::vector<std::shared_ptr<State>> StatesVector;
		
		std::weak_ptr<Ship> ship_;
		
		StatesVector states_;
		
		bool isCalculated_;
		bool reload_;

		int period_;
		int maxTime_;
		float capacitorRecharge_;
		float capacitorCapacity_;
		float capRecharge_;
		float capUsed_;
		int iterations_;
		int time_;
		float capStableEVE_;
		float capStableLow_;
		float capStableHigh_;
		
		void internalReset();
		void run();
        
        int gcd(int a, int b);
        int lcm(int a, int b);
	};
	
}