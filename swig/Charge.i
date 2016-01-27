%include "Item.i"

%shared_ptr(dgmpp::Charge);

namespace dgmpp {
	
	%nodefaultctor Charge;
	
	class Charge : public dgmpp::Item
	{
	public:
	};
	
}