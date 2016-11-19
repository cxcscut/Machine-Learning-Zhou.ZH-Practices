#include "TrainingSetLoader.h"
#include <iostream>

using namespace std;

DataLoader::DataLoader()
{

}

DataLoader::~DataLoader()
{

}

vector<string> DataLoader::LoaderTrainingSetFromFile(const std::string &filename) const throw(std::logic_error)
{
	vector<string> data_ret;
	string str_line;
	int k = 0;

	ifstream datafile;
	datafile.open(filename,ios::in);

	if (!datafile) {
		throw MLexception("Data file can not be opened");
		return data_ret;
	}

	for (k = 0; k < MAX_LINE && !datafile.eof(); k++)
	{
		getline(datafile,str_line);
		data_ret.push_back(str_line);
	}

	return data_ret;
}

bool DataLoader::isValid(const string &str,training_data &data) const throw()
{
	if (str.empty()) return false;

	string str_tmp;
	int l = str.length();
	int attr = color;

	for (int i = 0; i < l; i++)
	{
		if (str[i] != ',')
			str_tmp += str[i];
		else
		{
			switch (attr)
			{
			case color:
				if (str_tmp == "ÇàÂÌ")
					data.data_attr.color = green;
				else if (str_tmp == "ÎÚºÚ")
					data.data_attr.color = black;
				else if (str_tmp == "Ç³°×")
					data.data_attr.color = white;
				else
					return false;
				break;
			case root:
				if (str_tmp == "òéËõ")
					data.data_attr.root = curl;
				else if (str_tmp == "ÉÔòé")
					data.data_attr.root = slightly_curl;
				else if (str_tmp == "Ó²Í¦")
					data.data_attr.root = straight;
				else
					return false;
				break;
			case sound:
				if (str_tmp == "×ÇÏì")
					data.data_attr.sound = dull;
				else if (str_tmp == "³ÁÃÆ")
					data.data_attr.sound = very_dull;
				else if (str_tmp == "Çå´à")
					data.data_attr.sound = sharp;
				else
					return false;
				break;
			case texture:
				if (str_tmp == "ÇåÎú")
					data.data_attr.texture = clear;
				else if (str_tmp == "ÉÔºý")
					data.data_attr.texture = slightly_blur;
				else if (str_tmp == "Ä£ºý")
					data.data_attr.texture = blur;
				else
					return false;
				break;
			case navel:
				if (str_tmp == "°¼ÏÝ")
					data.data_attr.navel = hollow;
				else if (str_tmp == "ÉÔ°¼")
					data.data_attr.navel = slightly_hollow;
				else if (str_tmp == "Æ½Ì¹")
					data.data_attr.navel = flat;
				else
					return false;
				break;
			case touch:
				if (str_tmp == "Ó²»¬")
					data.data_attr.touch = smooth;
				else if (str_tmp == "ÈíÕ³")
					data.data_attr.touch = sticky;
				else
					return false;
				break;
			case LABEL_COUNT:
				if (str_tmp == "ÊÇ")
					data.label = good;
				else if (str_tmp == "·ñ")
					data.label = bad;
				else
					return false;
				break;
			default:
				break;
			}

			attr++;
			str_tmp.clear();
		}
	}
	
	return true;
}

vector<training_data> DataLoader::DataStringProcessing(const vector<string> &str) const throw(logic_error)
{
	typename vector<string>::const_iterator _piter;
	training_data tmp_data;
	vector<training_data> ret;

	for (_piter = str.begin(); _piter != str.end(); _piter++)
	{
		if (DataLoader::isValid(*_piter, tmp_data))
			ret.push_back(tmp_data);
		else {
			throw MLexception("data sample is invalid");
		}
	}

	return ret;
}

vector<training_data> DataLoader::GetTrainingData(const std::string &filename)const throw()
{
	vector<training_data> ret;
	vector<string> ret_string;

	try {
		ret_string = DataLoader::LoaderTrainingSetFromFile(filename);
	}
	catch (MLexception &e)
	{
		cout << e.what <<endl;
		std::abort();
	}

	try {
		ret = DataStringProcessing(ret_string);
	}
	catch (MLexception &e)
	{
		cout << e.what << endl;
		std::abort();
	}

	return ret;
}