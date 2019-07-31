#!/usr/bin/python
# -*- coding: utf-8 -*-
# 
## License: Apache 2.0. See LICENSE file in root directory.
## Copyright(c) 2019 Timyy Corporation. All Rights Reserved.

#####################################################
##              Draw short path graph              ##
#####################################################

## version 0.1

import numpy as np 
import matplotlib.pyplot as plt

gDebug = True
filename= r'D:\Timyy\project\noi\NoiAuto\src\信息学奥赛一本通\2. 数据结构\第4章 图论算法\3.最短路径\例4-1 最短路径问题short\short_data\short2.in'
with open(filename,'r') as f:
    nString = f.readline()
    n= int(nString)
    if gDebug:
        print(n)
    points = []
    for i in range(n):
        line = f.readline()
        linestr = line.split(" ");
        points.append([int(linestr[0]), int(linestr[1])])
     
    for point in points:
        if gDebug:
            print(point[0],point[1])
    nString = f.readline()
    m= int(nString)
    if gDebug:
        print(m)
    links = []
    for i in range(m):
        line = f.readline()
        linestr = line.split(" ")
        links.append([int(linestr[0])-1, int(linestr[1])-1])
    line = f.readline()
    linestr = line.split(" ")
    s = int(linestr[0])-1
    t = int(linestr[1])-1

plt.axis([-1,4,-1,4])
#plt.set_ylabel("v",fontsize=14)
#plt.set_xlabel("t",fontsize=14)
#p2.legend()
#tx = 2
#ty = 0.9
#plt.text(tx,ty,1,fontsize=15,verticalalignment="bottom",horizontalalignment="left")
#plt.annotate('3',xy=(1.8,0.5),xytext=(tx,ty),arrowprops=dict(arrowstyle="->",connectionstyle="arc3"))

x = [[1, 3], [2, 5]]
y = [[4, 7], [6, 3]]
 

for i in range(len(points)): 
#  plt.plot(x[i], y[i], color='r')
    # ax = plt.axes()
    # ax.arrow(x[i][0],y[i][0], x[i][1]-x[i][0],y[i][1]-y[i][0], head_width=0.2, head_length=0.5, fc='r', ec='r',length_includes_head = True)
    # plt.scatter(x[i], y[i], color='b')
    plt.scatter(points[i][0], points[i][1], color='', marker='o', edgecolors='y', s=200)
    plt.text(points[i][0],points[i][1],i,fontsize=12,verticalalignment="center",horizontalalignment="center")
    
  # 把 corlor 设置为空，通过edgecolors来控制颜色
# 画开始和结束点
plt.scatter(points[s][0], points[s][1], color='', marker='s', edgecolors='g', s=300)
plt.scatter(points[t][0], points[t][1], color='', marker='p', edgecolors='r', s=300)

print(80*'-')
for i in range(len(links)): 
#  plt.plot(x[i], y[i], color='r')
    ax = plt.axes()
    print(i, points[links[i][0]][0])
    ax.arrow(points[links[i][0]][0],points[links[i][0]][1], points[links[i][1]][0]-points[links[i][0]][0],points[links[i][1]][1]-points[links[i][0]][1], 
             head_width=0.2, head_length=0.5, fc='r', ec='b',length_includes_head = True)
    # plt.scatter(x[i], y[i], color='b')
    # plt.scatter(points[i][0], points[i][1], color='', marker='o', edgecolors='g', s=200)
    # plt.text(points[i][0],points[i][1],i,fontsize=15,verticalalignment="center",horizontalalignment="center")

plt.show()