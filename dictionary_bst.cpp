#include<bits/stdc++.h>
using namespace std;

struct st
{
    string key, definition;
    struct st *left, *right;
}   *root = NULL, *temp;

struct st* Add(struct st *head, string key_word, string def)
{
    if(head == NULL)
    {
        head = new struct st();
        head->key = key_word;
        head->definition = def;
        head->left = head->right = NULL;
        return head;
    }
    if(key_word < head->key) head->left = Add(head->left, key_word, def);
    else head->right = Add(head->right, key_word, def);
    return head;

}

vector<string>vec;
void check(struct st *head, char c)
{
    if(head == NULL) return;
    if(head->key[0] == c) vec.push_back(head->key);
    check(head->left, c);
    check(head->right, c);
}

struct st* Search(struct st *head, string key_word)
{
    if(head == NULL || head->key == key_word) return head;
    if(key_word < head->key) return Search(head->left, key_word);
    else return Search(head->right, key_word);
}

string Minimum(struct st *head)
{
    if(head->left == NULL) return head->key;
    return Minimum(head->left);
}

struct st* Delete(struct st *head, string key_word)
{
    if(head == NULL) return head;
    else if(key_word < head->key) head->left = Delete(head->left, key_word);
    else if(key_word > head->key) head->right = Delete(head->right, key_word);
    else
    {
        if(head->left == NULL)
        {
            temp = head;
            head = head->right;
            delete(temp);
        }
        else if(head->right == NULL)
        {
            temp = head;
            head = head->left;
            delete(temp);
        }
        else
        {
            string s = Minimum(head->right);
            head->key = s;
            head->right = Delete(head->right, s);
        }
    }

    return head;
}

void View_inorder(struct st *head)
{
    if(head == NULL) return;
    View_inorder(head->left);
    cout << head->key << endl;
    View_inorder(head->right);
}

int main()
{
    int option, option1;
    string key_word, def;

    while(1)
    {
        cout << "1. Add word"     << endl;
        cout << "2. Search word"  << endl;
        cout << "3. Delete word"  << endl;
        cout << "4. View words"   << endl;
        cout << "0. Exit program" << endl;
        cout << endl << "Choose option: ";
        cin >> option;
        system("cls");

        if(option == 1)
        {
            cout << "1. Take input from file" << endl;
            cout << "2. Take input manually " << endl;
            cout << endl << "Choose option: ";
            cin >> option1;
            system("cls");

            if(option1 == 1)
            {
                fstream file;
                file.open("input.txt");
                while(file >> key_word)
                {
                    getline(file >> ws, def);
                    root = Add(root, key_word, def);
                }
                file.close();
            }
            if(option1 == 2)
            {
                cout << "Enter key word to add: ";
                cin >> key_word;
                cout << "Enter definition: ";
                getline(cin >> ws, def);
                root = Add(root, key_word, def);
            }
            cout << endl << "Word(s) added successfully" << endl << endl;
        }
        if(option == 2)
        {
            cout << "Enter key word to search: ";
            cin >> key_word;
            temp = Search(root, key_word);
            if(temp != NULL)
            {
                cout << "The word \"" << key_word << "\" is found" << endl;
                cout << temp->key << ": " << temp->definition << endl;
            }
            else
            {
                cout << "The word \"" << key_word << "\" was not found" << endl;

                vec.clear();
                check(root, key_word[0]);
                if(!vec.empty())
                {
                    cout << "Did you mean";
                    for(int i=0; i<vec.size(); i++)
                    {
                        if(i) cout << ",";
                        printf(" \"%s\"",vec[i].c_str());
                    }
                    cout << " ?" << endl;
                }
            }
            cout << endl;
        }
        if(option == 3)
        {
            cout << "Enter key word to delete: ";
            cin >> key_word;
            root = Delete(root, key_word);
            cout << "Word deleted successfully" << endl << endl;
        }
        if(option == 4)
        {
            if(root == NULL)
            {
                cout << "Dictionary is empty." << endl << endl;
                continue;
            }
            cout << "Dictionary words are: " << endl;
            View_inorder(root);
            cout << endl;
        }
        if(option == 0) break;
    }

    return 0;
}
