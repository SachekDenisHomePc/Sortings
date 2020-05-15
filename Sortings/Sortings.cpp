#include <iostream>
#include <vector>
#include "Data.h"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include "DefData.h"
#include "VectorSorter.h"
#define MAX_NUM_OF_SECONDS (5*365*24*60*60)

using namespace std;

void Print(vector<Data> data);
void PrintInfo(SortInfo info);
void PrintSearch(int index, Data elementToFind, Data findedElement, int endWithSorting, double endWithoutSorting);
void interpolateSearch(vector<Data> search, int indexOfSearch);
char* getTime(time_t time);
char* getDate(time_t time);
void PrintDef(vector<DefData> data);
void Def();
void binarySearch(vector<DefData> search, int indexOfSearch);

int main()
{
	setlocale(LC_ALL,"Russian");

	Def();
	
	//int n =2000;
	//srand(time(NULL));

	//VectorSorter sorter;
	//
 //   auto source = std::vector<Data>(n);
	//auto first = std::vector<Data>(n);
	//auto second = std::vector<Data>(n);
	//auto third = std::vector<Data>(n);
	//auto thirdCheck = std::vector<Data>(n);
	//auto search = std::vector<Data>(n);
	//
	//for(int i = 0 ; i < source.size();i++ )
	//{
	//	source.at(i).number = rand() % 100;
	//	source.at(i).time1 = rand() % 10;
	//	source.at(i).time2 = rand() % 10;
	//}

	//copy(source.begin(), source.end(), first.begin());
	//copy(source.begin(), source.end(), second.begin());
	//copy(source.begin(), source.end(), third.begin());
	//copy(source.begin(), source.end(), thirdCheck.begin());
	//copy(source.begin(), source.end(), search.begin());

	//auto firstInfo = sorter.Sort<Data>(&first,[](Data first, Data second){return first.time1 < second.time1;});
	//
	//auto secondInfo = sorter.Sort<Data>(&second,[](Data first, Data second)
	//{
	//	if(first.time1 == second.time1)
	//		return first.time2 > second.time2;
	//	
	//	return first.time1 < second.time1;
	//});
	//
	//auto thirdInfo = sorter.Sort<Data>(&third,[](Data first, Data second)
	//{
	//	if(first.time1 == second.time1)
	//	{
	//		if(first.time2 == second.time2)
	//			return first.number > second.number;
	//		
	//		return first.time2 > second.time2;
	//	}
	//	
	//	return first.time1 < second.time1;
	//});

	//auto thirdInfoWithCheck = sorter.SortWithCheck(&thirdCheck,[](Data first, Data second)
	//{
	//	if(first.time1 == second.time1)
	//	{
	//		if(first.time2 == second.time2)
	//			return first.number > second.number;
	//		
	//		return first.time2 > second.time2;
	//	}
	//	
	//	return first.time1 < second.time1;
	//});
	
	//Print(first);
	//Print(second);
	//Print(third);
	//Print(thirdCheck);
	//cout << "По одному ключу (В)" << endl;
	//PrintInfo(firstInfo);
	//cout << "По двум ключам (ВУ)" << endl;
	//PrintInfo(secondInfo);
	//cout << "По трем ключам (ВУУ)" << endl;
	//PrintInfo(thirdInfo);
	//cout << "По трем ключам с проверкой (ВУУ)" << endl;
	//PrintInfo(thirdInfoWithCheck);
	//interpolateSearch(search,rand() % n);
	//interpolateSearch(search,rand() % n);
	//interpolateSearch(search,rand() % n);
	//interpolateSearch(search,rand() % n);
	//interpolateSearch(search,rand() % n);
	
}

void Def()
{
	int n =2000;
	srand(time(NULL));

	VectorSorter sorter;
	
    auto source = std::vector<DefData>(n);
	auto first = std::vector<DefData>(n);
	auto second = std::vector<DefData>(n);
	auto search = std::vector<DefData>(n);

	for(int i = 0 ; i < source.size();i++ )
	{
		source.at(i).number = rand() % 100 * 0.1;
		source.at(i).date = 1e+6 + rand()*1000 % MAX_NUM_OF_SECONDS;
	}

	copy(source.begin(), source.end(), first.begin());
	copy(source.begin(), source.end(), second.begin());
	copy(source.begin(), source.end(), search.begin());

	auto firstInfo = sorter.Sort<DefData>(&first,[](DefData first, DefData second){return first.number < second.number;});
	
	auto secondInfo = sorter.Sort<DefData>(&second,[](DefData first, DefData second)
	{
		if(first.number == second.number)
			return first.date < second.date;
		
		return first.number < second.number;
	});

	PrintDef(first);
	PrintDef(second);
	cout << "По одному ключу (В)" << endl;
	PrintInfo(firstInfo);
	cout << "По двум ключам (ВВ)" << endl;
	PrintInfo(secondInfo);
	binarySearch(search,rand() % n);
	binarySearch(search,rand() % n);
	binarySearch(search,rand() % n);
	binarySearch(search,rand() % n);
	binarySearch(search,rand() % n);
}

