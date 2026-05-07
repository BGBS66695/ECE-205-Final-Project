#include <cmath>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

struct Node { //structure for tree node
    string data;
    Node* left;
    Node* right;
};

Node* createnode(string value) //create the node
{
    Node* newNode = new Node();
    newNode -> data = value;
    newNode -> left = nullptr;
    newNode -> right = nullptr;
    return newNode;
}

int prece(char a)//multiplication and division is calculated first
{
    if (a == '*' || a == '/')
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

string transfer(string expr)
{
    stack<char> st;
    string result;
    for (int i = 0; i < expr.length(); i++)
    {
        char a = expr[i];
        if (a >= '0' && a <= '9')//if it is a digit, add to the output
        {
            string num = "";
            while (i < expr.length() && expr[i] >= '0' && expr[i] <= '9')
            {
                num +=expr[i];
                i++;
            }
            result += num + " ";
            i--;
            
        }
        else if (a == '(')//if it is a "(", push it to the stack
        {
            st.push('(');
        }
        else if (a == ')')//if it is a ")", pop and to output string from the stack
        {
            while(!st.empty() && st.top() != '(')
            {
                result += st.top();
                result += " ";
                st.pop();
            }
            st.pop();
        }
        else//if it is a operator, pop operators with higher precedence
        {
            while (!st.empty() && prece(expr[i]) <= prece(st.top()) && st.top() != '(')
            {
                result += st.top();
                result += " ";
                st.pop();
            }
            st.push(a);
        }
    }
    while (!st.empty())
        {
            result += st.top();
            result += " ";
            st.pop();
        }
    

    return result;
}

bool isoper(char a)//determine whether is a operator
{
    if (a == '*' || a == '/' || a == '+' || a == '-')
    {
        return true;
    }
    else
    {
        return false;
    }
}

Node* constructtree(string newexpr)
{
    stack<Node*> st;
    Node* t, * t1, * t2;

    for (int i = 0; i < newexpr.length(); i++)
    {
        if (newexpr[i] == ' ')//bypass space
        {
            continue;
        }
        if (!isoper(newexpr[i]))//if detect a digit, create tree node
        {
            string num = "";
            while (i < newexpr.length() && newexpr[i] >= '0' && newexpr[i] <= '9')
            {
                num += newexpr[i];
                i++;
            }
            i--;
            t = createnode(num);
            st.push(t);
        }
        else
        {
            string a = "";//convert to string and create operator node
            a += newexpr[i];
            t = createnode(a);
            
            t1 = st.top();
            st.pop();
            t2 = st.top();
            st.pop();

            t->right = t1;
            t->left = t2;
            st.push(t);
        }
        
    }
    t = st.top();
    st.pop();
    return t;
    
}

void printTree(Node* root, int space = 0, int height = 5) {//print the tree
    if (root == nullptr) return;
    space += height;
    printTree(root->right, space);
    cout << endl;
    for (int i = height; i < space; i++)
        cout << " ";
    cout << root->data << "\n";
    printTree(root->left, space);
}

int caltree(Node* tree)
{
    if (tree -> data[0] >= '0' && tree -> data[0] <= '9')//return a number if detected
    {
        return stoi(tree->data);
    }

    int left = caltree(tree->left);//recursion
    int right = caltree(tree->right);
    if (tree->data == "+")
    {
        return left + right;
    }
    else if (tree->data == "-")
    {
        return left - right;
    }
    else if (tree->data == "*")
    {
        return left * right;
    }
    else
    {
        return left / right;
    }
}

int main() {
    string expr;
    cout << "Please enter the expression" <<endl;//get the input
    cin >> expr;

    string newexpr = transfer(expr);

    cout << "postfix expression is: " << newexpr << endl;

    Node* tree = constructtree(newexpr);
    printTree(tree);
    
    int result = caltree(tree);

    cout << "The result is: " << result << endl;

    return 0;
}