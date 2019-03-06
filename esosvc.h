#ifndef __CFGSCRIPTOBJ_H
#define __CFGSCRIPTOBJ_H

#include "../../common/script/scriptobj.h"
#include "../../common/script/objcontroller.h"
#include "../../studio/services/svc_scriptobj.h"
//#include "../../studio/corecb.h"
#include "../../common/corehandle.h"
#include "../../bfc/svc_enum.h"
#include "../../pledit/svc_pldir.h"
#include "../../pledit/playlist.h"
#include "../../common/nsGUID.h"

#include "../../My Projects/Playlist3/Playlist3.H"

class ExampleObject;

extern ScriptObjectController *exampleController;

// -----------------------------------------------------------------------------------------------------
// ScriptObject Provider Service. This class tells the system that we have some ScriptObjectControllers
// to register.
class ExampleScriptObjectSvc : public svc_scriptObjectI 
{
public:
  ExampleScriptObjectSvc() {};
  virtual ~ExampleScriptObjectSvc() {};

  static const char *getServiceName() { return "Example Script Object Service"; }
  virtual ScriptObjectController *getController(int n);
};       

// -----------------------------------------------------------------------------------------------------
// Script classe GUID
// {B75CEEA2-BCF1-419d-B1EE-4FB3515E1E86} // this is the guid to use in your compiler definitions, change it for each new class!
static const GUID EXAMPLE_SCRIPTOBJECT_GUID = 
{ 0xb75ceea2, 0xbcf1, 0x419d, { 0xb1, 0xee, 0x4f, 0xb3, 0x51, 0x5e, 0x1e, 0x86 } };

// -----------------------------------------------------------------------------------------------------
// ScriptObject Interface. This is your script object, you could attach this class to a preexisting object
// you have, as a seconday inheritance, then fill in a few functions and events. Or you could start from the
// scriptobject and turn it into a wrapper to your own object. 
class ExampleObject : public ScriptObjectI, public vPlaylist3
{
  public:
    ExampleObject();
    virtual ~ExampleObject();

		svc_plDir *getPlService();
    
    virtual const char *vcpu_getClassName() { return "ExampleObject"; }
    virtual ScriptObjectController *vcpu_getController() { return exampleController; }

		static scriptVar v_getCurrent(SCRIPT_FUNCTION_PARAMS, ScriptObject *o);
		static scriptVar v_getTotal(SCRIPT_FUNCTION_PARAMS, ScriptObject *o);
//		static scriptVar v_getCurrent(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar handle);
		static scriptVar v_getTotalByHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar handle);

		static scriptVar v_getName(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID);
		static scriptVar v_getPlaystring(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID);
		static scriptVar v_getNameByHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID, scriptVar handle);
		static scriptVar v_getPlaystringByHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID, scriptVar handle);

		static scriptVar v_playSong(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID);
		static scriptVar v_playSongByHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID, scriptVar handle);
		static scriptVar v_getListName(SCRIPT_FUNCTION_PARAMS, ScriptObject *o);
		static scriptVar v_getListID(SCRIPT_FUNCTION_PARAMS, ScriptObject *o);

		static scriptVar v_batchBegin(SCRIPT_FUNCTION_PARAMS, ScriptObject *o);
		static scriptVar v_batchBeginByHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar handle);
		static scriptVar v_batchEnd(SCRIPT_FUNCTION_PARAMS, ScriptObject *o);
		static scriptVar v_batchGetName(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID);
		static scriptVar v_batchGetPlaystring(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID);

		static scriptVar v_getPlaylistName(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar handle);
		static scriptVar v_getPlaylistID(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar handle);
		static scriptVar v_getPlaylistHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID);
		static scriptVar v_getListHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o);

		static scriptVar v_setPlaylistByName(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar Name);
		static scriptVar v_setPlaylistByID(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID);
		static scriptVar v_setPlaylistByHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar handle);

		static scriptVar v_prevPlaylist(SCRIPT_FUNCTION_PARAMS, ScriptObject *o);
		static scriptVar v_nextPlaylist(SCRIPT_FUNCTION_PARAMS, ScriptObject *o);
		static scriptVar v_randPlaylist(SCRIPT_FUNCTION_PARAMS, ScriptObject *o);
};

// -----------------------------------------------------------------------------------------------------
// This class describes to the system how to handle, create and delete our script class

class ExampleScriptObjectController : public ScriptObjectControllerI {
  public:
    ExampleScriptObjectController() {} // (don't ask my why, the compiler wanted it.)
    virtual const char *getClassName() { return "ExampleObject"; } // has to match the controlled class' vcpu_getClassName() !
    virtual const char *getAncestorClassName() { return "Object"; }  // "Object" to inherit from root, otherwise name of parent class
    virtual ScriptObjectController *getAncestorController() { return NULL; } // NULL if inheriting from root, otherwise, your parent controller class
    virtual int getNumFunctions(); // number of functions and events in table
    virtual const function_descriptor_struct *getExportedFunctions() { return exportedFunction; } // pointer to function table
    virtual GUID getClassGuid() { return EXAMPLE_SCRIPTOBJECT_GUID; } // script class guid
    virtual int getInstantiable() { return 1; } // 1 if using '&' in compiler definitions
    virtual int getReferenceable() { return 1; } // usually 1, or 0 if using _predecl in compiler definitions
    virtual ScriptObject *instantiate() { return new ExampleObject; } // create your object here
    virtual void destroy(ScriptObject *o) { delete static_cast<ExampleObject *>(o); } // delete it here
    virtual void *encapsulate(ScriptObject *o) { return NULL; } // no encapsulation for exampleobject yet
    virtual void deencapsulate(void *o ) {} // no encapsulation for exampleobject yet

  private:
    static function_descriptor_struct exportedFunction[];
};
#endif

