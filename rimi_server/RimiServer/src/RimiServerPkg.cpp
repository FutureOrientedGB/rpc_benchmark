#include "RimiServer.hpp"

/*
* 定义所有的需要提供给外部用户的服务的标识.
*/
using namespace demo;

WTOE_DEFINE_PACKAGE_SERVICE_ID( RimiServer, RimiServer );

/*
* 定义所有的需要通过名字进行动态访问的服务.
*/
WTOE_PACKAGE_SERVICE_LIST_BEG()
WTOE_PACKAGE_SERVICE_LIST_ADD( RimiServer, RimiServer )
WTOE_PACKAGE_SERVICE_LIST_END()

/*
* 定义本服务包的标识.
*/
WTOE_DEFINE_PACKAGE_ID( RimiServer );