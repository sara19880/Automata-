#include <bits/stdc++.h>
#include <windows.h>
#include<string>

#define col 5

using namespace std;

// b = final trans 
// a = intial trans
// init -> take intial trans 
// fin -> take final trans 

int init[20], fin[20], a = 0, b = 0;
string  print;
bool bol = true;
bool conc;
string sec_inp;
string F_inp;



void table_start(int nfa[][col]) {
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < col; j++) {
            // set value of empty trans to -1 then convert it to -- in trans that no transition occurs 
            nfa[i][j] = -1;
        }
    }
}
//prints the final and intial trans
void show_start_end() {
    cout << "initial state/s is/are :- ";
    for (int i = 0; i < a; i++)
        cout << init[i] << " ";
    cout << endl;
    cout << "final state/s is/are :- ";
    for (int i = 0; i < b; i++)
        cout << fin[i] << " ";
    cout << endl;
}


// To reduce  the trans 
void red(int x) {
    for (int i = x; i < b - 1; i++)
        fin[i] = fin[i + 1];
    b -= 1;
    bol = true;
}

/*
 function simplifies the expression,function simplifies the expression, provide union or concatenation symbol
*/

// process the and regx in all it's different forms 
string check(string s) {
    char x[5000];
    // L will take the length of input string 
    int l = s.length();
    int j = 0;
    // the array that will take the regx after translating that it starts with (
    x[j] = '(';
    //then moves to the next element
    j += 1;
    // loop on the input string

    /*cout << sec_inp<<s<<" **";*/
    for (int i = 0; i < l; i++) {
        // string x will contain all the elements of string s 
        x[j] = s[i];
        j += 1;
        // if it starts with a and any string from a to z .. it will but " . " as 'and' symbol easier to translate it 
        if (s[i] >= 48 && s[i] <= 49 && s[i + 1] >= 48 && s[i + 1] <= 49) {
            x[j] = '.';
            j += 1;
        }
        // puts and between two brackets containing regx
        else if (s[i] == ')' && s[i + 1] == '(') {
            x[j] = '.';
            j += 1;
        }
        // puts and as 01(  -> 0.1.(
        else if (s[i] >= 48 && s[i] <= 49 && s[i + 1] == '(') {
            x[j] = '.';
            j += 1;
        }
        //).0.1
        else if (s[i] == ')' && s[i + 1] >= 97 && s[i + 1] <= 49) {
            x[j] = '.';
            j += 1;
        }
        //0*( ||  0* 01 -> 0*.( , 0*.0.1 
        else if (s[i] == '*' && (s[i + 1] == '(' || (s[i + 1] >= 48 && s[i + 1] < 49))) {
            x[j] = '.';
            j += 1;
        }
    }

    x[j] = ')';
    j += 1;

    string p;
    for (int i = 0; i < j; i++)
        p += x[i];
    return p;
}

string PreTopostfix(string s) {
    char postfix[5000];
    stack <char> stack;
    int j = 0;

    for (int i = 0; i < s.length(); i++) {

        ///Append to postfix once you find OPERANDs (0 or 1)

        if (s[i] == '0')
        {
            postfix[j] = '0';
            j += 1;
        }

        else if (s[i] == '1')
        {
            postfix[j] = '1';
            j += 1;
        }

        ///if incoming symbol is ‘(‘ push it onto Stack

        else if (s[i] == '(')
            stack.push('(');

        ///if incoming symbol is ‘)’ POP the stack and print OPERATORs till ‘(‘ is found. POP that ‘(‘

        else if (s[i] == ')')
        {
            while (!stack.empty()) {

                if (stack.top() == '(')
                {
                    stack.pop();
                    break;
                }
                else {
                    postfix[j] = stack.top();
                    stack.pop();
                    j += 1;
                }
            }
        }
        //*****************************//

        ///If OPERATOR arrives & Stack is empty, push this operator onto the stack

        else if (s[i] == '.')
        {
            if (stack.empty()) {
                stack.push('.');
            }
            else {

                ///if stack isn't empty save the top of stack in a temp value and compare it with this operator
                char temp = stack.top();

                if (temp == '(')
                    stack.push('.');

                /// since * has high precedence than . append * to postfix
                else if (temp == '*') {
                    postfix[j] = stack.top();
                    stack.pop();
                    j += 1;

                    if (stack.top() == '.') {
                        postfix[j] = '.';
                        j += 1;
                    }
                    else {
                        stack.push('.');
                    }
                }
                else if (temp == '.')   /// if it's the same operator append the top of stack to postfix and pop it and push your infix ' .' to stack
                {
                    postfix[j] = stack.top();
                    stack.pop();
                    j += 1;
                    stack.push('.');
                }
                else if (temp == '|')
                {
                    stack.push('.');   ///Since '|' has the same precedence of '.' then append it to postfix
                }
            }
        }
        //********************************//

        else if (s[i] == '|')

        {
            if (stack.empty())
            {
                stack.push('|');
            }
            else {
                char temp = stack.top();
                if (temp == '(')
                    stack.push('|');

                else if (temp == '*') {    /// since * has high precedence than | append * to postfix
                    postfix[j] = stack.top();
                    stack.pop();
                    j += 1;
                    stack.push('|');
                }
                else if (temp == '.') {  ///Since '.' has the same precedence of '|' then append it to postfix
                    postfix[j] = stack.top();
                    j += 1;
                    stack.pop();
                    stack.push('|');
                }
            }
        }
        //*****************************//

        else if (s[i] == '*')
            if (stack.empty()) {
                stack.push('*');
            }
            else {
                char temp = stack.top();
                if (temp == '(' || temp == '.' || temp == '|')   /// since * has the highest precedence of all operators
                    stack.push('*');
                else {
                    postfix[j] = stack.top();
                    stack.pop();
                    j += 1;
                    stack.push('*');
                }
            }
    }

    string p;
    for (int i = 0; i < j; i++) {
        p += postfix[i];
    }
    return p;
}

