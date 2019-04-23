import os
from os import path

def clang_format(filePath):
    previousWorkingDirectory = os.getcwd()    
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    extensions = [".cpp", ".hpp", ".c", ".h", ".inl"]

    ret = False
    if any(filePath.endswith(ext) for ext in extensions):
        cmd = "clang-format -style=file -i {}".format(filePath)
        print(cmd)
        os.system(cmd)
        ret = True

    os.chdir(previousWorkingDirectory )
    return ret


if __name__=="__main__":
    print("Error, file path not defined")
    print("Use clang_format(filePath)");
