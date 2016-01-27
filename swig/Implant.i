%include "Item.i"

%shared_ptr(dgmpp::Implant);

namespace dgmpp {

	%nodefaultctor Implant;
	
	class Implant : public dgmpp::Item
	{
	public:
		int getSlot();
	};
	
}