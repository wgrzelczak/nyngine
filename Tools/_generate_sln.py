import os

FILE = "premake5_solution.lua"
PLATFORM = "windows"
ACTION = "vs2017"
COMPILER = "gcc"

#os.chdir("..")
#print(os.getcwd())
print("Generating solution {}...".format(ACTION))
print(80*'-', "\n")

os.system("premake5.exe {} --file={} --os={} --cc={}".format(ACTION, FILE, PLATFORM, COMPILER))
#os.system("tools\\premake5.exe {} --file=tools\\{} --os={} --cc={}".format(ACTION, FILE, PLATFORM, COMPILER))

print("\n", 80*'-')
print("Solution generated")
os.system("pause")