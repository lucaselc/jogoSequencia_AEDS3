#!/usr/bin/env python
from random import randint
import argparse
import os

num = 5
nmin = 1
nmax = 50

parser = argparse.ArgumentParser()
parser.add_argument('--file', default=None)
parser.add_argument('--num', type=int, default=num)
parser.add_argument('--nmin', type=int, default=nmin)
parser.add_argument('--nmax', type=int, default=nmax)

args = parser.parse_args()

num = args.num
nmin = args.nmin
nmax = args.nmax
file = args.file

os.makedirs("inputs", exist_ok=True)
if file is None:
    file = f'entrada-{num}.txt'

file = f'inputs/{file}'

with open(file, 'w') as f:
    rand = [randint(nmin, nmax) for _ in range(0, num)]
    f.write(f'{num}\n')
    f.writelines(' '.join(map(str, rand)))

