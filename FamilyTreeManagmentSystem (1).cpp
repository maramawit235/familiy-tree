#include <iostream>
#include <vector>
#include <string>

using namespace std;
// To use the functions inside one onother we declared them here 
int main ();
void addChild(const string& headName, const string& parentName, const string& childName);
void deleteMember(const string& headName, const string& memberName);
void getMemberDetails(const string& headName, const string& name);
//

// represents a family structure 
struct familymember{
    string name; // identifier used to identify a family member
    familymember* parent; // pointer to another family member who is the parent of our member
    vector<familymember*> children; // pointer to other family member who is the chiled of our member. vector is used to allow dynamic resizing of childrens

    familymember (string n, familymember* p = nullptr) : name (n), parent(p) {} // constructor to initialize the name and parent of the family member

};

// Forms a 2d vector 
vector<pair<string, familymember*>> families;

// function to add a new family to the list of families by geting their head member name
void addFamily(const string& headName) {
    familymember* root = new familymember(headName);
    families.push_back({headName, root});  // Use head's name as the family identity
    cout << "Family created with head member " << headName << ".\n\n";

    cout << "Do you want to: \n";
    cout << "1. Add a child\n";
    cout << "2. Create another family\n";
    cout << "3. Return to home.\n";
    cout << "Enter your choice: ";
    int choice;
    //
    string Family;
    string Name;
    string Name2;
    //
    cin >> choice;

    switch (choice){
        case 1:
            cout << "Enter the name of the parent: ";
            cin >> Name;
            cout << "Enter the name of the child: ";
            cin >> Name2;
            addChild(headName, Name, Name2);
            break;
        case 2:
            cout << "Enter the name of the family Head: ";
            cin >> Name;
            addFamily(Name);
            break;
        case 3:
            main();
            break;

    }
    

}

// helper function to find the family member to use its name as searching key for other functions use
familymember* findMember(familymember* node, const string& name) {
    if (!node) return nullptr;             // If node is null, return null
    if (node->name == name) return node;   // If the name matches, return the node

    // Search recursively in children
    for (familymember* child : node->children) {
        familymember* found = findMember(child, name);
        if (found) return found;
    }
    return nullptr;                        // Return null if not found
}

// function to search for a family member by their name and the family head name
void searchFamilyMember(const string& headName, const string& name) {
    // Find the family by head member's name
    for (auto& family : families) {
        if (family.first == headName) {
            familymember* member = findMember(family.second, name);  // Find the member by name

            if (!member) {
                cout << "Member not found in family " << headName << "!\n";
                cout << "Would you like to: \n";
                cout << "1. Try again\n";
                cout << "2. Return to home\n";
                //
                int choice;
                string Name;
                //
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice)
                {
                    case 1:
                        cout << "Enter the name of the member: ";
                        cin >> Name;
                        searchFamilyMember(headName, Name);
                        break;
                    case 2:
                        main();
                        break;
                }
                return;
            }
            else {
                cout << "Member found in " << headName << "'s family" << "!\n";
                cout << "Would you like to: \n";
                cout << "1. Get details of the member\n";
                cout << "2. Return to home\n";
                //
                int choice;
                string Name;
                //
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice)
                {
                    case 1:
                        getMemberDetails(headName, name);
                        break;
                    case 2:
                        main();
                        break;
                }
                return;
            }
        }
    }
    cout << "Family with head " << headName << " not found.\n";
    cout << "Would you like to: \n";
    cout << "1. Create a family\n";
    cout << "2. Return to home\n";
    //
    int choice;
    string Name;
    //
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
        case 1:
            cout << "Enter the name of the family head: ";
            cin >> Name;
            addFamily(Name);
            break;
        case 2:
            main();
            break;
    }
}

