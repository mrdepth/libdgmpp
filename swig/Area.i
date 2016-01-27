%include "Item.i"

%shared_ptr(dgmpp::Area);

namespace dgmpp {

	%nodefaultctor Area;

	class Area : public dgmpp::Item
	{
		public:
	};
	
}