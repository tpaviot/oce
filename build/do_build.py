#!/usr/bin/python3
import subprocess
import shlex
import sys
import os
import typing

envvar_to_reset: typing.Dict[str, str] = {}
envvar_to_delete: typing.List[str] = []


def override_envvar(varname: str, value: str):
    if os.environ.get(varname):
        envvar_to_reset[varname] = os.environ[varname]
    else:
        envvar_to_delete.append(varname)
    os.environ[varname] = value


def reset_envvars():
    for key, value in envvar_to_reset.items():
        os.environ[key] = value
    for key in envvar_to_delete:
        del os.environ[key]


lib = "lib"
ver_major = 7.4
ver_minor = 0

"""
+ export DESTDIR=/root/rpmbuild/BUILDROOT/OCE-7.4.0-4.amzn2023.x86_64
+ DESTDIR=/root/rpmbuild/BUILDROOT/OCE-7.4.0-4.amzn2023.x86_64
+ CFLAGS='-O2 -ftree-vectorize -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -fstack-protector-strong -specs=/usr/lib/rpm/redhat/redhat-annobin-cc1  -m64 -march=x86-64-v2 -mtune=generic -fasynchronous-unwind-tables -fstack-clash-protection -fcf-protection'
+ export CFLAGS
+ CXXFLAGS='-O2 -ftree-vectorize -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -fstack-protector-strong -specs=/usr/lib/rpm/redhat/redhat-annobin-cc1  -m64 -march=x86-64-v2 -mtune=generic -fasynchronous-unwind-tables -fstack-clash-protection -fcf-protection'
+ export CXXFLAGS
+ FFLAGS='-O2 -ftree-vectorize -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -fstack-protector-strong -specs=/usr/lib/rpm/redhat/redhat-annobin-cc1  -m64 -march=x86-64-v2 -mtune=generic -fasynchronous-unwind-tables -fstack-clash-protection -fcf-protection -I/usr/lib64/gfortran/modules'
+ export FFLAGS
+ FCFLAGS='-O2 -ftree-vectorize -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -fstack-protector-strong -specs=/usr/lib/rpm/redhat/redhat-annobin-cc1  -m64 -march=x86-64-v2 -mtune=generic -fasynchronous-unwind-tables -fstack-clash-protection -fcf-protection -I/usr/lib64/gfortran/modules'
+ export FCFLAGS
+ VALAFLAGS=-g
+ export VALAFLAGS
+ LDFLAGS='-Wl,-z,relro -Wl,--as-needed  -Wl,-z,now -specs=/usr/lib/rpm/redhat/redhat-hardened-ld -specs=/usr/lib/rpm/redhat/redhat-annobin-cc1    -Wl,--build-id=sha1 -Wl,-dT'
+ export LDFLAGS
+ LT_SYS_LIBRARY_PATH=/usr/lib64:
+ export LT_SYS_LIBRARY_PATH
+ CC=gcc
+ export CC
+ CXX=g++
+ export CXX
+ /usr/bin/cmake -S . -B amazon-linux-build -DCMAKE_C_FLAGS_RELEASE:STRING=-DNDEBUG -DCMAKE_CXX_FLAGS_RELEASE:STRING=-DNDEBUG -DCMAKE_Fortran_FLAGS_RELEASE:STRING=-DNDEBUG -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DCMAKE_INSTALL_DO_STRIP:BOOL=OFF -DCMAKE_INSTALL_PREFIX:PATH=/usr -DINCLUDE_INSTALL_DIR:PATH=/usr/include -DLIB_INSTALL_DIR:PATH=/usr/lib64 -DSYSCONF_INSTALL_DIR:PATH=/etc -DSHARE_INSTALL_PREFIX:PATH=/usr/share -DLIB_SUFFIX=64 -DBUILD_SHARED_LIBS:BOOL=ON -GNinja -DINSTALL_DIR_LIB=lib64 -DINSTALL_DIR_CMAKE=lib64/cmake/oce-7.4 -DINSTALL_DIR_DATA=share/oce-7.4/data -DINSTALL_DIR_RESOURCE=share/oce-7.4/resources -DINSTALL_DIR_DOC=share/doc/oce-7.4 -DINSTALL_DIR_INCLUDE=local/include/opencascade -DINSTALL_DIR_RESOURCE=share/oce-7.4/resources -DINSTALL_DIR_SAMPLES=share/oce-7.4/samples -DINSTALL_DIR_TESTS=share/oce-7.4/tests -DBUILD_MODULE_Draw=OFF ../
"""

