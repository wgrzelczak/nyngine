import os
#GitPython package
import git
from distutils.util import strtobool

solutionDir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

previousWorkingDirectory = os.getcwd()
os.chdir(solutionDir)

git = git.Repo("").git
print(git.clean('-Xdn'))

print(80*'-', "\n")

if strtobool(input("Want remove above? (Y/N): ")):
    try:
        print(git.clean('-Xdf'))
    except Exception as e:
        print(80*'-', "\n")
        print("Some files wasn't removed. Exception trace:")
        print(e)
        print(80*'-', "\n")

os.chdir(previousWorkingDirectory)
os.system("pause")