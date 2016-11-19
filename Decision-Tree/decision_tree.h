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

	inline void SetTrainingSetFilePath(const std::string &filepath) throw(); //����ѵ�������ļ�·��
	std::vector<training_data> GetTrainingSetFromFile(const std::string filename) const throw(); // �ӱ����ļ��ж�ȡѵ����
	bool FeedWithTrainingSet() throw(); // ����ѵ����
	bool SaveTreeToFile(const std::string &filename) const throw(); // ����������ṹ�Ͳ���������
	bool LoadTreeFromFile(const std::string &filename) throw(); // �ӱ��ض�ȡ�������ṹ�Ͳ���

private:

	explicit CART(const CART &cart_tree);
	CART &operator =(const CART &cart_tree);
	
	int GetMaxLabel(const std::vector<training_data> &training_set) const throw(std::logic_error); // ��ȡѵ�������������������
	bool isSameAttr(const std::vector<training_data> &training_set) const throw(); // �ж����������Լ����Ƿ�ȡֵһ��
	bool isSameLabel(const std::vector<training_data> &training_set) const throw(); // �ж�ѵ����������ǩ�Ƿ�һ��
	bool isAttrEmpty(const std::vector<int> &attr) const throw(); // �ж����Լ��Ƿ�Ϊ��
	float Gini(const std::vector<training_data> &training_set) const throw();// �����ֵ
	float GetGini_Index(const std::vector<training_data> &training_set,const int &attr_type) const throw(std::logic_error); // �����ָ��
	int GetPatitionAttr(const std::vector<training_data> &training_set,const std::vector<int> &attr_set) const throw(std::logic_error); // ����ѻ��ֲ���
	dt_tree TreeGenerate(const std::vector<training_data> &training_set,std::vector<int> &attr_set) throw(); // ���ɾ��������
	void DeleteNode(dt_tree node) throw(); // ɾ���ڵ�

};

#endif // DECISION_TREE_H