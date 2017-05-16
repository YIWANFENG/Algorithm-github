#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fstream>
using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))


//定义训练样本结构体 
struct Sample
{
	int number;				//标号 
	int feature;			//特征 
	int label;				//类别 
	float weight; 			//权重 
};


//弱分类器基本信息 
struct BoostNode
{
	int index;            //弱分类器的数目 
	float threshold;      //每个弱分类器对应的阈值
	int p;                //每个弱分类器对应的不等号方向
	float alpha;          //每个弱分类器的权重alpha 
	BoostNode *next;      //下一个节点    	 
}; 
//读取训练样本数据 
void read_Sample(Sample *sam, int n)
{
	fstream file;
	file.open("train.txt", ios::in);
	if (file.fail())	
	{
		cout << "文件不存在" << endl;
		file.close(); 
	}
	else
	{
		int i = 0;
		while (!file.eof())
		{
			file >> sam[i].number;
			file >> sam[i].feature;
			file >> sam[i].label;
			sam[i].weight = (float) (1.0 / n);
			i++; 
		}
		file.close();   //关闭文件 
	}
}
//显示训练样本数据 
void show_Sample(Sample *sam, int n)
{
	cout << "样本详细信息如下：" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << sam[i].number << "\t" ;
		cout << sam[i].feature << "\t" ;
		cout << sam[i].label << "\t" ;
		cout << sam[i].weight << "\t" ;
		cout << endl;
	}
}
//生成G(x)函数，p为确定不等式方向，默认初始值为正负1； 
//依据某一分类器的阈值threshold来将x分类 
int generate_gfunc(float threshold, int x, int p)
{
	if (x * p < threshold * p)
		return 1;
	else
		return -1;	
} 
//计算阈值threshold的取值范围
void generate_threshold(float *threshold, Sample *sam, int n)
{
	for (int i = 0; i < n + 1; i++)
	{
		if (i == 0)
		{
			threshold[i] = (float) (sam[i].feature - 0.5);
		}
		else if (i == n)
		{
			threshold[i] = (float) (sam[i - 1].feature + 0.5);
		}
		else
		{
			threshold[i] = (float) ((sam[i].feature + sam[i - 1].feature) / 2.0);
		}
	}
//	for (int j = 0; j < n + 1; j++)
//	{
//		cout << threshold[j] << " " ;
//	}
} 
//计算每个阈值对应的错误率
void compute_error(Sample *sam, float *threshold, int *p, float *error, int n) 
{
	int result;
	float thred;
	int feature;
	float err;
	for (int i = 0; i < n + 1; i++)    //针对每个阈值，计算错误率   
	{
		err = 0;
		for (int j = 0; j < n; j++)    //计算每个样本的错误率
		{
			thred = threshold[i];
			feature = sam[j].feature;
			result = generate_gfunc(thred, feature, p[i]);
			if (result != sam[j].label)
			{
				err += sam[j].weight;
			}
		}
		if (err > 0.5)
		{	
			error[i] = 1 - err;
			p[i] = -1; //分类器分错几率>0.5时,取其判断结果的相反值 
		}
		else
		{
			error[i] = err;
		}
	}
//	for (int i = 0; i < n + 1; i++)
//	{
//		cout << threshold[i] << "\t" << p[i] << "\t" << error[i] << endl;
//	}
} 
//找出错误率最小的阈值对应的序号 
int find_Min_Error(float *error, int n)
{
	int result;
	float minerr = 1.0; 
	for (int i = 0; i < n + 1; i ++)
	{
		if (error[i] < minerr)
		{
			minerr = error[i];
			result = i;
		}	
	} 
	return result;
}
//计算alpha函数，即该弱分类器在强分类器中的权重 
double comp_Alpha(float error)
{
	const double eps = 1e-5;
	error = MAX(error, eps);
	error = MIN(error, 1.0 - eps);
//	cout << error << endl;
//	cout << log ((1.0 - error) / error) << endl;
	double err = (double) ((1.0 / 2.0) * (log ((1.0 - error) / error)));
	return err;	
} 