// function to add a child to a parent 
void addChild(const string& headName, const string& parentName, const string& childName) {
    // Find the parent by name
    for (auto& family : families) {
        if (family.first == headName) {
            familymember* parent = findMember(family.second, parentName);  // Find the parent by name

            if (parent) {
                familymember* child = new familymember{childName, parent};  // Create a new child with the given name and parent
                parent->children.push_back(child);  // Add child to parent's vector
                //
                int choice;
                string Name;
                //
                cout << "Added child " << childName << " to parent " << parentName << " in family " << headName << ".\n";
                cout <<"would you like to: \n";
                cout << "1. Add another child\n";
                cout << "2. Return home\n";
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice)
                {
                    case 1:
                        cout << "Enter the name of the child: ";
                        cin >> Name;
                        addChild(headName, parentName, Name);
                        break;
                    case 2:
                        main();
                        break;
                }
                return;
            } else {
                //
                int choice;
                string Name, Name2;
                //
                cout << "Parent " << parentName << " not found in family " << headName << ".\n";
                cout << "would you like: \n";
                cout << "1. Try again\n";
                cout << "2. Return home\n";
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice){
                    case 1:
                        cout << "Enter the child name: ";
                        cin >> Name2;
                        cout << "Enter the parents name: ";
                        cin >> Name;
                        addChild(headName, Name, Name2);
                        break;
                    case 2:
                        main();
                        break;
                }
                return;
            }
        }
    }
    cout << "Family with head " << headName << " not found.\n";
    //
    int choice; 
    //
    cout << "would you like to: \n";
    cout << "1. Add new familly\n";
    cout << "2. Return home\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice){
        case 1: 
            addFamily(headName);
            break;
        case 2: 
            main();
            break;
    }
}

// helper function for displaying the family tree by using recursion
void displayFamilyTreeHelper(familymember* current, int level) {
    // Print the current node's name with indentation based on level
    for (int i = 0; i < level; ++i) {
        cout << "    ";  // Indentation for each level
    }
    cout << "- " << current->name << endl;

    // Recursively print children
    for (familymember* child : current->children) {
        displayFamilyTreeHelper(child, level + 1);  // Move to next level
    }
}

// function to display the family tree by identifying theme by thier name using the above helper function for recursion
void displayFamilyTree(const string& headName) {
    bool familyFound = false;  // Flag to check if family is found

    // Loop through the families to find the family head
    for (const auto& family : families) {
        if (family.first == headName) {
            cout << "Family Tree of " << headName << ":\n";
            
            // Start with the head of the family
            familymember* current = family.second;
            
            // Call the helper function for recursion
            displayFamilyTreeHelper(current, 0);
            familyFound = true;  // Set flag to true when family is found
        }
        cout << "Would you like to: \n";
        cout << "1. See details of a member\n";
        cout << "2. Add a member\n";
        cout << "3. Delete a member\n";
        cout << "4. Return to home\n";
        //
        int choice;
        string Name, Name2;
        cin >> choice;
        //
        switch (choice)
            {
                case 1:
                    cout << "Enter the name of the member: ";
                    cin >> Name2;
                    getMemberDetails(headName, Name2);
                    break;
                case 2:
                    cout << "Enter the name of the new member: ";
                    cin >> Name2;
                    cout << "Enter the parnet name: ";
                    cin >> Name;
                    addChild(headName, Name, Name2);
                    break;
                case 3:
                    cout << "Enter the name of the member to delete: ";
                    cin >> Name2;
                    deleteMember(headName, Name2);
                    break;
                case 4:
                    main();
                    break;
            }

        return;
    }
    
    // If no family was found, print an error message
    if (!familyFound) {
        cout << "Family with head " << headName << " not found.\n";
        cout << "Would you like: \n";
        cout << "1. Create a family\n";
        cout << "2. Return to home\n";
        cout << "Enter your choice: ";
        int choice;
        string Name;
        cin >> choice;
        switch (choice)
        {
            case 1:
                cout << "Enter the name of the family head: ";
                cin >> Name;
                addFamily(Name);
                break;
            case 2:
                main();
                break;
        }
    }
    
}
           
