
namespace eufe {
	
	%nodefaultctor Skill;

	class Skill : public eufe::Item
	{
	public:
		bool isLearned() const;
		int getSkillLevel();
		void setSkillLevel(int level);
	};
	
}