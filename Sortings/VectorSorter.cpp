#include "VectorSorter.h"

#include "SortInfo.h"

SortInfo VectorSorter::Sort(vector<Data>* dataVector, function<bool(Data, Data)> comparator)
{
	SortInfo info;
	auto start = clock();
	for (auto i = 0; i < dataVector->size(); i++)
	{
		for (int j = 1; j < (dataVector->size() - i); j++)
		{
			info.NumberOfComparings++;
			if (comparator(dataVector->at(j), dataVector->at(j-1)))
			{
				info.NumberOfSwaps++;
				swap((*dataVector)[j], (*dataVector)[j-1]);
			}
		}
	}
	info.Time = clock() - start;
	return info;
}

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
			if (comparator(dataVector->at(j), dataVector->at(j-1)))
			{
				info.NumberOfSwaps++;
				swap((*dataVector)[j], (*dataVector)[j-1]);
				isSorted=false;
			}
		}
	}
	info.Time = clock() - start;
	return info;
}

int VectorSorter::SubData(Data first, Data second)
{
	return (first.time1 - second.time1) + (first.time2 - second.time2) + (first.number - second.number);
}

int VectorSorter::InterpolatingSearch(vector<Data> dataVector, Data data, function<bool(Data, Data)> comparator)
{
	int mid;
    int low = 0;
    int high = dataVector.size() - 1;

    while (comparator(dataVector.at(low), data) && comparator(data,dataVector.at(low))) {
    	
        mid = low + ((SubData(data, dataVector.at(low))) * (high - low)) / (SubData(dataVector.at(high),dataVector.at(low)));

        if (comparator(dataVector.at(mid),data))
            low = mid + 1;
        else if (comparator(data,dataVector.at(mid)))
            high = mid - 1;
        else
            return mid;
    }

    if (!comparator(dataVector.at(low), data) && !comparator(data,dataVector.at(low)))
        return low;
    if (!comparator(dataVector.at(high), data) && !comparator(data,dataVector.at(high)))
        return high;

    return -1; // Not found
}

