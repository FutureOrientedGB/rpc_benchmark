
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <wtoe/RimiMechanismProxy/RimiMechanismProxyExp.hpp>

#include "RimiTestProxier.hpp"
#include "RimiClientObserver.hpp"
#include "RimiLinkable.hpp"
#include "../../../iil/RimiTestItf.idl"

ACE_INET_Addr m_serveraddr( 12306 , "192.168.3.56");


int main(int argc, char *argv[])
{
	std::cout << "--- rimi client start ---" << std::endl;
	//��ʼ������ʱ��.
	if ( !atom::RimiRuntime::init() )
	{
		std::cout << "RimiRuntime::init Failed!\n";
		return -1;
	}
	
	//����RIMI���ƶ���
	boost::shared_ptr<atom::IRimiMechanism> m_rimi;
	m_rimi.reset( atom::RimiFactory::createRimiMechanism());
	if( !m_rimi )
    {
        atom::RimiRuntime::fini();
        return -1;
    }

    //����RIMI����
	m_rimi->setThreadStack(1024*1024);
    m_rimi->setParallelNum(3);

	//ע��Ϊ�ͻ���
	//atom::rimiServantRegister(m_rimi.get());
	atom::rimiProxierRegister(m_rimi.get());

	//��ʼ�����ƶ���
	if( !m_rimi->init() )
    {
        m_rimi->fini();
        atom::RimiRuntime::fini();
        return -1;
    }

	//������·״̬
	boost::shared_ptr<CRimiLinkable> m_linkable;
	m_linkable.reset( new CRimiLinkable() );
	if( !m_linkable )
    {
		m_rimi->fini();
        atom::RimiRuntime::fini();
        return -1;
    }
	m_linkable->init( m_rimi.get() );

	//���ӷ�����
	m_rimi->relink(m_serveraddr);

	//relink֮��ȴ�,�ȴ���ʱ�򷵻�ʧ��
    if ( !m_linkable->wait( 2000 ) )
    {
		m_rimi->fini();
        atom::RimiRuntime::fini();
        std::cout << "relink server Failed!\n";
		getchar();
        return -1;
    }
	
#if 1
	///���Ϻ�ע��۲���,�����֪��epid������ͨ���������ֲ�ѯ�������ڵ�epid��oref,��ǰ�����ڷ���˱���Ҫrebind
	atom::epid_t epid; atom::oref_t oref;
	if( !m_rimi->getServantORef(epid, oref, atom::fqdn(m_serveraddr, demo::RIMI_ACCESSSTRING_SERVERNOTIFY)) )
	{
		m_rimi->fini();
        atom::RimiRuntime::fini();
		std::cout << "------ get epid failed ----" << std::endl;
		getchar();
		return -1;
	}
	/// �۲���1
	atom::CSpIRimiObserver obser0( new CClientObserver( epid, demo::IServerNotify::IID() ) );
	m_rimi->reregister( demo::IServerNotify::IID(), 0, obser0 );

	atom::CSpIRimiObserver obser1( new CClientObserver( epid, demo::IServerNotify::IID() ) );
	m_rimi->reregister( demo::IServerNotify::IID(), 1, obser1 );

	/// �۲���2
	atom::CSpIRimiObserver obser2( new CClientObserver2( epid, demo::IServerNotify2::IID() ) );
	m_rimi->reregister( demo::IServerNotify2::IID(), 0, obser2 );
#endif

	while (true)
	{
		std::cout << "\nInput cmd:";
        std::string cmd;
        std::cin >> cmd;
		
		if( (cmd == "quit") || (cmd == "exit") )
		{
			break;
		}
		else
		{
			/// ��ȡԶ�̷������
			demo::CSpIServerManager server;
			if ( !m_rimi->getRimiProxier( server, atom::fqdn( m_serveraddr, demo::RIMI_ACCESSSTRING_SERVERMANAGER )))
			{
				m_rimi->fini();
				atom::RimiRuntime::fini();
				return -1;
			}

			std::cout << "\n-------------- invoke remote funcAdd -----------------" << std::endl;
			//invoke funcAdd test
			uint32_t result;
			server->funcAdd(10, 20, result);
			std::cout<<"> client call rimi funcAdd ok: ret = "<< result <<std::endl;
			
			std::cout << "\n-------------- invoke remote funcMul -----------------" << std::endl;
			//invoke funcMul test
			server->funcMul(10, 20, result);
			std::cout<<"> client call rimi funcMul ok: ret = "<< result <<std::endl;
			
			std::cout << "\n-------------- invoke remote func3 -----------------" << std::endl;
			//invoke func3 test
			std::vector<std::string> vec;
			server->func3(vec);
			std::cout << "vec.size = " << vec.size() << std::endl;
			std::vector<std::string>::iterator iter;
			for(iter = vec.begin(); iter != vec.end(); iter++)
			{
				std::cout << *iter << std::endl;
			}
			
			std::cout << "\n-------------- invoke remote Object active -----------------" << std::endl;
			//�ͻ��˼������������
			demo::CSpIObjectMgr objectMgr;
			if ( m_rimi->getRimiProxier( objectMgr, atom::fqdn( m_serveraddr, demo::RIMI_ACCESSSTRING_SERVEROBJECTMGR )))
			{
				boost::shared_ptr<demo::IObject> spObject = objectMgr->funcGenObj();
				std::string str = "rimi invoke test";
				spObject->funcObject(str);
			}

		}
	}

	m_rimi->unlink(m_serveraddr);
	m_rimi->fini();
	atom::RimiRuntime::fini();

	getchar();
	return 0;
}
