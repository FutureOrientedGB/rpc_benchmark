#include "RimiServer.hpp"

/*
* �������е���Ҫ�ṩ���ⲿ�û��ķ���ı�ʶ.
*/
using namespace demo;

WTOE_DEFINE_PACKAGE_SERVICE_ID( RimiServer, RimiServer );

/*
* �������е���Ҫͨ�����ֽ��ж�̬���ʵķ���.
*/
WTOE_PACKAGE_SERVICE_LIST_BEG()
WTOE_PACKAGE_SERVICE_LIST_ADD( RimiServer, RimiServer )
WTOE_PACKAGE_SERVICE_LIST_END()

/*
* ���屾������ı�ʶ.
*/
WTOE_DEFINE_PACKAGE_ID( RimiServer );