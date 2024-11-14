// Yunis Nabiyev
// CECS 325-02
// Prog 6 – BigInt
// Due Date (05/09/2024)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <iomanip> //for setw
#include <vector>
#include <algorithm> //for reverse()
#include <climits> //for INT_MAX

using namespace std;

class BigInt{
    private:
        vector<char> v;
        BigInt fiboHelper(BigInt n, BigInt a = 0, BigInt b = 1){
            if (n == BigInt(0))
                return a;
            else if (n == BigInt(1))
                return b;
            else
                return fiboHelper(n - 1, b, a + b);
        }
    public:
        BigInt (){
            v = vector<char>();
        }
    
        BigInt (int integer){
            v = vector<char>();
            //Iterate through each digit right to left and add it to the vector, then reverse it
            bool isnegative = false;
            if(integer < 0){
                isnegative = true;
                integer *= -1; //convert to positive
            }
            else if(integer == 0){
                v.push_back('0');
                return;
            }
            
            while (integer > 0){
                char ch = static_cast <char>((integer % 10) + 48);	//0 starts at ascii 48
                v.push_back (ch);
                integer /= 10;
            }
            if(isnegative){
                v.push_back('-'); //add a negative sign
            }
            reverse (v.begin(), v.end());
        }
    
        BigInt (string str){
            v = vector<char>();
            //Go through each character, checking if it's a number and if so add it to v, otherwise reset v and throw exception
            if(str == "0"){
                v = vector<char>{'0'}; 
                return;
            }
            if(str[0] == '-'){
                v.push_back('-');
            }
            for (char ch : str){
                if (('0' <= ch && ch <= '9')){
                    v.push_back(ch);
                }
                else if(ch != '-'){
                    throw invalid_argument ("string contains non-numeric");
                }
            }
        }
    
        BigInt operator+ (BigInt other){
            // this + other
            if(*this < BigInt(0)){ //this is negative
                BigInt t(*this);
                t.v.erase(t.v.begin()); //erase negative
                return other - t; // -x + y == y - x
            }
            if(other < BigInt(0)){//other is negative
                BigInt o(other);
                o.v.erase(o.v.begin()); //erase negative
                return (*this - o); // x + -y == x - y
            }
            
            int carry = 0;
            string result = "";
            int i = size() - 1;
            int j = other.size() - 1;

            while(i >= 0 || j >= 0 || carry){ //while we haven't reached the end of this, other, or there's a carry
                int sum = carry; //add carry to sum
                if(i >= 0){ //if we haven't reached the end of this
                    sum += int(v[i])-48; // convert char into respective int and add to sum
                    i--; //to go to next digit
                }
                if(j >= 0){ // if we haven't reached the end of other
                    sum += int(other[j])-48;  // convert char to respective int and add to sum
                    j--; //to go to next digit
                }
                carry = sum / 10; //store the 10's place of sum as the carry (in this case carry will be either 0 or 1)
                sum = sum % 10;
                result = char(sum+48) + result; //store the 1's place of sum (converted to a string) into result
            }
            
            return BigInt(result); //convert string to BigInt and return
        }
    
        BigInt operator- (BigInt other){
            // this - other
            if(*this < BigInt(0)){ //this is negative
                BigInt t(*this);
                t.v.erase(t.v.begin());
                return ((t + other) * BigInt(-1)); // -x - y == (x + y) * -1
            }
            if(other < BigInt(0)){//other is negative
                BigInt o(other);
                o.v.erase(o.v.begin());
                return (*this + o); // x - -y == x + y
            }
            //both are positive
            if(*this < other){
                return ((other-*this) * BigInt(-1));
            }

            int carry = 0;
            int i = size()-1;
            int j = other.size()-1;
            string result = "";
            
            while(i >= 0 || j >= 0){ //while we can traverse this or other
                int sub = 0; //default sub to 0
                if(i >= 0){ //if there are digits in this
                    sub = int(v[i])-48; //set sub to this digit
                    i--; //go to next digit
                }
                sub -= carry; //subtract any carry
                if(j >= 0){ //if there are still digits in other
                    sub -= int(other[j])-48; //subtract other digit from sub
                    j--; //go to next digit
                }
                carry = sub < 0; //if sub is negative, set carry to 1, otherwise 0
                sub = (sub+10)%10; //if sub is positive this will just get the one's place. 
                //If sub is negative we "carry over" 10 from the next digit (which we subtract from and keep track with carry)
                //The idea is that: (3 - 8)+10 == 3+10 - 8
                //anyways moving on
                result = char(sub+48) + result; //store the digit into result
            }
            
            //remove preceding 0's
            while(result[0] == '0' && result.size() > 1){ //if there is a 0 at the beginning and result isn't just a zero
                result.erase(result.begin()); //remove it
            }
            return BigInt(result);//return result
        }
    
