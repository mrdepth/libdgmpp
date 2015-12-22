#include "Attribute.h"
#include "ThirdParty/sqlite3.h"
#include "Engine.h"
#include <algorithm>
#include "Item.h"
#include <limits>
#include <cmath>
#include "Ship.h"
#include "Character.h"
#include <sstream>
#include <functional>

using namespace eufe;

const TypeID eufe::IS_ONLINE_ATTRIBUTE_ID = 2;
const TypeID eufe::MASS_ATTRIBUTE_ID = 4;
const TypeID eufe::CAPACITY_ATTRIBUTE_ID = 38;
const TypeID eufe::VOLUME_ATTRIBUTE_ID = 161;
const TypeID eufe::RADIUS_ATTRIBUTE_ID = 162;
const TypeID eufe::REQUIRED_SKILL1_ATTRIBUTE_ID = 182;
const TypeID eufe::REQUIRED_SKILL2_ATTRIBUTE_ID = 183;
const TypeID eufe::REQUIRED_SKILL3_ATTRIBUTE_ID = 184;
const TypeID eufe::REQUIRED_SKILL4_ATTRIBUTE_ID = 1285;
const TypeID eufe::REQUIRED_SKILL5_ATTRIBUTE_ID = 1289;
const TypeID eufe::REQUIRED_SKILL6_ATTRIBUTE_ID = 1290;
const TypeID eufe::RACE_ID_ATTRIBUTE_ID = 195;
const TypeID eufe::SKILL_LEVEL_ATTRIBUTE_ID = 280;
const TypeID eufe::IMPLANTNESS_ATTRIBUTE_ID = 331;
const TypeID eufe::BOOSTERNESS_ATTRIBUTE_ID = 1087;

const TypeID eufe::LOW_SLOTS_ATTRIBUTE_ID = 12;
const TypeID eufe::MED_SLOTS_ATTRIBUTE_ID = 13;
const TypeID eufe::HI_SLOTS_ATTRIBUTE_ID = 14;
const TypeID eufe::RIG_SLOTS_ATTRIBUTE_ID = 1137;
const TypeID eufe::MAX_SUBSYSTEMS_SLOTS_ATTRIBUTE_ID = 1367;

const TypeID eufe::LAUNCHER_SLOTS_LEFT_ATTRIBUTE_ID = 101;
const TypeID eufe::TURRET_SLOTS_LEFT_ATTRIBUTE_ID = 102;

const TypeID eufe::FITS_TO_SHIP_TYPE_ATTRIBUTE_ID = 1380;
const TypeID eufe::CAN_FIT_SHIP_TYPE1_ATTRIBUTE_ID = 1302;
const TypeID eufe::CAN_FIT_SHIP_TYPE2_ATTRIBUTE_ID = 1303;
const TypeID eufe::CAN_FIT_SHIP_TYPE3_ATTRIBUTE_ID = 1304;
const TypeID eufe::CAN_FIT_SHIP_TYPE4_ATTRIBUTE_ID = 1305;
const TypeID eufe::CAN_FIT_SHIP_TYPE5_ATTRIBUTE_ID = 1944;

const TypeID eufe::CAN_FIT_SHIP_GROUP1_ATTRIBUTE_ID = 1298;
const TypeID eufe::CAN_FIT_SHIP_GROUP2_ATTRIBUTE_ID = 1299;
const TypeID eufe::CAN_FIT_SHIP_GROUP3_ATTRIBUTE_ID = 1300;
const TypeID eufe::CAN_FIT_SHIP_GROUP4_ATTRIBUTE_ID = 1301;
const TypeID eufe::CAN_FIT_SHIP_GROUP5_ATTRIBUTE_ID = 1872;
const TypeID eufe::CAN_FIT_SHIP_GROUP6_ATTRIBUTE_ID = 1879;
const TypeID eufe::CAN_FIT_SHIP_GROUP7_ATTRIBUTE_ID = 1880;
const TypeID eufe::CAN_FIT_SHIP_GROUP8_ATTRIBUTE_ID = 1881;
const TypeID eufe::CAN_FIT_SHIP_GROUP9_ATTRIBUTE_ID = 2065;