// function to search a member and get details about theme
void getMemberDetails(const string& headName, const string& name) {
    // Find the family by head member's name
    for (auto& family : families) {
        if (family.first == headName) {
            familymember* member = findMember(family.second, name);  // Find the member by name

            if (!member) {
                cout << "Member not found in family " << headName << "!\n";
                cout << "Would you like to: \n";
                cout << "1. Try again\n";
                cout << "2. Return to home\n";
                //
                int choice;
                string Name;
                //
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice)
                {
                    case 1:
                        cout << "Enter the name of the member: ";
                        cin >> Name;
                        getMemberDetails(headName, Name);
                        break;
                    case 2:
                        main();
                        break;
                }
                return;
            }

            cout << "Details of: " << member->name << "\n";

            // Grandparent
            if (member->parent->parent) {
                cout << "Grandparent: " << member->parent->parent->name << "\n";
            } 
            else {
                cout << "Grandparent: None\n";
            }

            // Parent
            if (member->parent) {
                cout << "Parent: " << member->parent->name << "\n";
            }
            else {
                cout << "Parent: None\n";
            }

            // Children
            if (!member->children.empty()) {
                cout << "Children: ";
                for (auto* child : member->children) {
                    cout << child->name << " ";
                }
                cout << "\n";
            } 
            else {
                cout << "Children: None\n";
            }

            // Siblings
            if (member->parent->children.size() > 1) {
                cout << "Siblings: ";
                for (auto* sibling : member->parent->children) {
                    if (sibling != member) {
                        cout << sibling->name << " ";
                    }
                }
                cout << "\n";
            } 
            else {
                cout << "Siblings: None\n";
            }

            // Cousins
            if (member->parent && member->parent->parent) {
                cout << "Cousins: ";
                for (auto* auntUncle : member->parent->parent->children) {
                    if (auntUncle != member->parent) {
                        for (auto* cousin : auntUncle->children) {
                            cout << cousin->name << " ";
                        }
                    }
                }
                cout << "\n";
            } 
            else {
                cout << "Cousins: None\n";
            }
            cout << "Would you like to: \n";
            cout << "1. Delete the member\n";
            cout << "2. Return to home\n";
            int choice;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice)
            {
                case 1:
                    deleteMember(headName, name);
                    break;
                case 2:
                    main();
                    break;
            }
            return;
        }
    }
    cout << "Family with head " << headName << " not found.\n";
    cout << "Would you like: \n";
    cout << "1. Create a family\n";
    cout << "2. Return to home\n";
    cout << "Enter your choice: ";
    int choice;
    string Name;
    cin >> choice;
    switch (choice)
    {
        case 1:
            cout << "Enter the name of the family head: ";
            cin >> Name;
            addFamily(Name);
            break;
        case 2:
            main();
            break;
    }
}

// function to determine the relationship between two family members && add nephew and niece relationship and aunt and uncle relationships
void calculateRelationship(const string& headName, const string& name1, const string& name2) {
    // Find the family by head member's name
    for (auto& family : families) {
        if (family.first == headName) {
            familymember* member1 = findMember(family.second, name1);
            familymember* member2 = findMember(family.second, name2);
    
            if (!member1 || !member2) {
                cout << "One or both members not found in family " + headName + ".\n";
            }
            else if (member1 == member2) {
                cout << "Same person.\n";
            }

            // Parent-Child relationship
            else if (member1->parent == member2) {
                cout << name1 + " is the child of " + name2 + ".\n";
            } 
            else if (member2->parent == member1) {
                cout << name1 + " is the parent of " + name2 + ".\n";
            }

            // Sibling relationship
            else if (member1->parent == member2->parent) {
                cout << name1 + " and " + name2 + " are siblings.\n";
            }

            // Cousin relationship
            else if (member1->parent->parent == member2->parent->parent) {
                cout << name1 + " and " + name2 + " are cousins.\n";
            }

            // Grandparent-Grandchild relationship
            else if (member1->parent->parent == member2) {
                cout << name1 + " is a grandchild of " + name2 + ".\n";
            } 
            else if (member2->parent->parent == member1) {
                cout << name1 + " is a grandparent of " + name2 + ".\n";
            }

            // nephew/niece - aunt/uncle relationship
            else if (member2->parent->parent == member1->parent){
                cout << name1 + " is the aunt/uncle of " + name2 + ".\n";
            }
            else if (member1->parent->parent == member2->parent){
                cout << name1 + " is the nephew/niece of " + name2 + ".\n";
            }
     

            // No relationship found
            else{
                cout << "No relationship found between " + name1 + " and " + name2 + ".\n";
                }
            //
            int choice;
            string Name, Name2;
            //
            cout << "Would you like to: \n";
            cout << "1. Calculate another relationship\n";
            cout << "2. Return home\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice){
                case 1:
                    cout << "Enter the first member: ";
                    cin >> Name;
                    cout << "Enter the second member: ";
                    cin >> Name2;
                    calculateRelationship(headName, Name, Name2);
                    break;
                case 2:
                    main();
                    break;
            }
            return;
        }
    }
    cout << "Family with head " + headName + " not found.\n";
    //
    int choice;
    string Name;
    //
    cout << "Would you like to: \n";
    cout << "1. Add the family\n";
    cout << "2. Return home\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice){
        case 1:
            addFamily(headName);
            break;
        case 2:
            main();
            break;
    }

}

