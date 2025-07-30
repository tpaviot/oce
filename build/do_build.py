#!/usr/bin/python3
import subprocess
import shlex
import sys

lib = "lib"
ver_major = 7.4
ver_minor = 0

cmds = [
    f"""cmake -GNinja \
        -DINSTALL_DIRlib={lib} \
        -DINSTALL_DIR_CMAKE={lib}/cmake/oce-{ver_major}.{ver_minor} \
        -DINSTALL_DIR_DATA=share/oce-{ver_major}.{ver_minor}/data \
        -DINSTALL_DIR_RESOURCE=share/oce-{ver_major}.{ver_minor}/resources \
        -DINSTALL_DIR_DOC=share/doc/oce-{ver_major}.{ver_minor} \
        -DINSTALL_DIR_INCLUDE=include/opencascade \
        -DINSTALL_DIR_RESOURCE=share/oce-{ver_major}.{ver_minor}/resources \
        -DINSTALL_DIR_SAMPLES=share/oce-{ver_major}.{ver_minor}/samples \
        -DINSTALL_DIR_TESTS=share/oce-{ver_major}.{ver_minor}/tests \
        -DBUILD_MODULE_Draw=OFF \
        ../""".replace(
        "\\\n", ""
    ),
    f"""ninja-build -j 2 -v""",
    f"""ninja-build install""",
]

status = 0

for cmdstr in cmds:
    print(cmdstr)
    sp = subprocess.Popen(shlex.split(cmdstr))
    status = sp.wait()
    if status != 0:
        break

if status == 0:
    print("Done")
else:
    print("Problem!")

sys.stdout.write("\a")
sys.stdout.flush()
