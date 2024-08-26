#ifndef RimiServerCfg_HPP_
#define RimiServerCfg_HPP_

#if defined( WIN32 ) && defined( _MSC_VER )
#    ifdef RIMISERVER_PRJ
#        define RIMISERVER_PUBLIC __declspec(dllexport)
#    else
#        define RIMISERVER_PUBLIC __declspec(dllimport)
#    endif
#elif defined( __GNUC__ )
#    define RIMISERVER_PUBLIC //__attribute__((visibility("default")))
#    define RIMI_OBJECT_EXPORT 
#    define RIMI_OBJECT_IMPORT 
#    define RIMI_OBJECT_PUBLIC 
#    define RIMI_OBJECT_PRIVATE __attribute__((visibility("hidden")))
#endif

#if defined( TEST_SUPPORT )	// 单元测试支持
#    define RIMISERVER_PRIVATE RIMISERVER_PUBLIC
#else
#    if defined( WIN32 ) && defined( _MSC_VER )
#        define RIMISERVER_PRIVATE
#    elif defined( __GNUC__ )
#        define RIMISERVER_PRIVATE __attribute__((visibility("hidden")))
#    endif
#endif

#endif // RimiServerCfg_HPP_
