#pragma once
#include <functional>
#include <vector>
#include "Data.h"
#include "DefData.h"
#include "SortInfo.h"

using namespace std;

class VectorSorter
{
public:
	template< typename T >
	SortInfo Sort(vector<T>* dataVector, function<bool(T, T)> comparator);
	SortInfo SortWithCheck(vector<Data>* dataVector, function<bool(Data, Data)> comparator);
	int InterpolatingSearch(vector<Data> dataVector, Data data, function<bool(Data, Data)> comparator);
	int BinarySearch(vector<DefData> dataVector, DefData data, function<bool(DefData, DefData)> comparator);
private:
	int SubData(Data first, Data second, int n);
};

template<typename T>
inline SortInfo VectorSorter::Sort(vector<T>* dataVector, function<bool(T, T)> comparator)
{
	SortInfo info;
	auto start = clock();
	for (auto i = 0; i < dataVector->size(); i++)
	{
		for (int j = 1; j < (dataVector->size() - i); j++)
		{
			info.NumberOfComparings++;
			if (comparator(dataVector->at(j), dataVector->at(j - 1)))
			{
				info.NumberOfSwaps++;
				swap((*dataVector)[j], (*dataVector)[j - 1]);
			}
		}
	}
	info.Time = clock() - start;
	return info;
}

