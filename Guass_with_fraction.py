#!/usr/bin/env python3.5
# -*-coding: utf-8 -*-
"""
Created on 2018-6-9
@author: YWF

高斯消元法求解线性方程，
数字采用分数精确表示，无近似

"""
import numpy as np

def gcd(a,b):
    if a < b:
        c = a
        a = b
        b = c
    while a % b != 0:
        c = a % b
        a = b
        b = c
    return b

def lcm(a,b):
    return a * b / gcd(a,b)


class Fractional:

    def __init__(self,num,den):
        self.numerator = num
        if(den == 0):
            print("Error den")
        self.denominator = den
        pass
    def Simplify(self):
        if self.numerator == 0:
            return Fractional(0,1)
        gcd_ = gcd(self.denominator,self.numerator)
        if gcd_ != 1:
            self.denominator /= gcd_
            self.numerator /= gcd_
        return self
    def __sub__(self, other):
        lcm_ = lcm(self.denominator,other.denominator)
        self.numerator *= lcm_ / self.denominator
        num = self.numerator - other.numerator * lcm_ / other.denominator
        return Fractional(num,lcm_).Simplify()
    def __add__(self, other):
        lcm_ = lcm(self.denominator,other.denominator)
        self.numerator *= lcm_ / self.denominator
        num = self.numerator + other.numerator * lcm_ / other.denominator
        return Fractional(num,lcm_).Simplify()

    def __truediv__(self, other):
        return Fractional(self.numerator*other.denominator,
                          self.denominator*other.numerator).Simplify()

    def __mul__(self, other):
        return Fractional(self.numerator*other.numerator,
                          self.denominator*other.denominator).Simplify()
    def __gt__(self, other):
        item = self - other
        if item.numerator > 0 and item.denominator > 0:
            return True
        return False
    def __lt__(self, other):
        return not self > other

    def __eq__(self, other):
        if self.Simplify().numerator == other.Simplify().numerator:
            return True
        return False
    def __ne__(self, other):
        return not self == other

    def Decimal(self):
        return self.numerator / self.denominator
    def __repr__(self):
        return ("%d/%d = %f"%(self.numerator,self.denominator,self.Decimal()))

def list_is_all_zero(a):
    for x in a:
        if x != Fractional(0,1):
            return False
    return True

def Guass(A,row,num_var):
    '''
            求解 AX = b
    :param A:               增广矩阵(为python中的list)
    :param row:             矩阵行数
    :param num_var:         方程所含变量数
    :return:                status, x_out, x_base
                            status = 0 无解,  1 唯一解, -1 无穷解
                            x_out 为唯一解 or 特解
                            x_base 当无穷解时为基础解析，以及自由变元编号
    '''
    col = num_var + 1
    r = 0
    c = 0
    x_free =[]
    x_out = []
    x_base = []
    status = 0
    ###生成阶梯矩阵
    while c < num_var and r < row:
        #当前列中且行号不小于列号的数的最大的行号
        #为了后续计算时可以简化（即continue）
        Max_r = r
        for max_r_in_c in range(r+1, row):
            if A[max_r_in_c][c] > A[Max_r][c]:
                Max_r = max_r_in_c
        A[r], A[Max_r] = A[Max_r], A[r]
        if A[r][c] == Fractional(0, 1):
            x_free.append(c) #回收自由变元
            c += 1
            continue
        div = A[r][c]
        for c_cur in range(c, col):
            A[r][c_cur] = A[r][c_cur] / div
        for r_cur in range(r+1, row):
            if A[r_cur][c] == Fractional(0, 1):
                continue
            div = A[r_cur][c] / A[r][c]
            for c_cur in range(c, col):
                A[r_cur][c_cur] = A[r_cur][c_cur] - div * A[r][c_cur]
        c += 1
        r += 1
    pass
    # 回收自由变元 (当方程数不足,自由变元较多时)
    for x in range(c,num_var):
       x_free.append(x)
    #print("check",x_free)
    #show(A)
    # 查看有效方程数
    row_valid = 0
    for x in A:
        if not list_is_all_zero(x):
            row_valid += 1
    #print("有效的方程数", row_valid)
    ### 检查解的个数
    # 无解
    for r_cur in A[0:row_valid]:
        if r_cur[col-1] != Fractional(0,1) and list_is_all_zero(r_cur[0:col-1]):
            status = 0
            return status,x_out,x_base
    ####有解时生成最简矩阵(可选)
    row_staris = row_valid - 1                               #最低（当前处理）阶梯所在行
    for c_cur in range(col-2, -1, -1):                      #从最后一列开始消除
        if c_cur not in x_free and row_staris != 0:
            for r_cur in range(row_staris-1, -1, -1):       #从下向上每行依次减
                div = A[r_cur][c_cur] / A[row_staris][c_cur]
                for x in range(c_cur, col):                 #处理该行
                    A[r_cur][x] -= A[row_staris][x] * div
                pass
            row_staris -= 1
        pass
    ### 唯一解
    if row_valid == num_var:
        for r in range(0, row):
            x_out.append(A[r][col-1])
        status = 1
        return status,x_out,x_base
    ### 无穷解
    b = []
    for xx in range(row_valid):
        b.append(A[xx][col-1])
    x_out = [Fractional(0,1) for i in range(num_var)]
    #获得基础解析x_base与特解x_out
    for x in x_free:                #针对每个自由变元
        item = [Fractional(0,1) for i in range(num_var)]
        item[x] = Fractional(1,1)
        cnt = 0
        for xx in range(num_var):
            if xx not in x_free:
                item[xx] = b[cnt] - A[cnt][x]
                x_out[xx] = b[cnt]
                cnt += 1
        x_base.append(item)
    x_base.append(["自由变元编号"] + x_free)
    status = -1
    return status, x_out, x_base


def show(A):
    for i in range(0,len(A)):
        print(A[i])
    print("\n")

if __name__ == '__main__':
    # Test
    f = Fractional
    A = [[f(1,1),f(2,1),f(3,1),f(4,1)],
         [f(1,2),f(2,2),f(3,2),f(4,2)],
         [f(4,2),f(3,3),f(1,3),f(3,2)]
    ]
    B = [[f(1,1),f(2,1),f(3,1),f(4,1)],
         [f(0,1),f(0,1),f(2,1),f(4,1)],
         [f(0,1),f(0,1),f(2,1),f(4,1)]
    ]
    C = [[f(1,1),f(2,1),f(3,1),f(1,2),f(4,1)],
         [f(0,1),f(0,1),f(2,1),f(1,2),f(4,1)],
    ]
    D = [[f(1,1),f(2,1),f(0,1),f(4,1),f(3,1)],
        [f(0,1),f(0,1),f(1,1),f(2,1),f(2,1)],
    ]
    x = []
    x_base = []
    #show(C)
    #status,x_out,x_base = Guass(C,2,4)
    #show(B)
    #status,x_out,x_base = Guass(B,3,3)
    #show(A)
    #status,x_out,x_base = Guass(A,3,3)
    show(D)
    status,x_out,x_base = Guass(D,2,4)
    print(status)
    print(x_base)
    print(x_out)