const TypeID eufe::SUBSYSTEM_SLOT_ATTRIBUTE_ID = 1366;
const TypeID eufe::RIG_SIZE_ATTRIBUTE_ID = 1547;
const TypeID eufe::MAX_GROUP_FITTED_ATTRIBUTE_ID = 1544;

const TypeID eufe::CHARGE_SIZE_ATTRIBUTE_ID = 128;
const TypeID eufe::CHARGE_GROUP1_ATTRIBUTE_ID = 604;
const TypeID eufe::CHARGE_GROUP2_ATTRIBUTE_ID = 605;
const TypeID eufe::CHARGE_GROUP3_ATTRIBUTE_ID = 606;
const TypeID eufe::CHARGE_GROUP4_ATTRIBUTE_ID = 609;
const TypeID eufe::CHARGE_GROUP5_ATTRIBUTE_ID = 610;

const TypeID eufe::MAX_GROUP_ACTIVE_ATTRIBUTE_ID = 763;

const TypeID eufe::SPEED_ATTRIBUTE_ID = 51;
const TypeID eufe::DURATION_ATTRIBUTE_ID = 73;
const TypeID eufe::MISSILE_LAUNCH_DURATION_ATTRIBUTE_ID = 506;
const TypeID eufe::RELOAD_TIME_ATTRIBUTE_ID = 1795;
const TypeID eufe::MODULE_REACTIVATION_DELAY_ATTRIBUTE_ID = 669;

const TypeID eufe::CHARGE_RATE_ATTRIBUTE_ID = 56;
const TypeID eufe::CRYSTALS_GET_DAMAGED_ATTRIBUTE_ID = 786;

const TypeID eufe::HP_ATTRIBUTE_ID = 9;
const TypeID eufe::CRYSTAL_VOLATILITY_CHANCE_ATTRIBUTE_ID = 783;
const TypeID eufe::CRYSTAL_VOLATILITY_DAMAGE_ATTRIBUTE_ID = 784;
const TypeID eufe::CAPACITOR_NEED_ATTRIBUTE_ID = 6;
const TypeID eufe::CAPACITOR_BONUS_ATTRIBUTE_ID = 67;
const TypeID eufe::POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID = 90;
const TypeID eufe::ENERGY_DESTABILIZATION_AMOUNT_ATTRIBUTE_ID = 97;

const TypeID eufe::CAPACITOR_CAPACITY_ATTRIBUTE_ID = 482;
const TypeID eufe::CHARGE_ATTRIBUTE_ID = 18;
const TypeID eufe::RECHARGE_RATE_ATTRIBUTE_ID = 55;

const TypeID eufe::DISALLOW_ASSISTANCE_ATTRIBUTE_ID = 854;
const TypeID eufe::DISALLOW_OFFENSIVE_MODIFIERS_ATTRIBUTE_ID = 872;

const TypeID eufe::EM_DAMAGE_ATTRIBUTE_ID = 114;
const TypeID eufe::KINETIC_DAMAGE_ATTRIBUTE_ID = 117;
const TypeID eufe::EXPLOSIVE_DAMAGE_ATTRIBUTE_ID = 116;
const TypeID eufe::THERMAL_DAMAGE_ATTRIBUTE_ID = 118;
const TypeID eufe::DAMAGE_MULTIPLIER_ATTRIBUTE_ID = 64;
const TypeID eufe::MISSILE_DAMAGE_MULTIPLIER_ATTRIBUTE_ID = 212;