// function to delete a member from a family by identifying theme by thire name and family name
void deleteMember(const string& headName, const string& memberName) {
    // Find the family by head member's name
    for (auto it = families.begin(); it != families.end(); ++it) {
        if (it->first == headName) {  // Family found by headName
            familymember* member = findMember(it->second, memberName);  // Find the member by name

            if (!member) {
                cout << "Member " << memberName << " not found in family " << headName << ".\n";
                //
                int choice;
                string Name;
                //
                cout << "Would you like to: \n";
                cout << "1. Try again\n";
                cout << "2. Return to home\n";
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice){
                    case 1:
                        cout << "Enter the member name: ";
                        cin >> Name;
                        deleteMember(headName, Name);
                        break;
                    case 2:
                        main();
                        break;
                }
                return;
            }

            // If the member is the root (head of the family), delete the entire family
            else if (member == it->second) {
                // Delete all children first to avoid dangling pointers
                for (auto* child : it->second->children) {
                    delete child;
                }
                delete it->second;  // Delete the root member
                it->second = nullptr; // Set root pointer to nullptr
                families.erase(it);  // Remove the family from the list
                cout << "Family with head " << headName << " has been deleted.\n";
                //
                int choice;
                string Name, Name2;
                //
                cout << "would you like to: \n";
                cout << "1. Delete another member\n";
                cout << "2. Return to home\n";
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice){
                    case 1:
                        cout << "Enter the family name: ";
                        cin >> Name;
                        cout << "Enter the name of the member: ";
                        cin >> Name2;
                        deleteMember(Name, Name2);
                        break;
                    case 2:
                        main();
                        break;
                }
                return;
            }

            // If the member has children, reassign them to the parent
            if (!member->children.empty()) {
                for (auto* child : member->children) {
                    child->parent = member->parent;  // Reassign parent to the current member's parent
                    if (member->parent) {
                        member->parent->children.push_back(child);  // Add child to the parent's children list
                    }
                }
            }

            // Remove the member from the parent's children list
            if (member->parent) {
                auto& siblings = member->parent->children;
                for (auto sit = siblings.begin(); sit != siblings.end(); ++sit) {
                    if (*sit == member) {
                        siblings.erase(sit);
                        break;
                    }
                }
            }

            // Delete the member
            delete member;
            cout << "Member " << memberName << " has been deleted from family " << headName << ".\n";
            //
            int choice;
            string Name, Name2;
            //
            cout << "would you like to: \n";
            cout << "1. Delete another member\n";
            cout << "2. Return home\n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice){
                case 1: 
                    cout << "Enter the family name: ";
                    cin >> Name;
                    cout << "Enter the member name: ";
                    cin >> Name2;
                    deleteMember(Name, Name2);
                    break;
                case 2:
                    main();
                    break;
            }
            return;
        }
    }
    cout << "Family with head " << headName << " not found.\n";
      //
    int choice;
    string Name, Name2;
    //
    cout << "would you like to: \n";
    cout << "1. Delete from another family\n";
    cout << "2. Return home\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice){
        case 1: 
            cout << "Enter the family name: ";
            cin >> Name;
            cout << "Enter the member name: ";
            cin >> Name2;
            deleteMember(Name, Name2);
            break;
        case 2:
            main();
            break;
    }
}

