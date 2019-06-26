import os

previousWorkingDirectory = os.getcwd()
os.chdir(os.path.dirname(os.path.abspath(__file__)))

os.system("git submodule update --init --recursive")
os.system("python generate_sln.py")
os.system("python git_copy_hooks.py")

os.chdir(previousWorkingDirectory)
