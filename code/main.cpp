#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print_exit_message();

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

bool perform_chosen_option(unsigned int chosen_option, vector<string> options) {

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

	// Exit choice
	if (selected_option == exit_option) {
		print_exit_message();
		local_running = false; // false means successful exit 

		return local_running;
	}

	cout << "Chosen Option: "; 
	cout << selected_option << endl;
	
	return local_running;
}

void print_exit_message () {
	cout << "Exiting the program..." << endl;
	cout << "Goodbye!" << endl;	

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
	const int total_number_of_choices {menu_options.size()};
	/* 
	 * record table Id , amount , category, Description
	 * we can access a record using the id
	 */
	vector<float> record_amount{0.0}; 

	cout << "Welcome to CLI Expense Tracker!" << endl;
	
	//create_dummy_expense(record_id, record_amount, record_category, record_description);
	
	while (program_running) {
		print_menu(menu_options);
		
		cin >> current_choice;

		// Perform the chosen option
		program_running = perform_chosen_option(current_choice, menu_options);
	
	}	
	return 0;
}
