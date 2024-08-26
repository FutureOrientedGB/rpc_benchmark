#ifndef RIMISERVERPKG_HPP_
#define RIMISERVERPKG_HPP_

#include <wtoe/PackageManager/PackageManagerExp.hpp>

/*
* 声明本服务包的标识.
*/
WTOE_DECLARE_PACKAGE_NAME( RimiServer );
WTOE_DECLARE_PACKAGE_ID( RimiServer );

/*
* 声明所有的需要提供给外部用户的服务的标识.
*/
WTOE_DECLARE_PACKAGE_SERVICE_NAME( RimiServer, RimiServer );
WTOE_DECLARE_PACKAGE_SERVICE_ID( RimiServer, RimiServer );


#endif // RIMISERVERPKG_HPP_