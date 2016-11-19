#ifndef DECISION_TREE_H
#define DECISION_TREE_H

#include <vector>
#include "training_data.h"
#include "TrainingSetLoader.h"

class CART final
{

public:
	
	struct dt_node {
		int attr_type;
		std::vector<struct dt_node *> child;
		bool isleaf;
		int label;
	};

	typedef struct dt_node dt_node,*dt_tree;

	dt_tree Root;
	bool trained;
	std::vector<std::string> attr;
	DataLoader *dataloder;
	std::string TrainingSetPath;

	CART() = default; 
	~CART() = delete; 

	inline void SetTrainingSetFilePath(const std::string &filepath) throw(); //设置训练样本文件路径
	std::vector<training_data> GetTrainingSetFromFile(const std::string filename) const throw(); // 从本地文件中读取训练集
	bool FeedWithTrainingSet() throw(); // 输入训练集
	bool SaveTreeToFile(const std::string &filename) const throw(); // 保存决策树结构和参数至本地
	bool LoadTreeFromFile(const std::string &filename) throw(); // 从本地读取决策树结构和参数

private:

	explicit CART(const CART &cart_tree);
	CART &operator =(const CART &cart_tree);
	
	int GetMaxLabel(const std::vector<training_data> &training_set) const throw(std::logic_error); // 获取训练集中样本数最多的类别
	bool isSameAttr(const std::vector<training_data> &training_set) const throw(); // 判断样本在属性集上是否取值一致
	bool isSameLabel(const std::vector<training_data> &training_set) const throw(); // 判断训练集中类别标签是否一致
	bool isAttrEmpty(const std::vector<int> &attr) const throw(); // 判断属性集是否为空
	float Gini(const std::vector<training_data> &training_set) const throw();// 求基尼值
	float GetGini_Index(const std::vector<training_data> &training_set,const int &attr_type) const throw(std::logic_error); // 求基尼指数
	int GetPatitionAttr(const std::vector<training_data> &training_set,const std::vector<int> &attr_set) const throw(std::logic_error); // 求最佳划分参数
	dt_tree TreeGenerate(const std::vector<training_data> &training_set,std::vector<int> &attr_set) throw(); // 生成决策树结点
	void DeleteNode(dt_tree node) throw(); // 删除节点

};

#endif // DECISION_TREE_H