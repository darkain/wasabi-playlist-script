#include <lib/std.mi>
#include "exampleobject.mi"

Global PlaylistObject playlist;

System.onScriptLoaded() {

  playlist = new PlaylistObject;

  playlist.functionABC(32, 75.01248, "Hello, world");
}

System.onScriptLoaded() {
  delete playlist;
}
