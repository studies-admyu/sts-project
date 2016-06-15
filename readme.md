### For developers

There may be compatibility issues with some versions of Visual C++ compiler. See [an article](https://msdn.microsoft.com/en-us/library/hh567368.aspx) for details.

### Building

The project is cross-platform and tested at least on Windows, Linux (Ubuntu).
CMake >= 2.8 is used for building.

**WARNING: Building with CMake under Mac OS X is not supported.**

The dependencies:

 - Boost 1.57 (or higher) -
   You can download the latest version at [boost.org](http://www.boost.org/).
 - OGRE 1.9 -
   Refer to OGRE wiki for installation details. In Linux you may use packages or [build Ogre from sources](http://www.ogre3d.org/tikiwiki/Building+Ogre).
 - OIS -
   Can be installed with the pre-built OGRE SDK. You may also [build it from sources](http://github.com/wgois/OIS).
 - SDL 1.2.

Required CMake variables:

 - CMAKE_INSTALL_PREFIX -- where to install the project. Can be relative to the project root or absolute.
 - CMAKE_BUILD_TYPE -- Release or Debug. If Debug is used, you can also disable installing binaries by turning
     INSTALL_DEBUG_BINARIES off.

For example, building project on Linux may look like this:

`cd ${PROJECT_ROOT}; rm -rf build; mkdir build; cd build;`
`cmake -D CMAKE_INSTALL_PREFIX="." -D CMAKE_BUILD_TYPE="Debug" ..;`
`make && make install`

You must also provide Ogre config file `ogre.cfg` in `config` directory. Look at the `ogre.cfg.example` inside
for a sample. In addition, two versions of `plugins.cfg`, release and debug, can be specified there. They may
be necessary for Linux users since they specify `PluginFolder` path, fixing errors like
`Could not load dynamic library RenderSystem_GL.  System Error: RenderSystem_GL.so.1.9.0: cannot open shared object
 file: No such file or directory in DynLib::load`. Samples are also included.