        BigInt operator- (int other)
        {
            return *this - BigInt(other); //just convert the int to a BigInt and subtract
        }
        
        BigInt operator+ (int other){
            return *this + BigInt(other); //same as above but for addition
        }
    
        BigInt operator* (BigInt other){
            if(other == BigInt(0)){ // anything * 0 = 0
                return BigInt(0);
            }
            else if(other == BigInt(1)){ //anything * 1 = anything
                return *this;
            }
            else if(other == BigInt(-1)){ // anything * -1 = -(anything)
                if(*this == BigInt(0)){ // 0 * -1 = 0
                    return BigInt(0);
                }
                BigInt temp(*this);
                if(v[0] == '-'){ //if this is negative
                    temp.v.erase(temp.v.begin()); //remove negative
                }
                else{
                    temp.v.insert(temp.v.begin(), '-'); //place negative sign at front
                }
                return temp;//return the BigInt
            }
            else if(*this < BigInt(0)){ //this is negative
                BigInt t(*this);
                t.v.erase(t.v.begin());
                return ((t * other) * BigInt(-1)); // -x * y == (x * y) * -1
            }
            //this is positive
            else if(other < BigInt(0)){ //other is negative
                BigInt o(other);
                o.v.erase(o.v.begin());
                return ((*this * o) * BigInt(-1)); // x * -y == (x * y) * -1
            }
            else{ //both are positive
                if(*this < other){ //for faster calculation, multiplication is commutative
                    return other * *this;
                }
                else{
                    BigInt sum(0);
                    BigInt counter(other);
                    for(BigInt i(other); i > BigInt(0); i = i - 1){ // repeated addition
                        sum = sum + *this;
                    }
                    return sum;
                }
            } 
        }
    
        BigInt operator/ (BigInt other){
            if(other == BigInt(0)){ // anything / 0 = undef
                throw invalid_argument("Division by zero!");
            }
            else if(other == BigInt(1)){ // anything / 1 = anything
                return *this;
            }
            else if(other == BigInt(-1)){ //same result as multiply by -1
                return *this * BigInt(-1);
            }
            else if(*this < BigInt(0)){ //this is negative
                BigInt t(*this);
                t.v.erase(t.v.begin());
                return ((t / other) * BigInt(-1)); // -x / y == (x / y) * -1
            }
            //this is positive
            else if(other < BigInt(0)){ //other is negative
                BigInt o(other);
                o.v.erase(o.v.begin());
                return ((*this / o) * BigInt(-1)); // x / -y == (x / y) * -1
            }
            else{//both are positive
                BigInt counter(0);
                BigInt sub(*this);
                while(sub >= other){ //it's just repeated subtraction, we just want to know how many times we subtracted
                    counter = counter + 1;
                    sub = sub - other;
                }
                return counter;
            } 
        }
        
        BigInt operator% (BigInt other){
            if(other == BigInt(0)){ //anything % 0 = undef
                throw invalid_argument("Division by zero!");
            }
            else if(other == BigInt(1) || other == BigInt(-1)){ // anything % 1/-1 = 0
                return BigInt(0);
            }
            else if(*this > BigInt(0) && other > BigInt(0)){ //both are positive
                BigInt counter(0);
                BigInt sub(*this);
                while(sub >= other){
                    sub = sub - other;
                }
                return sub;
                
            }
            else if(*this < BigInt(0) && other < BigInt(0)){ // both are negative
                BigInt counter(0);
                BigInt sub(*this);
                while(sub <= other){
                    sub = sub - other;
                }
                return sub;
            }
            else{//either has opposing signs
                if(*this < other){//this is negative, other is positive
                    BigInt temp(*this);
                    while(temp < BigInt(0)){
                        temp = temp + other;
                    }
                    return temp;
                }
                else{//this is positive, other is negative
                    BigInt temp(*this);
                    BigInt o(other*BigInt(-1)); //make other positive
                    while(temp > BigInt(0)){
                        temp = temp - o;
                    }
                    return temp;
                }
            }
        }
        
        BigInt operator++ (int){
            BigInt temp(*this);
            *this = *this + 1;
            return temp;
        }
    
        BigInt operator++ (){
            *this = *this + 1;
            return *this;
            
        }
    
        char operator[](int index){					// index function, idk why this had a return value of BigInt when it should be char
            return v[index];
        }
    
