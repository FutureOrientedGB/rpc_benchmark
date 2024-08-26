#ifndef JSRIMISERVER_HPP_
#define JSRIMISERVER_HPP_

#include <boost/thread/condition.hpp>
#include <wtoe/JavaScriptEngine/JavaScriptEngineExp.hpp>
#include "../include/RimiServerExp.hpp"

namespace demo
{
	class RIMISERVER_PUBLIC CJsRimiServer : 
		public  wtoe::CJavaScriptAdapter<CJsRimiServer>,
		public	wtoe::CAdapterJavaScriptize
	{
		friend class wtoe::CJavaScriptAdapter<CJsRimiServer>;
	public:
		CJsRimiServer();
		virtual ~CJsRimiServer();

		static CJsRimiServer *createObject();

	public:
		JSBool help(JSContext *ctx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
		JSBool funcAdd(JSContext *ctx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
		JSBool funcMul(JSContext *ctx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);

	protected:
		WTOE_USING_BASE_CONSTRUCTOR( wtoe::CJavaScriptAdapter<CJsRimiServer> );
		WTOE_USING_BASE_FINALIZER( wtoe::CJavaScriptAdapter<CJsRimiServer> );

	};

}

#endif
