#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// GLOBAL CONSTANTS
const vector<string> available_categories {
    "Housing",
    "Utilities",
    "Food",
    "Transport",
    "Insurance",
    "Healthcare",
    "Leisure",
    "Shopping",
    "Savings",
    "Debt",
    "Travel",
    "Other"
};

void print_exit_message();
// functions for each option in the menu
string record_category()
{	
	
	string selected_category {""};
	bool valid_category {false};
	do {
	
	int index {0};
	for (auto c: available_categories) {
	    	cout << index << ". " << c << endl; 
		index++;
	}
	cout << "Select a category from the menu with number: ";
	unsigned int user_option {available_categories.size()};
	cin >> user_option;

	if (user_option >= 0 && user_option < available_categories.size()) {
		
		selected_category = available_categories.at(user_option);
		valid_category = true;
	}else {
		cout << "Invalid! Please select a category from the menu" << endl;
	}

	} while (!valid_category);

	return selected_category;
}
int record_expense(
		vector<float> &recorded_amounts, 
	      	vector<string> &recorded_categories,
		vector<string> &recorded_descriptions
		){
	float amount {0.0};
	string category {"General"};
	string description {"No Desc"};
	
	bool continue_next {false};
	
	// Check for valid amount	
	cout << "Please provide the amount: " ;
       	cin >> amount;
	while (!continue_next) {
	
		if (amount < 0.0) {
			cout << "Invalid! Amount can not be negative" << endl;
			cout << "Please Enter a valid amount: ";
			cin >> amount;
		
		} else {
			continue_next = true;
		}
	}
	
	// Get the category; no need for validation
	category = record_category();
	
	/* cout << "Please enter a category ( Leave empty for optional ):" << endl;
	 getline(cin, category);	
	*/ 

	// Get the Description; 
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Please enter a description ( Leave empty for optional ):" << endl;
	getline(cin, description);	
	

	// Confirmation
	cout << endl;
	cout << "Recording the following expense:" << endl;
		
       	cout << "Amount: $" << amount << endl;
       	cout << "Category: " << category << endl;
       	cout << "Description: " << description << endl;

	recorded_amounts.push_back(amount);
	recorded_categories.push_back(category);
	recorded_descriptions.push_back(description);


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
	string separator {" | "};

	if (	recorded_amounts.size() <= 0 || 
		recorded_categories.size() <= 0 || 
		recorded_descriptions.size() <= 0 ){
		
		cout << "No expenses recorded yet!" << endl;
	} else {

		cout << separator << "ID" <<  separator << "Amount" <<  separator <<  "Category" <<  separator << "Description" << separator << endl;
		for (unsigned int i = 0; i < recorded_amounts.size(); i++) {
			float amount {recorded_amounts.at(i)}; 
			string category {recorded_categories.at(i)}; 
			string description {recorded_descriptions.at(i)}; 

			cout << separator << i << separator << amount << separator << category << separator << description << separator << endl;				
		}
	}
	return 0;
	
};

void show_total_by_amount(
		vector<float> &recorded_amounts
		){
	
	size_t total_amount {};
	if (recorded_amounts.size() == 0) {
		cout << "No expenses recorded at this moment" << endl;
		return;
	}
	for (size_t i {}; i < recorded_amounts.size(); i++) {
		total_amount += recorded_amounts.at(i);
	} 
	cout << "Total Amount: $" <<  total_amount << endl; 
	return ;	
};
void show_total_by_category(
		vector<float> &recorded_amounts, 
	      	vector<string> &recorded_categories,
		vector<string> &recorded_descriptions
		){
	
	size_t total_amount {};
	string selected_category {""}; 
	if (recorded_amounts.size() == 0) {
		cout << "No expenses recorded at this moment" << endl;
		return;
	}
	selected_category = record_category();
	for (size_t i {}; i < recorded_amounts.size(); i++) {
		if (recorded_categories.at(i) == selected_category) {
			total_amount += recorded_amounts.at(i);
		}	
	} 
	cout << "Total Amount for " << selected_category << ": $" <<  total_amount << endl; 
	return ;

}
void print_exit_message () {
	cout << "Exiting the program..." << endl;
	cout << "Goodbye!" << endl;	
	return;
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
	
	for (unsigned int i = 0; i< options.size(); i++) {
		unsigned int option_number = i + 1; 
		cout << option_number << ". " <<  options.at(i) << endl;
	}
	return;
}

bool perform_chosen_option(
		unsigned int chosen_option,
	       	vector<string> options,
		vector<float> &recorded_amounts, 
	      	vector<string> &recorded_categories,
		vector<string> &recorded_descriptions
	
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
		cout << endl;
		cout << "--- Recording an expense" << endl;
		record_expense(
				recorded_amounts, 
				recorded_categories,
				recorded_descriptions
			      );
			
	}
		
	else if (chosen_option == 2) {
		// List all Expsenses
		cout << endl;
		cout << "--- Listing All Expenses" << endl;;
		list_all_expenses(
			recorded_amounts, 
			recorded_categories,
			recorded_descriptions
			);
	}
	else if (chosen_option == 3) {
		cout << endl;
		cout << "--- Total by Amount: " << endl;
		show_total_by_amount(
			recorded_amounts
			);

	}
	else if (chosen_option == 4) {
		cout << endl;
		cout << "--- Total by Category" << endl;
		show_total_by_category(
			recorded_amounts, 
			recorded_categories,
			recorded_descriptions
			);
	
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
	vector<float> recorded_amount{}; 
	vector<string> recorded_category{}; 
	vector<string> recorded_description{}; 

	cout << "Welcome to CLI Expense Tracker!" << endl;
	
	//create_dummy_expense(record_id, record_amount, record_category, record_description);
	
	while (program_running) {
		cout << endl;
		print_menu(menu_options);

		cout << "Pick an Option by the number: " ;
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
