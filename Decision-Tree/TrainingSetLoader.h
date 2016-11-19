#ifndef TRAINING_SET_LOADER_H
#define TRAINING_SET_LOADER_H
#include <fstream>
#include "training_data.h"
#include <vector>
#include "ML_exception.h"
#define MAX_LINE 1000
#define LABEL_COUNT NUM_OF_ATTR

class DataLoader final
{

public:
	
	DataLoader();
	~DataLoader();

	std::vector<training_data> GetTrainingData(const std::string &filename)const throw(); // ��ȡѵ��������

private:

	explicit DataLoader(const DataLoader &);
	DataLoader &operator =(const DataLoader &rhs);

	std::vector<std::string> LoaderTrainingSetFromFile(const std::string &filename) const throw(std::logic_error); // ���ļ��ж�ȡѵ���������ڴ�
	bool isValid(const std::string &str,training_data &data) const throw(); // ��֤������Ч��
	std::vector<training_data> DataStringProcessing(const std::vector<std::string> &str) const throw(std::logic_error); // �������ַ����з������������

};

#endif // TRAINING_SET_LOADER_H