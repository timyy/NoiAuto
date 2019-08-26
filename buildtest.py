#!/usr/bin/python
# -*- coding: utf-8 -*-
# 
## License: Apache 2.0. See LICENSE file in root directory.
## Copyright(c) 2019 Timyy Corporation. All Rights Reserved.

#####################################################
##              Noi auto check                     ##
#####################################################

## version 0.1
## 自动检查各目录下的所有CPP文件，如果存在同文件名的_data目录，自动进行编译。
#  并执行_data所有.in文件，结果和.out对比。 一样则通过，不同出错。
## 
## 适用于单文件，用在NOI下应该够了
##
import os
import subprocess

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
    # 构建命令行，文件名可能是长文件名，所以需要用"括起来。
    cmd = makecmd + ' "' + cppfile + '" -o ' + '"' + exefile + '"'

    if os.path.exists(inDir):
    # 有inDir才做
        cppfile_mtime = os.stat(cppfile).st_mtime
        exefile_mtime = 0
        if os.path.exists(exefile):
            # 如果exe文件存在，并新于cpp，就不做检查了，文件多了，能省时间。
            exefile_mtime = os.stat(exefile).st_mtime
            if exefile_mtime > cppfile_mtime:
                pass
            else:
                # exe文件旧于cpp，则编译。
                os.system(cmd)
        else:
            # 没有exe文件，则编译。
            os.system(cmd)  # 执行编译命令

        if os.path.exists(exefile) and exefile_mtime < cppfile_mtime:
        # 编译成功，或者以前的exe是旧的。
            print("Checking ... " + exefile)
            allfiles = os.listdir(inDir)
            for dirpath,dirnames,filenames in os.walk(inDir):
                for name in filenames:
                    # 需要加入大小写判断 BUG：20190727
                    if name.lower().endswith(".in"):
                        (shortName2,extension) = os.path.splitext(name);
                        infile = os.path.join(dirpath,name)
                        outfile = os.path.join(dirpath, shortName2 + ".out")

                        #BUG: 组合字串的长文件名必须用"括起来。
                        main = '"' + exefile + '"' + ' < "' + infile + '"'
                        #BUG 设置path环境变量，以便程序能正确运行。
                        new_env = os.environ.copy()
                        new_env['PATH'] = 'C:/MinGW/bin/;%PATH%'

                        #out= subprocess.Popen(main, env=new_env)
                        #stdout,stderr = out.communicate()
                        #outvalue = stdout
                        out= os.popen(main)
                        outvalue = out.read()
                        with open(outfile,'r') as f:
                            outRight = f.read()
                            if outvalue == outRight:
                                OKNum += 1
                                #print("OK")
                            else:
                                ErrorNum += 1
                                print("\033[1;31m[Error]:\033[0m")
                                print("\t\t", main)
                                print("\033[1;33m\tOUT:\n\033[0m",outvalue)
                                print("\033[1;32m\tTrueOut:\n\033[0m",outRight)
                                with open(outfile+".tmp","w") as fout:
                                    fout.write(outvalue)

if __name__ == '__main__':    
    OKNum = 0
    ErrorNum = 0
    currentPath = os.getcwd()
    for dirpath,dirnames,filenames in os.walk(currentPath):
        for name in filenames:
            if name.endswith(".cpp"):
                (shortName,extension) = os.path.splitext(name);
                makefile(dirpath,shortName)
    print()
    print('\033[5;33;44m',"="*48,'\033[0m')
    print(" \033[5;37;42m=\t\tTotal Passed:\t",OKNum,'\033[0m\t\t=')
    if ErrorNum:
        print(" \033[5;37;41m=\t\tTotal Error:\t",ErrorNum ,"\033[0m\t\t=")
    else:
        print(' \033[5;37;42m=\t\tAll OK!\033[0m\t\t\t=')
    print('\033[5;33;44m',"="*48,'\033[0m')
#    cppfile = "D:/Timyy/project/noi/pythonAuto/src/T1398.cpp"
#    exefile = "D:/Timyy/project/noi/pythonAuto/src/T1398.exe"