const TypeID eufe::MAX_RANGE_ATTRIBUTE_ID = 54;
const TypeID eufe::SHIELD_TRANSFER_RANGE_ATTRIBUTE_ID = 87;
const TypeID eufe::POWER_TRANSFER_RANGE_ATTRIBUTE_ID = 91;
const TypeID eufe::ENERGY_DESTABILIZATION_RANGE_ATTRIBUTE_ID = 98;
const TypeID eufe::EMP_FIELD_RANGE_ATTRIBUTE_ID = 99;
const TypeID eufe::ECM_BURST_RANGE_ATTRIBUTE_ID = 142;
const TypeID eufe::WARP_SCRAMBLE_RANGE_ATTRIBUTE_ID = 103;
const TypeID eufe::CARGO_SCAN_RANGE_ATTRIBUTE_ID = 126;
const TypeID eufe::SHIP_SCAN_RANGE_ATTRIBUTE_ID = 125;
const TypeID eufe::SURVEY_SCAN_RANGE_ATTRIBUTE_ID = 197;
const TypeID eufe::FALLOFF_ATTRIBUTE_ID = 158;
const TypeID eufe::FALLOFF_EFFECTIVENESS_ATTRIBUTE_ID = 2044;
const TypeID eufe::SHIP_SCAN_FALLOFF_ATTRIBUTE_ID = 510;
const TypeID eufe::TRACKING_SPEED_ATTRIBUTE_ID = 160;
const TypeID eufe::OPTIMAL_SIG_RADIUS_ATTRIBUTE_ID = 620;;

const TypeID eufe::MAX_VELOCITY_ATTRIBUTE_ID = 37;
const TypeID eufe::EXPLOSION_DELAY_ATTRIBUTE_ID = 281;
const TypeID eufe::AGILITY_ATTRIBUTE_ID = 70;

const TypeID eufe::ARMOR_DAMAGE_ATTRIBUTE_ID = 266;
const TypeID eufe::SHIELD_CHARGE_ATTRIBUTE_ID = 264;
const TypeID eufe::DAMAGE_ATTRIBUTE_ID = 3;
const TypeID eufe::SHIELD_CAPACITY_ATTRIBUTE_ID = 263;
const TypeID eufe::ARMOR_HP_ATTRIBUTE_ID =  265;
const TypeID eufe::SHIELD_RECHARGE_RATE_ATTRIBUTE_ID = 479;
const TypeID eufe::ARMOR_DAMAGE_AMOUNT_ATTRIBUTE_ID = 84;
const TypeID eufe::SHIELD_BONUS_ATTRIBUTE_ID = 68;
const TypeID eufe::STRUCTURE_DAMAGE_AMOUNT_ATTRIBUTE_ID = 83;

const TypeID eufe::KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID = 109;
const TypeID eufe::THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID = 110;
const TypeID eufe::EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID = 111;
const TypeID eufe::EM_DAMAGE_RESONANCE_ATTRIBUTE_ID = 113;
const TypeID eufe::ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID = 267;
const TypeID eufe::ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID = 268;
const TypeID eufe::ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID = 269;
const TypeID eufe::ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID = 270;
const TypeID eufe::SHIELD_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID = 271;
const TypeID eufe::SHIELD_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID = 272;
const TypeID eufe::SHIELD_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID = 273;
const TypeID eufe::SHIELD_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID = 274;

const TypeID eufe::ENTITY_MISSILE_TYPE_ID_ATTRIBUTE_ID = 507;
const TypeID eufe::ACTIVATION_BLOCKED_ATTRIBUTE_ID = 1349;