void Print(vector<Data> data)
{
	cout << std::setw(10) << "Время 1" << "|" <<std::setw(10) << "Время 2"<< "|" <<std::setw(10) << "Число" << "|" << endl;
	
	for(auto item : data)
	{
		cout << std::setw(10) << getTime(item.time1) << "|" << std::setw(10) << getTime(item.time2) << "|" << std::setw(10) << item.number << "|" <<endl;
	}

}

void PrintDef(vector<DefData> data)
{
	cout << std::setw(10) << "Double" << "|" <<std::setw(10) << "Date"<< "|" << endl;
	
	for(auto item : data)
	{
		cout << std::setw(10) << item.number << "|" << std::setw(10) << getDate(item.date)  << "|" <<endl;
	}

}

void PrintInfo(SortInfo info)
{
	cout << "Время (мс) = " << info.Time << " | " << "Количество сравнений = "
	<< info.NumberOfComparings << " | " << "Количество обменов = "
	<< info.NumberOfSwaps << "|" << endl;
}

void PrintSearch(int index, Data elementToFind, Data findedElement, int endWithSorting, double endWithoutSorting)
{
	cout << "Время поиска с сортировкой (мс) = " << endWithSorting << " | "<< "Время поиска без сортировки (мс) = "
	<< endWithoutSorting << " | " << "Индекс искомого элемента = " << index << " | " << "Искомый элемент "
	<< elementToFind.time1 << " " << elementToFind.time2 << " " << elementToFind.number << " | " << "Найденный элемент "
	<< findedElement.time1 << " " << findedElement.time2 << " " << findedElement.number << " | " << endl;
}

void PrintSearchDef(int index, DefData elementToFind, DefData findedElement, int endWithSorting, double endWithoutSorting)
{
	cout << "Время поиска с сортировкой (мс) = " << endWithSorting << " | "<< "Время поиска без сортировки (мс) = "
	<< endWithoutSorting << " | " << "Индекс искомого элемента = " << index << " | " << "Искомый элемент "
	<< getDate(elementToFind.date) << " " << elementToFind.number << " | " << "Найденный элемент "
	<< getDate(findedElement.date) << " " << findedElement.number << " | " << endl;
}

char* getTime(time_t time)
{
	int n=40;
	char* buffer = new char[n];
	tm* format = new tm;
	localtime_s(format,&time);
	strftime(buffer, n, "%H:%M:%S", format);
	return buffer;
}

char* getDate(time_t time)
{
	int n=40;
	char* buffer = new char[n];
	tm* format = new tm;
	localtime_s(format,&time);
	strftime(buffer, n, "%d.%m.%Y", format);
	return buffer;
}

void interpolateSearch(vector<Data> search, int indexOfSearch)
{
	VectorSorter sorter;
	
	auto interpolatingComparator = [](Data first, Data second)
	{
		if(first.time1 == second.time1)
		{
			if(first.time2 == second.time2)
				return first.number < second.number;
			
			return first.time2 < second.time2;
		}
		
		return first.time1 < second.time1;
	};
	
	auto startWithSorting = clock();
	sorter.SortWithCheck(&search,interpolatingComparator);
	
	auto startWithout = chrono::high_resolution_clock::now();
	auto elementToFind = search.at(indexOfSearch);
	auto index = sorter.InterpolatingSearch(search,elementToFind,interpolatingComparator);
	auto endWithSorting = clock() - startWithSorting;
	auto endWithouSorting = chrono::high_resolution_clock::now() - startWithout;
	double time_taken =  chrono::duration_cast<chrono::nanoseconds>(endWithouSorting).count() * 1e-6; 

	auto findedElement = search.at(index);

	cout << "Интерполяционный поиск" << endl;
	PrintSearch(index,elementToFind,findedElement,endWithSorting, time_taken);
}

void binarySearch(vector<DefData> search, int indexOfSearch)
{
	VectorSorter sorter;
	
	auto interpolatingComparator = [](DefData first, DefData second)
	{
		if(first.number == second.number)
			return first.date < second.date;
		
		return first.number < second.number;
	};
	
	auto startWithSorting = clock();
	sorter.Sort<DefData>(&search,interpolatingComparator);
	
	auto startWithout = chrono::high_resolution_clock::now();
	auto elementToFind = search.at(indexOfSearch);
	auto index = sorter.BinarySearch(search,elementToFind,interpolatingComparator);
	auto endWithSorting = clock() - startWithSorting;
	auto endWithouSorting = chrono::high_resolution_clock::now() - startWithout;
	double time_taken =  chrono::duration_cast<chrono::nanoseconds>(endWithouSorting).count() * 1e-6; 

	auto findedElement = search.at(index);

	cout << "Интерполяционный поиск" << endl;
	PrintSearchDef(index,elementToFind,findedElement,endWithSorting, time_taken);
}