#!/bin/sh
# -*- python -*-
# This file is bilingual. The following shell code finds our preferred python.
# Following line is a shell no-op, and starts a multi-line Python comment.
# See https://stackoverflow.com/a/47886254
""":"
# prefer SYSU_PYTHON environment variable, python3, python
SYSU_PREFERRED_PYTHONS="python3 python"
for cmd in "${SYSU_PYTHON:-}" ${SYSU_PREFERRED_PYTHONS}; do
    if command -v "$cmd" >/dev/null; then
        export SYSU_PYTHON="$(command -v "$cmd")"
        exec "${SYSU_PYTHON}" "$0" "$@"
    fi
done
echo "==> Error: $0 could not find a python interpreter!" >&2
exit 1
":"""


import subprocess
import os

has_colorama = False
try:
    from colorama import Fore, Style
    has_colorama = True
except Exception as e:
    print("module 'colorama' not installed, will not print color")


def main():
    basedir = os.path.dirname(os.path.dirname(__file__))
    datadir = os.path.join(basedir, 'data')
    outdir = os.path.join(basedir, 'out')
    builddir = os.path.join(basedir, 'build')
    fasbin = os.path.join(builddir, "src/fas")
    algos = ['greedy', 'sort', 'pagerank']
    datasets = ['wordassociation-2011.txt', 'enron.txt']
    num_nodes = [10617, 69244]
    kvalues = [100, 50, 25, 10]

    for idata in range(len(datasets)):
        for algo in algos:
            cmd = [fasbin, os.path.join(datadir, datasets[idata]),
                   '-o', os.path.join(outdir, datasets[idata][:-4]),
                   '-n', str(num_nodes[idata]),
                   '-a', algo,
                   '-s', '0']
            if algo == 'pagerank':
                for kvalue in kvalues:
                    cmd[-1] = str(kvalue)
                    if has_colorama:
                        print(Style.RESET_ALL + Fore.GREEN + ' '.join(cmd) + Style.RESET_ALL)
                    else:
                        print(' '.join(cmd))
                    subprocess.run(cmd)
            else:
                if has_colorama:
                    print(Style.RESET_ALL + Fore.GREEN + ' '.join(cmd) + Style.RESET_ALL)
                else:
                    print(' '.join(cmd))
                subprocess.run(cmd)



if __name__ == '__main__':
    main()
