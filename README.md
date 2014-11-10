[GDK - Gamemode SDK for C/C++][github]
========================================

[![Build Status][build_status]][build]

Introduction
-------------

The GDK (Gamemode Development Kit) is a library that allows you to write
SA-MP gamemodes in C/C++. It mirrors the Pawn scripting API provied by
the SA-MP server and lets you handle various SA-MP events a.k.a callbacks
in a similar fashion.

Building GDK
------------

Prerequisites:

* [SA-MP plugin SDK](https://github.com/Zeex/samp-plugin-sdk)
* [CMake](http://cmake.org) 2.8.12+
* [Python](http://python.org) 2.7+
* C89 compiler
* C++ compiler (for plugins)

Building the source code is as simple as running the following commands:

```sh
cd path/to/sampgdk
mkdir build && cd build
cmake ../ -DSDK_DIR=path/to/sdk
make
make install # optional
```

Supported options:

* SAMPGDK_STATIC             - Build as static library (default is OFF)
* SAMPGDK_BUILD_PLUGINS      - Build example plugins (default is OFF)
* SAMPGDK_BUILD_AMALGAMATION - Build amalgamation (default is OFF)

Getting Started
---------------

You can start with downloading the source code and playing a bit with the
[HelloWorld][helloworld] plugin.

### Using Git

If you know Git the simplest way to get started is probably to clone this
repo and create a new local branch for your personal project:

```
git clone git://github.com/Zeex/sampgdk.git
git checkout -b my-project
```

and begin working on it right inside the GDK source tree.

Later if you decide that it's time to update the library, say to version
v1.2.3, you would simply switch to master, pull the changes in and merge
them into your local branch:

```
<commit your changes>
git checkout master
git pull origin master
git checkout my-project
git merge v1.2.3
```

Documentation
-------------

The API documentation is generated using [Doxygen][doxygen] and is located
in the doc/html directory of the build tree. For the current release it is
also available [online][online-docs].

[github]: https://github.com/Zeex/sampgdk
[build]: https://travis-ci.org/Zeex/sampgdk
[build_status]: https://travis-ci.org/Zeex/sampgdk.png?branch=master
[helloworld]: https://github.com/Zeex/sampgdk/tree/master/plugins/helloworld
[doxygen]: http://www.stack.nl/~dimitri/doxygen/
[online-docs]: http://zeex.github.io/sampgdk/doc/html/index.html
[forums]: http://forum.sa-mp.com/showthread.php?t=421090