override_envvar(
    "CFLAGS",
    "-O2 -ftree-vectorize -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -fstack-protector-strong -specs=/usr/lib/rpm/redhat/redhat-annobin-cc1  -m64 -march=x86-64-v2 -mtune=generic -fasynchronous-unwind-tables -fstack-clash-protection -fcf-protection",
)
override_envvar(
    "CXXFLAGS",
    "-O2 -ftree-vectorize -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -fstack-protector-strong -specs=/usr/lib/rpm/redhat/redhat-annobin-cc1  -m64 -march=x86-64-v2 -mtune=generic -fasynchronous-unwind-tables -fstack-clash-protection -fcf-protection",
)
override_envvar(
    "FFLAGS",
    "-O2 -ftree-vectorize -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -fstack-protector-strong -specs=/usr/lib/rpm/redhat/redhat-annobin-cc1  -m64 -march=x86-64-v2 -mtune=generic -fasynchronous-unwind-tables -fstack-clash-protection -fcf-protection -I/usr/lib64/gfortran/modules",
)
override_envvar(
    "FCFLAGS",
    "-O2 -ftree-vectorize -flto=auto -ffat-lto-objects -fexceptions -g -grecord-gcc-switches -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -Wp,-D_GLIBCXX_ASSERTIONS -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -fstack-protector-strong -specs=/usr/lib/rpm/redhat/redhat-annobin-cc1  -m64 -march=x86-64-v2 -mtune=generic -fasynchronous-unwind-tables -fstack-clash-protection -fcf-protection -I/usr/lib64/gfortran/modules",
)
override_envvar(
    "LDFLAGS",
    "-Wl,-z,relro -Wl,--as-needed  -Wl,-z,now -specs=/usr/lib/rpm/redhat/redhat-hardened-ld -specs=/usr/lib/rpm/redhat/redhat-annobin-cc1    -Wl,--build-id=sha1 -Wl,-dT",
)
override_envvar("LT_SYS_LIBRARY_PATH", "/usr/lib64:")
override_envvar("CC", "gcc")
override_envvar("CXX", "g++")


cmds = [
    f"""/usr/bin/cmake -S . -DCMAKE_C_FLAGS_RELEASE:STRING=-DNDEBUG -DCMAKE_CXX_FLAGS_RELEASE:STRING=-DNDEBUG -DCMAKE_Fortran_FLAGS_RELEASE:STRING=-DNDEBUG -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DCMAKE_INSTALL_DO_STRIP:BOOL=OFF -DCMAKE_INSTALL_PREFIX:PATH=/usr -DINCLUDE_INSTALL_DIR:PATH=/usr/include -DLIB_INSTALL_DIR:PATH=/usr/lib64 -DSYSCONF_INSTALL_DIR:PATH=/etc -DSHARE_INSTALL_PREFIX:PATH=/usr/share -DLIB_SUFFIX=64 -DBUILD_SHARED_LIBS:BOOL=ON -GNinja -DINSTALL_DIR_LIB=lib64 -DINSTALL_DIR_CMAKE=lib64/cmake/oce-7.4 -DINSTALL_DIR_DATA=share/oce-7.4/data -DINSTALL_DIR_RESOURCE=share/oce-7.4/resources -DINSTALL_DIR_DOC=share/doc/oce-7.4 -DINSTALL_DIR_INCLUDE=local/include/opencascade -DINSTALL_DIR_RESOURCE=share/oce-7.4/resources -DINSTALL_DIR_SAMPLES=share/oce-7.4/samples -DINSTALL_DIR_TESTS=share/oce-7.4/tests -DBUILD_MODULE_Draw=OFF ../""",
    f"""/usr/bin/cmake --build -j2 --verbose""",
    f"""/usr/bin/cmake --install """,
]

status = 0

for cmdstr in cmds:
    print(cmdstr)
    sp = subprocess.Popen(shlex.split(cmdstr))
    status = sp.wait()
    if status != 0:
        break

reset_envvars()

if status == 0:
    print("Done")
else:
    print("Problem!")

sys.stdout.write("\a")
sys.stdout.flush()
