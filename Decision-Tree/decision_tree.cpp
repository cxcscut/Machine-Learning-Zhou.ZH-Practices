#include "decision_tree.h"
#include "ML_exception.h"
#include <iostream>

using namespace std;

CART::CART() :
	Root(nullptr),
	trained(false)
{
	CART::dataloder = new DataLoader;
}

CART::~CART()
{
	CART::DeleteNode(Root);

	if (!dataloder)
		delete dataloder;
}

void CART::DeleteNode(CART::dt_tree node) throw()
{
	if (!node) return;
	if (node->child.size() <= 0) { delete node; return; }

	typename vector<struct dt_node*>::const_iterator piter;

	for (piter = node->child.begin(); piter != node->child.end(); piter++)
		if (*piter != nullptr)
			CART::DeleteNode(*piter);

	delete node;
}

float CART::Gini(const vector<training_data> &training_set) const throw()
{
	float sum = 0.0f;
	int d = training_set.size();
	int dv = 0;
	vector<float> pk;

	for (int i = 0; i < NUM_OF_LABEL; i++) // 计算pk
	{
		typename vector<training_data>::const_iterator piter;
		float pk_temp = 0.0f;

		for (piter = training_set.begin(); piter != training_set.end(); piter++)
		{
			if (piter->label == label(i))
				dv++;
		}

		pk_temp = dv / d;
		pk.push_back(pk_temp);
		dv = 0;
	}

	for (int k = 0; k < NUM_OF_LABEL; k++) // 计算基尼值
		sum = sum + pk[k] * pk[k];

	return 1 - sum;
}

float CART::GetGini_Index(const vector<training_data> &training_set, const int &attr_type) const throw(logic_error)
{
	if (CART::attr.empty()) {
		throw MLexception("attibutes has not been preprocessed");
	}
	float ret = 0.0f;
	int dv = 0;
	int d = training_set.size();
	int v = 0;

	typename vector<training_data>::const_iterator piter;
	vector<training_data> Dv;

	switch (attr_type)
	{
	case color:
		v = NUM_OF_COLOR;
		for (int i = 0; i < v; i++)
		{
			for (piter = training_set.begin(); piter != training_set.end(); piter++)
			{
				if (piter->data_attr.color == i)
				{
					dv++;
					Dv.push_back(*piter);
				}
			}
			ret = ret + (dv / d) * CART::Gini(Dv);
			Dv.clear();
			dv = 0;
		}
		break;
	case root:
		v = NUM_OF_ROOT;
		for (int i = 0; i < v; i++)
		{
			for (piter = training_set.begin(); piter != training_set.end(); piter++)
			{
				if (piter->data_attr.root == i)
				{
					dv++;
					Dv.push_back(*piter);
				}
			}
			ret = ret + (dv / d) * CART::Gini(Dv);
			Dv.clear();
			dv = 0;
		}
		break;
	case sound:
		v = NUM_OF_SOUND;
		for (int i = 0; i < v; i++)
		{
			for (piter = training_set.begin(); piter != training_set.end(); piter++)
			{
				if (piter->data_attr.sound == i)
				{
					dv++;
					Dv.push_back(*piter);
				}
			}
			ret = ret + (dv / d) * CART::Gini(Dv);
			Dv.clear();
			dv = 0;
		}
		break;
	case texture:
		v = NUM_OF_TEXTURE;
		for (int i = 0; i < v; i++)
		{
			for (piter = training_set.begin(); piter != training_set.end(); piter++)
			{
				if (piter->data_attr.texture == i)
				{
					dv++;
					Dv.push_back(*piter);
				}
			}
			ret = ret + (dv / d) * CART::Gini(Dv);
			Dv.clear();
			dv = 0;
		}
		break;
	case navel:
		v = NUM_OF_NAVEL;
		for (int i = 0; i < v; i++)
		{
			for (piter = training_set.begin(); piter != training_set.end(); piter++)
			{
				if (piter->data_attr.navel == i)
				{
					dv++;
					Dv.push_back(*piter);
				}
			}
			ret = ret + (dv / d) * CART::Gini(Dv);
			Dv.clear();
			dv = 0;
		}
		break;
	case touch:
		v = NUM_OF_TOUCH;
		for (int i = 0; i < v; i++)
		{
			for (piter = training_set.begin(); piter != training_set.end(); piter++)
			{
				if (piter->data_attr.touch == i)
				{
					dv++;
					Dv.push_back(*piter);
				}
			}
			ret = ret + (dv / d) * CART::Gini(Dv);
			Dv.clear();
			dv = 0;
		}
		break;
	default:
		break;
	}

	return ret;
}

