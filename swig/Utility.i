%include "std_vector.i"
%include ""

namespace std {
	template <intmax_t _Num, intmax_t _Den = 1>
	class ratio
	{
	public:
	};

	namespace chrono {
		
		typedef ratio<1LL, 1000000000000000000LL> atto;
		typedef ratio<1LL,    1000000000000000LL> femto;
		typedef ratio<1LL,       1000000000000LL> pico;
		typedef ratio<1LL,          1000000000LL> nano;
		typedef ratio<1LL,             1000000LL> micro;
		typedef ratio<1LL,                1000LL> milli;
		typedef ratio<1LL,                 100LL> centi;
		typedef ratio<1LL,                  10LL> deci;
		typedef ratio<                 10LL, 1LL> deca;
		typedef ratio<                100LL, 1LL> hecto;
		typedef ratio<               1000LL, 1LL> kilo;
		typedef ratio<            1000000LL, 1LL> mega;
		typedef ratio<         1000000000LL, 1LL> giga;
		typedef ratio<      1000000000000LL, 1LL> tera;
		typedef ratio<   1000000000000000LL, 1LL> peta;
		typedef ratio<1000000000000000000LL, 1LL> exa;

		
		template <class _Rep, class _Period>
		class duration {
		public:
			rep count() const;
		};
		
		typedef duration<long long,         nano> nanoseconds;
		typedef duration<long long,        micro> microseconds;
		typedef duration<long long,        milli> milliseconds;
		typedef duration<long long              > seconds;
		typedef duration<     long, ratio<  60> > minutes;
		typedef duration<     long, ratio<3600> > hours;

	}
	

}

namespace dgmpp {
	
	template<typename Rep, typename Period = std::chrono::seconds>
	class rate {
	public:
		Rep count() const noexcept;
	};
	
	typedef double Float;
//	typedef enum TypeID;
//	typedef enum GroupID;
//	typedef enum CategoryID;
//	typedef enum AttributeID;
	typedef Float GigaJoule;
	typedef Float Teraflops;
	typedef Float MegaWatts;
	typedef Float CalibrationPoints;
	typedef Float CubicMeter;
	typedef Float Meter;
	typedef Float Millimeter;
	typedef Float MegabitsPerSecond;
	typedef Float Kilogram;
	typedef Float Points;
	typedef Float HP;
	typedef Float Radians;
	typedef Float AstronomicalUnit;
	typedef Float Percent;
	typedef Float Multiplier;
	typedef Float Seconds;
	typedef rate<GigaJoule, std::chrono::seconds> GigaJoulePerSecond;
	typedef rate<CubicMeter, std::chrono::seconds> CubicMeterPerSecond;
	typedef rate<Radians, std::chrono::seconds> RadiansPerSecond;
	typedef rate<Meter, std::chrono::seconds> MetersPerSecond;
	typedef rate<Meter, std::chrono::seconds> AstronomicalUnitsPerSecond;
	typedef rate<HP, std::chrono::seconds> HPPerSecond;
	
	class DamageVector {
	    public:
		    HP em;
		    HP thermal;
		    HP kinetic;
		    HP explosive;

		    HP total();
	};
	
	typedef rate<DamageVector, std::chrono::seconds> DamagePerSecond;
	%template(DamagePerSecond) rate<DamageVector, std::chrono::seconds>;
	%template(UnitsPerSecond) rate<Float, std::chrono::seconds>;
	%template(UnitsPerHour) rate<Float, std::chrono::hours>;

	struct Tank {
		HPPerSecond passiveShield;
		HPPerSecond shieldRepair;
		HPPerSecond armorRepair;
		HPPerSecond hullRepair;
	};
	
	struct Resistances {
		struct Layer {
			Percent em;
			Percent thermal;
			Percent kinetic;
			Percent explosive;
		};
		
		struct {
			Layer shield;
			Layer armor;
			Layer hull;
		};
	};
	
	struct HitPoints {
		HP shield;
		HP armor;
		HP hull;
	};
	
}
