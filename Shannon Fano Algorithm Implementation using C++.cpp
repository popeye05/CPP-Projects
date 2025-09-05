#include<iostream>
#include <algorithm>
#include <string>
#include<vector>
#include <unordered_map>
//Everything can be done using #include<bits/stdc++.h> My DEVC++ doesn't support it thats why ive done this way..
using namespace std;
class symbol
{
public:
	char ch; //The Characters of String
	int prob;	//The Probabilites of each Symbol
	string code; //As the name suggests, code is stored here on the class.
	
	// My Custom constructor, But lets not do it to avoid ambiguity:
	/*symbol(char ch,int freq,string code)
	{
		this->ch=ch;
		 prob =freq;
		this -> code =code;
	}*/
};
//One Comparator to check the Freq. of the symbols:
bool cmprefreq(symbol &a,symbol &b)
{
	return a.prob > b.prob;
}

void sfano(vector<symbol*> &arr, int l, int r) //We reference Symbol addresses.
{
	if(l>=r) return;
	//Otherwise
	int total = 0,i;
	for(i=l;i<=r;i++) total += arr[i]->prob;
	int half =total/2,sum=0,mid=l;
	//We now check upto how much a group is permissible
	for(i=l;i<=r;i++)
	{
		sum+= arr[i]->prob;
		if(sum>=half) {mid=i; break;}
	} 
	//Now according to Shannon fano tree , The left hand is assigned 
//	with 0 in practice and the right half with 1.
	
	for(i=l;i<=mid;i++) arr[i]->code += "0";
	for(i=mid+1;i<=r;i++) arr[i]->code += "1";
	
	//Now I will recursively call the function for teh left half and right half respectively...
	sfano(arr,l,mid);//For the left half.
	sfano(arr,mid+1,r); //For the right half.
}


int main()
{
	//-----------------------------------------------------------------------------------------------------
	string message;
	cout<<"This is a Shannon Fano Encoder program.\n"<<"Write your Message: ";
	getline(cin,message);	
	//In a string the frequency of characters can be used for the probability itself!
	//Thus we can easily count the frequency using a hashmap
	unordered_map<char,int> freq;
	for (char c : message) freq[c]++;
	//Now we need the symbol array:
	vector<symbol> symbols;//A vector of the class Symbol is created!
	for(auto &i: freq) symbols.push_back({i.first,i.second,""}); //Key is the character, Value is freq;
	sort(symbols.begin(), symbols.end(), cmprefreq);
	vector<symbol *> ptrs; 
	for(auto &s: symbols) ptrs.push_back(&s);
	//Complete Code!
	
	//------------------------------------------------------------------------------------------------------
	
  	sfano(ptrs, 0, ptrs.size()-1); //Function Call
   //finally  we will be printing it: 
	//i.e.
   cout << "\nShannon-Fano Encoded Output is:\n";
    for (auto &s : symbols) {
        cout << s.ch << " : " << s.code << "\n";
    }
}
