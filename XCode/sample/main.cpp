#include <iostream>
#include "dgmpp.hpp"
#include <typeinfo>
#include <type_traits>

using namespace dgmpp;

int factorial(int x) {
	return x == 0 ? 1 : x * factorial(x-1);
}

namespace N{
	constexpr std::size_t sfCount = 10;
	constexpr int expIterations = 10;
	
	constexpr double pow(double x, int y) {
		return y == 0 ? 1.0 : x * pow(x, y-1);
	}
	
	constexpr int factorial(int x) {
		return x == 0 ? 1 : x * factorial(x-1);
	}
	
	constexpr Float exp(Float x, int n = expIterations) {
		return n == 0 ? 1 : exp(x, n-1) + pow(x,n) / factorial(n);
	};
	
	Float sf(int n) {
		return std::exp(-static_cast<Float>(n * n) / 7.1289);
	}
	
	template<class Function, std::size_t... Indices>
	auto make_array_helper(Function f, std::index_sequence<Indices...>)
	-> std::array<typename std::result_of<Function(std::size_t)>::type, sizeof...(Indices)>
	{
		return {{ f(Indices)... }};
	}
	
	template<int N, class Function>
	auto make_array(Function f)
	-> std::array<typename std::result_of<Function(std::size_t)>::type, N>
	{
		return make_array_helper(f, std::make_index_sequence<N>{});
	}
	
	auto stackingFactor = make_array<sfCount>(sf);
	
	template <typename... Args>
	struct _AssociationComparer {
		bool operator()(const Modifier* modifier) {
			return std::find(associations.begin(), associations.end(), modifier->metaInfo().association) != associations.end();
		}
		
		constexpr _AssociationComparer(Args... arg): associations{arg...} {};
		std::array<MetaInfo::Modifier::Association, sizeof...(Args)> associations;
	};
	
	template <typename... Args>
	_AssociationComparer<Args...> AssociationComparer(Args&&... args) {
		return _AssociationComparer<Args...>(std::forward<Args>(args)...);
	}
}


int main(int argc, const char * argv[]) {
	double d = 1;
	for (auto n = 10; n > 0; n--)
		d += std::pow(10, n) / factorial(n);
//		std::cout << N::pow(10,n) / N::factorial(n) << " | " << std::pow(10, n) / factorial(n) << std::endl;
	double d2 = exp(10);
	auto f = N::exp(-100/7.1289, 10);
	auto gang = Gang::Create();
	auto pilot = gang->addPilot();

	pilot->setSkillLevels(5);
	auto ship = pilot->ship(TypeID::apostle);
	
	for (int i = 0; i < 4; i++)
		ship->addModule(TypeID::CONCORDCapitalRemoteArmorRepairer);
	ship->addModule(TypeID::triageModuleII);
	ship->addModule(TypeID::armorCommandBurstII)->charge(TypeID::armorEnergizingCharge);
	
	ship->addModule(TypeID::imperialNavyCapRecharger);
	ship->addModule(TypeID::imperialNavyCapRecharger);
	
	ship->addModule(TypeID::dominationCapitalCapBattery);
	ship->addModule(TypeID::dominationCapitalCapBattery);
	
	ship->addModule(TypeID::CONCORDCapitalArmorRepairer);
	ship->addModule(TypeID::CONCORDCapitalArmorRepairer);
	for (int i = 0; i < 4; i++)
		ship->addModule(TypeID::darkBloodCapacitorPowerRelay);
//	ship->addModule(TypeID::centumATypeEnergizedAdaptiveNanoMembrane);
	
	ship->addModule(TypeID::capitalCapacitorControlCircuitI);
	ship->addModule(TypeID::capitalCapacitorControlCircuitII);
	ship->addModule(TypeID::capitalCapacitorControlCircuitII);
	
	(*ship)[AttributeID::armorKineticDamageResonance]->dumpAffectors();

	
	std::cout << "DPS: " << (ship->dronesDPS() * 1s).total() << std::endl;
	std::cout << "Volley: " << ship->dronesVolley().total() << std::endl;
	
    return 0;
}