//更新权重函数
void update(Sample *sam, int num_min_error_classifier, float *threshold, float *error,
				 float *est, int *p, double alpha, int n)
{
//	cout << "权重为:" << alpha << endl;
	float tmpthred = threshold[num_min_error_classifier];
//	cout<<tmpthred << endl; 
	int tmpp = p[num_min_error_classifier];
//	cout << tmpp << endl;
	float sumZ = 0.0;
	int estimate;
//	cout << error[num_min_error_classifier] << endl;
	for (int i = 0; i < n; i++)
	{ 
		estimate = generate_gfunc(tmpthred, sam[i].feature, tmpp);
//		cout << "评估的label为：" << estimate << endl;
		est[i] += alpha * estimate;
		sam[i].weight = sam[i].weight * exp(-1 * alpha * sam[i].label * estimate); 
		sumZ += sam[i].weight;
	}
	for (int i = 0; i < n; i++)
	{
		sam[i].weight /= sumZ;
	}	
}
//评估是否所有样本均分类正确
int judge_Classify(Sample *sam, float *est, int n)
{
	int label; 
	int count = 0;                    //分错样本的数目 
	for (int i = 0; i < n; i++)
	{
		if (est[i] >= 0 && sam[i].label == -1)
		{ 
			count++;
		}
		else if (est[i] < 0 && sam[i].label == 1)
		{
			count++;
		} 
	}
	return count;
} 

//Adaboost分类器算法 
BoostNode *adaboost(Sample *sam, int n)
{
	int ind = 0;
	//float min_error = 1.0;
	int num_misclassification = n;                //统计分错样本数 
	BoostNode *head = (BoostNode *) malloc (sizeof(BoostNode));     //头指针是一个标志指针，未存入实际的值 
	head->alpha = -1.0;
	head->index = 0;
	head->p = 0;
	head->threshold = 0.0;
	BoostNode *tp = head; 
	BoostNode *tmp; 
	//候选阈值存放位置
	float *threshold = (float *) malloc ((n + 1) * sizeof(float));
	//找所有的阈值 
	generate_threshold(threshold, sam, n);			      
	//每个分类器阈值对应的错误率 
	float *error = (float *) malloc ((n + 1) * sizeof(float)); 		
	int num_min_error_classifier; 	
	double alp;	 
	int *p = (int *) malloc ((n + 1) * sizeof(int));
	float *est = (float *) malloc (n * sizeof(float));    //评估正确率；
	for (int i = 0; i < n; i++)
	{
		est[i] = 0.0;
	} 
	while (ind < 10 && num_misclassification > 0)
	{
		ind++;
		for (int i = 0; i < n + 1; i++)
		{
			p[i] = 1;
		} 
		//计算所有阈值对应的分类器的错误率
		compute_error(sam, threshold, p, error, n);
		//错误率最小对应的阈值标号
		num_min_error_classifier = find_Min_Error(error, n);             
		//计算此次分类器在强分类器中的权重
		alp = comp_Alpha(error[num_min_error_classifier]);
		tmp = (BoostNode *) malloc (sizeof(BoostNode));
		tmp->alpha = alp;
		tmp->threshold = threshold[num_min_error_classifier];
		tmp->index = ind;
		tmp->p = p[num_min_error_classifier];
		tp->next = tmp;
		tp = tp->next;
		update(sam, num_min_error_classifier, threshold, error, est, p, alp, n);
		 //使用sign(符号函数)判断强分类分错的样本数目
		num_misclassification = judge_Classify(sam, est, n); 	  
//		cout << "更新后的样本权重为:" << endl;
//		for (int i = 0; i < n; i++)
//		{
//			cout << sam[i].weight << " ";
//		}
//		cout << endl; 
	}
	tp->next = NULL;
	return head;
} 
//显示强分类器信息 
void show_Classify(BoostNode *head)
{
	BoostNode *tmp;
	tmp = head->next;
	while (tmp != NULL)
	{
		cout << "第" << tmp->index << "个弱分类器信息（阈值，方向，alpha) 如下：" ;
		cout << tmp->threshold << "\t" << tmp->p << "\t" << tmp->alpha << endl;
		tmp = tmp->next;
	}
}

void test_by_classify(BoostNode *head, float x) {
	//其实这里的10个样本完全分类，所以结果一定正确 
	BoostNode *tmp = head->next;
	int lable = -1;
	float odds = 0;
	while(tmp) {
		odds += generate_gfunc(tmp->threshold,x,tmp->p) * tmp->alpha;
		tmp = tmp->next;
	}
	if(odds > 0 ) lable = 1;

	cout<<"样本 "<<x<<" 为 "<<lable;
}
int main()
{
	cout << "请输入样本的数量：" << endl;
	int n;
	cin >> n;
	Sample *sam = (Sample *)malloc(n * sizeof(Sample));
	read_Sample(sam, n);
	show_Sample(sam, n);
	BoostNode *head = adaboost(sam, n);
	show_Classify(head);
	
	float test_sam;
	cout<<"输入测试样本"<<endl;
	cin>>test_sam;
	test_by_classify(head,test_sam);
	
	return 0; 
}

