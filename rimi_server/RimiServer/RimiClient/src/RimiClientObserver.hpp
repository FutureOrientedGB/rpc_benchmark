
#ifndef RIMICLIENTOBSERVER_HPP_
#define RIMICLIENTOBSERVER_HPP_

#include <atom/RimiMechanismExp.hpp>
#include "../../../iil/RimiTestItf.idl"


class CClientObserver : public atom::CRimiObserver,  //atom中的Rimi观察者基类
						public demo::IServerNotify
{
public:
    CClientObserver( atom::epid_t epid, atom::oref_c oref );
    ~CClientObserver();

public:
	//rimi
	virtual bool funcNotify( in_ const uint32_t res, RIMI_NOTIFY_PARAM );
	virtual bool funcNotify1( in_ const std::string res, RIMI_NOTIFY_PARAM );
};





class CClientObserver2 : public atom::CRimiObserver,  //atom中的Rimi观察者基类
						public demo::IServerNotify2
{
public:
	CClientObserver2( atom::epid_t epid, atom::oref_c oref ) :atom::CRimiObserver( epid, oref ){}
	~CClientObserver2(){}

public:
	//rimi
	virtual bool funcNotify2( in_ const std::string res, RIMI_NOTIFY_PARAM );
};

#endif // RIMICLIENTOBSERVER_HPP_
