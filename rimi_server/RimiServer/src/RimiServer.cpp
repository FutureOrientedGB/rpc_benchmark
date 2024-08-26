
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <wtoe/RimiMechanismProxy/RimiMechanismProxyExp.hpp>
#include <wtoe/JavaScriptEngine/JavaScriptEngineExp.hpp>
#include <atom/RimiMechanismExp.hpp>
#include "../include/RimiServerExp.hpp"
#include "RimiServer.hpp"
#include "RimiTestItf.hpp"

namespace demo
{
    
//#define _CREATE_RIMI_

	CRimiServer::CRimiServer()
		: m_stop(false)
	{
	}

	CRimiServer::~CRimiServer()
	{
	}

	bool CRimiServer::startupImpl()
	{
		std::cout << "==== CRimiServer::startupImpl ====" << std::endl;

		//ע��js����
		boost::shared_ptr<wtoe::IJavaScriptVirtualMachine> jvm;
		if ( !wtoe::getMainApp()->getServiceInstance( WTOE_SNAME_JavaScriptEngine_JavaScriptVirtualMachine, jvm ) )
			return false;

		if( !jvm->registerJavaScriptObject( &CRimiServer::javaScriptRegister ) )
			return false;

#ifndef _CREATE_RIMI_
		if (!wtoe::getMainApp()->getServiceInstance(WTOE_SNAME_RimiMechanismProxy_RimiMechanismProxy, m_rimi) || !m_rimi)
		{
			return false;
		}

#else	/*����ԭ����rimi*/
		std::cout <<"=========== create rimi =====================" <<std::endl;
		if ( !atom::RimiRuntime::init() ) //��ʼ������ʱ��
		{
			std::cout << "RimiRuntime::init Failed!\n";
			return false;
		}

		//����RIMI���ƶ���
		m_rimi.reset( atom::RimiFactory::createRimiMechanism());
		if( !m_rimi )
		{
			atom::RimiRuntime::fini();
			return false;
		}

		//����RIMI����
		m_rimi->setThreadStack(1024*1024);
		m_rimi->setParallelNum(4);

		//��ʼ�����ƶ���
		if( !m_rimi->init() )
		{
			m_rimi->fini();
			atom::RimiRuntime::fini();
			return false;
		}

#endif // _CREATE_RIMI_
		
		//ע��Ϊ�����
		atom::rimiServantRegister(m_rimi.get());
		//atom::rimiProxierRegister(m_rimi.get());


		//����RIMI�������
		m_serverManager.reset( new CServerManager( m_rimi.get(), (atom::epid_t)-1 ) );
		if( !m_serverManager )
        {
            return false;
        }

		//�󶨷���
        m_rimi->rebind( RIMI_ACCESSSTRING_SERVERMANAGER, m_serverManager );
		m_rimi->rebind( RIMI_ACCESSSTRING_SERVEROBJECTMGR, m_serverManager );
		
		//m_object.reset( new CObject( m_rimi.get(), (atom::epid_t)-1 ) );
		//m_rimi->rebind( RIMI_ACCESSSTRING_SERVEROBJECT, m_object );

#if 1	
		//��֪ͨ�������
		boost::shared_ptr<atom::CRimiPublisher> notifier;
		if ( m_rimi->getRimiServant( notifier, demo::IServerNotify::IID() ) )
		{
			atom::CRimiPublisher *obj = notifier->clone();
			m_rimi->rebind( RIMI_ACCESSSTRING_SERVERNOTIFY, atom::CSpIRimiServant( obj ) );
		} 

		if ( m_rimi->getRimiServant( notifier, demo::IServerNotify2::IID() ) )
		{
			atom::CRimiPublisher *obj = notifier->clone();
			m_rimi->rebind( RIMI_ACCESSSTRING_SERVERNOTIFY2, atom::CSpIRimiServant( obj ) );
		} 
#endif

		//������·״̬
		m_rimi->subscribe( this );


#ifdef _CREATE_RIMI_
		//ԭ����rimi,��Ҫ���ü�����ַ
        ACE_INET_Addr addr( 12306 , "192.168.3.56");
        if ( !m_rimi->listen( addr ) )
        {
			m_rimi->cancelSub( this );
			m_rimi->fini();
        	atom::RimiRuntime::fini();
        	return false;
        }
#endif // _CREATE_RIMI_

		return true;
	}

	bool CRimiServer::shutdownImpl()
	{
		std::cout << "====CRimiServer::shutdownImpl====" << std::endl;
		
		if(m_rimi)
		{
			m_rimi->cancelSub( this );
			m_rimi->unbind( RIMI_ACCESSSTRING_SERVERMANAGER, m_serverManager );
			m_rimi->unbind( RIMI_ACCESSSTRING_SERVEROBJECTMGR, m_serverManager );
			
#ifdef _CREATE_RIMI_
			m_rimi->fini();
			m_rimi.reset();
			atom::RimiRuntime::fini();
#endif
		}

		return true;
	}

	void CRimiServer::accept( atom::epid_t epid, const ACE_INET_Addr &lAddr, const ACE_INET_Addr &rAddr )
    {
		std::cout << "CRimiServer::accept, epid = "<< epid << std::endl;
    }

    void CRimiServer::reject( atom::epid_t epid, const ACE_INET_Addr &lAddr, const ACE_INET_Addr &rAddr )
    {
        std::cout << "CRimiServer::reject, epid = " << epid << std::endl;
    }

	void CRimiServer::serverReady( atom::epid_t epid )
    {
        std::cout << "CRimiServer::serverReady, epid = " << epid << std::endl;
    }


	uint32_t CRimiServer::funcJsAdd( uint32_t a, uint32_t b )
	{
		uint32_t c;
		m_serverManager->funcAdd(a, b, c);
		std::cout << "CRimiServer::funcJsAdd " << " ret = " << c << std::endl;
		return c;
	}

	bool CRimiServer::funcJsMul( uint32_t a, uint32_t b )
	{
		uint32_t c;
		m_serverManager->funcMul(a, b, c);
		std::cout << "CRimiServer::funcJsMul " << " ret = " << c << std::endl;
		return true;
	}
}
