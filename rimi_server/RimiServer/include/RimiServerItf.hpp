
#ifndef RIMISERVERITF_HPP_
#define RIMISERVERITF_HPP_

#include "RimiServerCfg.hpp"

namespace demo
{
    /*
     * 包接口，当别人加载包时，会访问该接口指针
     */
    interface RIMISERVER_PUBLIC IRimiServer
    {
    public:
        IRimiServer(){};
        virtual ~IRimiServer(){};

        virtual uint32_t funcInternal(uint32_t a, uint32_t b) = 0;
    };


} // namespace demo


#endif
