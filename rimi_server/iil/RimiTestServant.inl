#include <boost/shared_ptr.hpp>
#include <ace/Message_Block.h>

namespace demo {

class RIMI_OBJECT_PRIVATE CRimiIServerNotifyPrivate
{
public:
    CRimiIServerNotifyPrivate( atom::IRimiServant &servant ) : m_servant( servant )
    {
    }

public:
    bool funcNotify( const uint32_t res, RIMI_NOTIFY_PARAM ) 
    {
        /*参数申明*/
        /*入参数列集*/
        RIMI_OAR_ALLOCA_MSG( msg, m_servant.rimi() );
        RIMI_OAR_RETURN2( res, (atom::epid_t)-1, atom::sequ_t( -1 ), boost::true_type(), false );
        RIMI_OAR_DETACH_MSG();
        /*远程调用*/
        return m_servant.rimi()->notify( rimi_env.epid, m_servant.oref(), IServerNotify::IID(), 0, *msg );
    }
    bool funcNotify1( const std :: string res, RIMI_NOTIFY_PARAM ) 
    {
        /*参数申明*/
        /*入参数列集*/
        RIMI_OAR_ALLOCA_MSG( msg, m_servant.rimi() );
        RIMI_OAR_RETURN2( res, (atom::epid_t)-1, atom::sequ_t( -1 ), boost::true_type(), false );
        RIMI_OAR_DETACH_MSG();
        /*远程调用*/
        return m_servant.rimi()->notify( rimi_env.epid, m_servant.oref(), IServerNotify::IID(), 1, *msg );
    }

private:
    atom::IRimiServant &m_servant;
};

class RIMI_OBJECT_PRIVATE CRimiIServerNotify2Private
{
public:
    CRimiIServerNotify2Private( atom::IRimiServant &servant ) : m_servant( servant )
    {
    }

public:
    bool funcNotify2( const std :: string res, RIMI_NOTIFY_PARAM ) 
    {
        /*参数申明*/
        /*入参数列集*/
        RIMI_OAR_ALLOCA_MSG( msg, m_servant.rimi() );
        RIMI_OAR_RETURN2( res, (atom::epid_t)-1, atom::sequ_t( -1 ), boost::true_type(), false );
        RIMI_OAR_DETACH_MSG();
        /*远程调用*/
        return m_servant.rimi()->notify( rimi_env.epid, m_servant.oref(), IServerNotify2::IID(), 0, *msg );
    }

private:
    atom::IRimiServant &m_servant;
};

}

