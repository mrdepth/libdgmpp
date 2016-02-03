%include "Item.i"

%shared_ptr(dgmpp::Booster);

namespace dgmpp {

	%nodefaultctor Booster;
	
	class Booster : public dgmpp::Item
	{
	public:
		int getSlot();
	};
	
}