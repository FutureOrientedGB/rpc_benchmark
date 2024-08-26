#include "RimiTestItf.hpp"

#define RIMI_SERVANT_REGISTER_ENTRY__ RIMISERVER_PUBLIC rimiServantRegister
#include "../../iil/RimiTestServant.inl"
#undef  RIMI_SERVANT_REGISTER_ENTRY__

#define RIMI_PROXIER_REGISTER_ENTRY__ RIMISERVER_PUBLIC rimiProxierRegister
#include "../../iil/RimiTestProxier.inl"
#undef  RIMI_PROXIER_REGISTER_ENTRY__