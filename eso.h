#ifndef _ESO_H
#define _ESO_H

#include "../../studio/wac.h"

class WACExampleScriptObject : public WAComponentClient {
public:
  WACExampleScriptObject();

  virtual const char *getName() { return "Playlist Script Object"; };
  virtual GUID getGUID();

  virtual void onCreate();
  virtual void onDestroy();

private:
};

extern WACExampleScriptObject *esowac;

#endif
