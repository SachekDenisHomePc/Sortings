#include "VectorSorter.h"

#include "DefData.h"
#include "SortInfo.h"

SortInfo VectorSorter::SortWithCheck(vector<Data>* dataVector, function<bool(Data, Data)> comparator)
{
	SortInfo info;
	bool isSorted = false;
	auto start = clock();
	for (auto i = 0; i < dataVector->size() && !isSorted; i++)
	{
		isSorted = true;
		for (int j = 1; j < (dataVector->size() - i); j++)
		{
			info.NumberOfComparings++;
			if (comparator(dataVector->at(j), dataVector->at(j - 1)))
			{
				info.NumberOfSwaps++;
				swap((*dataVector)[j], (*dataVector)[j - 1]);
				isSorted = false;
			}
		}
	}
	info.Time = clock() - start;
	return info;
}

int VectorSorter::SubData(Data first, Data second, int n)
{
	if( n==0 )
		return first.time1 - second.time1;
	if(n==1)
		return first.time2- second.time2;
	if(n==2)
		return first.number- second.number;
}

int VectorSorter::InterpolatingSearch(vector<Data> dataVector, Data data, function<bool(Data, Data)> comparator)
{
	int n = 0;
	int mid;
	int low = 0;
	int high = dataVector.size() - 1;

	while (comparator(dataVector.at(low), data) && comparator(data, dataVector.at(high)))
	{
		if(SubData(dataVector.at(high), dataVector.at(low), n) == 0)
			n++;
		mid = low + (SubData(data, dataVector.at(low),n) * (high - low)) / (SubData(dataVector.at(high), dataVector.at(low),n));
		
		if (comparator(dataVector.at(mid), data))
			low = mid + 1;
		else if (comparator(data, dataVector.at(mid)))
			high = mid - 1;
		else
			return mid;
	}

	if (!comparator(dataVector.at(low), data) && !comparator(data, dataVector.at(low)))
		return low;
	if (!comparator(dataVector.at(high), data) && !comparator(data, dataVector.at(high)))
		return high;

	return -1;
}

int VectorSorter::BinarySearch(vector<DefData> dataVector, DefData data, function<bool(DefData, DefData)> comparator)
{
	int left = 0; 
	int right = dataVector.size();
	int search = -1;
	while (left <= right && search == -1)
	{
		int mid = (left + right) / 2;
		if (!comparator(data, dataVector[mid]) && !comparator(dataVector[mid],data)) {
			search = mid;
		}
		if (comparator(data, dataVector[mid]))
			right = mid - 1;
		else
		left = mid + 1;
	}

	return search;
}