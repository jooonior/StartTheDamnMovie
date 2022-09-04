# Template for Source SDK 2013 plugins

Quick start for developing plugins for Source SDK 2013 based games in Visual Studio.

For resources on writing plugins, see
[Source SDK 2013](https://developer.valvesoftware.com/wiki/Source_SDK_2013) and
[Server Plugins](https://developer.valvesoftware.com/wiki/Server_plugins) on Valve
Developer Wiki.

## Notes

When first opening the project, if Visual Studio prompts to retarget, avoid upgrading
platform toolset.

Installation specific parameters are defined as user macros in `Source SDK.props`.
Directory paths in macros must end with a backslash.

Debugging will launch the game with the plugin loaded. Breakpoints and hot reload work
as you'd expect.

## TODO

- Port to CMake for Linux compatibility