namespace atom {


template<>
inline ERimiResult CRimiWrapper<demo::IServerManager, 0>::invoke( CSpIRimiServant obj, oref_c oref, ACE_Message_Block *msg, const SRimiEnv &env, sequ_t sequ )
{
    using namespace demo;

    /*判断参数是否有效*/
    if ( !obj || !msg ) return ERimiResult::NOSUCHO;
    /*获取对应接口*/
    boost::shared_ptr<demo::IServerManager> ptr_ = boost::dynamic_pointer_cast<demo::IServerManager>( obj );
    if ( !ptr_ ) return ERimiResult::NOSUCHI;

    /*参数列表*/
    atom::byv<bool >::type r_return = atom::byv<bool >::type();
    atom::byv<atom::oref_c >::type r_oref = atom::byv<atom::oref_c >::type();

    /*散集入参数*/
    RIMI_IAR_ATTACH_MSG( msg, obj->rimi() );
    RIMI_IAR_RETURN( r_oref, env.epid, sequ, boost::true_type(), ERimiResult::IARFAIL );
    RIMI_IAR_DETACH_MSG();

    /*调用方法*/
    ERimiResult rimi_err = ERimiResult::SUCCESS;
    r_return = ptr_->anyCast( r_oref, &rimi_err, env );
    /*调用后处理*/
    if ( !rimi_err ) return rimi_err;

    /*列集出参数*/
    if ( !env.tway ) return ERimiResult::SUCCESS;

    RIMI_OAR_ATTACH_MSG( ( msg->reset(), msg ), obj->rimi() );
    RIMI_OAR_RETURN2( r_return, env.epid, sequ, boost::true_type(), ERimiResult::OARFAIL );
    RIMI_OAR_DETACH_REL();

    return ERimiResult::SUCCESS;
}

template<>
inline ERimiResult CRimiWrapper<demo::IServerManager, 1>::invoke( CSpIRimiServant obj, oref_c oref, ACE_Message_Block *msg, const SRimiEnv &env, sequ_t sequ )
{
    using namespace demo;

    /*判断参数是否有效*/
    if ( !obj || !msg ) return ERimiResult::NOSUCHO;
    /*获取对应接口*/
    boost::shared_ptr<demo::IServerManager> ptr_ = boost::dynamic_pointer_cast<demo::IServerManager>( obj );
    if ( !ptr_ ) return ERimiResult::NOSUCHI;

    /*参数列表*/

    /*散集入参数*/

    /*调用方法*/
    ERimiResult rimi_err = ERimiResult::SUCCESS;
    ptr_->rdelete( &rimi_err, env );
    /*调用后处理*/
    if ( !rimi_err ) return rimi_err;

    /*列集出参数*/
    if ( !env.tway ) return ERimiResult::SUCCESS;

    RIMI_OAR_ATTACH_MSG( ( msg->reset(), msg ), obj->rimi() );
    RIMI_OAR_DETACH_REL();

    return ERimiResult::SUCCESS;
}

template<>
inline ERimiResult CRimiWrapper<demo::IServerManager, 2>::invoke( CSpIRimiServant obj, oref_c oref, ACE_Message_Block *msg, const SRimiEnv &env, sequ_t sequ )
{
    using namespace demo;

    /*判断参数是否有效*/
    if ( !obj || !msg ) return ERimiResult::NOSUCHO;
    /*获取对应接口*/
    boost::shared_ptr<demo::IServerManager> ptr_ = boost::dynamic_pointer_cast<demo::IServerManager>( obj );
    if ( !ptr_ ) return ERimiResult::NOSUCHI;

    /*参数列表*/
    atom::byv<bool >::type r_return = atom::byv<bool >::type();
    atom::byv<const uint32_t >::type r_a = atom::byv<const uint32_t >::type();
    atom::byv<const uint32_t >::type r_b = atom::byv<const uint32_t >::type();
    atom::byv<uint32_t & >::type r_c = atom::byv<uint32_t & >::type();

    /*散集入参数*/
    RIMI_IAR_ATTACH_MSG( msg, obj->rimi() );
    RIMI_IAR_RETURN( r_a, env.epid, sequ, boost::true_type(), ERimiResult::IARFAIL );
    RIMI_IAR_RETURN( r_b, env.epid, sequ, boost::true_type(), ERimiResult::IARFAIL );
    RIMI_IAR_DETACH_MSG();

    /*调用方法*/
    ERimiResult rimi_err = ERimiResult::SUCCESS;
    r_return = ptr_->funcAdd( r_a, r_b, r_c, &rimi_err, env );
    /*调用后处理*/
    if ( !rimi_err ) return rimi_err;

    /*列集出参数*/
    if ( !env.tway ) return ERimiResult::SUCCESS;

    RIMI_OAR_ATTACH_MSG( ( msg->reset(), msg ), obj->rimi() );
    RIMI_OAR_RETURN2( r_return, env.epid, sequ, boost::true_type(), ERimiResult::OARFAIL );
    RIMI_OAR_RETURN2( r_c, env.epid, sequ, boost::true_type(), ERimiResult::OARFAIL );
    RIMI_OAR_DETACH_REL();

    return ERimiResult::SUCCESS;
}

template<>
inline ERimiResult CRimiWrapper<demo::IServerManager, 3>::invoke( CSpIRimiServant obj, oref_c oref, ACE_Message_Block *msg, const SRimiEnv &env, sequ_t sequ )
{
    using namespace demo;

    /*判断参数是否有效*/
    if ( !obj || !msg ) return ERimiResult::NOSUCHO;
    /*获取对应接口*/
    boost::shared_ptr<demo::IServerManager> ptr_ = boost::dynamic_pointer_cast<demo::IServerManager>( obj );
    if ( !ptr_ ) return ERimiResult::NOSUCHI;

    /*参数列表*/
    atom::byv<bool >::type r_return = atom::byv<bool >::type();
    atom::byv<const uint32_t >::type r_a = atom::byv<const uint32_t >::type();
    atom::byv<const uint32_t >::type r_b = atom::byv<const uint32_t >::type();
    atom::byv<uint32_t & >::type r_c = atom::byv<uint32_t & >::type();

    /*散集入参数*/
    RIMI_IAR_ATTACH_MSG( msg, obj->rimi() );
    RIMI_IAR_RETURN( r_a, env.epid, sequ, boost::true_type(), ERimiResult::IARFAIL );
    RIMI_IAR_RETURN( r_b, env.epid, sequ, boost::true_type(), ERimiResult::IARFAIL );
    RIMI_IAR_DETACH_MSG();

    /*调用方法*/
    ERimiResult rimi_err = ERimiResult::SUCCESS;
    r_return = ptr_->funcMul( r_a, r_b, r_c, &rimi_err, env );
    /*调用后处理*/
    if ( !rimi_err ) return rimi_err;

    /*列集出参数*/
    if ( !env.tway ) return ERimiResult::SUCCESS;

    RIMI_OAR_ATTACH_MSG( ( msg->reset(), msg ), obj->rimi() );
    RIMI_OAR_RETURN2( r_return, env.epid, sequ, boost::true_type(), ERimiResult::OARFAIL );
    RIMI_OAR_RETURN2( r_c, env.epid, sequ, boost::true_type(), ERimiResult::OARFAIL );
    RIMI_OAR_DETACH_REL();

    return ERimiResult::SUCCESS;
}

template<>
inline ERimiResult CRimiWrapper<demo::IServerManager, 4>::invoke( CSpIRimiServant obj, oref_c oref, ACE_Message_Block *msg, const SRimiEnv &env, sequ_t sequ )
{
    using namespace demo;

    /*判断参数是否有效*/
    if ( !obj || !msg ) return ERimiResult::NOSUCHO;
    /*获取对应接口*/
    boost::shared_ptr<demo::IServerManager> ptr_ = boost::dynamic_pointer_cast<demo::IServerManager>( obj );
    if ( !ptr_ ) return ERimiResult::NOSUCHI;

    /*参数列表*/
    atom::byv<bool >::type r_return = atom::byv<bool >::type();
    atom::byv<std :: vector < std :: string > & >::type r_res = atom::byv<std :: vector < std :: string > & >::type();

    /*散集入参数*/
    RIMI_IAR_ATTACH_MSG( msg, obj->rimi() );
    RIMI_IAR_RETURN( r_res, env.epid, sequ, boost::true_type(), ERimiResult::IARFAIL );
    RIMI_IAR_DETACH_MSG();

    /*调用方法*/
    ERimiResult rimi_err = ERimiResult::SUCCESS;
    r_return = ptr_->func3( r_res, &rimi_err, env );
    /*调用后处理*/
    if ( !rimi_err ) return rimi_err;

    /*列集出参数*/
    if ( !env.tway ) return ERimiResult::SUCCESS;

    RIMI_OAR_ATTACH_MSG( ( msg->reset(), msg ), obj->rimi() );
    RIMI_OAR_RETURN2( r_return, env.epid, sequ, boost::true_type(), ERimiResult::OARFAIL );
    RIMI_OAR_RETURN2( r_res, env.epid, sequ, boost::true_type(), ERimiResult::OARFAIL );
    RIMI_OAR_DETACH_REL();

    return ERimiResult::SUCCESS;
}

template<>
inline ERimiResult CRimiWrapper<demo::IObject, 0>::invoke( CSpIRimiServant obj, oref_c oref, ACE_Message_Block *msg, const SRimiEnv &env, sequ_t sequ )
{
    using namespace demo;

    /*判断参数是否有效*/
    if ( !obj || !msg ) return ERimiResult::NOSUCHO;
    /*获取对应接口*/
    boost::shared_ptr<demo::IObject> ptr_ = boost::dynamic_pointer_cast<demo::IObject>( obj );
    if ( !ptr_ ) return ERimiResult::NOSUCHI;

    /*参数列表*/
    atom::byv<bool >::type r_return = atom::byv<bool >::type();
    atom::byv<atom::oref_c >::type r_oref = atom::byv<atom::oref_c >::type();

    /*散集入参数*/
    RIMI_IAR_ATTACH_MSG( msg, obj->rimi() );
    RIMI_IAR_RETURN( r_oref, env.epid, sequ, boost::true_type(), ERimiResult::IARFAIL );
    RIMI_IAR_DETACH_MSG();

    /*调用方法*/
    ERimiResult rimi_err = ERimiResult::SUCCESS;
    r_return = ptr_->anyCast( r_oref, &rimi_err, env );
    /*调用后处理*/
    if ( !rimi_err ) return rimi_err;

    /*列集出参数*/
    if ( !env.tway ) return ERimiResult::SUCCESS;

    RIMI_OAR_ATTACH_MSG( ( msg->reset(), msg ), obj->rimi() );
    RIMI_OAR_RETURN2( r_return, env.epid, sequ, boost::true_type(), ERimiResult::OARFAIL );
    RIMI_OAR_DETACH_REL();

    return ERimiResult::SUCCESS;
}

template<>
inline ERimiResult CRimiWrapper<demo::IObject, 1>::invoke( CSpIRimiServant obj, oref_c oref, ACE_Message_Block *msg, const SRimiEnv &env, sequ_t sequ )
{
    using namespace demo;

    /*判断参数是否有效*/
    if ( !obj || !msg ) return ERimiResult::NOSUCHO;
    /*获取对应接口*/
    boost::shared_ptr<demo::IObject> ptr_ = boost::dynamic_pointer_cast<demo::IObject>( obj );
    if ( !ptr_ ) return ERimiResult::NOSUCHI;

    /*参数列表*/

    /*散集入参数*/

    /*调用方法*/
    ERimiResult rimi_err = ERimiResult::SUCCESS;
    ptr_->rdelete( &rimi_err, env );
    /*调用后处理*/
    if ( !rimi_err ) return rimi_err;

    /*列集出参数*/
    if ( !env.tway ) return ERimiResult::SUCCESS;

    RIMI_OAR_ATTACH_MSG( ( msg->reset(), msg ), obj->rimi() );
    RIMI_OAR_DETACH_REL();

    return ERimiResult::SUCCESS;
}

template<>
inline ERimiResult CRimiWrapper<demo::IObject, 2>::invoke( CSpIRimiServant obj, oref_c oref, ACE_Message_Block *msg, const SRimiEnv &env, sequ_t sequ )
{
    using namespace demo;

    /*判断参数是否有效*/
    if ( !obj || !msg ) return ERimiResult::NOSUCHO;
    /*获取对应接口*/
    boost::shared_ptr<demo::IObject> ptr_ = boost::dynamic_pointer_cast<demo::IObject>( obj );
    if ( !ptr_ ) return ERimiResult::NOSUCHI;

    /*参数列表*/
    atom::byv<bool >::type r_return = atom::byv<bool >::type();
    atom::byv<std :: string & >::type r_str = atom::byv<std :: string & >::type();

    /*散集入参数*/
    RIMI_IAR_ATTACH_MSG( msg, obj->rimi() );
    RIMI_IAR_RETURN( r_str, env.epid, sequ, boost::true_type(), ERimiResult::IARFAIL );
    RIMI_IAR_DETACH_MSG();

    /*调用方法*/
    ERimiResult rimi_err = ERimiResult::SUCCESS;
    r_return = ptr_->funcObject( r_str, &rimi_err, env );
    /*调用后处理*/
    if ( !rimi_err ) return rimi_err;

    /*列集出参数*/
    if ( !env.tway ) return ERimiResult::SUCCESS;

    RIMI_OAR_ATTACH_MSG( ( msg->reset(), msg ), obj->rimi() );
    RIMI_OAR_RETURN2( r_return, env.epid, sequ, boost::true_type(), ERimiResult::OARFAIL );
    RIMI_OAR_DETACH_REL();

    return ERimiResult::SUCCESS;
}

template<>
inline ERimiResult CRimiWrapper<demo::IObjectMgr, 0>::invoke( CSpIRimiServant obj, oref_c oref, ACE_Message_Block *msg, const SRimiEnv &env, sequ_t sequ )
{
    using namespace demo;

    /*判断参数是否有效*/
    if ( !obj || !msg ) return ERimiResult::NOSUCHO;
    /*获取对应接口*/
    boost::shared_ptr<demo::IObjectMgr> ptr_ = boost::dynamic_pointer_cast<demo::IObjectMgr>( obj );
    if ( !ptr_ ) return ERimiResult::NOSUCHI;

    /*参数列表*/
    atom::byv<bool >::type r_return = atom::byv<bool >::type();
    atom::byv<atom::oref_c >::type r_oref = atom::byv<atom::oref_c >::type();

    /*散集入参数*/
    RIMI_IAR_ATTACH_MSG( msg, obj->rimi() );
    RIMI_IAR_RETURN( r_oref, env.epid, sequ, boost::true_type(), ERimiResult::IARFAIL );
    RIMI_IAR_DETACH_MSG();

    /*调用方法*/
    ERimiResult rimi_err = ERimiResult::SUCCESS;
    r_return = ptr_->anyCast( r_oref, &rimi_err, env );
    /*调用后处理*/
    if ( !rimi_err ) return rimi_err;

    /*列集出参数*/
    if ( !env.tway ) return ERimiResult::SUCCESS;

    RIMI_OAR_ATTACH_MSG( ( msg->reset(), msg ), obj->rimi() );
    RIMI_OAR_RETURN2( r_return, env.epid, sequ, boost::true_type(), ERimiResult::OARFAIL );
    RIMI_OAR_DETACH_REL();

    return ERimiResult::SUCCESS;
}

template<>
inline ERimiResult CRimiWrapper<demo::IObjectMgr, 1>::invoke( CSpIRimiServant obj, oref_c oref, ACE_Message_Block *msg, const SRimiEnv &env, sequ_t sequ )
{
    using namespace demo;

    /*判断参数是否有效*/
    if ( !obj || !msg ) return ERimiResult::NOSUCHO;
    /*获取对应接口*/
    boost::shared_ptr<demo::IObjectMgr> ptr_ = boost::dynamic_pointer_cast<demo::IObjectMgr>( obj );
    if ( !ptr_ ) return ERimiResult::NOSUCHI;

    /*参数列表*/

    /*散集入参数*/

    /*调用方法*/
    ERimiResult rimi_err = ERimiResult::SUCCESS;
    ptr_->rdelete( &rimi_err, env );
    /*调用后处理*/
    if ( !rimi_err ) return rimi_err;

    /*列集出参数*/
    if ( !env.tway ) return ERimiResult::SUCCESS;

    RIMI_OAR_ATTACH_MSG( ( msg->reset(), msg ), obj->rimi() );
    RIMI_OAR_DETACH_REL();

    return ERimiResult::SUCCESS;
}

template<>
inline ERimiResult CRimiWrapper<demo::IObjectMgr, 2>::invoke( CSpIRimiServant obj, oref_c oref, ACE_Message_Block *msg, const SRimiEnv &env, sequ_t sequ )
{
    using namespace demo;

    /*判断参数是否有效*/
    if ( !obj || !msg ) return ERimiResult::NOSUCHO;
    /*获取对应接口*/
    boost::shared_ptr<demo::IObjectMgr> ptr_ = boost::dynamic_pointer_cast<demo::IObjectMgr>( obj );
    if ( !ptr_ ) return ERimiResult::NOSUCHI;

    /*参数列表*/
    atom::byv<boost :: shared_ptr < IObject > >::type r_return = atom::byv<boost :: shared_ptr < IObject > >::type();

    /*散集入参数*/

    /*调用方法*/
    ERimiResult rimi_err = ERimiResult::SUCCESS;
    r_return = ptr_->funcGenObj( &rimi_err, env );
    /*调用后处理*/
    if ( !rimi_err ) return rimi_err;

    /*列集出参数*/
    if ( !env.tway ) return ERimiResult::SUCCESS;

    RIMI_OAR_ATTACH_MSG( ( msg->reset(), msg ), obj->rimi() );
    RIMI_OAR_RETURN2( r_return, env.epid, sequ, boost::true_type(), ERimiResult::OARFAIL );
    RIMI_OAR_DETACH_REL();

    return ERimiResult::SUCCESS;
}

}

