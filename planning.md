# Planning

## verion 1.0.0
The program must run until we or the user exits the program. so for this to work we can use basic boolean and while loop; the same comcept as in the game dev. \

### The User flow and the data
we have to process the users expense and each expense should have these three properties:
        - Amount 
        - Category
        - Short Description
However, lets first talk about the what the user is able to do:
    - See a text based menu with the following options:
        - Record an expense
        - List all recorded expenses
        - Show the total amount spent
        - Show total by category

#### Expenses
We can implement this as a multi dimensional vector that we can easily update and index while the application is running. This will allow for easy access to individual expenses or all expenses. Example visual: \

|-----|--------|-----------|-------------| 
| ID  | Amount | Category  | Description |
|-----|--------|-----------|-------------| 
| 1   | 20     | Food      | some text   |
| 2   | 50     | Tech      | some shit   |

We can easily implement this struct using multi-dimensional vectors.

#### Using Functions
We can create individual functions for creating, accessing and processing expenses from the expenses vector. This will allow for modularization and flexible and clean code.
 

