#ifndef RIMISERVER_HPP_
#define RIMISERVER_HPP_

#include <wtoe/PackageManager/PackageManagerExp.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>

#include "atom/RimiMechanismExp.hpp"
#include "../include/RimiServerExp.hpp"
#include "RimiServerManager.hpp"
#include "../../iil/RimiTestItf.idl"


namespace demo
{
    class RIMISERVER_PUBLIC CRimiServer : public wtoe::IServiceEntry,
											public atom::IRimiLinkable //用于监听链路状态										
    {
    public:
        CRimiServer();
        virtual ~CRimiServer();

    protected:
        virtual bool startupImpl();
        virtual bool shutdownImpl();

	public:
        virtual void accept( atom::epid_t epid, const ACE_INET_Addr &lAddr, const ACE_INET_Addr &rAddr );
        virtual void reject( atom::epid_t epid, const ACE_INET_Addr &lAddr, const ACE_INET_Addr &rAddr );
		virtual void serverReady( atom::epid_t epid );

	public:
		//js用
		virtual uint32_t funcJsAdd( uint32_t a, uint32_t b );
		virtual bool funcJsMul( uint32_t a, uint32_t b );
		static  bool javaScriptRegister( JSContext *jsCtx, JSObject *jsObj );

    private:
        bool  m_stop;
		boost::shared_ptr<atom::IRimiMechanism> m_rimi;
		boost::shared_ptr<CServerManager> m_serverManager;
		//boost::shared_ptr<CObject> m_object;
    };

	typedef boost::shared_ptr<CRimiServer> SpCRimiServer;
}

#endif //RIMISERVER_HPP_
