
#ifndef RIMISERVERITF_HPP_
#define RIMISERVERITF_HPP_

#include "RimiServerCfg.hpp"

namespace demo
{
    /*
     * ���ӿڣ������˼��ذ�ʱ������ʸýӿ�ָ��
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
