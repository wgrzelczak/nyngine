import os
os.chdir("..")

print("Cleaning solution...")
print(80*'-', "\n")

os.system("tools\\premake5.exe clean")

print("\n", 80*'-')
print("Solution cleaned")
#os.system("pause")