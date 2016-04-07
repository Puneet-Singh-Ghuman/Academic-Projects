#include<algorithm>
#include<string>
#include<iostream>
#include<vector>
#include<iomanip>
#include<math.h>
#include<fstream>
#include<cctype>
using namespace std;
int scrabbleValue(char ch){
   char c = tolower(ch);
   int val = 0;
   switch(c){
   case 'a': case 'e':
   case 'i': case 'o':
   case 'n': case 'r':
   case 't': case 'l':
   case 's': case 'u': val= 1;
		       break;
   case 'd': case 'g': val= 2;
		       break;
   case 'b': case 'c':
   case 'm': case 'p': val=3 ;
		       break;
   case 'f': case 'h':
   case 'v': case 'w': case 'y': val= 4;
				 break;
   case 'k': val= 5;
	     break;
   case 'j': case 'x': val= 8;
		       break;
   case 'q': case 'z': val= 10;	       
   default: break;
}
return val;
}

int scrabbleValue(string s){
	char c;
	int value = 0;
   for(int i=0; i< s.length(); i++){
	   c = s[i];
	   if( (c>=65 && c<=90)||(c>=97 && c<=122)){
	   value += scrabbleValue(c);
   }
   }
   return value;
}

// Passive data node for hash tables.
struct Node {
    string word;
    Node* next;
};

class HashTable {
    public :
	HashTable ();
	HashTable (int K);
	virtual ~HashTable();
	void insert (string word);
	void remove (string word);	    // You implement this!
	bool lookup (string word) const;
	void print () const;
	void report () const;
	static const int DefaultSize;
    protected : 
	int getTableSize() const;	    
    private : 
	vector<Node*> table;
	// The "hash" function will be defined by each child class, 
	// each one using a different strategy.  But it needs to be
	// abstract (aka "pure virtual") in the abstract parent class.
	virtual int hash (string key) const = 0;
	
};

// Note that insert/lookup are completely defined here (and call hash) even
// tho hash is not defined here.  This is called the Template Method design
// pattern.  The hash function is private, meaning the children can't call
// it.  However, they can *define* it.  In fact, that's the only difference
// between the children classes: they each provide a difference
// implementation of hash!

const int HashTable::DefaultSize = 1000;
HashTable::HashTable() : table(DefaultSize) {}
HashTable::HashTable(int K) : table(K) {}

// The destructor has lots of garbage to clean up!  For each bucket with an
// overflow list, we delete the nodes.
HashTable::~HashTable(){
    for (int i=0; i<getTableSize(); i++) {
	Node* p = table[i];
	while (p!=NULL) {
	    Node* temp = p;
	    p = p->next;
	    delete temp;
	}
    }
}

// Simple accessor function that will be used by children classes to
// implement the hash function.  It's protected as children need to use it
// but not public as external clients do not need to know about it.
// This is the only information about the table that the children classes
// need to know, so we can make the table itself private!
int HashTable::getTableSize() const {
    return (int) table.size();
}

// Use open hashing with unsorted linked list for overflow.
void HashTable::insert(string key) {
    const int slot = hash(key);
    Node* newNode = new Node;
    newNode->word = key;
    newNode->next = table[slot];
    table[slot] = newNode;
}

bool HashTable::lookup (string key) const {
    const int slot = hash(key);
    Node* curNode = table[slot];
    while (curNode != NULL) {
	if (curNode->word == key) {
	    return true;
	}
	curNode = curNode -> next;
    }
    return false;
}

// You implement this!
void HashTable::remove(string key) {
    if(!lookup(key)) return;
    const int slot = hash(key);
    Node* todelete = table[slot];
    if(todelete->word==key){ //Node to be deleted is the first node in list
	    table[slot] = todelete->next;
	    delete todelete;
	    return;
    }
    Node* previous = todelete;
    while(todelete->word!=key){
	    previous = todelete;
	    todelete=todelete->next;
    }
    previous->next = todelete->next;
    delete todelete;
}

// To help you debug, if you find it useful.
void HashTable::print() const {
    for (int i=0; i<getTableSize(); i++) {
	if (table[i] != NULL) {
	    Node* p = table[i];
	    while (p != NULL) {
		cout << i << "    " << p->word << endl;
		p = p->next;
	    }
	}
    }
}

