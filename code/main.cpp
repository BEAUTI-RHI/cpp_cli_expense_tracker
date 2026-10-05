#include <iostream>
#include <vector>
#include <string>

using namespace std;

int create_dummy_expense(
	vector<int> record_id 
	, vector<float> record_amount 
	, vector<string> record_category 
	, vector<string> record_description 
	)
{	
	record_id.push_back(record_id.at(record_id.size() -1) + 1);
	record_amount.push_back(20.0);
	record_category.push_back("Food");
	record_description.push_back("Goceries for Monday");


	return 0;
}

int main () {
	bool running {true};

	/* 
	 * record table Id , amount , category, Description
	 * we can access a record using the id
	 */
	vector<int> record_id {0}; 
	vector<float> record_amount {0.0}; 
	vector<string> record_category {""}; 
	vector<string> record_description {""}; 
	

	cout << "Welcome to CLI Expense Tracker!" << endl;
	
	cout << record_id.at(0) << endl;	
	cout << record_amount.at(0) << endl;	
	cout << record_category.at(0) << endl;	
	cout << record_description.at(0) << endl;	

	//create_dummy_expense(record_id, record_amount, record_category, record_description);

	print_menu();
		
	return 0;
}
