
#ifndef RIMISERVERMANAGER_HPP_
#define RIMISERVERMANAGER_HPP_

#include "../../iil/RimiTestItf.idl"
#include "../include/RimiServerExp.hpp"

#include <boost/thread.hpp>

namespace demo
{
    class RIMISERVER_PRIVATE CServerManager : public atom::CRimiServant, //如果有远程接口，就继承这个类
												public IServerManager,
												public IObjectMgr,
												public IRimiServer //pkg
    {
    public:
        CServerManager( atom::IRimiMechanism *mech, atom::epid_t epid = (atom::epid_t)-1 );
        ~CServerManager();

    public:
		//rimi
		virtual bool funcAdd( in_ const uint32_t a, in_ const uint32_t b, out_ uint32_t &c, RIMI_INVOKE_PARAM );
		virtual bool funcMul( in_ const uint32_t a, in_ const uint32_t b, out_ uint32_t &c, RIMI_INVOKE_PARAM );
		virtual bool func3( inout_ std::vector<std::string> &res, RIMI_INVOKE_PARAM );

		virtual boost::shared_ptr<IObject> funcGenObj( RIMI_INVOKE_PARAM );

	public:
		//pkg interface
		virtual uint32_t funcInternal(uint32_t a, uint32_t b);

    private:
        atom::IRimiMechanism *m_rimi;

    };


	class RIMISERVER_PRIVATE CObject : public atom::CRimiServant, //如果有远程接口，就继承这个类
												public IObject
    {
    public:
		CObject( atom::IRimiMechanism *mech, atom::epid_t epid = (atom::epid_t)-1 ):atom::CRimiServant( mech, epid ),m_rimi( mech ){}
		~CObject(){}

    public:
		//rimi
		virtual bool funcObject( in_ std::string &str, RIMI_INVOKE_PARAM );

	private:
        atom::IRimiMechanism *m_rimi;

    };


} // namespace demo

#endif // RIMISERVERMANAGER_HPP_
