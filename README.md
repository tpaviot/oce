Travis-CI:
[![Build Status](https://travis-ci.org/tpaviot/oce.png?branch=master)](https://travis-ci.org/tpaviot/oce)
Appveyor:
[![Build Status](https://ci.appveyor.com/api/projects/status/wq74bifo9lojmxsj?svg=true)](https://ci.appveyor.com/project/tpaviot/oce)

## About

[![Join the chat at https://gitter.im/tpaviot/oce](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/tpaviot/oce?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

oce is a C++ 3D modeling library. It can be used to develop CAD/CAM softwares, for instance [FreeCad](http://www.freecadweb.org/) or [IfcOpenShell](http://www.ifcopenshell.org/).

oce stands for **o**pencascade **c**ommunity **e**dition. This project aims at gathering patches/ changes/ improvements from the OCC community over the latest release (currently OCCT 6.8.0). Official OCCT documentation and sources are available at http://www.opencascade.org/, you can also theck their development portal at http://dev.opencascade.org. 

## Download latest release

You can download source code as well as precompiled binaries for windows at:

**[oce-0.17](https://github.com/tpaviot/oce/releases/tag/OCE-0.17)** (March 2015)

## OCE history

Below are listed all the oce release since the beginning of the project, the OCCT matching version, as well as ABI Change if any (an ABI change means that OCE binaries are not compatible with previous ones).

| OCE release number | ABI Change | OCE release date | OCCT version |
| ------------- | ------------- |  ------------- |------------- |
| [0.17](https://github.com/tpaviot/oce/releases/tag/OCE-0.17)  | Yes | March 2015 | 6.8.0 |
| [0.16.1](https://github.com/tpaviot/oce/releases/tag/OCE-0.16.1) | No | November 2014 | 6.7.1 |
| [0.16](https://github.com/tpaviot/oce/releases/tag/OCE-0.16) | Yes | July 2014 | 6.7.1 |
| [0.15](https://github.com/tpaviot/oce/releases/tag/OCE-0.15) | Yes | February 2014 | 6.7.0 |
| [0.14.1](https://github.com/tpaviot/oce/releases/tag/OCE-0.14.1) | No | January 2014 | 6.6.0 |
| [0.14](https://github.com/tpaviot/oce/releases/tag/OCE-0.14) | No | December 2013 | 6.6.0 |
| [0.13](https://github.com/tpaviot/oce/releases/tag/OCE-0.13) | Yes | September 2013 | 6.6.0 |
| [0.12](https://code.google.com/p/oce-binaries/downloads/list) | Yes | March 2013 | 6.5.2 |
| [0.11](https://code.google.com/p/oce-binaries/downloads/list)| Yes | December 2012 | 6.5.4 |
| 0.10 | Yes | June 2012 | 6.5.3 |
| 0.9.1 | No | January 2012 | 6.5.2 |
| 0.9.0 | No | January 2012 | 6.5.2 |
| 0.8.0 | No | December 2011 | 6.5.1 |
| 0.7.0 | No | October 2011 | 6.5.1 |
| 0.6.0 | No | September 2011 | 6.5.1 |
| 0.5.0 | No | August 2011 | 6.5.1 |
| 0.4.0 | No | July 2011 | 6.5.0 |
| 0.3.0 | No | June 2011 | 6.5.0 |
| 0.2.0 | No | May 2011 | 6.5.0 |
| 0.1.0 |  First public release | April 2011 | 6.5.0 |

## OCE community

We use the following online resources:
  * Sources
       https://github.com/tpaviot/oce
  * Releases/Downloads/Precompiled binaries:
       https://github.com/tpaviot/oce/releases
  * Bug tracker
       https://github.com/tpaviot/oce/issues
  * Mailing list
       http://groups.google.com/group/oce-dev/about
  * Travic-CI
       https://travis-ci.org/tpaviot/oce
  * Appveyor
       https://ci.appveyor.com/project/tpaviot/oce

Just ask @tpaviot (tpaviot@gmail.com) or @dbarbier (bouzim@gmail.com) for a
request regarding write access to the repository.

## Get the source and compile
 
  * Create a local copy of the github repository:
``` bash
$ git clone git://github.com/tpaviot/oce.git
```
  * Stay to date with latests developements:

``` bash
$ cd oce
$ git pull
```
  * Compile:

Read [BUILD.Unix.md](BUILD.Unix.md) file for instructions on compiling for Unix (for both Linux and MacOSX users).Windows users should read [BUILD.MINGWw64.md](BUILD.MINGWw64.md) if they use Mingw or [BUILD.MSVC.md](BUILD.MSVC.md) if they prefer MSVC compiler.

## License

OCE has the same license as OCCT; since OCCT 6.7.0 (OCE-0.16.x), you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 2.1 as published by the Free Software Foundation, with special exception defined in the file OCCT_LGPL_EXCEPTION.txt. See LICENSE_LGPL_21.txt for the full license text.