        bool operator== (BigInt other){
            if (v.size () != other.size ()){
                return false;
            }
            for (int i = 0; i < size (); i++){
                if (v[i] != other[i]){
                    return false;
                }
            }
            return true;
        }
        
        bool operator!= (BigInt other){
            return !(*this == other);
        }
        
        bool operator< (BigInt other){
            if(v[0] == '-'){ //this is negative
                if(other[0] != '-'){ //other is positive
                    return true;
                }
                //both negative
                else if(v.size() < other.size()){ //this has less digits, meaning other is more negative, meaning it is less
                    return false;
                }
                else if(v.size() > other.size()){//this has more digits, meaning this is more negative, meaning it is less
                   return true;
                }
                //both are of equal size
                else{
                    for(int i = 0; i < size(); i++){
                        if(v[i] < other[i]){ //this digit is smaller, meaning other is more negative, meaning it is less
                            return false;
                        }
                        else if(v[i] > other[i]){ //this digit is larger, meaning this is more negative, meaning it is less
                            return true;
                        }
                    }
                    return false; //they are equal
                }
            }
            else{ //this is positive
                if(other[0] == '-'){ //other is negative
                    return false;
                }
                //both positive
                else if(v.size() < other.size()){ //this has less digits, meaning other is more positive, meaning this is less
                    return true;
                }
                else if(v.size() > other.size()){//this has more digits, meaning this is more positive, meaning other is less
                   return false;
                }
                //both are of equal size
                else{
                    for(int i = 0; i < size(); i++){
                        if(v[i] < other[i]){ //this digit is smaller, meaning other is more positive, meaning this is less
                            return true;
                        }
                        else if(v[i] > other[i]){ //this digit is larger, meaning this is more positive, meaning other is less
                            return false;
                        }
                    }
                    return false; //they are equal
                }
            }
        }
        
        bool operator <= (BigInt other){ // less than OR equal to
            return (*this < other) || (*this == other);
        }
        
        bool operator> (BigInt other){ // greater than == !less than
            if(*this == other){
                return false;
            }
            else{
                return !(*this<other);
            }
        }
        
        bool operator >= (BigInt other){ // greater than OR equal to
            return (*this > other) || (*this == other);
        }
    
        void print (){
            string str = ""; 
            for (int i = 0; i < v.size (); i++){
                str += v[i];
            }
            cout << str << endl;
        }
    
        int size (){
            return v.size();
        }
    
        BigInt fibo (){		// calls fiboHelper
            return fiboHelper(*this);
        }
        
        BigInt fact (){ //simple factorial algorithm converted to use BigInt operators
            if (*this == BigInt(0))
                return BigInt(1);
            BigInt i(*this);
            BigInt fact(1);
            while ((*this / i) != *this) {
                fact = fact * i;
                i = i - 1;
            }
            return fact;
        }
    	   
        friend ostream& operator<< (ostream & os, const BigInt& bi){
            BigInt temp = bi;
            string str = "";
            if(temp[0] == '-' && temp.size() > 13){//if negative and there are 12 digits (13 since '-' is technically a digit)
                str = temp[0]; //add negative
                str += temp[1]; //add first digit
                str += '.'; //add decimal
                for(int i = 0; i < 6; i++){
                    str += temp[i+2];
                }
                str += 'e';
                str += to_string(temp.size()-2);
            }
            else if(temp.size() > 12){ //if more than 12 digits
                str = temp[0]; //add first digit
                str += '.'; //add decimal
                for(int i = 0; i < 6; i++){
                    str += temp[i+1];
                }
                str += 'e';
                str += to_string(temp.size()-1);
            }
            else{ //print normally
                for (int i = 0; i < temp.size(); i++){
                    str += temp[i];
                }
            }
            return os << str;
        }
        
        friend BigInt operator+ (int integer, BigInt other){
            return BigInt(integer) + other;
        }
}; 
	   
