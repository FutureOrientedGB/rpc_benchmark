#ifndef RIMILINKABLE_HPP_
#define RIMILINKABLE_HPP_

#include <iostream>
#include <ace/Thread_Mutex.h>
#include <ace/OS_NS_unistd.h>
#include <ace/OS_NS_sys_time.h>
#include <ace/Condition_Thread_Mutex.h>
#include <atom/RimiMechanismExp.hpp>


/**
 * 连接状态指示.
 */
class CRimiLinkable : public atom::IRimiLinkable
{
public:
    CRimiLinkable();
	~CRimiLinkable();
	bool init( atom::IRimiMechanism *rimi);
	void fini();

public:
	bool wait( uint32_t msec );
	virtual void linkup( in_ atom::epid_t epid, in_ const ACE_INET_Addr &lAddr, in_ const ACE_INET_Addr &rAddr );
	virtual void linkdown( in_ atom::epid_t epid, in_ const ACE_INET_Addr &lAddr, in_ const ACE_INET_Addr &rAddr );
	virtual void linkfail( in_ const ACE_INET_Addr &rAddr );

	virtual void accept( atom::epid_t epid, const ACE_INET_Addr &lAddr, const ACE_INET_Addr &rAddr );
	virtual void serverReady( atom::epid_t epid );
	virtual void clientReady( atom::epid_t epid );
	const ACE_INET_Addr &peer();
    

private:
	atom::IRimiMechanism		*m_rimi;
    ACE_Thread_Mutex			m_mutex;
    ACE_Condition_Thread_Mutex	m_condi;
    volatile bool				m_linked;
    ACE_INET_Addr				m_peer;
};

#endif