#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print_exit_message();
// functions for each option in the menu

int record_expense(){

	cout << "Recording an expense" << endl;
	return 0;	
};

int list_all_expenses(
		vector<float> recorded_amounts, 
	      	vector<string> recorded_categories,
		vector<string> recorded_descriptions
		) {
	/* 
	 * TODO : 
	 * Create a table like structure
	 * | ID | Amount | Category | Description | 
	 * | 1  | 20	 | some thing | Hello     | 
	 * */
	
	if (	recorded_amounts.size() <= 0 || 
		recorded_categories.size() <= 0 || 
		recorded_descriptions.size() <= 0 ){
		
		cout << "No expenses recorded yet!" << endl;
	} else {
		for (unsigned int i = 0; i < recorded_amounts.size(); i++) {
			float amount {recorded_amounts.at(i)}; 
			string category {recorded_categories.at(i)}; 
			string description {recorded_descriptions.at(i)}; 

			cout << "ID: " << i << endl;
			cout << "Amount: " << amount << endl;
			cout << "Category: " << category << endl;
			cout << "Description: " << description << endl;

				
		}
	}
	return 0;
	
};

int show_total_by_amount(){

	cout << "Showing total by amount" << endl;
	return 0;	
};
int show_total_by_category(){

	cout << "Showing total by category" << endl;
	return 0;;

}
void print_exit_message () {
	cout << "Exiting the program..." << endl;
	cout << "Goodbye!" << endl;	

}


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

void print_menu(vector<string> options) {
	if (options.empty())
	{
		// Error Handling required
		return;
	}
	
	cout << "Pick an Option by the number: " << endl;
	for (unsigned int i = 0; i< options.size(); i++) {
		unsigned int option_number = i + 1; 
		cout << option_number << ". " <<  options.at(i) << endl;
	}
}

bool perform_chosen_option(
		unsigned int chosen_option,
	       	vector<string> options,
		vector<float> recorded_amounts, 
	      	vector<string> recorded_categories,
		vector<string> recorded_descriptions
	
		) {

	bool local_running {true}; 
	// Out of bounds check
	if (chosen_option < 1 || chosen_option > options.size()) {
		// error handling and displaying error
		cout << "Incorrect Option! Please pick an option from the menu: " << endl;
		local_running = true;

		return local_running;
	}
	
	string exit_option {options.at(options.size() - 1)};
	
	string selected_option {options.at(chosen_option -1)};
	 
	cout << "Chosen Option: "; 
	cout << selected_option << endl;
	
	if (chosen_option == 1) {
		// Record an expense
		cout << "Recording an expense" << endl;
	
		cout << "-----------------------------------" << endl;
	}
		
	else if (chosen_option == 2) {
		// List all Expsenses
		list_all_expenses(
			recorded_amounts, 
			recorded_categories,
			recorded_descriptions
			);

		cout << "-----------------------------------" << endl;
	}
	else if (chosen_option == 3) {
		show_total_by_amount();

		cout << "-----------------------------------" << endl;
	}
	else if (chosen_option == 4) {
		show_total_by_category();

		cout << "-----------------------------------" << endl;
	
	}
	// Exit choice
	else  {
		print_exit_message();
		local_running = false; // false means successful exit 

		return local_running;
	}
	

	return local_running;
}


int main () {
	const vector <string> menu_options {
	"Record an Expense.",
	"List all Recorded Expenses.",
	"Show the total by amount.",
	"Show total by category.",
	"Exit!"
	}; 
	bool program_running {true};
	int current_choice {0};
	const int total_number_of_choices {5};
	/* 
	 * record table Id , amount , category, Description
	 * we can access a record using the id
	 */
	vector<float> recorded_amount{0.0}; 
	vector<string> recorded_category{}; 
	vector<string> recorded_description{}; 

	cout << "Welcome to CLI Expense Tracker!" << endl;
	
	//create_dummy_expense(record_id, record_amount, record_category, record_description);
	
	while (program_running) {
		print_menu(menu_options);
		
		cin >> current_choice;

		// Perform the chosen option
		program_running = perform_chosen_option(
				current_choice,
			       	menu_options,
				recorded_amount,
				recorded_category,
				recorded_description	
				);
	
	}	
	return 0;
}