void testUnit (){
   int space = 10;
   cout << "\a\nTestUnit:\n" << flush;
   system ("whoami"); 
   system ("date");
   // initialize variables
   BigInt n1 (25);
   BigInt s1 ("25");
   BigInt n2 (1234);
   BigInt s2 ("1234");
   BigInt n3 (n2);
   BigInt fibo (12345);
   BigInt fact (50);
   BigInt imax = INT_MAX; BigInt big ("9223372036854775807");
   // display variables
   cout << "n1(int) :" << setw (space) << n1 << endl;
   cout << "s1(str) :" << setw (space) << s1 << endl;
   cout << "n2(int) :" << setw (space) << n2 << endl;
   cout << "s2(str) :" << setw (space) << s2 << endl;
   cout << "n3(n2) :" << setw (space) << n3 << endl;
   cout << "fibo(12345):" << setw (space) << fibo << endl;
   cout << "fact(50) :" << setw (space) << fact << endl;
   cout << "imax :" << setw (space) << imax << endl;
   cout << "big :" << setw (space) << big << endl;
   cout << "big.print(): "; big.print (); cout << endl;
  cout << n2 << "/"<< n1<< " = "<< n2/n1 <<" rem "<<n2%n1<<endl;
  cout << "fibo("<<fibo<<") = "<<fibo.fibo() << endl;
  cout << "fact("<<fact<<") = "<<fact.fact() << endl;
  cout << "10 + n1 = " << 10+n1 << endl;
  cout << "n1 + 10 = " << n1+10 << endl;
  cout << "(n1 == s1)? --> "<<((n1==s1)?"true":"false")<<endl;
  cout << "n1++ = ? --> before:"<<n1++<<" after:"<<n1<<endl;
  cout << "++s1 = ? --> before:"<<++s1<<" after:"<<s1<<endl;
  cout << "s2 * big = ? --> "<< s2 * big<<endl;
  cout << "big * s2 = ? --> "<< big * s2<<endl;
}

