#include "RimiLinkable.hpp"
#include "RimiClientObserver.hpp"
#include <atom/RimiMechanismExp.hpp>
#include "../../../iil/RimiTestItf.idl"

CRimiLinkable::CRimiLinkable() : m_condi( m_mutex ), m_linked( false ), m_rimi(0)
{

}

CRimiLinkable::~CRimiLinkable()
{

}

bool CRimiLinkable::init( atom::IRimiMechanism *rimi)
{
    if( rimi == 0 )
        return false;
    m_rimi = rimi;
    m_rimi->subscribe( this );
    return true;
}

void CRimiLinkable::fini()
{
    if( m_rimi )
    {
        m_rimi->cancelSub( this );
    }
    m_rimi = 0;
}

bool CRimiLinkable::wait( uint32_t msec )
{
    ACE_GUARD_RETURN( ACE_Thread_Mutex, guard, m_mutex, false );

    if ( msec != -1 )
    {
        ACE_Time_Value tv( 0, msec * 1000 ); 
		tv += ACE_OS::gettimeofday();
        return 0 == m_condi.wait( &tv ) || m_linked;
    }

    return 0 == m_condi.wait() || m_linked;
}

void CRimiLinkable::accept( atom::epid_t epid, const ACE_INET_Addr &lAddr, const ACE_INET_Addr &rAddr ) 
{
    m_peer = rAddr;
}

void CRimiLinkable::serverReady( atom::epid_t epid )
{
    ACE_GUARD_RETURN( ACE_Thread_Mutex, guard, m_mutex, ; );

    m_condi.signal();        
    m_linked = true;
}

void CRimiLinkable::clientReady( atom::epid_t epid )
{
	std::cout << "CRimiLinkable::clientReady: epid = " << epid << std::endl;

	ACE_GUARD_RETURN( ACE_Thread_Mutex, guard, m_mutex, ; );
    m_condi.signal();        
    m_linked = true;

#if 0
	///连上后，可以顺便注册观察者
	atom::CSpIRimiObserver obser( new CClientObserver( epid, demo::IServerNotify::IID() ) );
	m_rimi->reregister( demo::IServerNotify::IID(), 0, obser );
#endif
}

void CRimiLinkable::linkup( in_ atom::epid_t epid, in_ const ACE_INET_Addr &lAddr, in_ const ACE_INET_Addr &rAddr )
{
    std::cout << "CRimiLinkable::linkup epid = " << epid << std::endl;
    ACE_GUARD_RETURN( ACE_Thread_Mutex, guard, m_mutex, ; );
    m_condi.signal();
    m_linked = true;
}

void CRimiLinkable::linkdown( in_ atom::epid_t epid, in_ const ACE_INET_Addr &lAddr, in_ const ACE_INET_Addr &rAddr )
{
    std::cout << "CRimiLinkable::linkdown" << std::endl;
}

void CRimiLinkable::linkfail( in_ const ACE_INET_Addr &rAddr )
{
    std::cout << "CRimiLinkable::linkfail" << std::endl;
    ACE_GUARD_RETURN( ACE_Thread_Mutex, guard, m_mutex, ; );
    m_condi.signal();
    m_linked = false;
}

const ACE_INET_Addr& CRimiLinkable::peer()
{
    return m_peer;
}