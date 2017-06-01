#include<iostream>
#include<conio.h>
#include<vector>
#include<set>
#include<algorithm>
#include <time.h>

using namespace std;
long totalBytes = 0;

bool sortcol(const vector<int>& v1,
	const vector<int>& v2) {
	return v1[0] < v2[0];
}
void uniqueVect(vector<vector <int>> &list)
{
	vector<vector <int>> tempList;


	int arr[] = {list[0][0], list[0][1]};
	tempList.push_back(vector <int> (arr,arr+2));



	int j = 1;
	for (int i = 1; i < list.size(); i++)
	{
		if (tempList[j-1][0] != list[i][0])
		{
			j++;
			int arr[] = { list[i][0], list[i][1] };
			tempList.push_back(vector <int>(arr, arr + 2));
		}

	}

	list.clear();
	list.swap(tempList);
	

}

void mSort(vector<vector <int>> &list, vector<vector<int>> &list1)
{
	vector<vector<int>> tempList;

	
	tempList.reserve(list.size() + list1.size()); // preallocate memory
	tempList.insert(tempList.end(), list.begin(), list.end());
	tempList.insert(tempList.end(), list1.begin(), list1.end());

	sort(tempList.begin(), tempList.end(), sortcol);


	uniqueVect(tempList);

	//tempList.erase(unique(tempList.begin(), tempList.end()), tempList.end());

	list.clear();
	list.swap(tempList);

}
void subsetprob(vector<vector <int>> &list, int input[], int target, int n, int printFactor = 0)
{

	vector <vector<int>> list1;
	int arr1[] = { 0, 0 };

	list.push_back(vector <int>(arr1, arr1 + 2));

	for (int i = 0; i < n; i++)
	{

		for (int j=0; j < list.size(); ++j)
		{
	
			if ((list[j][0] + input[i]) <= target)
			{
			int	arr[] = { list[j][0] + input[i], i };
			list1.push_back(vector <int>(arr, arr + 2));
	
			}
		}
mSort(list, list1);
totalBytes += list.size() * 4; // Because each vector has 2 intgers
		list1.clear();
		if (printFactor==0||printFactor==n/2)
		cout << "\nList " << i+printFactor << " for " << input[i] << " has " << list.size() << " elements.  ";
		else if(printFactor==-2)
		{

			cout << "\nList " << i *2 << " for " << input[i] << " has " << list.size() << " elements.  ";
		}
	
		else if(printFactor ==-3)
		{

			cout << "\nList " << (i*2)+1<< " for " << input[i] << " has " << list.size() << " elements.  ";
		}


	}


}

void printAnswer(vector<vector <int>> &list, int input[], int target,int n, int printingFactor)
{
	int max = list[list.size() - 1][0];
	int sum = target;

	int inputValue;
	int inputIndex=0;

	int flag = 0;

	int arr[100][2];
	int i = 0;

	while (flag == 0)
	{
		if (max != target || sum < 0)
		{
			flag = -1;
			cout << " \nNo subset found that matches the target " << target;
		}

		else{
			for (int j = 0; j < list.size(); j++)
			{
				if (list[j][0] == sum)
				{
					inputIndex = list[j][1];

				}

			}
			inputValue = input[inputIndex];

			arr[i][0] = inputValue;
			arr[i][1] = inputIndex;
			i++;
			sum = sum - inputValue;
			if (sum == 0)
			{
				flag = 1;
			}
		}
		

		if (flag == 1)
		{ if (printingFactor== -2)
		cout << "\nSubset for even indexed inputs";
		else if(printingFactor == -3)
			cout << "\nSubset for odd indexed inputs";
		else 
			cout << "\nUsing inputs " << 0 + printingFactor << " to " << n+ printingFactor;

			for (int j = 0; j < i; j++)
			{


					if (printingFactor == -2)
				{
					cout << "\n " << arr[j][0] << " \t(" << arr[j][1] *2 << ")";
				}

					else if (printingFactor == -3)
				{
					cout << "\n " << arr[j][0] << " \t(" << (arr[j][1]*2)+1 << ")";

				}
				else
				{
					cout << "\n " << arr[j][0] << " \t(" << arr[j][1] +printingFactor << ")";
				}




			}
		}
	}
}
void main()
{
	vector< vector<int>> list,list2;

	clock_t start, end;
	double cpu_time_used;
	int input[100];

	int n, target;

	cin >> n >> target;
	for (int i = 0; i < n; i++)
	{
		cin >> input[i];
	}

	cout << "\n#######################################################\n";
	start = clock();
	subsetprob(list,input, target, n,0);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	cout << "\nSubset that sums to " << target;
	printAnswer(list, input, target,n,0);
	cout << "\nVersion 1 CPU : "<< cpu_time_used;
	cout << "\nVersion 1 maximum bytes used :" << totalBytes;
	totalBytes = 0;
	cout << "\n#######################################################\n";

	list.clear();
	list2.clear();

	int input1[50], input2[50];
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		if (i < n / 2)
		{
			input1[i] = input[i];
		}
		else{
			input2[k] = input[i];
			k++;
		}


	}



	
	start = clock();
	subsetprob(list, input1, target, n/2, 0);

	subsetprob(list2, input2, target, n/2, n/2);

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	cout << "\nSubset that sums to " << target;
	cout << "\n First half :";
	printAnswer(list, input1, target,n/2,0);
	cout << "\n Second half :";
	printAnswer(list2, input2, target,n/2,n/2);
	cout << "\nVersion 2a CPU :" << cpu_time_used;
	cout << "\nVersion 2a maximum bytes used :" << totalBytes;
	totalBytes = 0;

	cout << "\n#######################################################\n";
	list.clear();
	list2.clear();

	int j1 = 0;int j2 = 0;

	for (int i = 0; i < n; i++)
	{
		if ( i % 2==0)
		{
			input1[j1] = input[i];
			j1++;
		}
		else{
			input2[j2] = input[i];
			j2++;
		}


	}




	start = clock();
	cout << "\nEven";
	subsetprob(list, input1, target, n/2, -2);
	cout << "\nOdd";
	subsetprob(list2, input2, target, n/2, -3);
	cout << "\nSubset that sums to " << target;
	cout << "\n Even:";
	printAnswer(list, input1, target,j1, -2);
	cout << "\n Odd:";
	printAnswer(list2, input2, target,j2, -3);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	
	cout << "\nVersion 2b Odd CPU :" << cpu_time_used;
	cout << "\nVersion 2b Odd maximum bytes used :" << totalBytes ;

	
}