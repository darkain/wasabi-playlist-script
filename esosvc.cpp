#include "esosvc.h"
#include "eso.h"

static ExampleScriptObjectController _exampleController;
ScriptObjectController *exampleController = &_exampleController;


// -----------------------------------------------------------------------------------------------------
// Service
ScriptObjectController *ExampleScriptObjectSvc::getController(int n) {
  switch (n) {
    case 0:
      return exampleController;
    // add more controllers here
  }
  return NULL;
}


// -----------------------------------------------------------------------------------------------------
// ExampleObject
ExampleObject::ExampleObject() {}

ExampleObject::~ExampleObject() {}

//void vPlaylist::setPlaylist(vPlaylistI *newList) {}
int Rand(int n) { if (n==0) return 0; else return (rand() % n - 1) + 1; }



// Table of exported functions and events
// "function name",  n. params, function_pointer
function_descriptor_struct ExampleScriptObjectController::exportedFunction[] =
{
	{"getCurrent",						0,	ExampleObject::v_getCurrent},
	{"getTotal",							0,	ExampleObject::v_getTotal},
	{"getTotalByHandle",			1,	ExampleObject::v_getTotalByHandle},
	
	{"getName",								1,	ExampleObject::v_getName},
	{"getPlaystring",					1,	ExampleObject::v_getPlaystring},
	{"getNameByHandle",				2,	ExampleObject::v_getNameByHandle},
	{"getPlaystringByHandle",	2,	ExampleObject::v_getPlaystringByHandle},

	{"playSong",							1,	ExampleObject::v_playSong},
	{"playSongByHandle",			2,	ExampleObject::v_playSong},
	{"getListName",						0,	ExampleObject::v_getListName},
	{"getListID",							0,	ExampleObject::v_getListID},

	{"batchBegin",						0,	ExampleObject::v_batchBegin},
	{"batchBeginByHandle",		1,	ExampleObject::v_batchBeginByHandle},
	{"batchGetName",					1,	ExampleObject::v_batchGetName},
	{"batchGetPlaystring",		1,	ExampleObject::v_batchGetPlaystring},
	{"batchEnd",							0,	ExampleObject::v_batchEnd},

	{"getPlaylistName",				1,	ExampleObject::v_getPlaylistName},
	{"getPlaylistID",					1,	ExampleObject::v_getPlaylistID},
	{"getPlaylistHandle",			1,	ExampleObject::v_getPlaylistHandle},
	{"getListHandle",					0,	ExampleObject::v_getListHandle},

	{"setPlaylistByName",			1,	ExampleObject::v_setPlaylistByName},
	{"setPlaylistByID",				1,	ExampleObject::v_setPlaylistByID},
	{"setPlaylistByHandle",		1,	ExampleObject::v_setPlaylistByHandle},

	{"prevPlaylist",					0,	ExampleObject::v_prevPlaylist},
	{"nextPlaylist",					0,	ExampleObject::v_nextPlaylist},
	{"randPlaylist",					0,	ExampleObject::v_randPlaylist},
};


ExampleScriptObjectController::getNumFunctions()
{
  return sizeof(exportedFunction) / sizeof(function_descriptor_struct); 
}


scriptVar ExampleObject::v_getCurrent(SCRIPT_FUNCTION_PARAMS, ScriptObject *o)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_INT((static_cast<ExampleObject *>(o))->currentTrackID());
}


scriptVar ExampleObject::v_getTotal(SCRIPT_FUNCTION_PARAMS, ScriptObject *o)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_INT((static_cast<ExampleObject *>(o))->getPlaylistLength());
}


scriptVar ExampleObject::v_getTotalByHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar handle)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_INT((static_cast<ExampleObject *>(o))->getPlaylistLength(GET_SCRIPT_INT(handle)));
}


scriptVar ExampleObject::v_playSong(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID)
{
  SCRIPT_FUNCTION_INIT
	(static_cast<ExampleObject *>(o))->playSong(GET_SCRIPT_INT(ID));
	return MAKE_SCRIPT_VOID();
}


scriptVar ExampleObject::v_getListName(SCRIPT_FUNCTION_PARAMS, ScriptObject *o)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_STRING((static_cast<ExampleObject *>(o))->getPlaylistName());
}


scriptVar ExampleObject::v_getListID(SCRIPT_FUNCTION_PARAMS, ScriptObject *o)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_INT((static_cast<ExampleObject *>(o))->getPlaylistID());
}


//----------------------------------------------------
//Get Song Info
//----------------------------------------------------
scriptVar ExampleObject::v_getName(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_STRING((static_cast<ExampleObject *>(o))->getItem(GET_SCRIPT_INT(ID)));
}


scriptVar ExampleObject::v_getPlaystring(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_STRING((static_cast<ExampleObject *>(o))->getItemFile(GET_SCRIPT_INT(ID)));
}


scriptVar ExampleObject::v_getNameByHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID, scriptVar handle)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_STRING((static_cast<ExampleObject *>(o))->getItem(GET_SCRIPT_INT(ID), GET_SCRIPT_INT(handle)));
}


scriptVar ExampleObject::v_getPlaystringByHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID, scriptVar handle)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_STRING((static_cast<ExampleObject *>(o))->getItemFile(GET_SCRIPT_INT(ID), GET_SCRIPT_INT(handle)));
}