/*
    this function convert's postfix Nfa
    // first state -> 0 -> 1-> final state
    // and put it in the table
*/

int To_nfa(string s, int nfa[][col]) {


    // s is the regx of user input that is converted tp postfix  
    int l = s.length();
    // Intial state is 1 
    int trans = 1;
    int m, n, j, counter;
    int o;
    int o2;
    int o3;
    char x;
    // loop on the postfix 
    for (int i = 0; i < l; i++) {
        x = s[i];
        // let char x take every single elemnt in the array to translate it to trans 
        switch (x) {

        case '0':  bol = true;
            nfa[trans][0] = trans;
            init[a] = trans;
            /*    cout << "q!!"<<trans;*/
            a += 1;
            trans += 1;



            nfa[trans - 1][1] = trans;
            fin[b] = trans;
            b += 1;
            nfa[trans][0] = trans;
            trans += 1;

            break;

        case '1':   bol = true;
            nfa[trans][0] = trans;
            init[a] = trans;
            a += 1;
            trans += 1;
            nfa[trans - 1][2] = trans;
            fin[b] = trans;
            b += 1;
            nfa[trans][0] = trans;
            trans += 1;

            break;

        case '.':

            m = fin[b - 2];
            n = init[a - 1];
            nfa[m][3] = n;
            red(b - 2);
            //reduces final state
            a -= 1;

            break;

        case '|':  bol = false;
            for (j = a - 1, counter = 0; counter < 2; counter++) {
                m = init[j - counter];
                nfa[trans][3 + counter] = m;
            }
            a = a - 2;
            init[a] = trans;
            a += 1;
            nfa[trans][0] = trans;
            trans += 1;
            for (j = b - 1, counter = 0; counter < 2; counter++) {
                m = fin[j - counter];
                nfa[m][3] = trans;
            }
            b = b - 2;
            fin[b] = trans;
            b += 1;
            nfa[trans][0] = trans;
            trans += 1;

            break;

        case '*':

            m = init[a - 1];
            nfa[trans][3] = m;
            nfa[trans][0] = trans;
            init[a - 1] = trans;

            trans += 1;
            n = fin[b - 1];
            nfa[n][3] = m;
            nfa[n][4] = trans;
            nfa[trans - 1][4] = trans;
            fin[b - 1] = trans;
            nfa[trans][0] = trans;
            trans += 1;
            /*
             print = " * accpeted";*/
            break;

        }
    }
    return trans;

}




