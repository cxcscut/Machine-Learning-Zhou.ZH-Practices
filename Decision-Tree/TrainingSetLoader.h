#ifndef TRAINING_SET_LOADER_H
#define TRAINING_SET_LOADER_H
#include <fstream>
#include "training_data.h"
#include <vector>
#include "ML_exception.h"

using MAX_LINE = 1000;
using LABEL_COUNT = NUM_OF_ATTR

class DataLoader final
{

public:
	
	DataLoader();
	~DataLoader();

	std::vector<training_data> GetTrainingData(const std::string &filename)const throw(); // 获取训练样本集

private:

	explicit DataLoader(const DataLoader &);
	DataLoader &operator =(const DataLoader &rhs);

	std::vector<std::string> LoaderTrainingSetFromFile(const std::string &filename) const throw(std::logic_error); // 从文件中读取训练样本到内存
	bool isValid(const std::string &str,training_data &data) const throw(); // 验证样本有效性
	std::vector<training_data> DataStringProcessing(const std::vector<std::string> &str) const throw(std::logic_error); // 从样本字符串中分离出属性与标记

};

#endif // TRAINING_SET_LOADER_H
