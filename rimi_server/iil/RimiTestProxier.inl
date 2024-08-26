#include <boost/shared_ptr.hpp>
#include <ace/Message_Block.h>

namespace demo {

class RIMI_OBJECT_PRIVATE CRimiIServerManagerPrivate
{
public:
    CRimiIServerManagerPrivate( atom::IRimiProxier &proxier ) : m_proxier( proxier )
    {
    }

public:
    bool anyCast( atom::oref_c oref, RIMI_INVOKE_PARAM ) 
    {
        atom::CRimiResult r_result;
        /*参数申明*/
        atom::byv<bool >::type r_return = atom::byv<bool >::type();
#if 0
        /*同步引用关系*/
        if ( !m_proxier.syncReference() )
        {
            if ( !m_proxier.rimi()->hasEpid( m_proxier.epid() ) )
                r_result.result( atom::ERimiResult::NOSUCHE );
            else
                r_result.result( atom::ERimiResult::NOSUCHO );
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
#endif
        /*入参数列集*/
        RIMI_OAR_ALLOCA_MSG( msg, m_proxier.rimi() );
        RIMI_OAR_EXCEPTION_RETURN2( oref, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_OAR_DETACH_MSG();
        /*远程调用*/
        if ( !m_proxier.rimi()->invoke( m_proxier.oref(), IServerManager::IID(), 0, *msg, &r_result, atom::SRimiEnv( m_proxier.epid(), rimi_env.msec, rimi_env.tway ) ) ||
             !r_result.good() )
        {
#if 0
            if ( atom::ERimiResult::NOSUCHE == r_result.result()
              || atom::ERimiResult::NOSUCHO == r_result.result() )
                m_proxier.loseReference();
            if ( atom::ERimiResult::TIMEOUT == r_result.result() )
                m_proxier.rimi()->reclaimCao( m_proxier.epid(), r_result.sequ() );

#endif
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
        /*散集出参数*/
        if ( !rimi_env.tway )
        {
            if ( rimi_err ) *rimi_err = r_result.result();
            return r_return;
        }

        RIMI_IAR_ATTACH_MSG( r_result.getMsg(), m_proxier.rimi() );
        RIMI_IAR_EXCEPTION_RETURN( r_return, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_IAR_DETACH_MSG();
        /*返回异常处理*/
        RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
    }
    void rdelete( RIMI_INVOKE_PARAM ) 
    {
        atom::CRimiResult r_result;
        /*参数申明*/
#if 0
        /*同步引用关系*/
        if ( !m_proxier.syncReference() )
        {
            if ( !m_proxier.rimi()->hasEpid( m_proxier.epid() ) )
                r_result.result( atom::ERimiResult::NOSUCHE );
            else
                r_result.result( atom::ERimiResult::NOSUCHO );
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, ; );
        }
#endif
        /*入参数列集*/
        RIMI_OAR_ALLOCA_MSG( msg, m_proxier.rimi() );
        RIMI_OAR_DETACH_MSG();
        /*远程调用*/
        if ( !m_proxier.rimi()->invoke( m_proxier.oref(), IServerManager::IID(), 1, *msg, &r_result, atom::SRimiEnv( m_proxier.epid(), rimi_env.msec, rimi_env.tway ) ) ||
             !r_result.good() )
        {
#if 0
            if ( atom::ERimiResult::NOSUCHE == r_result.result()
              || atom::ERimiResult::NOSUCHO == r_result.result() )
                m_proxier.loseReference();
            if ( atom::ERimiResult::TIMEOUT == r_result.result() )
                m_proxier.rimi()->reclaimCao( m_proxier.epid(), r_result.sequ() );

#endif
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, ; );
        }
        /*散集出参数*/
        if ( !rimi_env.tway )
        {
            if ( rimi_err ) *rimi_err = r_result.result();
            return ;;
        }

        RIMI_IAR_ATTACH_MSG( r_result.getMsg(), m_proxier.rimi() );
        RIMI_IAR_DETACH_MSG();
        /*返回异常处理*/
        RIMI_EXCEPTION_RETURN( rimi_err, r_result, ; );
    }
    bool funcAdd( const uint32_t a, const uint32_t b, uint32_t & c, RIMI_INVOKE_PARAM ) 
    {
        atom::CRimiResult r_result;
        /*参数申明*/
        atom::byv<bool >::type r_return = atom::byv<bool >::type();
#if 0
        /*同步引用关系*/
        if ( !m_proxier.syncReference() )
        {
            if ( !m_proxier.rimi()->hasEpid( m_proxier.epid() ) )
                r_result.result( atom::ERimiResult::NOSUCHE );
            else
                r_result.result( atom::ERimiResult::NOSUCHO );
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
#endif
        /*入参数列集*/
        RIMI_OAR_ALLOCA_MSG( msg, m_proxier.rimi() );
        RIMI_OAR_EXCEPTION_RETURN2( a, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_OAR_EXCEPTION_RETURN2( b, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_OAR_DETACH_MSG();
        /*远程调用*/
        if ( !m_proxier.rimi()->invoke( m_proxier.oref(), IServerManager::IID(), 2, *msg, &r_result, atom::SRimiEnv( m_proxier.epid(), rimi_env.msec, rimi_env.tway ) ) ||
             !r_result.good() )
        {
#if 0
            if ( atom::ERimiResult::NOSUCHE == r_result.result()
              || atom::ERimiResult::NOSUCHO == r_result.result() )
                m_proxier.loseReference();
            if ( atom::ERimiResult::TIMEOUT == r_result.result() )
                m_proxier.rimi()->reclaimCao( m_proxier.epid(), r_result.sequ() );

#endif
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
        /*散集出参数*/
        if ( !rimi_env.tway )
        {
            if ( rimi_err ) *rimi_err = r_result.result();
            return r_return;
        }

        RIMI_IAR_ATTACH_MSG( r_result.getMsg(), m_proxier.rimi() );
        RIMI_IAR_EXCEPTION_RETURN( r_return, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_IAR_EXCEPTION_RETURN( c, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_IAR_DETACH_MSG();
        /*返回异常处理*/
        RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
    }
    bool funcMul( const uint32_t a, const uint32_t b, uint32_t & c, RIMI_INVOKE_PARAM ) 
    {
        atom::CRimiResult r_result;
        /*参数申明*/
        atom::byv<bool >::type r_return = atom::byv<bool >::type();
#if 0
        /*同步引用关系*/
        if ( !m_proxier.syncReference() )
        {
            if ( !m_proxier.rimi()->hasEpid( m_proxier.epid() ) )
                r_result.result( atom::ERimiResult::NOSUCHE );
            else
                r_result.result( atom::ERimiResult::NOSUCHO );
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
#endif
        /*入参数列集*/
        RIMI_OAR_ALLOCA_MSG( msg, m_proxier.rimi() );
        RIMI_OAR_EXCEPTION_RETURN2( a, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_OAR_EXCEPTION_RETURN2( b, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_OAR_DETACH_MSG();
        /*远程调用*/
        if ( !m_proxier.rimi()->invoke( m_proxier.oref(), IServerManager::IID(), 3, *msg, &r_result, atom::SRimiEnv( m_proxier.epid(), rimi_env.msec, rimi_env.tway ) ) ||
             !r_result.good() )
        {
#if 0
            if ( atom::ERimiResult::NOSUCHE == r_result.result()
              || atom::ERimiResult::NOSUCHO == r_result.result() )
                m_proxier.loseReference();
            if ( atom::ERimiResult::TIMEOUT == r_result.result() )
                m_proxier.rimi()->reclaimCao( m_proxier.epid(), r_result.sequ() );

#endif
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
        /*散集出参数*/
        if ( !rimi_env.tway )
        {
            if ( rimi_err ) *rimi_err = r_result.result();
            return r_return;
        }

        RIMI_IAR_ATTACH_MSG( r_result.getMsg(), m_proxier.rimi() );
        RIMI_IAR_EXCEPTION_RETURN( r_return, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_IAR_EXCEPTION_RETURN( c, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_IAR_DETACH_MSG();
        /*返回异常处理*/
        RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
    }
    bool func3( std :: vector < std :: string > & res, RIMI_INVOKE_PARAM ) 
    {
        atom::CRimiResult r_result;
        /*参数申明*/
        atom::byv<bool >::type r_return = atom::byv<bool >::type();
#if 0
        /*同步引用关系*/
        if ( !m_proxier.syncReference() )
        {
            if ( !m_proxier.rimi()->hasEpid( m_proxier.epid() ) )
                r_result.result( atom::ERimiResult::NOSUCHE );
            else
                r_result.result( atom::ERimiResult::NOSUCHO );
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
#endif
        /*入参数列集*/
        RIMI_OAR_ALLOCA_MSG( msg, m_proxier.rimi() );
        RIMI_OAR_EXCEPTION_RETURN2( res, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_OAR_DETACH_MSG();
        /*远程调用*/
        if ( !m_proxier.rimi()->invoke( m_proxier.oref(), IServerManager::IID(), 4, *msg, &r_result, atom::SRimiEnv( m_proxier.epid(), rimi_env.msec, rimi_env.tway ) ) ||
             !r_result.good() )
        {
#if 0
            if ( atom::ERimiResult::NOSUCHE == r_result.result()
              || atom::ERimiResult::NOSUCHO == r_result.result() )
                m_proxier.loseReference();
            if ( atom::ERimiResult::TIMEOUT == r_result.result() )
                m_proxier.rimi()->reclaimCao( m_proxier.epid(), r_result.sequ() );

#endif
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
        /*散集出参数*/
        if ( !rimi_env.tway )
        {
            if ( rimi_err ) *rimi_err = r_result.result();
            return r_return;
        }

        RIMI_IAR_ATTACH_MSG( r_result.getMsg(), m_proxier.rimi() );
        RIMI_IAR_EXCEPTION_RETURN( r_return, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_IAR_EXCEPTION_RETURN( res, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_IAR_DETACH_MSG();
        /*返回异常处理*/
        RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
    }

private:
    atom::IRimiProxier &m_proxier;
};

class RIMI_OBJECT_PRIVATE CRimiIObjectPrivate
{
public:
    CRimiIObjectPrivate( atom::IRimiProxier &proxier ) : m_proxier( proxier )
    {
    }

public:
    bool anyCast( atom::oref_c oref, RIMI_INVOKE_PARAM ) 
    {
        atom::CRimiResult r_result;
        /*参数申明*/
        atom::byv<bool >::type r_return = atom::byv<bool >::type();
#if 0
        /*同步引用关系*/
        if ( !m_proxier.syncReference() )
        {
            if ( !m_proxier.rimi()->hasEpid( m_proxier.epid() ) )
                r_result.result( atom::ERimiResult::NOSUCHE );
            else
                r_result.result( atom::ERimiResult::NOSUCHO );
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
#endif
        /*入参数列集*/
        RIMI_OAR_ALLOCA_MSG( msg, m_proxier.rimi() );
        RIMI_OAR_EXCEPTION_RETURN2( oref, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_OAR_DETACH_MSG();
        /*远程调用*/
        if ( !m_proxier.rimi()->invoke( m_proxier.oref(), IObject::IID(), 0, *msg, &r_result, atom::SRimiEnv( m_proxier.epid(), rimi_env.msec, rimi_env.tway ) ) ||
             !r_result.good() )
        {
#if 0
            if ( atom::ERimiResult::NOSUCHE == r_result.result()
              || atom::ERimiResult::NOSUCHO == r_result.result() )
                m_proxier.loseReference();
            if ( atom::ERimiResult::TIMEOUT == r_result.result() )
                m_proxier.rimi()->reclaimCao( m_proxier.epid(), r_result.sequ() );

#endif
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
        /*散集出参数*/
        if ( !rimi_env.tway )
        {
            if ( rimi_err ) *rimi_err = r_result.result();
            return r_return;
        }

        RIMI_IAR_ATTACH_MSG( r_result.getMsg(), m_proxier.rimi() );
        RIMI_IAR_EXCEPTION_RETURN( r_return, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_IAR_DETACH_MSG();
        /*返回异常处理*/
        RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
    }
    void rdelete( RIMI_INVOKE_PARAM ) 
    {
        atom::CRimiResult r_result;
        /*参数申明*/
#if 0
        /*同步引用关系*/
        if ( !m_proxier.syncReference() )
        {
            if ( !m_proxier.rimi()->hasEpid( m_proxier.epid() ) )
                r_result.result( atom::ERimiResult::NOSUCHE );
            else
                r_result.result( atom::ERimiResult::NOSUCHO );
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, ; );
        }
#endif
        /*入参数列集*/
        RIMI_OAR_ALLOCA_MSG( msg, m_proxier.rimi() );
        RIMI_OAR_DETACH_MSG();
        /*远程调用*/
        if ( !m_proxier.rimi()->invoke( m_proxier.oref(), IObject::IID(), 1, *msg, &r_result, atom::SRimiEnv( m_proxier.epid(), rimi_env.msec, rimi_env.tway ) ) ||
             !r_result.good() )
        {
#if 0
            if ( atom::ERimiResult::NOSUCHE == r_result.result()
              || atom::ERimiResult::NOSUCHO == r_result.result() )
                m_proxier.loseReference();
            if ( atom::ERimiResult::TIMEOUT == r_result.result() )
                m_proxier.rimi()->reclaimCao( m_proxier.epid(), r_result.sequ() );

#endif
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, ; );
        }
        /*散集出参数*/
        if ( !rimi_env.tway )
        {
            if ( rimi_err ) *rimi_err = r_result.result();
            return ;;
        }

        RIMI_IAR_ATTACH_MSG( r_result.getMsg(), m_proxier.rimi() );
        RIMI_IAR_DETACH_MSG();
        /*返回异常处理*/
        RIMI_EXCEPTION_RETURN( rimi_err, r_result, ; );
    }
    bool funcObject( std :: string & str, RIMI_INVOKE_PARAM ) 
    {
        atom::CRimiResult r_result;
        /*参数申明*/
        atom::byv<bool >::type r_return = atom::byv<bool >::type();
#if 0
        /*同步引用关系*/
        if ( !m_proxier.syncReference() )
        {
            if ( !m_proxier.rimi()->hasEpid( m_proxier.epid() ) )
                r_result.result( atom::ERimiResult::NOSUCHE );
            else
                r_result.result( atom::ERimiResult::NOSUCHO );
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
#endif
        /*入参数列集*/
        RIMI_OAR_ALLOCA_MSG( msg, m_proxier.rimi() );
        RIMI_OAR_EXCEPTION_RETURN2( str, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_OAR_DETACH_MSG();
        /*远程调用*/
        if ( !m_proxier.rimi()->invoke( m_proxier.oref(), IObject::IID(), 2, *msg, &r_result, atom::SRimiEnv( m_proxier.epid(), rimi_env.msec, rimi_env.tway ) ) ||
             !r_result.good() )
        {
#if 0
            if ( atom::ERimiResult::NOSUCHE == r_result.result()
              || atom::ERimiResult::NOSUCHO == r_result.result() )
                m_proxier.loseReference();
            if ( atom::ERimiResult::TIMEOUT == r_result.result() )
                m_proxier.rimi()->reclaimCao( m_proxier.epid(), r_result.sequ() );

#endif
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
        /*散集出参数*/
        if ( !rimi_env.tway )
        {
            if ( rimi_err ) *rimi_err = r_result.result();
            return r_return;
        }

        RIMI_IAR_ATTACH_MSG( r_result.getMsg(), m_proxier.rimi() );
        RIMI_IAR_EXCEPTION_RETURN( r_return, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_IAR_DETACH_MSG();
        /*返回异常处理*/
        RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
    }

private:
    atom::IRimiProxier &m_proxier;
};

class RIMI_OBJECT_PRIVATE CRimiIObjectMgrPrivate
{
public:
    CRimiIObjectMgrPrivate( atom::IRimiProxier &proxier ) : m_proxier( proxier )
    {
    }

public:
    bool anyCast( atom::oref_c oref, RIMI_INVOKE_PARAM ) 
    {
        atom::CRimiResult r_result;
        /*参数申明*/
        atom::byv<bool >::type r_return = atom::byv<bool >::type();
#if 0
        /*同步引用关系*/
        if ( !m_proxier.syncReference() )
        {
            if ( !m_proxier.rimi()->hasEpid( m_proxier.epid() ) )
                r_result.result( atom::ERimiResult::NOSUCHE );
            else
                r_result.result( atom::ERimiResult::NOSUCHO );
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
#endif
        /*入参数列集*/
        RIMI_OAR_ALLOCA_MSG( msg, m_proxier.rimi() );
        RIMI_OAR_EXCEPTION_RETURN2( oref, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_OAR_DETACH_MSG();
        /*远程调用*/
        if ( !m_proxier.rimi()->invoke( m_proxier.oref(), IObjectMgr::IID(), 0, *msg, &r_result, atom::SRimiEnv( m_proxier.epid(), rimi_env.msec, rimi_env.tway ) ) ||
             !r_result.good() )
        {
#if 0
            if ( atom::ERimiResult::NOSUCHE == r_result.result()
              || atom::ERimiResult::NOSUCHO == r_result.result() )
                m_proxier.loseReference();
            if ( atom::ERimiResult::TIMEOUT == r_result.result() )
                m_proxier.rimi()->reclaimCao( m_proxier.epid(), r_result.sequ() );

#endif
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
        /*散集出参数*/
        if ( !rimi_env.tway )
        {
            if ( rimi_err ) *rimi_err = r_result.result();
            return r_return;
        }

        RIMI_IAR_ATTACH_MSG( r_result.getMsg(), m_proxier.rimi() );
        RIMI_IAR_EXCEPTION_RETURN( r_return, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_IAR_DETACH_MSG();
        /*返回异常处理*/
        RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
    }
    void rdelete( RIMI_INVOKE_PARAM ) 
    {
        atom::CRimiResult r_result;
        /*参数申明*/
#if 0
        /*同步引用关系*/
        if ( !m_proxier.syncReference() )
        {
            if ( !m_proxier.rimi()->hasEpid( m_proxier.epid() ) )
                r_result.result( atom::ERimiResult::NOSUCHE );
            else
                r_result.result( atom::ERimiResult::NOSUCHO );
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, ; );
        }
#endif
        /*入参数列集*/
        RIMI_OAR_ALLOCA_MSG( msg, m_proxier.rimi() );
        RIMI_OAR_DETACH_MSG();
        /*远程调用*/
        if ( !m_proxier.rimi()->invoke( m_proxier.oref(), IObjectMgr::IID(), 1, *msg, &r_result, atom::SRimiEnv( m_proxier.epid(), rimi_env.msec, rimi_env.tway ) ) ||
             !r_result.good() )
        {
#if 0
            if ( atom::ERimiResult::NOSUCHE == r_result.result()
              || atom::ERimiResult::NOSUCHO == r_result.result() )
                m_proxier.loseReference();
            if ( atom::ERimiResult::TIMEOUT == r_result.result() )
                m_proxier.rimi()->reclaimCao( m_proxier.epid(), r_result.sequ() );

#endif
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, ; );
        }
        /*散集出参数*/
        if ( !rimi_env.tway )
        {
            if ( rimi_err ) *rimi_err = r_result.result();
            return ;;
        }

        RIMI_IAR_ATTACH_MSG( r_result.getMsg(), m_proxier.rimi() );
        RIMI_IAR_DETACH_MSG();
        /*返回异常处理*/
        RIMI_EXCEPTION_RETURN( rimi_err, r_result, ; );
    }
    boost :: shared_ptr < IObject > funcGenObj( RIMI_INVOKE_PARAM ) 
    {
        atom::CRimiResult r_result;
        /*参数申明*/
        atom::byv<boost :: shared_ptr < IObject > >::type r_return = atom::byv<boost :: shared_ptr < IObject > >::type();
#if 0
        /*同步引用关系*/
        if ( !m_proxier.syncReference() )
        {
            if ( !m_proxier.rimi()->hasEpid( m_proxier.epid() ) )
                r_result.result( atom::ERimiResult::NOSUCHE );
            else
                r_result.result( atom::ERimiResult::NOSUCHO );
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
#endif
        /*入参数列集*/
        RIMI_OAR_ALLOCA_MSG( msg, m_proxier.rimi() );
        RIMI_OAR_DETACH_MSG();
        /*远程调用*/
        if ( !m_proxier.rimi()->invoke( m_proxier.oref(), IObjectMgr::IID(), 2, *msg, &r_result, atom::SRimiEnv( m_proxier.epid(), rimi_env.msec, rimi_env.tway ) ) ||
             !r_result.good() )
        {
#if 0
            if ( atom::ERimiResult::NOSUCHE == r_result.result()
              || atom::ERimiResult::NOSUCHO == r_result.result() )
                m_proxier.loseReference();
            if ( atom::ERimiResult::TIMEOUT == r_result.result() )
                m_proxier.rimi()->reclaimCao( m_proxier.epid(), r_result.sequ() );

#endif
            RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
        }
        /*散集出参数*/
        if ( !rimi_env.tway )
        {
            if ( rimi_err ) *rimi_err = r_result.result();
            return r_return;
        }

        RIMI_IAR_ATTACH_MSG( r_result.getMsg(), m_proxier.rimi() );
        RIMI_IAR_EXCEPTION_RETURN( r_return, m_proxier.epid(), atom::sequ_t( -1 ), boost::false_type(), rimi_err, r_return );
        RIMI_IAR_DETACH_MSG();
        /*返回异常处理*/
        RIMI_EXCEPTION_RETURN( rimi_err, r_result, r_return );
    }

private:
    atom::IRimiProxier &m_proxier;
};


}

namespace demo {

class RIMI_OBJECT_PRIVATE CRimiIServerManagerProxier : public atom::CRimiProxier<CRimiIServerManagerProxier, IServerManager>
{
public:
    virtual ~CRimiIServerManagerProxier()
    {
        if ( ( m_spid == (atom::epid_t)-1 ) || m_prev ) return ;
        atom::ERimiResult result = atom::ERimiResult::UNKNOWN;
        rdelete( &result );
        if ( result.value() > atom::ERimiResult::NOSUCHM.value() )
            rimi()->reclaimCao( epid(), oref() );
    }
    CRimiIServerManagerProxier( atom::oref_c oref, atom::epid_t epid, atom::epid_t spid, atom::IRimiMechanism *mech = 0 )
    : atom::CRimiProxier<CRimiIServerManagerProxier, IServerManager>( oref, epid, spid, mech ),
      m_CRimiIServerManagerPrivate( *this )
    {
    }

public:
    virtual bool anyCast( atom::oref_c oref, RIMI_INVOKE_PARAM ) 
    {
        return m_CRimiIServerManagerPrivate.anyCast( oref, rimi_err, rimi_env );
    }
    virtual void rdelete( RIMI_INVOKE_PARAM ) 
    {
        return m_CRimiIServerManagerPrivate.rdelete( rimi_err, rimi_env );
    }
    virtual bool funcAdd( const uint32_t a, const uint32_t b, uint32_t & c, RIMI_INVOKE_PARAM ) 
    {
        return m_CRimiIServerManagerPrivate.funcAdd( a, b, c, rimi_err, rimi_env );
    }
    virtual bool funcMul( const uint32_t a, const uint32_t b, uint32_t & c, RIMI_INVOKE_PARAM ) 
    {
        return m_CRimiIServerManagerPrivate.funcMul( a, b, c, rimi_err, rimi_env );
    }
    virtual bool func3( std :: vector < std :: string > & res, RIMI_INVOKE_PARAM ) 
    {
        return m_CRimiIServerManagerPrivate.func3( res, rimi_err, rimi_env );
    }

private:
    CRimiIServerManagerPrivate m_CRimiIServerManagerPrivate;
};

class RIMI_OBJECT_PRIVATE CRimiIObjectProxier : public atom::CRimiProxier<CRimiIObjectProxier, IObject>
{
public:
    virtual ~CRimiIObjectProxier()
    {
        if ( ( m_spid == (atom::epid_t)-1 ) || m_prev ) return ;
        atom::ERimiResult result = atom::ERimiResult::UNKNOWN;
        rdelete( &result );
        if ( result.value() > atom::ERimiResult::NOSUCHM.value() )
            rimi()->reclaimCao( epid(), oref() );
    }
    CRimiIObjectProxier( atom::oref_c oref, atom::epid_t epid, atom::epid_t spid, atom::IRimiMechanism *mech = 0 )
    : atom::CRimiProxier<CRimiIObjectProxier, IObject>( oref, epid, spid, mech ),
      m_CRimiIObjectPrivate( *this )
    {
    }

public:
    virtual bool anyCast( atom::oref_c oref, RIMI_INVOKE_PARAM ) 
    {
        return m_CRimiIObjectPrivate.anyCast( oref, rimi_err, rimi_env );
    }
    virtual void rdelete( RIMI_INVOKE_PARAM ) 
    {
        return m_CRimiIObjectPrivate.rdelete( rimi_err, rimi_env );
    }
    virtual bool funcObject( std :: string & str, RIMI_INVOKE_PARAM ) 
    {
        return m_CRimiIObjectPrivate.funcObject( str, rimi_err, rimi_env );
    }

private:
    CRimiIObjectPrivate m_CRimiIObjectPrivate;
};

class RIMI_OBJECT_PRIVATE CRimiIObjectMgrProxier : public atom::CRimiProxier<CRimiIObjectMgrProxier, IObjectMgr>
{
public:
    virtual ~CRimiIObjectMgrProxier()
    {
        if ( ( m_spid == (atom::epid_t)-1 ) || m_prev ) return ;
        atom::ERimiResult result = atom::ERimiResult::UNKNOWN;
        rdelete( &result );
        if ( result.value() > atom::ERimiResult::NOSUCHM.value() )
            rimi()->reclaimCao( epid(), oref() );
    }
    CRimiIObjectMgrProxier( atom::oref_c oref, atom::epid_t epid, atom::epid_t spid, atom::IRimiMechanism *mech = 0 )
    : atom::CRimiProxier<CRimiIObjectMgrProxier, IObjectMgr>( oref, epid, spid, mech ),
      m_CRimiIObjectMgrPrivate( *this )
    {
    }

public:
    virtual bool anyCast( atom::oref_c oref, RIMI_INVOKE_PARAM ) 
    {
        return m_CRimiIObjectMgrPrivate.anyCast( oref, rimi_err, rimi_env );
    }
    virtual void rdelete( RIMI_INVOKE_PARAM ) 
    {
        return m_CRimiIObjectMgrPrivate.rdelete( rimi_err, rimi_env );
    }
    virtual boost :: shared_ptr < IObject > funcGenObj( RIMI_INVOKE_PARAM ) 
    {
        return m_CRimiIObjectMgrPrivate.funcGenObj( rimi_err, rimi_env );
    }

private:
    CRimiIObjectMgrPrivate m_CRimiIObjectMgrPrivate;
};


}

namespace atom {


template<>
inline ERimiResult CRimiSubscriber<demo::IServerNotify, 0>::invoke( CSpIRimiServant obj, oref_c oref, ACE_Message_Block *msg, const SRimiEnv &env, sequ_t sequ )
{
    using namespace demo;

    /*判断参数是否有效*/
    if ( !msg || this->empty() ) return ERimiResult::NOSUCHO;
    /*参数列表*/
    atom::byv<const uint32_t >::type r_res = atom::byv<const uint32_t >::type();
    /*散集入参数*/
    RIMI_IAR_ATTACH_MSG( msg, obj->rimi() );
    RIMI_IAR_RETURN( r_res, env.epid, atom::sequ_t( -1 ), boost::false_type(), ERimiResult::IARFAIL );
    RIMI_IAR_DETACH_MSG();
    /*锁定订阅者列表，避免多线程竞争*/
    ACE_GUARD_RETURN( ACE_Thread_Mutex, guard, m_mutex, ERimiResult::UNKNOWN );
    /*通知所有的订阅者*/
    for ( CSubscriberSet::iterator it = m_subscribers.begin(); it != m_subscribers.end(); ++it )
    {
        if ( (*it)->epid() != env.epid || (*it)->oref() != oref  )
            continue;

        boost::shared_ptr<demo::IServerNotify> notifier = boost::dynamic_pointer_cast<demo::IServerNotify>( *it );
        if ( notifier )
            notifier->funcNotify( r_res, env );
    }
    return ERimiResult::SUCCESS;
}

template<>
inline ERimiResult CRimiSubscriber<demo::IServerNotify, 1>::invoke( CSpIRimiServant obj, oref_c oref, ACE_Message_Block *msg, const SRimiEnv &env, sequ_t sequ )
{
    using namespace demo;

    /*判断参数是否有效*/
    if ( !msg || this->empty() ) return ERimiResult::NOSUCHO;
    /*参数列表*/
    atom::byv<const std :: string >::type r_res = atom::byv<const std :: string >::type();
    /*散集入参数*/
    RIMI_IAR_ATTACH_MSG( msg, obj->rimi() );
    RIMI_IAR_RETURN( r_res, env.epid, atom::sequ_t( -1 ), boost::false_type(), ERimiResult::IARFAIL );
    RIMI_IAR_DETACH_MSG();
    /*锁定订阅者列表，避免多线程竞争*/
    ACE_GUARD_RETURN( ACE_Thread_Mutex, guard, m_mutex, ERimiResult::UNKNOWN );
    /*通知所有的订阅者*/
    for ( CSubscriberSet::iterator it = m_subscribers.begin(); it != m_subscribers.end(); ++it )
    {
        if ( (*it)->epid() != env.epid || (*it)->oref() != oref  )
            continue;

        boost::shared_ptr<demo::IServerNotify> notifier = boost::dynamic_pointer_cast<demo::IServerNotify>( *it );
        if ( notifier )
            notifier->funcNotify1( r_res, env );
    }
    return ERimiResult::SUCCESS;
}

template<>
inline ERimiResult CRimiSubscriber<demo::IServerNotify2, 0>::invoke( CSpIRimiServant obj, oref_c oref, ACE_Message_Block *msg, const SRimiEnv &env, sequ_t sequ )
{
    using namespace demo;

    /*判断参数是否有效*/
    if ( !msg || this->empty() ) return ERimiResult::NOSUCHO;
    /*参数列表*/
    atom::byv<const std :: string >::type r_res = atom::byv<const std :: string >::type();
    /*散集入参数*/
    RIMI_IAR_ATTACH_MSG( msg, obj->rimi() );
    RIMI_IAR_RETURN( r_res, env.epid, atom::sequ_t( -1 ), boost::false_type(), ERimiResult::IARFAIL );
    RIMI_IAR_DETACH_MSG();
    /*锁定订阅者列表，避免多线程竞争*/
    ACE_GUARD_RETURN( ACE_Thread_Mutex, guard, m_mutex, ERimiResult::UNKNOWN );
    /*通知所有的订阅者*/
    for ( CSubscriberSet::iterator it = m_subscribers.begin(); it != m_subscribers.end(); ++it )
    {
        if ( (*it)->epid() != env.epid || (*it)->oref() != oref  )
            continue;

        boost::shared_ptr<demo::IServerNotify2> notifier = boost::dynamic_pointer_cast<demo::IServerNotify2>( *it );
        if ( notifier )
            notifier->funcNotify2( r_res, env );
    }
    return ERimiResult::SUCCESS;
}

}
namespace atom {

void RIMI_PROXIER_REGISTER_ENTRY__( IRimiMechanism *mech )
{
    mech->addRimiProxier( CSpIRimiProxier( new demo::CRimiIServerManagerProxier( nil_uuid(), (atom::epid_t)-1, (atom::epid_t)-1, mech ) ) );
    mech->addRimiProxier( CSpIRimiProxier( new demo::CRimiIObjectProxier( nil_uuid(), (atom::epid_t)-1, (atom::epid_t)-1, mech ) ) );
    mech->addRimiProxier( CSpIRimiProxier( new demo::CRimiIObjectMgrProxier( nil_uuid(), (atom::epid_t)-1, (atom::epid_t)-1, mech ) ) );

    mech->addRimiWrapper( CSpIRimiWrapper( new CRimiSubscriber<demo::IServerNotify, 0> ) );
    mech->addRimiWrapper( CSpIRimiWrapper( new CRimiSubscriber<demo::IServerNotify, 1> ) );
    mech->addRimiWrapper( CSpIRimiWrapper( new CRimiSubscriber<demo::IServerNotify2, 0> ) );
}

}