// used to terminate the program
void Exit(){
    cout << "Thank you for using our program. we hope you enjoyed it. by ^_^\n";
    exit(0);
}

// Display the details of the program and the group members
void about(){
    cout <<"\nWellcome to our about page. this program was developed by students of section 3 for our Data structure and Algorithm course project.\n"
           "we used linked list to implement Tree data structure to represent family tree. we also added functionalities such as deleting, finding,\n" 
           "adding and callculating the relationship of a member based on theire name and family name. the family name is important because our program\n" 
           "hunddles multiple faimlis at the same time. the families are identified by their root member name.\n"
           ;
    cout << "We are very greatefull for the oportunity and knowlage our instructor gave us. Thankyou! ^_^\n\n"
            "----------Group Members----------\n" 
            "1. Yeabsira Alexander ---- sec.3 -- G. 6 -- UGR/35603/16\n"
            "2. Tadele Rogo ---- sec.3 -- G. 5 -- UGR/*****/16\n"
            "3. Daniel Endalkachew ---- sec.3 -- G. 5 -- UGR/34193/16\n"
            "4. Menwuyelet Temesgen ---- sec.3 -- G. 5 -- UGR/34920/16\n"
            "5. Mandela Derje ---- sec.3 -- G. 6 -- UGR/34855/16\n"
            "6. Maramawit Esualegn ---- sec.3 -- G. 5 -- UGR/34857/16\n"
            "7. Abigiya Gebremicheal ---- sec.3 -- G. 5 -- UGR/*****/16\n"
            "\n"
            ;
    cout << "Would you like to: \n";
    cout << "1. Return to home\n";
    cout << "2. Exit\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            main();
            break;
        case 2:
            cout << "Terminating the program\n";
            Exit();
            break;
    }
}

int main (){

    cout << "\n------ Wellcome to the Family Tree Program ------\n\n";
    cout << "Choose an option:\n";
    cout << "1. Create a Family\n";
    cout << "2. Display Family Tree\n";
    cout << "3. Search for a Member\n";
    cout << "4. Get Member Details\n";
    cout << "5. Add chilled\n";
    cout << "6. Calculate Relationship\n";
    cout << "7. Delete Member\n";
    cout << "8. About\n";
    cout << "9. Exit\n";


    familymember* Root;

    int Choice;
    cout << "Enter your choice: ";
    cin >> Choice;
    string Family;
    string Name;
    string Name2;

// modify the swicth to acomodate link to return to main after complation of a function.

    switch (Choice) {
        case 1:
            cout << "Enter the name of the Head of the family: ";
            cin >> Name;
            addFamily(Name);
            break;
        case 2:
            cout << "Enter the name of the Head of the family: ";
            cin >> Name;
            displayFamilyTree(Name);
            break;
        case 3:
            cout << "Enter the name of the Head of the family: ";
            cin >> Name;
            cout << "Enter the name of the member: ";
            cin >> Name2;
            searchFamilyMember(Name, Name2);
            break;
        case 4:
            cout << "Enter the name of the family: ";
            cin >> Family;
            cout << "Enter the name of the name of the family member: ";
            cin >> Name;
            getMemberDetails(Family, Name);
            break;
        case 5:
            cout << "Enter the family name: ";
            cin >> Family;
            cout << "Enter the parent name: ";
            cin >> Name;
            cout << "Enter the child name: ";
            cin >> Name2;
            addChild(Family, Name, Name2);
            break;
        case 6:
            cout << "Enter the family name: ";
            cin >> Family;
            cout << "Enter the name of the first member: ";
            cin >> Name;
            cout << "Enter the name of the second member: ";
            cin >> Name2;
            calculateRelationship(Family, Name, Name2);
            break;
        case 7:
            cout << "Enter the family name: ";
            cin >> Family;
            cout << "Enter the name of the member to delete: ";
            cin >> Name;
            deleteMember(Family, Name);
            break;
        case 8:
            about();
            break;
        case 9:
            Exit();
            break;
        default:
            cout << "Invalid choice\n";
            cout << "Choose again.\n";
            main();
            break;
    }
}













