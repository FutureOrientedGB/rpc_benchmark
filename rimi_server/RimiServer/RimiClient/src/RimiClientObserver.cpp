
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "RimiClientObserver.hpp"


CClientObserver::CClientObserver( atom::epid_t epid, atom::oref_c oref )
    : atom::CRimiObserver( epid, oref )
{
}

CClientObserver::~CClientObserver()
{
}

bool CClientObserver::funcNotify( in_ const uint32_t res, RIMI_NOTIFY_PARAM_DEFINE )
{
	std::cout << "--- CClientObserver::funcNotify: res = " << res << " ---" << std::endl;

    return true;
}

bool CClientObserver::funcNotify1( in_ const std::string res, RIMI_NOTIFY_PARAM_DEFINE )
{
	std::cout << "--- CClientObserver::funcNotify1: res = " << res << " ---" << std::endl;

    return true;
}



bool CClientObserver2::funcNotify2( in_ const std::string res, RIMI_NOTIFY_PARAM_DEFINE )
{
	std::cout << "--- CClientObserver2::funcNotify2: res = " << res << " ---" << std::endl;

    return true;
}