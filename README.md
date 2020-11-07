[![Azure Build Status](https://dev.azure.com/tpaviot/oce/_apis/build/status/tpaviot.oce?branchName=azure-ci)](https://dev.azure.com/tpaviot/oce/_build?definitionId=6)
[![Join the chat at https://gitter.im/tpaviot/oce](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/tpaviot/oce?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

## About

oce (Open Cascade community Edition) is a fork of the Open Cascade 3D c++ modeling library. This project aims at gathering patches/changes/improvements from the OCC community. Official OCCT documentation and sources are available at http://dev.opencascade.org/

## How is this project page structured ?

There are 4 main branches:

1. [upstream/master](https://github.com/tpaviot/oce/tree/upstream/master) is a mirror of the official OpenCascade git repository master branch. Both are updated about once a week. Note that you need to sign a CLA to access the upstream repository, even in read only mode, otherwise you only have a gitweb access to the source. First commit is the snapshot of the 7.4.0 release.

2. [oce/patches](https://github.com/tpaviot/oce/tree/oce/patches) contains community patches. oce/patches is rebased on top of upstream/master each time it is updated. oce/patches is set as the default branch in the github project settings.

3. [azure-ci](https://github.com/tpaviot/oce/tree/azure-ci) contains programs to build oce on a MS Azure pipeline. azure-ci is 

4. [official-upstream-packages](https://github.com/tpaviot/oce/tree/official-upstream-packages) is an empty branch (dos not contain any source), also known as an orphan branch. It is a container for copies of official source and binary packages. This allows anonymous download of official packages, whereas upstream webstie requires to be logged in to start any download.

Tags/Releases:

Since official 7.4.0, all upstream tags are mirrored using the upstream/ prefix (e.g. the [7_4_0p1](http://git.dev.opencascade.org/gitweb/?p=occt.git;a=commit;h=fd47711d682be943f0e0a13d1fb54911b0499c31) upstream tag is available as [upstream/7_4_0p1](https://github.com/tpaviot/oce/releases/tag/upstream%2FV7_4_0p1) on this repository).

## Download latest release

oce has not released any recent version after upstream 7.5.0 was released.

## OCE documentation

Read the official upstream documentation for 7.5.0 release, at:

https://www.opencascade.com/doc/occt-7.5.0/refman/html/index.html

## OCE community

We use the following online resources:
  * git repository
       https://github.com/tpaviot/oce
  * Mailing list
       http://groups.google.com/group/oce-dev/about
  * Azure CI
       https://dev.azure.com/tpaviot/oce

To request write access to the repository, just ask @tpaviot (tpaviot@gmail.com).

## License

OCE has the same license as OCCT; since OCCT 6.7.0 (OCE-0.16.x), you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 2.1 as published by the Free Software Foundation, with special exception defined in the file OCCT_LGPL_EXCEPTION.txt. See LICENSE_LGPL_21.txt for the full license text.

## OCE history

The oce project was started in 2011.
