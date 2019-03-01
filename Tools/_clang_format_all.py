import os
from os import path
from itertools import chain
from clang_format_one import clang_format

currentDir = os.getcwd()
slnDir = os.path.dirname(currentDir)
gameDir = os.path.join(slnDir, "Game", "Nyngine")

for dir, dirs, files in chain.from_iterable(os.walk(path) for path in [gameDir]):
    for file in files:
        filePath = os.path.join(dir, file)
        clang_format(filePath)

os.system("pause")