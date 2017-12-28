%include "Type.i"
%include "Character.i"

namespace dgmpp {
	class Gang : public Type {
	public:
		Gang();
		Character* addPilot();
		void remove (Character* pilot);
		std::vector<Character*> pilots() const;

		Area* area() const noexcept;
		Area* area(TypeID typeID);

	};
}