// So we can tell how good your hash function is ...
// Do NOT override this function in the version you submit.  We will check!
void HashTable::report () const {
    // K is number of buckets
    const int K = getTableSize();
    // How many overflow elements in each bucket?
    vector<int> stats (K);
    int totalNumEntries = 0;
    int numNonZeros = 0;
    int maxOverflowSize = 0;
    for (int i=0; i<K ; i++) {
	if (table[i] != NULL) {
	    numNonZeros++;
	    int numEntriesInThisBucket = 0;
	    Node* p = table[i];
	    while (p != NULL) {
		p = p->next;
		numEntriesInThisBucket++;
	    }
	    totalNumEntries += numEntriesInThisBucket;
	    if (numEntriesInThisBucket > maxOverflowSize) {
		maxOverflowSize = numEntriesInThisBucket;
	    }
	    stats[i]=numEntriesInThisBucket;
	}
    }
    // This part added 28 March 2014:
    // Compute average # of probes required to establish that an element 
    // is not present by summing the squares of the bucket list lengths, 
    // then dividing by totalNumEntries
    int sumOfSquaresOfBucketListLengths = 0;
    for (int i=0; i<stats.size(); i++) {
	sumOfSquaresOfBucketListLengths += stats.at(i) * stats.at(i);
    }
    const double avgNumberOfProbes = (double) sumOfSquaresOfBucketListLengths 
	/ (double) totalNumEntries;
    cout << "Average # of probes to establish an element is not present: " 
	<< setprecision(3) << fixed << avgNumberOfProbes << endl;

    // If we sort, it's trivial to find the median.
    sort(stats.begin(), stats.end());
    const int numEmptyBuckets = K - numNonZeros;
    const int firstNonZeroBucketIndex = numEmptyBuckets;
    cout << "Number of entries in table: " << totalNumEntries << endl;
    cout << "Total # buckets: " << K << " of which " << numEmptyBuckets 
	<< " (" << 100 * numEmptyBuckets / K << "%)" << " were empty." <<
	endl;
    // We want the avg and median # of elements, but ignoring the empty
    // buckets, on the grounds that if we're looking for a valid word, it
    // doesn't matter how many empty buckets there are, as we'll be hashing
    // to a non-empty bucket and traversing that list.
    // To compute the median, find the index that is half-way between
    // firstNonZeroBucketIndex and K.
    const int median = stats[firstNonZeroBucketIndex + numNonZeros/2];
    const int average = totalNumEntries / numNonZeros;
    cout << "Overflow list length:  Max = " << maxOverflowSize 
	<< "  Median = " << median << "  Average = " << average <<  endl;
}

class SimpleHashTable : public HashTable{
    public:
	    SimpleHashTable();
	    SimpleHashTable(int K);
	    virtual ~SimpleHashTable();
    private:
           int hash(string key) const;
};

SimpleHashTable::SimpleHashTable() : HashTable(){}

SimpleHashTable::SimpleHashTable(int K) : HashTable(K){}

SimpleHashTable::~SimpleHashTable(){}

int SimpleHashTable::hash(string key) const{
   int hash = 0;
   int size= getTableSize();
   for(int i=0; i<key.size(); i++){ 
	   hash+=key[i];
   	}
   hash = hash % size;
   return hash;
}

class SmartHashTable : public HashTable{
    public:
	    SmartHashTable();
	    SmartHashTable(int K);
	    virtual ~SmartHashTable();
    private:
           int hash(string key) const;
};

SmartHashTable::SmartHashTable() : HashTable(){}

SmartHashTable::SmartHashTable(int K) : HashTable(K){}

SmartHashTable::~SmartHashTable(){}

int SmartHashTable::hash(string key) const{
   int r = 196;
   int hash = 0;
   int size= getTableSize();
   for(int i=0; i<key.length(); i++, r+=1){ 
	   hash+= key[i]*r;
   	}
   hash = hash % size;
   return hash; 
}

// Ancillary function for powerset.  It adds a character onto the beginning
// of each string in a vector.
vector<string> addChar (const vector<string>& v, char c) {
    vector<string> ans;
    for (int i=0; i<(int)v.size() ; i++) {
	ans.push_back(c + v.at(i));
    }
    return ans;
}

// Note that I wrote this in scheme first!  Programming "shell game"
// recursion puzzles is easier with weak typing.
// This takes a string and returns the power(multi)set of its characters
// as a vector.  For example, powerset of "aab" would be the vector with
// elements (in no particular order): "aab" "ab" "aa" "a" "ab" "a" "b".
// Assume we don't care about eliminating duplicates for now.
vector<string> powerset (string s) {
    vector<string> ans;
    if (s.size() == 0) {
	ans.push_back("");
    } else {
	char c = s.at(0);
	string rest = s.substr(1);
	vector<string> psetRest = powerset (rest);
	ans = addChar (psetRest, c);
	ans.insert(ans.end(), psetRest.begin(), psetRest.end());
    }
    return ans;
}

int main(int argc, char* argv[]){
  // do file including stuff
  SmartHashTable s1;
  if(argc == 1){
	  cerr << "Error, no word list file name provided." << endl;
	  return 0;
  }
  string file=argv[1];
  ifstream wordlistfilename(file.c_str());
   if (!wordlistfilename.is_open()){
       cerr << "Error, couldn't open word list file.\n";
     return 0;
     }
  string read;
  while ( wordlistfilename >> read){
	  s1.insert(read);
  }
  wordlistfilename.close();
  string s;
  string str;
  vector<string> powersets;
  while( cin >> s){ 
	powersets = powerset(s);
	string max;
	int maxval=0;
	int j=0;
	for(int i=0; i< powersets.size(); i++){
	  str = powersets[i];
	  sort(str.begin(), str.end());
	  do{
		if(!(s1.lookup(str))){
		     ;	// do nothing
		}
		else{
                 int scr = scrabbleValue(str);
	         if(scr > maxval){
		   max = str;
	   	   maxval = scr;
		   j++;	   
		}
	  }
	  }while (next_permutation (str.begin(), str.end()));
	}
          if(j==0){ // no matches
		  cout << s <<": no matches" << endl;
	  }
	  else{
		cout << s <<": " << max << " has score of " << maxval << endl;
	  }
  }
  return 0;
}


