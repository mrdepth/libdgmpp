%include "Utility.i"
%include "Attribute.i"

namespace std {
	%template(Types) vector<dgmpp::Type*>;
}

namespace dgmpp {
	%nodefaultctor Type;
	class Type {
	public:
		Type (const Type& other) = delete;
		Type (Type&& other) = delete;
		Type& operator= (const Type& other) = delete;
		Type& operator= (Type&& other) = delete;
		virtual ~Type();

		%extend {
			TypeID typeID() const { return $self->metaInfo().typeID; }
			GroupID groupID() const { return $self->metaInfo().groupID; }
			CategoryID categoryID() const { return $self->metaInfo().categoryID; }
			
			Attribute* attribute (AttributeID attributeID) {
				if (auto attribute = (*$self)[attributeID])
					return attribute.get();
				else
					return nullptr;
			}
			
			std::vector<Type*> affectors() const {
				auto c = $self->affectors();
				return {c.begin(), c.end()};
			}
			
			std::vector<Attribute*> attributes() const {
				auto c = $self->attributes();
				return {c.begin(), c.end()};
			}
		}
		
		Type* parent();
		bool isDescendant (Type& parent) const noexcept;
	};
	
}
