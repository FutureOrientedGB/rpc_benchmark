
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "RimiServerManager.hpp"

namespace demo
{
    CServerManager::CServerManager( atom::IRimiMechanism *mech, atom::epid_t epid )
        : atom::CRimiServant( mech, epid )
        , m_rimi( mech )
    {
    }

    CServerManager::~CServerManager()
    {
    }
	
    bool CServerManager::funcAdd( in_ const uint32_t a, in_ const uint32_t b, out_ uint32_t &c, RIMI_INVOKE_PARAM_DEFINE )
    {
		c = a + b;
		std::cout << "\n--- rimi funcAdd invoke: a = " << a << ", b = " << b << ", result = " << c << std::endl;

        //调用通知函数
        demo::CSpIServerNotify notifyServer;
		if ( m_rimi->getRimiServant( notifyServer, demo::IServerNotify::IID() ) )
        {
            notifyServer->funcNotify( c );
        }
        return true;
    }

	bool CServerManager::funcMul( in_ const uint32_t a, in_ const uint32_t b, out_ uint32_t &c, RIMI_INVOKE_PARAM_DEFINE )
	{
		c = funcInternal(a, b); //internal call
		std::cout << "\n--- rimi funcMul invoke: a = " << a << ", b = " << b << ", result = " << c << std::endl;

        //调用通知函数
        demo::CSpIServerNotify notifyServer;
		if ( m_rimi->getRimiServant( notifyServer, demo::IServerNotify::IID() ) )
        {
            notifyServer->funcNotify( c );

			std::string str = "successful";
			notifyServer->funcNotify1( str );
        }
        return true;

	}

	bool CServerManager::func3( inout_ std::vector<std::string> &res, RIMI_INVOKE_PARAM_DEFINE )
	{
		std::cout << "\n--- rimi func3 invoke ---" << std::endl;
		
		res.push_back(to_string(boost::uuids::random_generator()()));
		res.push_back(to_string(boost::uuids::random_generator()()));
		res.push_back(to_string(boost::uuids::random_generator()()));

		return true;		
	}

	boost::shared_ptr<IObject> CServerManager::funcGenObj( RIMI_INVOKE_PARAM_DEFINE )
	{
		return boost::shared_ptr<IObject>( new CObject( rimi(), rimi_env.epid ) );
	}
	
	//pkg
	uint32_t CServerManager::funcInternal(uint32_t a, uint32_t b)
    {
		std::cout << "CRimiServer::funcInternal" << std::endl;
        return a * b;      
    }





	bool CObject::funcObject( in_ std::string &str, RIMI_INVOKE_PARAM_DEFINE )
	{
		std::cout << "\n--- CObject::funcObject: " << str << std::endl;

		//调用通知函数
        demo::CSpIServerNotify2 notifyServer;
        if ( m_rimi->getRimiServant( notifyServer, demo::IServerNotify2::IID() ) )
		//if ( m_rimi->getRimiServant( notifyServer, demo::RIMI_ACCESSSTRING_SERVERNOTIFY ) )
        {
            notifyServer->funcNotify2( str );
        }

		return true;
	}

} // namespace demo
