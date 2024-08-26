#include <iostream>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/algorithm/string.hpp>
#include "JsRimiServer.hpp"
#include "RimiServer.hpp"


namespace wtoe
{
	template<>
	JSClass CJavaScriptAdapter<demo::CJsRimiServer>::s_jsClass = 
	{
		"RimiServer",		// ¿âÃû 
		JSCLASS_HAS_PRIVATE,
		JS_PropertyStub,	// add
		JS_PropertyStub,	// del
		JS_PropertyStub,	// get
		JS_PropertyStub,	// vector
		JS_EnumerateStub, 
		JS_ResolveStub, 
		JS_ConvertStub, 
		WTOE_JS_FINALIZER( demo::CJsRimiServer , finalize ),
		JSCLASS_NO_OPTIONAL_MEMBERS
	};

	template<>
	JSPropertySpec CJavaScriptAdapter<demo::CJsRimiServer>::s_jsClassProperties[] =
	{
		{ 0, 0, 0, 0, 0 }
	};

	template<>
	JSFunctionSpec CJavaScriptAdapter<demo::CJsRimiServer>::s_jsClassMethords[] =
	{
		{ "help", WTOE_JS_METHORD( demo::CJsRimiServer, help )},
		{ "funcAdd", WTOE_JS_METHORD( demo::CJsRimiServer, funcAdd ),0,0,0 },
		{ "funcMul", WTOE_JS_METHORD( demo::CJsRimiServer, funcMul ),0,0,0 },
		{ 0, 0, 0, 0, 0 }
	};

	template<>
	JSPropertySpec CJavaScriptAdapter<demo::CJsRimiServer>::s_jsObjectProperties[] =
	{
		{ 0, 0, 0, 0, 0 }
	};

	template<>
	JSFunctionSpec CJavaScriptAdapter<demo::CJsRimiServer>::s_jsObjectMethords[] =
	{
		{ 0, 0, 0, 0, 0 }
	};
}

namespace demo
{
	CJsRimiServer::CJsRimiServer()
	{

	}

	CJsRimiServer::~CJsRimiServer()
	{

	}

	CJsRimiServer * CJsRimiServer::createObject()
	{
		return NULL;
	}

	JSBool CJsRimiServer::help(JSContext *ctx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
	{
		std::cout << "------- Usage ----------" << std::endl;
		std::cout << "RimiServer.funcAdd(param1, param2)" << std::endl;
		std::cout << "RimiServer.funcMul(param1, param2)" << std::endl;

		return JS_TRUE;
	}

	JSBool CJsRimiServer::funcAdd(JSContext *ctx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
	{
		
		SpCRimiServer sp;
		if(!wtoe::getMainApp()->getServiceInstance(WTOE_SNAME_RimiServer_RimiServer, sp)
			|| !sp)
		{
			return JS_FALSE;
		}

		uint32_t a = (uint32_t)JSVAL_TO_INT(argv[0]);
		uint32_t b = (uint32_t)JSVAL_TO_INT(argv[1]);

		uint32_t ret = sp->funcJsAdd(a,b);
		std::cout << "ret = " << ret << std::endl;
		if( ret )
			return JS_TRUE;
		else
			return JS_FALSE;
	}

	JSBool CJsRimiServer::funcMul( JSContext *ctx, JSObject *obj, uintN argc, jsval *argv, jsval *rval )
	{
		SpCRimiServer sp;
		if(!wtoe::getMainApp()->getServiceInstance(WTOE_SNAME_RimiServer_RimiServer, sp)
			|| !sp)
		{
			return JS_FALSE;
		}

		uint32_t a = (uint32_t)JSVAL_TO_INT(argv[0]);
		uint32_t b = (uint32_t)JSVAL_TO_INT(argv[1]);

		bool ret = sp->funcJsMul(a,b);

		if( ret )
			return JS_TRUE;
		else
			return JS_FALSE;
	}

	/******************************************************************************/
	/* javaScriptRegister                                                         */
	/******************************************************************************/
	bool CRimiServer::javaScriptRegister( JSContext *jsCtx, JSObject *jsObj )
	{
		return wtoe::CJavaScriptAdapter<demo::CJsRimiServer>::registerJavaScriptClass( jsCtx, jsObj );
	}

}
