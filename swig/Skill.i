%include "Item.i"

%shared_ptr(dgmpp::Skill);

namespace dgmpp {

	%nodefaultctor Skill;

	class Skill : public dgmpp::Item
	{
	public:
		bool isLearned() const;
		int getSkillLevel();
		void setSkillLevel(int level);
	};
	
}