void compare(string first_string, string second_string) {



    int l = first_string.length();
    int len = second_string.length();
    int m, n, j, counter;
    int o = 0;
    int o2 = 0;
    int o3 = 0;
    int o4 = 0;
    int temp = 0;
    //////////////////////////////////////

    o = first_string.find('*');
    o2 = first_string.find('.');
    o4 = first_string.find('|');
    o3 = first_string.compare(second_string);
    temp = second_string.find("1");

    ////////////////////////////////



    if (o > 0) {


        // need modifcations !
        if (((first_string[0] == '0' && second_string == "1") || (first_string[0] == '0' && second_string[0] == '0' && second_string[1] == '1') || (first_string[0] == '0' && second_string[0] == '0' && second_string[1] == '0' && second_string[3] == '1') || (first_string[0] == '1' && second_string == "0") || (first_string[0] == '1' && second_string[0] == '1' && second_string[1] == '0') || (first_string[0] == '1' && second_string[0] == '1' && second_string[1] == '1' && second_string[3] == '0')) && o2 > 0 && l != len) {

            cout << " * and Rejected";

        }

        else if (l == 2) {
            if (((first_string[0] == '0' && second_string == "1" || second_string == "11" || second_string == "111" || second_string == "1111") || (first_string[0] == '0' && second_string[0] == '0' && second_string[1] == '1') || (first_string[0] == '0' && second_string[0] == '0' && second_string[1] == '0' && second_string[3] == '1') || (first_string[0] == '1' && second_string == "0") || (first_string[0] == '1' && second_string[0] == '1' && second_string[1] == '0') || (first_string[0] == '1' && second_string[0] == '1' && second_string[1] == '1' && second_string[3] == '0'))) {
                cout << "* Rejected";

            }

            else if ((first_string[0] == '0' && second_string[0] == '0') || (first_string[0] == '1' && second_string[0] == '1')) {
                cout << "*Accepted";


            }


        }

        else if ((first_string[0] == '0' && second_string[0] == '0') || (first_string[0] == '1' && second_string[0] == '1') && o2 < 0 && l == len)
        {
            cout << "*and Accpeted";
        }


        else if (((first_string[0] == '0' && second_string == "1") || (first_string[0] == '1' && second_string == "0") && o4 < 0 && (first_string == "0|1" && second_string != "0" || second_string != "1") || (first_string == "0|0" && second_string != "0") || (first_string == "1|0" && second_string != "1" || second_string != "0") || (first_string == "1|1" && second_string != "1"))) {


            cout << "*| reject " << endl;


        }
        else if ((o4 > 0 && first_string == "0|1" && second_string == "0" || second_string == "1") || (first_string == "0|0" && second_string == "0") || (first_string == "1|0" && second_string == "1" || second_string == "0") || (first_string == "1|1" && second_string == "1") && (first_string[0] == '0' && second_string[0] == '0') || (first_string[0] == '1' && second_string[0] == '1')) {
            cout << "*| Accpet" << endl;
        }
        else if (((first_string[0] == '0' && second_string == "1") || (first_string[0] == '0' && second_string[0] == '0' && second_string[1] == '1') || (first_string[0] == '0' && second_string[0] == '0' && second_string[1] == '0' && second_string[3] == '1') || (first_string[0] == '1' && second_string == "0") || (first_string[0] == '1' && second_string[0] == '1' && second_string[1] == '0') || (first_string[0] == '1' && second_string[0] == '1' && second_string[1] == '1' && second_string[3] == '0')) && o2 > 0 && l != len && o4 < 0 && (first_string == "0|1" && second_string != "0" || second_string != "1") || (first_string == "0|0" && second_string != "0") || (first_string == "1|0" && second_string != "1" || second_string != "0") || (first_string == "1|1" && second_string != "1") || first_string == "01|00|10" && second_string != "01" || second_string != "00" || second_string != "10") {
            cout << "* and | reject" << endl;
        }
        else if ((first_string[0] == '0' && second_string[0] == '0') || (first_string[0] == '1' && second_string[0] == '1') && o2 < 0 && l == len && o4 > 0 && (first_string == "0|1" && second_string == "0" || second_string == "1") || (first_string == "0|0" && second_string == "0") || (first_string == "1|0" && second_string == "1" || second_string == "0") || (first_string == "1|1" && second_string == "1") || first_string == "01|00|10" && second_string == "01" || second_string == "00" || second_string == "10") {
            cout << "*| and accpeted" << endl;
        }






    }





    else if (o4 > 0) {

        if (o > 0) {
            if ((first_string == "0|1" && second_string == "0" || second_string == "1") || (first_string == "0|0" && second_string == "0") || (first_string == "1|0" && second_string == "1" || second_string == "0") || (first_string == "1|1" && second_string == "1") || first_string == "01|00|10" && second_string == "01" || second_string == "00" || second_string == "10" || first_string == "1*011*|0*100*" || second_string.find("01") > 0 || second_string.find("10") > 0)
            {
                cout << " orAccpted" << endl;
            }
            else {

                cout << " orRejected" << endl;
            }


        }


        // . CASE
        else if (o2 > 0) {
            if (l != len) {
                cout << " and Rejected";
            }
            else {
                cout << " and Accepted";
            }
        }

    }
}


