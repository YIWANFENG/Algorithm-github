import numpy  as np 
from sklearn.decomposition import PCA as SKPCA


def PCA(X,dim):
    '''
    对X PCA分解，降到dim空间中，并输出降维结果
    params:
        X第一维是数据编号，第二维为每个数据各分量
        如 
        X = np.array([  [-1,-1,0,2,1],
                        [2,0,0,-1,-1],
                        [2,0,1,1,0]] )
        dim为指定的低维空间维数
    return 
        X_low =  [  [ 2.6838453  -0.36098161]
                    [-2.09303664 -0.78689112]
                    [-0.59080867  1.14787272]]
    '''
    #data_size = X.shape[0]    #向量数量
    #data_channel = X.shape[1] #降维前 向量的维度

    ## 1.特征标准化 {  X = X - X_mean ) }
    X_col_mean = np.mean(X,axis=0)
    X_std = X - X_col_mean

    ## 2.计算协方差矩阵cc  {  1/m * sum{ (x^i)(x^i)^T } = np.cov(X_std,rowvar=0)   }
    cc = np.cov(X_std,rowvar=0) # == np.dot(X_std.T,X_std) / (data_size - 1)

    ## 3.计算cc的特征值与特征向量, vec一列为一特征向量
    val ,vec = np.linalg.eigh(np.mat(cc))

    ## 4.抽取前 dim 大的特征向量组成变换矩阵
    val_ind = np.argsort(val)
    val_ind_select = val_ind[-1:-(dim+1):-1]
    vec_trans = vec[:,val_ind_select] #一列为一特征向量

    ## 5.变换 vec_trans * X
    X_low = np.dot(X_std,vec_trans)

    ## 6.重建 X ,此项默认不开启
    #X_recon = X_low * vec_trans.T + X_col_mean 
    return X_low



# 辅助函数
def check_precentage_to_n(val,precent):
    '''
    依据保留信息百分比参数precent计算PCA应该保留的维度n
    params:
        val 特征值
        precent 保留百分比
    return:
        n 应该保留的维度
    '''
    sortArr = np.sort(val) 
    sortArr = sortArr[-1::-1]
    ArrSum = np.sum(sortArr)
    tmp = 0
    n = 0
    for x in sortArr:
        tmp += x
        n += 1
        if tmp >= ArrSum * precent:
            return n 


if __name__ == "__main__":
    X = np.array([  [-1,-1,0,2,1],
                    [2,0,0,-1,-1],
                    [2,0,1,1,0]] )
    X_ = PCA(X,2)
    print("自定义PCA\n",X_)

    # PCA by Scikit-learn
    pca = SKPCA(n_components=2)
    pca.fit(X) #输入数据
    print('PCA Scikit-learn')
    print(pca.fit_transform(X))

