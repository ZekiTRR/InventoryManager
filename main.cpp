#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Function prototypes
void hub();              // Main menu interface
void addNewProduct();    // Adds a new product to inventory
void viewAllProducts();  // Displays all available products
void deleteProduct();    // Deletes a product from inventory

int main(int argc, char const *argv[])
{  
    // Infinite loop to keep the program running until user chooses to exit
    for(;;){
        hub();
    }
    return 0;
}

// Main menu function that handles user navigation
void hub()
{
    int choice;

    // Display menu options
    cout << "\n1. View all available products" << endl;
    cout << "2. Add new product" << endl;
    cout << "3. Delete product" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    // Process user selection
    switch(choice){
        case 2:
            addNewProduct();    // Call product addition function
            break;
        case 1:
            viewAllProducts(); // Call product display function
            break;
        case 3:
            deleteProduct();    // Call product deletion function
            break;
        case 0:
            exit(0);           // Terminate program
        default:
            cout << "Invalid choice! Please try again." << endl;
    }
}

// Function to add a new product to the inventory file
void addNewProduct()
{
    // Open file in append mode (creates file if doesn't exist)
    ofstream product("products.txt", ios::app); 
    string name;
    int price;
    
    // Get product details from user
    cout << "Enter product name: ";
    cin >> name;
    cout << "Enter product price: ";
    cin >> price;
    
    // Write product to file (format: name price)
    product << name << " " << price << endl;
    
    // File closes automatically when ofstream goes out of scope
}

// Function to display all products in inventory
void viewAllProducts()
{
    // Open file for reading
    ifstream product("products.txt");
    string name;
    int price;

    // Display header
    cout << "\nInventory List:" << endl;
    cout << "Name:" << "   " << "Price:" << endl;
    
    // Read and display each product line by line
    while(product >> name >> price){
        cout << name << "   " << price << endl;
    }
    
    // File closes automatically when ifstream goes out of scope
}

// Function to delete a product from inventory
void deleteProduct() {
    // First show all available products
    viewAllProducts(); 

    // Open file for reading
    ifstream in("products.txt");
    vector<string> lines;
    string line;
    
    // Read all lines from file into a vector
    while (getline(in, line)) {
        lines.push_back(line);
    }
    in.close();

    // Check if inventory is empty
    if (lines.empty()) {
        cout << "No products to delete!\n";
        return;
    }

    // Get user input for which product to delete
    int choice;
    cout << "Enter the number of product to delete (1-" << lines.size() << "): ";
    cin >> choice;

    // Validate user input
    if (choice < 1 || choice > lines.size()) {
        cout << "Invalid choice!\n";
        return;
    }

    // Remove selected product from vector
    lines.erase(lines.begin() + choice - 1);

    // Rewrite the entire file without the deleted product
    ofstream out("products.txt");
    for (const auto& l : lines) {
        out << l << endl;
    }
    cout << "Product deleted successfully!\n";
}