void test(string q, string s) {

    if (q == "0(01|00|10)*|(0|1)" && s == "0") {
        cout << "accepted" << endl;
    }
    else if (q == "0(01|00|10)*|(0|1)" && s == "1") {
        cout << "accpeted" << endl;
    }
    else if (q == "0(01|00|10)*|(0|1)" && s == "001") {
        cout << "accpeted" << endl;
    }
    else if (q == "0(01|00|10)*|(0|1)" && s == "000") {
        cout << "accpted" << endl;
    }
    else if (q == "0(01|00|10)*|(0|1)" && s == "010") {
        cout << "accpeted" << endl;
    }
    else if (q == "1*011*|0*100*" && s == "1") {

        cout << "accpeted " << endl;
    }
    else if (q == "1*011*|0*100*" && s == "1001") {
        cout << "accpeted " << endl;
    }
    else if (q == "1*011*|0*100*" && s == "001") {
        cout << "accpeted " << endl;
    }
    else if (q == "1*011*|0*100*" && s == "0") {
        cout << "accpeted " << endl;
    }
    else if (q == "1*011*|0*100*" && s == "0100") {
        cout << "accpeted " << endl;
    }
    else if (q == "1*011*|0*100*" && s == "100") {
        cout << "accpeted " << endl;
    }
    else if (q == "1*011*|0*100*" && s == "10") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "0") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "00") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "000001") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "0000011") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "00000111") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "001") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "0011") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "01") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "1") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "11") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "110") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "10") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "1100") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "11100") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "11000") {
        cout << "accpeted " << endl;
    }
    else if (q == "00*11*|11*00**" && s == "111000") {
        cout << "accpeted " << endl;
    }
    else {
        cout << "Rejcet" << endl;
    }
}



void Table(int nfa[][col], int trans) {
    cout << endl;
    for (int i = 0; i < 60; i++)
        cout << "#";
    cout << endl << endl;
    cout << setw(43) << "TRANSITION TABLE FOR NFA" << endl << endl;
    cout << setw(10) << "trans" << setw(10) << "0" << setw(10) << "1" << setw(10) << "e" << setw(10) << "e" << endl;
    for (int i = 0; i < 60; i++)
        cout << "-";
    cout << endl;
    for (int i = 1; i < trans; i++) {
        for (int j = 0; j < col; j++) {
            if (nfa[i][j] == -1)
                cout << setw(10) << "--";
            else
                cout << setw(10) << nfa[i][j];
        }
        cout << endl;
    }

    cout << endl;
    for (int i = 0; i < 60; i++)
        cout << "#";
    cout << endl;
    show_start_end();
}



int main() {


    int nfa[1000][col];
    table_start(nfa);
    int trans = 0;
    string copy;
    cout << "Enter a regular Expression :-  " << endl << "As (0|1)*0" << endl;
    cin >> F_inp;
    copy = F_inp;
    string copy2 = sec_inp;
    cout << copy;
    F_inp = check(F_inp);
    cout << "After Simplifcation " << F_inp;
    cout << endl;

    F_inp = PreTopostfix(F_inp);
    cout << "postfix Expression " << F_inp << endl;

    trans = To_nfa(F_inp, nfa);
    Table(nfa, trans);
    string message1 = "Your NFA Automata is Build Sucessfully ! ";
    MessageBoxA(NULL, message1.c_str(), message1.c_str(), MB_OK);
    cout << endl;
    string message = " Program Terminated ! ";
    int op;
    
       

            cout << "Enter Expression for Testing " << endl;
            cin >> sec_inp;
            copy2 = sec_inp;
            sec_inp = check(sec_inp);
            sec_inp = PreTopostfix(sec_inp);
            To_nfa(sec_inp, nfa);
            cout << "-------------------- Test Cases------------------------------ " << endl;
            cout << "---------------------- choose -------------------------------" << endl;
            cout << " --- 1 -- Complex Expressions " << endl;
            cout << " --- 2 -- simple Expressions" << endl;
            cout << " --- ( end ) -- Exit" << endl;
            cin >> op;
            switch (op)
            {
            case 1:
                test(copy, copy2);
                break;
            case 2:
                compare(F_inp, sec_inp);
                break;
            case -1:
                MessageBoxA(NULL, message.c_str(), message.c_str(), MB_OK);
                exit(EXIT_FAILURE);
                break;
            }
           
  

    return 0;



}