//----------------------------------------------------
//Batch Stuff
//----------------------------------------------------
scriptVar ExampleObject::v_batchBegin(SCRIPT_FUNCTION_PARAMS, ScriptObject *o)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_BOOLEAN((static_cast<ExampleObject *>(o))->batchBegin());
}


scriptVar ExampleObject::v_batchBeginByHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar handle)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_BOOLEAN((static_cast<ExampleObject *>(o))->batchBegin(GET_SCRIPT_INT(handle)));
}


scriptVar ExampleObject::v_batchEnd(SCRIPT_FUNCTION_PARAMS, ScriptObject *o)
{
  SCRIPT_FUNCTION_INIT
	(static_cast<ExampleObject *>(o))->batchEnd();
	return MAKE_SCRIPT_VOID();
}


scriptVar ExampleObject::v_batchGetName(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_STRING((static_cast<ExampleObject *>(o))->batchGetItem(GET_SCRIPT_INT(ID)));
}


scriptVar ExampleObject::v_batchGetPlaystring(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_STRING((static_cast<ExampleObject *>(o))->batchGetItemFile(GET_SCRIPT_INT(ID)));
}


//----------------------------------------------------
//Get Playlist Info
//----------------------------------------------------
scriptVar ExampleObject::v_getPlaylistName(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar handle)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_STRING((static_cast<ExampleObject *>(o))->getPlaylistName(GET_SCRIPT_INT(handle)));
}


scriptVar ExampleObject::v_getPlaylistID(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar handle)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_INT((static_cast<ExampleObject *>(o))->getPlaylistID(GET_SCRIPT_INT(handle)));
}


scriptVar ExampleObject::v_getPlaylistHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_INT((static_cast<ExampleObject *>(o))->getPlaylistHandle(GET_SCRIPT_INT(ID)));
}


scriptVar ExampleObject::v_getListHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o)
{
  SCRIPT_FUNCTION_INIT
	return MAKE_SCRIPT_INT((static_cast<ExampleObject *>(o))->getPlaylistHandle());
}



//----------------------------------------------------
//Set Playlist
//----------------------------------------------------
scriptVar ExampleObject::v_setPlaylistByName(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar Name)
{
  SCRIPT_FUNCTION_INIT
	(static_cast<ExampleObject *>(o))->setPlaylist(GET_SCRIPT_STRING(Name));
	return MAKE_SCRIPT_VOID();
}


scriptVar ExampleObject::v_setPlaylistByID(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar ID)
{
  SCRIPT_FUNCTION_INIT
	(static_cast<ExampleObject *>(o))->setPlaylist(GET_SCRIPT_INT(ID));
	return MAKE_SCRIPT_VOID();
}


scriptVar ExampleObject::v_setPlaylistByHandle(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar handle)
{
  SCRIPT_FUNCTION_INIT
	(static_cast<ExampleObject *>(o))->setPlaylist((PlaylistHandle)GET_SCRIPT_INT(handle));
	return MAKE_SCRIPT_VOID();
}


scriptVar ExampleObject::v_prevPlaylist(SCRIPT_FUNCTION_PARAMS, ScriptObject *o)
{
  SCRIPT_FUNCTION_INIT
	(static_cast<ExampleObject *>(o))->prevPlaylist();
	return MAKE_SCRIPT_VOID();
}


scriptVar ExampleObject::v_nextPlaylist(SCRIPT_FUNCTION_PARAMS, ScriptObject *o)
{
  SCRIPT_FUNCTION_INIT
	(static_cast<ExampleObject *>(o))->nextPlaylist();
	return MAKE_SCRIPT_VOID();
}


scriptVar ExampleObject::v_randPlaylist(SCRIPT_FUNCTION_PARAMS, ScriptObject *o)
{
  SCRIPT_FUNCTION_INIT
	(static_cast<ExampleObject *>(o))->randPlaylist();
	return MAKE_SCRIPT_VOID();
}





/*
// This is called when a script calls ExampleObject.functionABC(...)
scriptVar ExampleObject::example_functionABC(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar a, scriptVar b, scriptVar c) {
  // the following line is mandatory at the start of all exported script function/events
  SCRIPT_FUNCTION_INIT   
  // this calls the actual function off the object
  return MAKE_SCRIPT_INT((static_cast<ExampleObject *>(o))->functionABC(GET_SCRIPT_INT(a), GET_SCRIPT_FLOAT(b), GET_SCRIPT_STRING(c)));
}

scriptVar ExampleObject::example_eventOnSomething(SCRIPT_FUNCTION_PARAMS, ScriptObject *o, scriptVar msg) {
  // the following line is mandatory at the start of all exported script function/events
  SCRIPT_FUNCTION_INIT  
  // this needs to be called after script_function_init for all events, using the object pointer passed to the function, the scriptController pointer, and your event parameters
  // note the '1' at the end of the macro name, this is the number of parameters in your event
  PROCESS_HOOKS1(o, exampleController, msg); 
  // this prevents the scripting engine to run events that are not trapped by anyone
  SCRIPT_FUNCTION_CHECKABORTEVENT;
  // this actually runs all scripts associated with the event, note '1' in the macro, this is again the number of parameters in your event
  SCRIPT_EXEC_EVENT1(o, msg);
}
*/
