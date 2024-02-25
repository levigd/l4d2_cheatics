#include "IBaseClient.h"

ClientClass* BaseClientDLL::GetAllClasses(void)
{
	return callVirtual<5, ClientClass*>(this);
}
