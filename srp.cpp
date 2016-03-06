/*
 * Single Responsibility Principle states that 
 * there should be only one reason for any entity to change. 
 * 
 * Check the Journal struct and see how by adding a save method
 * we would making Journal responsible to 2 things and thus
 * adding complexity and future changes to it
 */

#include <string>
#include <vector>
#include <fstream>

struct Journal
{
	std::string m_title;
	std::vector<std::string> m_entries;

	explicit Journal(const std::string& title) 
		: m_title(title)
	{

	}

	Journal& add(const std::string& entry)
	{
		m_entries.push_back(entry);
		return *this;
	}
};

struct PersistenceManager
{
	/*
	 * In this case the entity Journal is self contained and is not responsible 
	 * for saving itself since that would violate the SINGLE RESPONSIBILITY PRINCIPLE
	 *
	 * Instead the PersistenceManager takes care of saving the Journal entity,
	 * this can open the door for formatting options, memory caching etc 
	 * that would be totally unfitting for the journal entity but compatible with the 
	 * responsibilities of the PersistenceManager
	 */
	static void save(const Journal& j, const std::string& filename)
	{
		std::ofstream ofs(filename);
		for (auto& s : j.m_entries)
		{
			ofs << s << std::endl;
		}
	}
};


