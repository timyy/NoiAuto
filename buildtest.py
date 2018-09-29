#!/usr/bin/python
# -*- coding: utf-8 -*-

import os

global OKNum,ErrorNum

makecmd  = "C:/MinGW/bin/g++.exe" #如果更通用一些的话，可以不带目录，在系统环境中设好目录。

class make2test:
    def __init__(self, *args, **kwargs):
        return super().__init__(*args, **kwargs)
    def make(self):
        rc,out= subprocess.getstatusoutput(main)

def makefile(path, shortName):
    global OKNum,ErrorNum
    cppfile = os.path.join(path, shortName + ".cpp")
    exefile = os.path.join(path, shortName + ".exe")
    inDir = os.path.join(path, shortName + "_data")
    cmd = makecmd + " " + cppfile + " -o " + exefile
    os.system(cmd)  # 执行编译命令


    if os.path.exists(exefile) and os.path.exists(inDir):
        allfiles = os.listdir(inDir)
        for dirpath,dirnames,filenames in os.walk(inDir):
            for name in filenames:
                if name.endswith(".in"):
                    (shortName2,extension) = os.path.splitext(name);
                    infile = os.path.join(dirpath,name)
                    outfile = os.path.join(dirpath, shortName2 + ".out")
                    main = exefile + " < " + infile
                    out= os.popen(main)
                    outvalue = out.read()
                    with open(outfile,'r') as f:
                        outRight = f.read()
                        if outvalue == outRight:
                            OKNum += 1
                            #print("OK")
                        else:
                            ErrorNum += 1
                            print("Error:",cppfile,infile)
                            print("OUT:\n",outvalue)
                            print("TrueOut:\n",outRight)
                            with open(outfile+".tmp","w") as fout:
                                fout.write(outvalue)

if __name__ == '__main__':
    global OKNum,ErrorNum
    OKNum = 0
    ErrorNum = 0
    currentPath = os.getcwd()
    for dirpath,dirnames,filenames in os.walk(currentPath):
        for name in filenames:
            if name.endswith(".cpp"):
                (shortName,extension) = os.path.splitext(name);
                makefile(dirpath,shortName)
    print("="*40)
    print("Total Passed:",OKNum)
    print("Total Error:",ErrorNum)
#    cppfile = "D:/Timyy/project/noi/pythonAuto/src/T1398.cpp"
#    exefile = "D:/Timyy/project/noi/pythonAuto/src/T1398.exe"


