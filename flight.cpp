#include<iostream>
#include<string>
#include<algorithm>
#include<iomanip>
using namespace std;

const int MAX = 10;

class FlightGraph
{
	string cities[MAX];
	int matrix[MAX][MAX];
	int citycount;
	
	string toLowerCase(string s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
	}
	
public:
	FlightGraph()
	{
		citycount = 0;
		for(int i = 0; i < MAX; i++)
		{
			for(int j = 0; j < MAX; j++)
			matrix[i][j] = 0;
		}
	}
	
	int getCityIndex(string name)
	{
		string lowername = toLowerCase(name);
		for(int i = 0; i < citycount; i++)
		{
			if(toLowerCase(cities[i]) == lowername)
				return i;
		}
		cities[citycount] = name;
		return citycount++;
	}
	
	void addFlight(string from, string To, int cost)
	{
		int i = getCityIndex(from);
		int j = getCityIndex(To);
		matrix[i][j] = cost;
	}
	
	void displaymatrix()
	{
		cout << "\n Flight Matrix: \n";
		cout << setw(10) << " ";
		for(int i = 0; i < citycount; i++)
		{
			cout << setw(5) << cities[i] << "\t";
		} 
		cout << "\n";
		
		for(int i = 0; i < citycount; i++)
		{
			cout << setw(5) << cities[i] << "\t";
			for(int j = 0; j < citycount; j++)
			{
				cout << setw(5) << matrix[i][j] << "\t";
			}
			cout << "\n";
		}
	}
	
	void displaylist()
	{
		cout << "\n Flight List:\n";
		for(int i =  0; i < citycount; i++)
		{
			cout << cities[i] << "-->";
			bool hasFlight = false;
			for(int j = 0; j < citycount; j++)
			{
				if(matrix[i][j] != 0)
				{
					cout << "[ " << cities[j] << "," <<  matrix[i][j] << "]";
					hasFlight = true;
				}
			}
			if(!hasFlight) cout << "No Flight!";
			cout << "\n";
		}
	}
	
	void checkconnection(string from, string To)
	{
		int i = getCityIndex(from);
		int j = getCityIndex(To);
		if(matrix[i][j] != 0)
			cout << "Yes ! Flight Exists from" << from << "To" << To << "\n";
		else
			cout << "No ! Flight Exists from " << from << "To" << To << "\n";
	}
};
	
int main()
{
	FlightGraph f;
	int choice, cost;
	string from, To;
	
	do 
	{
		cout << "\n 1.Add Flight \n 2.Display Matrix \n 3.Display List \n 4.CheckConnection \n 5.Exit \n";
		cout << "Enter Your choice: ";
		cin >> choice;
		switch(choice)
		{
			case 1: 
				cout << "From City: ";
				cin >> from;
				cout << "To City: ";
				cin >> To;
				cout << "Flight Cost: ";
				cin >> cost;
				f.addFlight(from,To,cost);
				break;
			case 2:
				f.displaymatrix();
				break;
			case 3:
				f.displaylist();
				break;
			case 4:
				cout  << "From city: ";
				cin >> from;
				cout << "To city: ";
				cin >> To;
				f.checkconnection(from, To);
				break;
			case 5:
				cout << "Visit Again\n" ;
				break;
			default:
				cout << "Invalid Choice!!!\n";
				
		}
		
	}while(choice != 5);
	return 0;	
}
