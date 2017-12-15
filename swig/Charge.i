%include "Type.i"

namespace dgmpp {
	class Charge : public Type {
	public:
		enum class Size {
			none = 0,
			small = 1,
			medium = 2,
			large = 3,
			xLarge = 4
		};
		Size size();
		
	};
}
