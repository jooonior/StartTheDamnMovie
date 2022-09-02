# Template for Source SDK 2013 plugins

Quick start for developing plugins for Source SDK 2013 based games.

For resources on writing plugins, see
[Source SDK 2013](https://developer.valvesoftware.com/wiki/Source_SDK_2013) and
[Server Plugins](https://developer.valvesoftware.com/wiki/Server_plugins) on Valve
Developer Wiki.

## Notes

When first opening the project, if Visual Studio prompts to retarget, avoid upgrading
platform toolset.

Installation specific parameters are defined as user macros in `Source SDK.props`.
Directory paths in macros must end with a backslash.

## TODO

- Port to CMake for Linux compatibility