void operatorTest (){
   srand (time (0));
   int space = 10;
   cout << "\a\nOperatorTest:\n" << flush;
   system ("whoami"); system ("date");
   // initialize variables
   int doNegatives = -1;//(rand()%2) == 0 ? 1 : -1;

   //multiplication waiting game, set to lower numbers
   int a = (rand () % (10000 - 0 + 1) + 0)* ((rand()%2) == 0 ? 1 : -1);
   int b = (rand () % (10000 - 0 + 1) + 0)* ((rand()%2) == 0 ? 1 : -1);
   int c = (rand () % (1000000000 - 0 + 1) + 0)* ((rand()%2) == 0 ? 1 : -1);
   int d = (rand () % (1000000000 - 0 + 1) + 0)* ((rand()%2) == 0 ? 1 : -1);
   BigInt zero (0);
   BigInt negone (-1);
   BigInt n1 (a);
   BigInt s1 (to_string(b));
   BigInt n2 (c);
   BigInt s2 (to_string(d));
   BigInt n3 (n2);
   BigInt imax = INT_MAX; BigInt big ("9223372036854775807");
   // display variables
   
   cout << "zero(int) :" << setw (space) << zero << endl;
   cout << "negone(int) :" << setw (space) << negone << endl;
   cout << "n1(int) :" << setw (space) << n1 << endl;
   cout << "s1(str) :" << setw (space) << s1 << endl;
   cout << "n2(int) :" << setw (space) << n2 << endl;
   cout << "s2(str) :" << setw (space) << s2 << endl;
   cout << "n3(n2) :" << setw (space) << n3 << endl;
   cout << "imax :" << setw (space) << imax << endl;
   cout << "big :" << setw (space) << big << endl;
   cout << "big.print(): "; big.print (); cout << endl;
   
   // comparison test
   cout << "n1 > s1?: " << setw (space) << (n1 > s1) << "(" << (a>b) << ")" << endl;
   cout << "n2 > s2?: " << setw (space) << (n2 > s2) << "(" << (c>d) << ")" << endl;
   cout << "n1 > n2?: " << setw (space) << (n1 > n2) << "(" << (a>c) << ")" << endl;
   cout << "s1 > s2?: " << setw (space) << (s1 > s1) << "(" << (b>d) << ")" << endl;
   // > passed
   cout << "n1 >= s1?: " << setw (space) << (n1 >= s1) << "(" << (a>=b) << ")" << endl;
   cout << "n2 >= s2?: " << setw (space) << (n2 >= s2) << "(" << (c>=d) << ")" << endl;
   cout << "n1 >= n2?: " << setw (space) << (n1 >= n2) << "(" << (a>=c) << ")" << endl;
   cout << "s1 >= s2?: " << setw (space) << (s1 >= s1) << "(" << (b>=d) << ")" << endl;
   // >= passed
   cout << "n1 < s1?: " << setw (space) << (n1 < s1) << "(" << (a<b) << ")" << endl;
   cout << "n2 < s2?: " << setw (space) << (n2 < s2) << "(" << (c<d) << ")" << endl;
   cout << "n1 < n2?: " << setw (space) << (n1 < n2) << "(" << (a<c) << ")" << endl;
   cout << "s1 < s2?: " << setw (space) << (s1 < s1) << "(" << (b<d) << ")" << endl;
   // < passed
   cout << "n1 <= s1?: " << setw (space) << (n1 <= s1) << "(" << (a<=b) << ")" << endl;
   cout << "n2 <= s2?: " << setw (space) << (n2 <= s2) << "(" << (c<=d) << ")" << endl;
   cout << "n1 <= n2?: " << setw (space) << (n1 <= n2) << "(" << (a<=c) << ")" << endl;
   cout << "s1 <= s2?: " << setw (space) << (s1 <= s1) << "(" << (b<=d) << ")" << endl;
   // <= passed
   
   // arithmatic test
   cout << "100 + -10 = " << setw (space) << BigInt(100) + BigInt(-10) << "(" << 100+(-10) << ")" << endl;
   cout << "-100 + -10 = " << setw (space) << BigInt(-100) + BigInt(-10) << "(" << (-100) + (-10) << ")" << endl;
   cout << "n1 + s1 = " << setw (space) << n1 + s1 << "(" << a+b << ")" << endl;
   cout << "n2 + s2 = " << setw (space) << n2 + s2 << "(" << c+d << ")" << endl;
   cout << "n1 + n2 = " << setw (space) << n1 + n2 << "(" << a+c << ")" << endl;
   cout << "s1 + s2 = " << setw (space) << s1 + s2 << "(" << b+d << ")" << endl;
   // + passed for positive, negative, and mixed
   cout << "100 - -10 = " << setw (space) << BigInt(100) - BigInt(-10) << "(" << 100-(-10) << ")" << endl;
   cout << "-100 - -10 = " << setw (space) << BigInt(-100) - BigInt(-10) << "(" << (-100) - (-10) << ")" << endl;
   cout << "n1 - s1 = " << setw (space) << n1 - s1 << "(" << a-b << ")" << endl;
   cout << "n2 - s2 = " << setw (space) << n2 - s2 << "(" << c-d << ")" << endl;
   cout << "n1 - n2 = " << setw (space) << n1 - n2 << "(" << a-c << ")" << endl;
   cout << "s1 - s2 = " << setw (space) << s1 - s2 << "(" << b-d << ")" << endl;
   // - passed for positive, negative, and mixed
   //Due to overflow, the answers in parans may be wrong
   cout << "100 * -10 = " << setw (space) << BigInt(100) * BigInt(-10) << "(" << 100*(-10) << ")" << endl;
   cout << "-100 * -10 = " << setw (space) << BigInt(-100) * BigInt(-10) << "(" << (-100) * (-10) << ")" << endl;
   cout << "n1 * s1 = " << setw (space) << n1 * s1 << "(" << a*b << ")" << endl;
   cout << "n2 * s2 = " << setw (space) << n2 * s2 << "(" << c*d << ")" << endl;
   cout << "n1 * n2 = " << setw (space) << n1 * n2 << "(" << a*c << ")" << endl;
   cout << "s1 * s2 = " << setw (space) << s1 * s2 << "(" << b*d << ")" << endl;
   // * passed for positive, negative, and mixed
   cout << "100 / -10 = " << setw (space) << BigInt(100) / BigInt(-10) << "(" << 100/(-10) << ")" << endl;
   cout << "-100 / -10 = " << setw (space) << BigInt(-100) / BigInt(-10) << "(" << (-100) / (-10) << ")" << endl;
   cout << "n1 / s1 = " << setw (space) << n1 / s1 << "(" << a/b << ")" << endl;
   cout << "n2 / s2 = " << setw (space) << n2 / s2 << "(" << c/d << ")" << endl;
   cout << "n2 / n1 = " << setw (space) << n2 / n1 << "(" << c/a << ")" << endl;
   cout << "s2 / s1 = " << setw (space) << s2 / s1 << "(" << d/b << ")" << endl;
   // / passed for positive, negative, and mixed
   //For some reason the answer in parans, when mixing negative and positive numbers, returns the left number ? my implement works though
   cout << "100 % -10 = " << setw (space) << BigInt(100) % BigInt(-10) << "(" << 100%(-10) << ")" << endl;
   cout << "-100 % -10 = " << setw (space) << BigInt(-100) % BigInt(-10) << "(" << (-100) % (-10) << ")" << endl;
   cout << "n1 \% s1 = " << setw (space) << n1 % s1 << "(" << a%b << ")" << endl;
   cout << "n2 \% s2 = " << setw (space) << n2 % s2 << "(" << c%d << ")" << endl;
   cout << "n1 \% n2 = " << setw (space) << n1 % n2 << "(" << a%c << ")" << endl;
   cout << "s1 \% s2 = " << setw (space) << s1 % s2 << "(" << b%d << ")" << endl;
   // % passed for positive, and mixed
}

int main ()
{
    //operatorTest ();
    testUnit();
}