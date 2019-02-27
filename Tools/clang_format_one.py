import os
from os import path

def clang_format(filePath):
    extensions = [".cpp", ".hpp", ".c", ".h", ".inl"]
    if any(filePath.endswith(ext) for ext in extensions):
        cmd = "clang-format -style=file -i {}".format(filePath)
        print(cmd)
        os.system(cmd)
        return True
    return False


if __name__=="__main__":
    print("Error, file path not defined")
    print("Use clang_format(filePath)");
