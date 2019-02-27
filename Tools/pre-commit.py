import sys
import os
from os import path
from subprocess import check_output

cd = os.getcwd()
sys.path.append(os.path.join(cd, "Tools"))
from clang_format_one import clang_format

def formatAllFiles():
    os.system("python Tools\clang_format_all.py")
    cmd = "git add ."
    print(cmd)
    os.system(cmd)


def formatChangedFiles():
    std_in = check_output("git diff --cached --name-only").splitlines()
    for line in std_in:
        line = line.decode("utf-8") 
        filePath = os.path.join(cd, line.rstrip())
        filePath = filePath.replace("\\", "/")
        if clang_format(filePath):
            cmd = "git add {}".format(filePath)
            print(cmd)
            os.system(cmd)
            

def main():
    #formatAllFiles()
    formatChangedFiles()

if __name__=="__main__":
    main()