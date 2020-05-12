#include <iostream>
#include <vector>
#include "Data.h"
#include <algorithm>
#include <iomanip>


#include "VectorSorter.h"

using namespace std;

void Print(vector<Data> data);
void PrintInfo(SortInfo info);

int main()
{
	setlocale(LC_ALL,"Russian");
	int n =4000;
	srand(time(NULL));

	VectorSorter sorter;
	
    auto source = std::vector<Data>(n);
	auto first = std::vector<Data>(n);
	auto second = std::vector<Data>(n);
	auto third = std::vector<Data>(n);
	auto thirdCheck = std::vector<Data>(n);
	
	for(int i = 0 ; i < source.size();i++ )
	{
		source.at(i).number = rand() % 100;
		source.at(i).time1 = rand() % 10;
		source.at(i).time2 = rand() % 10;
	}

	copy(source.begin(), source.end(), first.begin());
	copy(source.begin(), source.end(), second.begin());
	copy(source.begin(), source.end(), third.begin());
	copy(source.begin(), source.end(), thirdCheck.begin());

	auto firstInfo = sorter.Sort(&first,[](Data first, Data second){return first.time1 < second.time1;});
	
	auto secondInfo = sorter.Sort(&second,[](Data first, Data second)
	{
		if(first.time1 == second.time1)
			return first.time2 > second.time2;
		
		return first.time1 < second.time1;
	});
	
	auto thirdInfo = sorter.Sort(&third,[](Data first, Data second)
	{
		if(first.time1 == second.time1)
		{
			if(first.time2 == second.time2)
				return first.number > second.number;
			
			return first.time2 > second.time2;
		}
		
		return first.time1 < second.time1;
	});

	auto thirdInfoWithCheck = sorter.SortWithCheck(&thirdCheck,[](Data first, Data second)
	{
		if(first.time1 == second.time1)
		{
			if(first.time2 == second.time2)
				return first.number > second.number;
			
			return first.time2 > second.time2;
		}
		
		return first.time1 < second.time1;
	});

	Print(first);
	Print(second);
	Print(third);
	Print(thirdCheck);
	PrintInfo(firstInfo);
	PrintInfo(secondInfo);
	PrintInfo(thirdInfo);
	PrintInfo(thirdInfoWithCheck);
	
	int k = 5;
}

void Print(vector<Data> data)
{
	cout << std::setw(10) << "Время 1" << "|" <<std::setw(10) << "Время 2"<< "|" <<std::setw(10) << "Число" << "|" << endl;
	
	for(auto item : data)
	{
		cout << std::setw(10) << item.time1 << "|" << std::setw(10) << item.time2 << "|" << std::setw(10) << item.number << "|" <<endl;
	}

}

void PrintInfo(SortInfo info)
{
	cout << "Время (мс) = " << info.Time << " | " << "Количество сравнений = " << info.NumberOfComparings << " | " << "Количество обменов = " << info.NumberOfSwaps << "|" << endl;
}
