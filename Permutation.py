# -*- coding: utf-8 -*-
"""
Created on Sat Jul 30 07:32:34 2016

@author: yiwan
"""

def Permutation(list, end):
    result = []
    re = []
    #print("list", list)
    if 0 == end:
        re.append(list)
    else:
        for i in list:

            list_tmp = list[:]
            list_tmp.remove(i)
            #print("list_tmp", list_tmp)
            for x in (Permutation(list_tmp, end-1)):
                result = []
                result.append(i)
                result.extend(x)
                #print("result", result)
                re.append(result)
    #print("re", re)
    return re
    pass

def main():
    list = [1,2,3]
    for x in (Permutation(list, 2)):
        print(x)
    pass


if __name__ == '__main__':
    main()
    input("Enter any key to exit")
