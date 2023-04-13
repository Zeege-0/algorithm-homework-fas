import subprocess
import os
from colorama import Fore, Back, Style


def main():
    basedir = os.path.dirname(os.path.dirname(__file__))
    datadir = os.path.join(basedir, 'data')
    outdir = os.path.join(basedir, 'out')
    fasbin = os.path.join(basedir, "build/src/fas")
    algos = ['greedy', 'sort', 'pagerank']
    datasets = [os.path.join(datadir, i) for i in['wordassociation-2011.txt', 'enron.txt']]
    num_nodes = [10617, 69244]
    kvalues = [10]
    for idata in range(len(datasets)):
        for algo in algos:
            cmd = [fasbin, datasets[idata],
                   '-o', os.path.join(outdir, datasets[idata][:-4]),
                   '-n', str(num_nodes[idata]),
                   '-a', algo]
            if algo == 'pagerank':
                for kvalue in kvalues:
                    cmd.extend(['-s', str(kvalue)])
                    print(Fore.GREEN + ' '.join(cmd) + Style.RESET_ALL)
                    subprocess.run(cmd)
            else:
                print(Fore.GREEN + ' '.join(cmd) + Style.RESET_ALL)
                subprocess.run(cmd)



if __name__ == '__main__':
    main()