const TypeID eufe::UPGRADE_COST_ATTRIBUTE_ID = 1153;
const TypeID eufe::UPGRADE_CAPACITY_ATTRIBUTE_ID = 1132;
const TypeID eufe::CPU_LOAD_ATTRIBUTE_ID = 49;
const TypeID eufe::POWER_LOAD_ATTRIBUTE_ID = 15;
const TypeID eufe::POWER_OUTPUT_ATTRIBUTE_ID = 11;
const TypeID eufe::CPU_OUTPUT_ATTRIBUTE_ID = 48;
const TypeID eufe::DRONE_BANDWIDTH_USED_ATTRIBUTE_ID = 1272;
const TypeID eufe::DRONE_BANDWIDTH_ATTRIBUTE_ID = 1271;
const TypeID eufe::DRONE_CAPACITY_ATTRIBUTE_ID = 283;
const TypeID eufe::BASE_WARP_SPEED_ATTRIBUTE_ID = 1281;
const TypeID eufe::WARP_SPEED_MULTIPLIER_ATTRIBUTE_ID = 600;
const TypeID eufe::SIGNATURE_RADIUS_ATTRIBUTE_ID = 552;
const TypeID eufe::WARP_CAPACITOR_NEED_ATTRIBUTE_ID = 153;
const TypeID eufe::MAX_LOCKED_TARGETS_ATTRIBUTE_ID = 192;
const TypeID eufe::MAX_TARGET_RANGE_ATTRIBUTE_ID = 76;
const TypeID eufe::SCAN_RADAR_STRENGTH_ATTRIBUTE_ID = 208;
const TypeID eufe::SCAN_LADAR_STRENGTH_ATTRIBUTE_ID = 209;
const TypeID eufe::SCAN_MAGNETOMETRIC_STRENGTH_ATTRIBUTE_ID = 210;
const TypeID eufe::SCAN_GRAVIMETRIC_STRENGTH_ATTRIBUTE_ID = 211;
const TypeID eufe::MAX_ACTIVE_DRONES_ATTRIBUTE_ID = 352;
const TypeID eufe::SCAN_RESOLUTION_ATTRIBUTE_ID = 564;

const TypeID eufe::HI_SLOT_MODIFIER_ATTRIBUTE_ID = 1374;
const TypeID eufe::MED_SLOT_MODIFIER_ATTRIBUTE_ID = 1375;
const TypeID eufe::LOW_SLOT_MODIFIER_ATTRIBUTE_ID = 1376;
const TypeID eufe::TURRET_HARD_POINT_MODIFIER_ATTRIBUTE_ID = 1368;
const TypeID eufe::LAUNCHER_HARD_POINT_MODIFIER_ATTRIBUTE_ID = 1369;

const TypeID eufe::HEAT_ATTENUATION_HI_ATTRIBUTE_ID = 1259;
const TypeID eufe::HEAT_ATTENUATION_LOW_ATTRIBUTE_ID = 1262;
const TypeID eufe::HEAT_ATTENUATION_MED_ATTRIBUTE_ID = 1261;
const TypeID eufe::HEAT_CAPACITY_HI_ATTRIBUTE_ID = 1178;
const TypeID eufe::HEAT_CAPACITY_LOW_ATTRIBUTE_ID = 1200;
const TypeID eufe::HEAT_CAPACITY_MED_ATTRIBUTE_ID = 1199;
const TypeID eufe::HEAT_DISSIPATION_RATE_HI_ATTRIBUTE_ID = 1179;
const TypeID eufe::HEAT_DISSIPATION_RATE_LOW_ATTRIBUTE_ID = 1198;
const TypeID eufe::HEAT_DISSIPATION_RATE_MED_ATTRIBUTE_ID = 1196;
const TypeID eufe::HEAT_GENERATION_MULTIPLIER_ATTRIBUTE_ID = 1224;
const TypeID eufe::HEAT_ABSORBTION_RATE_MODIFIER_ATTRIBUTE_ID = 1180;
const TypeID eufe::HEAT_DAMAGE_ATTRIBUTE_ID = 1211;

const TypeID eufe::POWER_ATTRIBUTE_ID = 30;
const TypeID eufe::CPU_ATTRIBUTE_ID = 50;

const TypeID eufe::HULL_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID = 976;
const TypeID eufe::HULL_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID = 977;
const TypeID eufe::HULL_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID = 975;
const TypeID eufe::HULL_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID = 974;

const TypeID eufe::MISSILE_ENTITY_VELOCITY_MULTIPLIER_ATTRIBUTE_ID = 645;
const TypeID eufe::MISSILE_ENTITY_FLIGHT_TIME_MULTIPLIER_ATTRIBUTE_ID = 646;

const TypeID eufe::DRONE_CONTROL_DISTANCE_ATTRIBUTE_ID = 458;

const TypeID eufe::CHARGE_ARMOR_DAMAGE_MULTIPLIER_ATTRIBUTE_ID = 1886;

const TypeID eufe::TACTICAL_MODES_ATTRIBUTE_ID = 10000;

