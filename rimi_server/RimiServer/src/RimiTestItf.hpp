#ifndef RIMITESTITF_HPP_
#define RIMITESTITF_HPP_

#include <atom/RimiMechanismExp.hpp>

#include "../include/RimiServerCfg.hpp"
#include "../../iil/RimiTestItf.idl"

namespace atom {

	void RIMISERVER_PUBLIC rimiServantRegister( atom::IRimiMechanism *rimi );
	void RIMISERVER_PUBLIC rimiProxierRegister( atom::IRimiMechanism *rimi );

}
#endif