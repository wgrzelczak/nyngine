import os
from os import walk
from os import path
from shutil import copyfile

currentDir = os.path.dirname(os.path.abspath(__file__))
solutionDir = os.path.dirname(currentDir)

hooksDir = os.path.join(solutionDir, ".git", "hooks")

for dir, dirs, files in os.walk(currentDir):
    for file in files:
        if file.endswith(".hook"):
            src = os.path.join(dir, file)
            dst = os.path.join(hooksDir, file.replace(".hook", ""))

            print("Copy: {} >>> {}".format(src, dst))
            copyfile(src, dst)

os.system("pause")