int CART::GetPatitionAttr(const std::vector<training_data> &training_set,const vector<int> &attr_set) const throw(logic_error)
{
	int min_index = 0;
	if (attr_set.empty()) {
		throw MLexception("attributes set is empty");
	}
	vector<float> Gini_index;
	typename vector<int>::const_iterator piter;

	for (piter = attr_set.begin(); piter != attr_set.end(); piter++)
	{
		Gini_index.push_back(GetGini_Index(training_set,*piter));
	}

	for (int i = 0; i < Gini_index.size(); i++)
	{
		if (Gini_index[i] < Gini_index[min_index])
			min_index = i;
	}

	return min_index;
}

bool CART::isSameLabel(const vector<training_data> &training_set) const throw()
{
	if (training_set.size() <= 0) return false;
	const int data_label = training_set[0].label;
	typename vector<training_data>::const_iterator piter;

	for (piter = training_set.begin(); piter != training_set.end(); piter++)
		if (piter->label != data_label)
			return false;

	return true;
}

bool CART::isAttrEmpty(const vector<int> &attr) const throw()
{
	if (attr.size() <= 0)
		return true;
	else
		return false;
}

bool CART::isSameAttr(const vector<training_data> &training_set) const throw()
{
	if (training_set.size() <= 0) return false;
	typename vector<training_data>::const_iterator piter;
	const attributes data_attr = training_set[0].data_attr;

	for (piter = training_set.begin(); piter != training_set.end(); piter++)
	{
		if (!(piter->data_attr == data_attr))
			return false;
	}

	return true;
}

int CART::GetMaxLabel(const vector<training_data> &training_set) const throw(logic_error)
{
	if (training_set.empty()) {
		throw MLexception("training_set is empty");
	}

	int max_index = 0;
	vector<int> label_num(NUM_OF_LABEL,0);
	typename vector<training_data>::const_iterator piter;

	for (piter = training_set.begin(); piter != training_set.end(); piter++)
		label_num[piter->label]++;

	for (int i = 0; i < NUM_OF_LABEL; i++)
		if (label_num[i] > label_num[max_index])
			max_index = i;

	return max_index;
}