const TypeID eufe::AOE_DAMAGE_REDUCTION_FACTOR_ATTRIBUTE_ID = 1353;
const TypeID eufe::AOE_DAMAGE_REDUCTION_SENSITIVITY_ATTRIBUTE_ID = 1354;
const TypeID eufe::AOE_CLOUD_SIZE_ATTRIBUTE_ID = 654;
const TypeID eufe::AOE_VELOCITY_ATTRIBUTE_ID = 653;
const TypeID eufe::ENTITY_FLY_RANGE_ATTRIBUTE_ID = 416;
const TypeID eufe::ENTITY_CRUISE_SPEED_ATTRIBUTE_ID = 508;
const TypeID eufe::WARP_SCRAMBLE_STRENGTH_ATTRIBUTE_ID = 105;
const TypeID eufe::WARP_SCRAMBLE_STRENGTH_HIDDEN_ATTRIBUTE_ID = 1318;

template<typename InputIterator, typename Output>
Output multiply(InputIterator first, InputIterator last, Output value, bool stacking)
{
	if (stacking)
	{
		//static int precalculatedExp = 0;
		//static float* pExp = nullptr;
		static std::vector<float> pExp;
		long n = std::distance(first, last);
		for (long i = pExp.size(); i < n; i++) {
			float j = i;
			pExp.push_back(expf(- j * j / 7.1289f));
		}
		/*if (n > precalculatedExp) {
			if (pExp)
				delete[] pExp;
			precalculatedExp += 20;
			pExp = new float[precalculatedExp];
			float j = 0;
			for (int i = 0; i < precalculatedExp; i++, j++)
				pExp[i] = expf(- j * j / 7.1289f);
		}*/
		
//		if (pExp)
			for (int i = 0; first != last; first++, i++)
				value *= static_cast<float>(1.0 + (*first - 1.0) * pExp[i]);
	}
	else
	{
		for (; first != last; first++)
			value *= *first;
	}
	return value;
}

std::shared_ptr<Attribute> Attribute::getAttribute(std::shared_ptr<Engine> const& engine, TypeID attributeID, std::shared_ptr<Item> const& owner, bool isFakeAttribute, float value) {
	return std::make_shared<Attribute>(engine, AttributePrototype::getAttributePrototype(engine, attributeID), owner, isFakeAttribute, value);
}

Attribute::Attribute(std::shared_ptr<Engine> const& engine, std::shared_ptr<AttributePrototype> const& prototype, std::shared_ptr<Item> const& owner, bool isFakeAttribute, float value): engine_(engine), prototype_(prototype), owner_(owner), isFakeAttribute_(isFakeAttribute), value_(value), initialValue_(value), calculated_(false), forcedValue_(std::numeric_limits<float>::quiet_NaN()) {
	if (std::isnan(value))
		initialValue_ = prototype_->getDefaultValue();
	sync = false;
	reset();
}

Attribute::~Attribute(void)
{
}

std::shared_ptr<Item> Attribute::getOwner() const
{
	return owner_.lock();
}

TypeID Attribute::getAttributeID() const
{
	return prototype_->getAttributeID();
}

bool Attribute::isFakeAttribute() const
{
	return isFakeAttribute_;
}

float Attribute::getValue()
{
	auto engine = engine_.lock();
	if (!engine)
		return 0;
	uint32_t generation = engine->getGeneration();
	if (generation_ != generation) {
		calculate();
		generation_ = generation;
	}
	return value_;
}

float Attribute::getInitialValue() const
{
	return initialValue_;
}

bool Attribute::isStackable() const
{
	return prototype_->isStackable();
}

bool Attribute::highIsGood() const
{
	return prototype_->highIsGood();
}

float Attribute::dec(float value)
{
	if (std::isnan(forcedValue_))
		forcedValue_ = initialValue_;
	isFakeAttribute_ = false;
	return forcedValue_ -= value;
}

float Attribute::inc(float value)
{
	if (std::isnan(forcedValue_))
		forcedValue_ = initialValue_;
	isFakeAttribute_ = false;
	return forcedValue_ += value;
}

void Attribute::setValue(float value)
{
	value_ = value;
	forcedValue_ = value;
	isFakeAttribute_ = false;
}

