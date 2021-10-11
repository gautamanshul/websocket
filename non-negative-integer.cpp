#include <vector>
#include <iostream>
#include <sstream>
#include <stack>
#include <algorithm>

using namespace std;

const int32_t UINT20_MIN = 0;
const int32_t UINT20_MAX = 0xfffff;

vector<string> extractWords_v1(const string& str)
{
    vector<string> words;
    // word variable to store word
    string word;

    // making a string stream
    stringstream iss(str);

    // Read and print each word.
    while (iss >> word)
        words.push_back(word);

    return words;
}

void throwIfEmpty_v1(const string& op, const stack<int32_t>& numStack)
{
    if (numStack.empty())
    {
        throw runtime_error(op + " called with empty stack");
    }
}

void throwIfNotEnough_v1(const string& op, const stack<int32_t>& numStack)
{
    if (numStack.size() < 2)
    {
        throw runtime_error(op + " called with less than 2 numbers on stack");
    }
}

int32_t solution_v1(string& s)
{
    auto ops = extractWords_v1(s);
    if (ops.empty()) {
        cerr << "Empty list of operations";
    }
    stack<int32_t> numStack;
    try
    {
        for (auto& op : ops)
        {
            transform(op.begin(), op.end(), op.begin(), ::toupper);
            if (op == "POP")
            {
                throwIfEmpty_v1(op, numStack);
                numStack.pop();
            }
            else if (op == "DUP")
            {
                throwIfEmpty_v1(op, numStack);
                numStack.push(numStack.top());
            }
            else if (op == "+" || op == "-")
            {
                if (numStack.size() < 2)
                {
                    throw runtime_error(op + " called with empty stack");
                }
                int32_t first = numStack.top();
                numStack.pop();
                int32_t second = numStack.top();
                numStack.pop();
                int32_t result = 0;
                if (op == "+")
                {
                    result = first + second;
                }
                else
                {
                    result = first - second;
                }
                if (result >= UINT20_MAX)
                {
                    throw runtime_error(op + " resulted in overflow");
                }
                else if (result < 0)
                {
                    throw runtime_error(op + " resulted in underflow");
                }
                numStack.push(result);
            }
            else
            {
                int32_t result = 0;
                try
                {
                    result = stoi(op);
                }
                catch (const exception & e)
                {
                    throw runtime_error("Failed to push invalid number " + s);
                }
                if (result >= UINT20_MAX)
                {
                    throw runtime_error("push " + op + " resulted in overflow");
                }
                else if (result < 0)
                {
                    throw runtime_error("push " + op + " resulted in underflow");
                }
                numStack.push(result);
            }
        }
        if (numStack.empty())
        {
            throw runtime_error("Stack is empty after all operations");
        }
        return numStack.top();
    }
    catch (const exception & e)
    {
        cerr << e.what() << endl;
    }

    return -1;
}


int main_nonnegative()
{
    std::string ops = "+ DUP POP";

    auto res = solution_v1(ops);

    std::cout << "Result is " << res << std::endl;
    return 0;
}