CART::dt_tree CART::TreeGenerate(const vector<training_data> &training_set,vector<int> &attr_set) throw()
{
	CART::dt_tree node_new = new CART::dt_node;
	int optimal_attr;

	if (CART::isSameLabel(training_set)) // 训练集中所有样本属于同一个类别
	{
		node_new->isleaf = true; // 标记为叶结点
		node_new->label = training_set[0].label; // 将该叶结点标记为该标签
	}

	if (attr_set.size() <= 0 || CART::isSameAttr(training_set)) // 如果属性集为空集或者训练集在该属性集上的取值均相同
	{
		node_new->isleaf = true; // 标记为叶结点
		try {
			node_new->label = CART::GetMaxLabel(training_set);
		}
		catch (MLexception &e)
		{
			cout << e.what << endl;
			std::abort();
		}
	}
	
	try {
		optimal_attr = CART::GetPatitionAttr(training_set, attr_set);
	}
	catch(MLexception &e){
		cout << e.what << endl;
		std::abort;
	}

	int v;

	switch (optimal_attr)
	{
	case color:
		v = NUM_OF_COLOR;
		node_new->isleaf = false;
		node_new->attr_type = optimal_attr;

		for (int k = 0; k < v; k++)
		{
			vector<training_data> Dv;
			CART::dt_tree node_branch;
			typename vector<training_data>::const_iterator piter;

			for (piter = training_set.begin(); piter != training_set.end(); piter++) // 得到D中在划分属性上取值为av的样本子集
				if (piter->data_attr.color == k)
					Dv.push_back(*piter);

			if (Dv.size() <= 0) // 如果Dv为空
			{
				node_branch = new dt_node;
				node_branch->isleaf = true;
				node_branch->label = CART::GetMaxLabel(training_set); // 将分支结点标记为训练集中最多的类
			}
			else
			{
				typename vector<int>::iterator _piter;

				for (_piter = attr_set.begin(); _piter != attr_set.end(); _piter++) // 属性集中删除划分属性
				{
					if (*_piter == optimal_attr) {
						attr_set.erase(_piter); 
						_piter = attr_set.begin(); // 防止erase之后_piter变为野指针
					}
				}

				node_branch = CART::TreeGenerate(Dv,attr_set);
			}

			node_new->child.push_back(node_branch);
		}
		break;
	case root:
		v = NUM_OF_ROOT;
		node_new->isleaf = false;
		node_new->attr_type = optimal_attr;

		for (int k = 0; k < v; k++)
		{
			vector<training_data> Dv;
			CART::dt_tree node_branch;
			typename vector<training_data>::const_iterator piter;

			for (piter = training_set.begin(); piter != training_set.end(); piter++) // 得到D中在划分属性上取值为av的样本子集
				if (piter->data_attr.root == k)
					Dv.push_back(*piter);

			if (Dv.size() <= 0) // 如果Dv为空
			{
				node_branch = new dt_node;
				node_branch->isleaf = true;
				node_branch->label = CART::GetMaxLabel(training_set); // 将分支结点标记为训练集中最多的类
			}
			else
			{
				typename vector<int>::iterator _piter;

				for (_piter = attr_set.begin(); _piter != attr_set.end(); _piter++) // 属性集中删除划分属性
				{
					if (*_piter == optimal_attr) {
						attr_set.erase(_piter);
						_piter = attr_set.begin(); // 防止erase之后_piter变为野指针
					}
				}

				node_branch = CART::TreeGenerate(Dv, attr_set);
			}

			node_new->child.push_back(node_branch);
		}
		break;
	case sound:
		v = NUM_OF_SOUND;
		node_new->isleaf = false;
		node_new->attr_type = optimal_attr;

		for (int k = 0; k < v; k++)
		{
			vector<training_data> Dv;
			CART::dt_tree node_branch;
			typename vector<training_data>::const_iterator piter;

			for (piter = training_set.begin(); piter != training_set.end(); piter++) // 得到D中在划分属性上取值为av的样本子集
				if (piter->data_attr.sound == k)
					Dv.push_back(*piter);

			if (Dv.size() <= 0) // 如果Dv为空
			{
				node_branch = new dt_node;
				node_branch->isleaf = true;
				node_branch->label = CART::GetMaxLabel(training_set); // 将分支结点标记为训练集中最多的类
			}
			else
			{
				typename vector<int>::iterator _piter;

				for (_piter = attr_set.begin(); _piter != attr_set.end(); _piter++) // 属性集中删除划分属性
				{
					if (*_piter == optimal_attr) {
						attr_set.erase(_piter);
						_piter = attr_set.begin(); // 防止erase之后_piter变为野指针
					}
				}

				node_branch = CART::TreeGenerate(Dv, attr_set);
			}

			node_new->child.push_back(node_branch);
		}
		break;
	case texture:
		v = NUM_OF_TEXTURE;
		node_new->isleaf = false;
		node_new->attr_type = optimal_attr;

		for (int k = 0; k < v; k++)
		{
			vector<training_data> Dv;
			CART::dt_tree node_branch;
			typename vector<training_data>::const_iterator piter;

			for (piter = training_set.begin(); piter != training_set.end(); piter++) // 得到D中在划分属性上取值为av的样本子集
				if (piter->data_attr.texture == k)
					Dv.push_back(*piter);

			if (Dv.size() <= 0) // 如果Dv为空
			{
				node_branch = new dt_node;
				node_branch->isleaf = true;
				node_branch->label = CART::GetMaxLabel(training_set); // 将分支结点标记为训练集中最多的类
			}
			else
			{
				typename vector<int>::iterator _piter;

				for (_piter = attr_set.begin(); _piter != attr_set.end(); _piter++) // 属性集中删除划分属性
				{
					if (*_piter == optimal_attr) {
						attr_set.erase(_piter);
						_piter = attr_set.begin(); // 防止erase之后_piter变为野指针
					}
				}

				node_branch = CART::TreeGenerate(Dv, attr_set);
			}

			node_new->child.push_back(node_branch);
		}
		break;
	case navel:
		v = NUM_OF_NAVEL;
		node_new->isleaf = false;
		node_new->attr_type = optimal_attr;

		for (int k = 0; k < v; k++)
		{
			vector<training_data> Dv;
			CART::dt_tree node_branch;
			typename vector<training_data>::const_iterator piter;

			for (piter = training_set.begin(); piter != training_set.end(); piter++) // 得到D中在划分属性上取值为av的样本子集
				if (piter->data_attr.navel == k)
					Dv.push_back(*piter);

			if (Dv.size() <= 0) // 如果Dv为空
			{
				node_branch = new dt_node;
				node_branch->isleaf = true;
				node_branch->label = CART::GetMaxLabel(training_set); // 将分支结点标记为训练集中最多的类
			}
			else
			{
				typename vector<int>::iterator _piter;

				for (_piter = attr_set.begin(); _piter != attr_set.end(); _piter++) // 属性集中删除划分属性
				{
					if (*_piter == optimal_attr) {
						attr_set.erase(_piter);
						_piter = attr_set.begin(); // 防止erase之后_piter变为野指针
					}
				}

				node_branch = CART::TreeGenerate(Dv, attr_set);
			}

			node_new->child.push_back(node_branch);
		}
		break;
	case touch:
		v = NUM_OF_TOUCH;
		node_new->isleaf = false;
		node_new->attr_type = optimal_attr;

		for (int k = 0; k < v; k++)
		{
			vector<training_data> Dv;
			CART::dt_tree node_branch;
			typename vector<training_data>::const_iterator piter;

			for (piter = training_set.begin(); piter != training_set.end(); piter++) // 得到D中在划分属性上取值为av的样本子集
				if (piter->data_attr.touch == k)
					Dv.push_back(*piter);

			if (Dv.empty()) // 如果Dv为空
			{
				node_branch = new dt_node;
				node_branch->isleaf = true;
				node_branch->label = CART::GetMaxLabel(training_set); // 将分支结点标记为训练集中最多的类
			}
			else
			{
				typename vector<int>::iterator _piter;

				for (_piter = attr_set.begin(); _piter != attr_set.end(); _piter++) // 属性集中删除划分属性
				{
					if (*_piter == optimal_attr) {
						attr_set.erase(_piter);
						_piter = attr_set.begin(); // 防止erase之后_piter变为野指针
					}
				}

				node_branch = CART::TreeGenerate(Dv, attr_set);
			}

			node_new->child.push_back(node_branch);
		}
		break;
	default:
		break;
	}
}

bool CART::FeedWithTrainingSet() throw()
{
	vector<int> attr{ color,root,sound,texture,navel,touch };
	vector<training_data> training_set;

	if (CART::TrainingSetPath.empty())
		return false;

	training_set = CART::GetTrainingSetFromFile(CART::TrainingSetPath);

	CART::Root = CART::TreeGenerate(training_set,attr);

	CART::trained = true;
	return true;
}

vector<training_data> CART::GetTrainingSetFromFile(const string filename) const throw()
{
	vector<training_data> ret;

	ret = dataloder->GetTrainingData(filename);

	return ret;
}

inline void CART::SetTrainingSetFilePath(const string &filepath) throw()
{
	CART::TrainingSetPath = filepath;
}
