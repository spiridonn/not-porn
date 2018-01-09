#ifndef __SECTION_DATA_H__
#define __SECTION_DATA_H__

#include <string>

namespace smartCampus
{

struct SectionData
{
	/* data */
	std::string m_name;
	std::string m_ip;
	int m_msgPort;
	int m_regtistrationPort;
};

}

#endif /* __SECTION_DATA_H__ */

