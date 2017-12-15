%include "Utility.i"

namespace std {
	%template(Attributes) vector<dgmpp::Attribute*>;
}

namespace dgmpp {
	class Type;
	%nodefaultctor Attribute;
	class Attribute {
	public:
		Attribute (const Attribute& other) = delete;
		Attribute (Attribute&& other) = delete;
		Attribute& operator= (const Attribute& other) = delete;
		Attribute& operator= (Attribute&& other) = delete;

		%extend {
			AttributeID attributeID() const { return $self->metaInfo().attributeID; }
		}
		
		Type& owner() const noexcept;
		Float value();
		Float initialValue() const;
	};
}
