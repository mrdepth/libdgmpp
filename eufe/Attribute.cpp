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
const TypeID eufe::SHIP_SCAN_FALLOFF_ATTRIBUTE_ID = 510;
const TypeID eufe::TRACKING_SPEED_ATTRIBUTE_ID = 160;

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


template<typename InputIterator, typename Output>
Output multiply(InputIterator first, InputIterator last, Output value, bool stacking)
{
	if (stacking)
	{
		static int precalculatedExp = 0;
		static float* pExp = NULL;
		long n = last - first;
		if (n > precalculatedExp) {
			if (pExp)
				delete[] pExp;
			precalculatedExp += 20;
			pExp = new float[precalculatedExp];
			float j = 0;
			for (int i = 0; i < precalculatedExp; i++, j++)
				pExp[i] = expf(- j * j / 7.1289f);
		}
		
		if (pExp)
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

Attribute::Attribute()
{
	sync = false;
}

Attribute::Attribute(Attribute& attribute) : owner_(NULL), calculated_(false)
{
	engine_			= attribute.engine_;
	//owner_			= attribute.owner_;
	attributeID_	= attribute.attributeID_;
	maxAttributeID_ = attribute.maxAttributeID_;
	value_			= attribute.value_;
	initialValue_	= attribute.initialValue_;
	forcedValue_	= attribute.forcedValue_;
	isStackable_	= attribute.isStackable_;
	highIsGood_		= attribute.highIsGood_;
	isFakeAttribute_= attribute.isFakeAttribute_;
	//calculated_		= attribute.calculated_;
#if _DEBUG
	attributeName_	= attribute.attributeName_;
#endif
	sync = false;
}

#if _DEBUG
Attribute::Attribute(Engine* engine, TypeID attributeID, TypeID maxAttributeID, float value, bool isStackable, bool highIsGood, Item* owner, const char* attributeName, bool isFakeAttribute) : engine_(engine), owner_(owner), attributeID_(attributeID), maxAttributeID_(maxAttributeID), value_(value), initialValue_(value), isStackable_(isStackable), highIsGood_(highIsGood), calculated_(false), attributeName_(attributeName), isFakeAttribute_(isFakeAttribute)
#else
Attribute::Attribute(Engine* engine, TypeID attributeID, TypeID maxAttributeID, float value, bool isStackable, bool highIsGood, Item* owner, bool isFakeAttribute) : engine_(engine), owner_(owner), attributeID_(attributeID), maxAttributeID_(maxAttributeID), value_(value), initialValue_(value), isStackable_(isStackable), highIsGood_(highIsGood), calculated_(false), isFakeAttribute_(isFakeAttribute)
#endif
{
	Engine::ScopedLock lock(*engine);

	forcedValue_ = std::numeric_limits<float>::infinity();
	
#if _DEBUG
	if (attributeName[0] == 0 && attributeID != 0)
	{
        std::stringstream sql;
		sql << "SELECT attributeName, stackable FROM dgmAttributeTypes WHERE attributeID = " << attributeID_;
		std::shared_ptr<FetchResult> result = engine_->getSqlConnector()->exec(sql.str().c_str());
		if (result->next()) {
			attributeName_ = result->getText(0);
			isStackable_ = result->getInt(1) != 0;
		}
	}
#endif
	sync = false;
}

Attribute::Attribute(Engine* engine, TypeID attributeID, Item* owner, bool isFakeAttribute) : engine_(engine), owner_(owner), attributeID_(attributeID), value_(0), initialValue_(0), isStackable_(false), calculated_(false), isFakeAttribute_(isFakeAttribute)
{
	Engine::ScopedLock lock(*engine);

	forcedValue_ = std::numeric_limits<float>::infinity();

	std::stringstream sql;
#if _DEBUG
	sql << "SELECT stackable, maxAttributeID, defaultValue, highIsGood, attributeName FROM dgmAttributeTypes WHERE attributeID = " << attributeID_;
#else
	sql << "SELECT stackable, maxAttributeID, defaultValue, highIsGood FROM dgmAttributeTypes WHERE attributeID = " << attributeID_;
#endif
	std::shared_ptr<FetchResult> result = engine_->getSqlConnector()->exec(sql.str().c_str());
	if (result->next()) {
		isStackable_ = result->getInt(0) != 0;
		maxAttributeID_ = static_cast<eufe::TypeID>(result->getInt(1));
		value_ = initialValue_ = static_cast<float>(result->getDouble(2));
		highIsGood_ = result->getInt(3) != 0;
#if _DEBUG
		attributeName_ = result->getText(4);
#endif
	}
	sync = false;
}

Attribute::~Attribute(void)
{
}

Item* Attribute::getOwner() const
{
	return owner_;
}

void Attribute::setOwner(Item* owner)
{
	owner_ = owner;
}

TypeID Attribute::getAttributeID() const
{
	return attributeID_;
}

bool Attribute::isFakeAttribute() const
{
	return isFakeAttribute_;
}

float Attribute::getValue()
{
	Engine::ScopedLock lock(*engine_);

	if (!calculated_)
		calculate();
	return value_;
}

float Attribute::getInitialValue() const
{
	return initialValue_;
}

bool Attribute::isStackable() const
{
	return isStackable_;
}

bool Attribute::highIsGood() const
{
	return highIsGood_;
}

float Attribute::dec(float value)
{
	Engine::ScopedLock lock(*engine_);

	if (forcedValue_ == std::numeric_limits<float>::infinity())
		forcedValue_ = initialValue_;
	isFakeAttribute_ = false;
	return forcedValue_ -= value;
}

float Attribute::inc(float value)
{
	Engine::ScopedLock lock(*engine_);

	if (forcedValue_ == std::numeric_limits<float>::infinity())
		forcedValue_ = initialValue_;
	isFakeAttribute_ = false;
	return forcedValue_ += value;
}

void Attribute::setValue(float value)
{
	Engine::ScopedLock lock(*engine_);

	value_ = value;
	forcedValue_ = value;
	isFakeAttribute_ = false;
}

void Attribute::reset()
{
	Engine::ScopedLock lock(*engine_);

	calculated_ = false;
	value_ = initialValue_;
	
	sync = false;
}

void Attribute::calculate()
{
	if (forcedValue_ != std::numeric_limits<float>::infinity())
		value_ = forcedValue_;
	else
	{
#if _DEBUG
		if (sync)
		{
			std::cout << "Deadlock: " << attributeName_ << std::endl;
		}
#endif
		sync = true;
		value_ = initialValue_;
		
		Environment environment = getOwner()->getEnvironment();
		Item* currentCharacter = environment.find("Char") != environment.end() ? environment["Char"] : NULL;
		Ship* ship = environment.find("Ship") != environment.end() ? dynamic_cast<Ship*>(environment["Ship"]) : NULL;
		bool isDisallowedAssistance = ship && attributeID_ != DISALLOW_ASSISTANCE_ATTRIBUTE_ID ? ship->isDisallowedAssistance() : false;
		bool isDisallowedOffensiveModifiers = ship && attributeID_ != DISALLOW_OFFENSIVE_MODIFIERS_ATTRIBUTE_ID ? ship->isDisallowedOffensiveModifiers() : false;
		
		ModifiersList modifiers;
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
		
		owner_->getModifiers(this, std::inserter(modifiers, modifiers.begin()));
		
		ModifiersList::iterator i = modifiers.begin(), end = modifiers.end();
		if (i != end)
			isFakeAttribute_ = false;
		
		for (; i != end; i++)
		{
			Item* character = (*i)->getCharacter();
			bool projected = character && currentCharacter && character != currentCharacter;
			if (projected && (((*i)->isAssistance() && isDisallowedAssistance) || ((*i)->isOffensive() && isDisallowedOffensiveModifiers)))
				continue;
			
			TypeID categoryID = (*i)->getModifier()->getOwner()->getCategoryID();
			bool needsStackingCheck = categoryID == MODULE_CATEGORY_ID || categoryID == CHARGE_CATEGORY_ID || categoryID == DRONE_CATEGORY_ID || categoryID == STRUCTURE_CATEGORY_ID;
			float value = (*i)->getValue();
			bool isNegative = (highIsGood_ && value < 1.0) || (!highIsGood_ && value > 1.0);

			switch ((*i)->getAssociation()) {
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
					if (needsStackingCheck && !isStackable_)// && !(*i)->isStackable())
					{
						if (isNegative)
							preMultipliersStackableNegative.push_back((*i)->getValue());
						else
							preMultipliersStackable.push_back((*i)->getValue());
					}
					else
						preMultipliers.push_back((*i)->getValue());
					break;
				case Modifier::ASSOCIATION_PRE_DIV:
					if (needsStackingCheck && !isStackable_)// && !(*i)->isStackable())
					{
						if (isNegative)
							preDividersStackableNegative.push_back((*i)->getValue());
						else
							preDividersStackable.push_back((*i)->getValue());
					}
					else
						preMultipliers.push_back((*i)->getValue());
					break;
				case Modifier::ASSOCIATION_POST_MUL:
					if (needsStackingCheck && !isStackable_)// && !(*i)->isStackable())
					{
						if (isNegative)
							postMultipliersStackableNegative.push_back((*i)->getValue());
						else
							postMultipliersStackable.push_back((*i)->getValue());
					}
					else
						postMultipliers.push_back((*i)->getValue());
					break;
				case Modifier::ASSOCIATION_POST_DIV:
					if (needsStackingCheck && !isStackable_)// && !(*i)->isStackable())
					{
						if (isNegative)
							postDividersStackableNegative.push_back((*i)->getValue());
						else
							postDividersStackable.push_back((*i)->getValue());
					}
					else
						postMultipliers.push_back((*i)->getValue());
					break;
				case Modifier::ASSOCIATION_POST_PERCENT:
					if (needsStackingCheck && !isStackable_)// && !(*i)->isStackable())
					{
						if (isNegative)
							postPercentsStackableNegative.push_back((*i)->getValue());
						else
							postPercentsStackable.push_back((*i)->getValue());
					}
					else
						postMultipliers.push_back((*i)->getValue());
					break;
				default:
					break;
			}
		}
		
		if (highIsGood_)
		{
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
			value_ = preAssignments[0];
		
		if (postAssignments.size() > 0)
			value_ = postAssignments[0];

		std::vector<float>::iterator j, endj = modAdds.end();
		for (j = modAdds.begin(); j != endj; j++)
			value_ += *j;
		
		value_ = multiply(preMultipliers.begin(), preMultipliers.end(), value_, false);
		value_ = multiply(preMultipliersStackable.begin(), preMultipliersStackable.end(), value_, true);
		value_ = multiply(preDividersStackable.begin(), preDividersStackable.end(), value_, true);
		value_ = multiply(preMultipliersStackableNegative.begin(), preMultipliersStackableNegative.end(), value_, true);
		value_ = multiply(preDividersStackable.begin(), preDividersStackable.end(), value_, true);
		
		value_ = multiply(postMultipliers.begin(), postMultipliers.end(), value_, false);
		value_ = multiply(postMultipliersStackable.begin(), postMultipliersStackable.end(), value_, true);
		value_ = multiply(postDividersStackable.begin(), postDividersStackable.end(), value_, true);
		value_ = multiply(postPercentsStackable.begin(), postPercentsStackable.end(), value_, true);
		value_ = multiply(postMultipliersStackableNegative.begin(), postMultipliersStackableNegative.end(), value_, true);
		value_ = multiply(postDividersStackableNegative.begin(), postDividersStackableNegative.end(), value_, true);
		value_ = multiply(postPercentsStackableNegative.begin(), postPercentsStackableNegative.end(), value_, true);
		
		if (maxAttributeID_ > 0) {
			float maxValue = owner_->getAttribute(maxAttributeID_)->getValue();
			value_ = std::min(value_, maxValue);
		}
		sync = false;
	}

	calculated_ = true;
}

Attribute::Attribute(Decoder& decoder, Engine* engine, Item* owner) : engine_(engine), owner_(owner), calculated_(false)
{
	decoder.decode(attributeID_);
	decoder.decode(maxAttributeID_);
	decoder.decode(value_);
	decoder.decode(initialValue_);
	decoder.decode(forcedValue_);
	decoder.decode(isStackable_);
	decoder.decode(highIsGood_);
	decoder.decode(isFakeAttribute_);
}

void Attribute::encode(Encoder& encoder)  const
{
	encoder.encode(attributeID_);
	encoder.encode(maxAttributeID_);
	encoder.encode(value_);
	encoder.encode(initialValue_);
	encoder.encode(forcedValue_);
	encoder.encode(isStackable_);
	encoder.encode(highIsGood_);
	encoder.encode(isFakeAttribute_);
}

#if _DEBUG

const char* Attribute::getAttributeName() const
{
	return attributeName_.c_str();
}

std::ostream& eufe::operator<<(std::ostream& os, eufe::Attribute& attribute)
{
	os	<< "{\"attributeName\":\"" << attribute.attributeName_
		<< "\", \"typeName\":\"" << attribute.getOwner()->getTypeName()
		<< "\", \"attributeID\":\"" << attribute.attributeID_
		<< "\", \"value\":\"" << attribute.getValue()
		<< "\", \"initialValue\":\"" << attribute.getInitialValue()
		<< "\", \"stackable\":\"" << attribute.isStackable_ << "\"}";
	return os;
}

#endif
