#pragma once
#include <functional>
#include <vector>
#include "Data.h"
#include "SortInfo.h"

using namespace std;

class VectorSorter
{
public:
	SortInfo Sort(vector<Data>* dataVector, function<bool (Data, Data)> comparator);
	SortInfo SortWithCheck(vector<Data>* dataVector, function<bool(Data, Data)> comparator);
	int InterpolatingSearch(vector<Data> dataVector, Data data, function<bool(Data, Data)> comparator);
private:
	int SubData(Data first, Data second);
};
