#include "eso.h"
#include "esosvc.h"

#include "resource.h"
#include "../../studio/api.h"

static WACExampleScriptObject eso;
WAComponentClient *the = &eso;
WACExampleScriptObject *esowac = &eso;

// {20A21F85-BF86-455e-8249-06C1661ADEE1}
static const GUID guid = 
{ 0x20a21f85, 0xbf86, 0x455e, { 0x82, 0x49, 0x6, 0xc1, 0x66, 0x1a, 0xde, 0xe1 } };

#include "../../studio/services/creators.h"	


WACExampleScriptObject::WACExampleScriptObject()
{
  registerService(new ScriptObjectCreator<ExampleScriptObjectSvc>);
}


GUID WACExampleScriptObject::getGUID() { return guid; }
void WACExampleScriptObject::onCreate() {}
void WACExampleScriptObject::onDestroy() {}