void Attribute::reset()
{
	generation_ = UINT32_MAX;
	calculated_ = false;
	value_ = initialValue_;
	
	sync = false;
}

void Attribute::calculate()
{
	if (!std::isnan(forcedValue_))
		value_ = forcedValue_;
	else
	{
		auto owner = getOwner();
		if (!owner)
			return;
		if (sync)
		{
			std::cout << "Deadlock: " << prototype_->getAttributeName() << std::endl;
		}
		sync = true;
		value_ = initialValue_;
		
		auto environment = owner;
		//std::shared_ptr<Item> currentCharacter = environment.find("Char") != environment.end() ? environment["Char"] : nullptr;
		Item* currentCharacter = environment->character();
		Ship* ship = dynamic_cast<Ship*>(environment->ship());
		
//		std::shared_ptr<Ship> ship = environment.find("Ship") != environment.end() ? std::dynamic_pointer_cast<Ship>(environment["Ship"]) : nullptr;
		auto attributeID = prototype_->getAttributeID();
		auto highIsGood = prototype_->highIsGood();
		auto isStackable = prototype_->isStackable();
		bool isDisallowedAssistance = ship && attributeID != DISALLOW_ASSISTANCE_ATTRIBUTE_ID ? ship->isDisallowedAssistance() : false;
		bool isDisallowedOffensiveModifiers = ship && attributeID != DISALLOW_OFFENSIVE_MODIFIERS_ATTRIBUTE_ID ? ship->isDisallowedOffensiveModifiers() : false;
		
		/*std::list<float>preAssignments;
		std::list<float>postAssignments;
		std::list<float>modAdds;
		std::list<float>preMultipliers;
		std::list<float>preMultipliersStackable;
		std::list<float>preDividersStackable;
		std::list<float>preMultipliersStackableNegative;
		std::list<float>preDividersStackableNegative;
		std::list<float>postMultipliers;
		std::list<float>postMultipliersStackable;
		std::list<float>postDividersStackable;
		std::list<float>postPercentsStackable;
		std::list<float>postMultipliersStackableNegative;
		std::list<float>postDividersStackableNegative;
		std::list<float>postPercentsStackableNegative;*/
		
		std::vector<float>preAssignments;
		std::vector<float>postAssignments;
		std::vector<float>modAdds;
		std::vector<float>preMultipliers;
		std::vector<float>preMultipliersStackable;
		std::vector<float>preDividersStackable;
		std::vector<float>preMultipliersStackableNegative;
		std::vector<float>preDividersStackableNegative;
		std::vector<float>postMultipliers;
		std::vector<float>postMultipliersStackable;
		std::vector<float>postDividersStackable;
		std::vector<float>postPercentsStackable;
		std::vector<float>postMultipliersStackableNegative;
		std::vector<float>postDividersStackableNegative;
		std::vector<float>postPercentsStackableNegative;
		
		//ModifiersList modifiers = owner->getModifiers(shared_from_this());
		ModifiersList modifiers;
		owner->getModifiers(this, std::inserter(modifiers, modifiers.end()));


		
//		ModifiersList::iterator i = modifiers.begin(), end = modifiers.end();
//		if (i != end)
//			isFakeAttribute_ = false;
		if (std::distance(modifiers.begin(), modifiers.end()) > 0)
			isFakeAttribute_ = false;
		for (const auto& i: modifiers)
		{
			Item* character = i->getCharacter();
			bool projected = character && currentCharacter && character != currentCharacter;
			if (projected && ((i->isAssistance() && isDisallowedAssistance) || (i->isOffensive() && isDisallowedOffensiveModifiers)))
				continue;
			
			TypeID categoryID = i->getModifier()->getOwner()->getCategoryID();
			bool needsStackingCheck = categoryID == MODULE_CATEGORY_ID || categoryID == CHARGE_CATEGORY_ID || categoryID == DRONE_CATEGORY_ID || categoryID == STRUCTURE_CATEGORY_ID;
			float value = i->getValue();
			bool isNegative = (highIsGood && value < 1.0) || (!highIsGood && value > 1.0);

			switch (i->getAssociation()) {
				case Modifier::ASSOCIATION_PRE_ASSIGNMENT:
					preAssignments.push_back(value);
					break;
				case Modifier::ASSOCIATION_POST_ASSIGNMENT:
					postAssignments.push_back(value);
					break;
				case Modifier::ASSOCIATION_MOD_ADD:
				case Modifier::ASSOCIATION_ADD_RATE:
					modAdds.push_back(value);
					break;
				case Modifier::ASSOCIATION_MOD_SUB:
				case Modifier::ASSOCIATION_SUB_RATE:
					modAdds.push_back(-value);
					break;
				case Modifier::ASSOCIATION_PRE_MUL:
					if (needsStackingCheck && !isStackable)// && !(*i)->isStackable())
					{
						if (isNegative)
							preMultipliersStackableNegative.push_back(value);
						else
							preMultipliersStackable.push_back(value);
					}
					else
						preMultipliers.push_back(value);
					break;
				case Modifier::ASSOCIATION_PRE_DIV:
					if (needsStackingCheck && !isStackable)// && !(*i)->isStackable())
					{
						if (isNegative)
							preDividersStackableNegative.push_back(value);
						else
							preDividersStackable.push_back(value);
					}
					else
						preMultipliers.push_back(value);
					break;
				case Modifier::ASSOCIATION_POST_MUL:
					if (needsStackingCheck && !isStackable)// && !(*i)->isStackable())
					{
						if (isNegative)
							postMultipliersStackableNegative.push_back(value);
						else
							postMultipliersStackable.push_back(value);
					}
					else
						postMultipliers.push_back(value);
					break;
				case Modifier::ASSOCIATION_POST_DIV:
					if (needsStackingCheck && !isStackable)// && !(*i)->isStackable())
					{
						if (isNegative)
							postDividersStackableNegative.push_back(value);
						else
							postDividersStackable.push_back(value);
					}
					else
						postMultipliers.push_back(value);
					break;
				case Modifier::ASSOCIATION_POST_PERCENT:
					if (needsStackingCheck && !isStackable)// && !(*i)->isStackable())
					{
						if (isNegative)
							postPercentsStackableNegative.push_back(value);
						else
							postPercentsStackable.push_back(value);
					}
					else
						postMultipliers.push_back(value);
					break;
				default:
					break;
			}
		}
		
		if (highIsGood)
		{
			/*preMultipliersStackable.sort(std::greater<float>());
			preDividersStackable.sort(std::greater<float>());
			postMultipliersStackable.sort(std::greater<float>());
			postDividersStackable.sort(std::greater<float>());
			postPercentsStackable.sort(std::greater<float>());
			
			preMultipliersStackableNegative.sort(std::less<float>());
			preDividersStackableNegative.sort(std::less<float>());
			postMultipliersStackableNegative.sort(std::less<float>());
			postDividersStackableNegative.sort(std::less<float>());
			postPercentsStackableNegative.sort(std::less<float>());*/

			std::sort(preMultipliersStackable.begin(), preMultipliersStackable.end(), std::greater<float>());
			std::sort(preDividersStackable.begin(), preDividersStackable.end(), std::greater<float>());
			std::sort(postMultipliersStackable.begin(), postMultipliersStackable.end(), std::greater<float>());
			std::sort(postDividersStackable.begin(), postDividersStackable.end(), std::greater<float>());
			std::sort(postPercentsStackable.begin(), postPercentsStackable.end(), std::greater<float>());

			std::sort(preMultipliersStackableNegative.begin(), preMultipliersStackableNegative.end(), std::less<float>());
			std::sort(preDividersStackableNegative.begin(), preDividersStackableNegative.end(), std::less<float>());
			std::sort(postMultipliersStackableNegative.begin(), postMultipliersStackableNegative.end(), std::less<float>());
			std::sort(postDividersStackableNegative.begin(), postDividersStackableNegative.end(), std::less<float>());
			std::sort(postPercentsStackableNegative.begin(), postPercentsStackableNegative.end(), std::less<float>());
		}
		else
		{
			/*preMultipliersStackable.sort(std::less<float>());
			preDividersStackable.sort(std::less<float>());
			postMultipliersStackable.sort(std::less<float>());
			postDividersStackable.sort(std::less<float>());
			postPercentsStackable.sort(std::less<float>());

			preMultipliersStackableNegative.sort(std::greater<float>());
			preDividersStackableNegative.sort(std::greater<float>());
			postMultipliersStackableNegative.sort(std::greater<float>());
			postDividersStackableNegative.sort(std::greater<float>());
			postPercentsStackableNegative.sort(std::greater<float>());*/

			std::sort(preMultipliersStackable.begin(), preMultipliersStackable.end(), std::less<float>());
			std::sort(preDividersStackable.begin(), preDividersStackable.end(), std::less<float>());
			std::sort(postMultipliersStackable.begin(), postMultipliersStackable.end(), std::less<float>());
			std::sort(postDividersStackable.begin(), postDividersStackable.end(), std::less<float>());
			std::sort(postPercentsStackable.begin(), postPercentsStackable.end(), std::less<float>());

			std::sort(preMultipliersStackableNegative.begin(), preMultipliersStackableNegative.end(), std::greater<float>());
			std::sort(preDividersStackableNegative.begin(), preDividersStackableNegative.end(), std::greater<float>());
			std::sort(postMultipliersStackableNegative.begin(), postMultipliersStackableNegative.end(), std::greater<float>());
			std::sort(postDividersStackableNegative.begin(), postDividersStackableNegative.end(), std::greater<float>());
			std::sort(postPercentsStackableNegative.begin(), postPercentsStackableNegative.end(), std::greater<float>());
		}
		
		if (preAssignments.size() > 0)
			value_ = preAssignments.front();
		
		for (const auto& j: modAdds)
			value_ += j;
		
		value_ = multiply(preMultipliers.begin(), preMultipliers.end(), value_, false);
		value_ = multiply(preMultipliersStackable.begin(), preMultipliersStackable.end(), value_, true);
		value_ = multiply(preDividersStackable.begin(), preDividersStackable.end(), value_, true);
		value_ = multiply(preMultipliersStackableNegative.begin(), preMultipliersStackableNegative.end(), value_, true);
		value_ = multiply(preDividersStackable.begin(), preDividersStackable.end(), value_, true);
		
		if (postAssignments.size() > 0)
			value_ = postAssignments.front();

		value_ = multiply(postMultipliers.begin(), postMultipliers.end(), value_, false);
		value_ = multiply(postMultipliersStackable.begin(), postMultipliersStackable.end(), value_, true);
		value_ = multiply(postDividersStackable.begin(), postDividersStackable.end(), value_, true);
		value_ = multiply(postPercentsStackable.begin(), postPercentsStackable.end(), value_, true);
		value_ = multiply(postMultipliersStackableNegative.begin(), postMultipliersStackableNegative.end(), value_, true);
		value_ = multiply(postDividersStackableNegative.begin(), postDividersStackableNegative.end(), value_, true);
		value_ = multiply(postPercentsStackableNegative.begin(), postPercentsStackableNegative.end(), value_, true);
		
		auto maxAttributeID = prototype_->getMaxAttributeID();
		if (maxAttributeID > 0) {
			float maxValue = owner->getAttribute(maxAttributeID)->getValue();
			value_ = std::min(value_, maxValue);
		}
		sync = false;
	}

	calculated_ = true;
}

const char* Attribute::getAttributeName() const
{
	return prototype_->getAttributeName();
}

std::ostream& eufe::operator<<(std::ostream& os, eufe::Attribute& attribute)
{
	os	<< "{\"attributeName\":\"" << attribute.prototype_->getAttributeName()
		<< "\", \"typeName\":\"" << attribute.getOwner()->getTypeName()
		<< "\", \"attributeID\":\"" << attribute.prototype_->getAttributeID()
		<< "\", \"value\":\"" << attribute.getValue()
		<< "\", \"initialValue\":\"" << attribute.getInitialValue()
		<< "\", \"stackable\":\"" << attribute.prototype_->isStackable() << "\"}";
	return os;
}