namespace demo {

class RIMI_OBJECT_PRIVATE CRimiIServerNotifyNotifier : public atom::CRimiPublisher, public IServerNotify
{
public:
    CRimiIServerNotifyNotifier( atom::IRimiMechanism *mech, atom::epid_t epid, bool isClone = false )
    : atom::CRimiPublisher( mech, epid ),
      m_CRimiIServerNotifyPrivate( *this )
    {
        if ( !isClone ) m_oref = IServerNotify::IID();
    }

public:
    virtual bool funcNotify( const uint32_t res, RIMI_NOTIFY_PARAM ) 
    {
        return m_CRimiIServerNotifyPrivate.funcNotify( res, rimi_env );
    }
    virtual bool funcNotify1( const std :: string res, RIMI_NOTIFY_PARAM ) 
    {
        return m_CRimiIServerNotifyPrivate.funcNotify1( res, rimi_env );
    }
    virtual atom::CRimiPublisher *clone()
    {
        return new CRimiIServerNotifyNotifier( rimi(), epid(), true );
    }

private:
    CRimiIServerNotifyPrivate m_CRimiIServerNotifyPrivate;
};

class RIMI_OBJECT_PRIVATE CRimiIServerNotify2Notifier : public atom::CRimiPublisher, public IServerNotify2
{
public:
    CRimiIServerNotify2Notifier( atom::IRimiMechanism *mech, atom::epid_t epid, bool isClone = false )
    : atom::CRimiPublisher( mech, epid ),
      m_CRimiIServerNotify2Private( *this )
    {
        if ( !isClone ) m_oref = IServerNotify2::IID();
    }

public:
    virtual bool funcNotify2( const std :: string res, RIMI_NOTIFY_PARAM ) 
    {
        return m_CRimiIServerNotify2Private.funcNotify2( res, rimi_env );
    }
    virtual atom::CRimiPublisher *clone()
    {
        return new CRimiIServerNotify2Notifier( rimi(), epid(), true );
    }

private:
    CRimiIServerNotify2Private m_CRimiIServerNotify2Private;
};

}
namespace atom {

void RIMI_SERVANT_REGISTER_ENTRY__( IRimiMechanism *mech )
{
    mech->addRimiWrapper( CSpIRimiWrapper( new CRimiWrapper<demo::IServerManager, 0> ) );
    mech->addRimiWrapper( CSpIRimiWrapper( new CRimiWrapper<demo::IServerManager, 1> ) );
    mech->addRimiWrapper( CSpIRimiWrapper( new CRimiWrapper<demo::IServerManager, 2> ) );
    mech->addRimiWrapper( CSpIRimiWrapper( new CRimiWrapper<demo::IServerManager, 3> ) );
    mech->addRimiWrapper( CSpIRimiWrapper( new CRimiWrapper<demo::IServerManager, 4> ) );
    mech->addRimiWrapper( CSpIRimiWrapper( new CRimiWrapper<demo::IObject, 0> ) );
    mech->addRimiWrapper( CSpIRimiWrapper( new CRimiWrapper<demo::IObject, 1> ) );
    mech->addRimiWrapper( CSpIRimiWrapper( new CRimiWrapper<demo::IObject, 2> ) );
    mech->addRimiWrapper( CSpIRimiWrapper( new CRimiWrapper<demo::IObjectMgr, 0> ) );
    mech->addRimiWrapper( CSpIRimiWrapper( new CRimiWrapper<demo::IObjectMgr, 1> ) );
    mech->addRimiWrapper( CSpIRimiWrapper( new CRimiWrapper<demo::IObjectMgr, 2> ) );

    mech->rebind( CSpIRimiServant( new demo::CRimiIServerNotifyNotifier( mech, (atom::epid_t)-1 ) ) );
    mech->rebind( CSpIRimiServant( new demo::CRimiIServerNotify2Notifier( mech, (atom::epid_t)-1 ) ) );
}

}
