#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
// This function saves the lines read as token oriented input into a vector called lines
void rr (int N, vector<string> & v, vector<int> & l, vector<string>& lines){
   int nline=0;
 int  len=0;
   for(int i=0; i<v.size() ; i++){
       len+=l[i];
       if(i==0) lines.push_back(v[0]);
       else{
       if(len<N ){
        // cout << " " << v[i];
        lines[nline]+= " ";
        lines[nline]+=v[i];
           len++;
       }
       else {
      //     cout << endl << v[i];
           lines.push_back(v[i]);
           len=l[i];
           nline++;
       }
       //white spaces should be here
       
       }
   }
 /*  for(int i=lines.size()-1; i>=0; i--){
       cout << lines[i] << endl;
   }*/
}
// rr ends here

// This function reads in input and adds it to vector called lines 
void j (int N, int &numlines, vector<string> &v, vector<int>&l, vector<int> &tokens, vector<int> & wspaces, vector<string> &lines){
   int nline=0;
 int  num=0;
 int  len=0;
   int i=0;
 int  flag=0;
 int  j=0;
   int check=0;
   int q, r, a;
   while(numlines){
       if(tokens[j]==1){
           q=0;
           r= N-l[i];
           a=q;
       }
       else{
       q = wspaces[j]/(tokens[j]-1);
       r = wspaces[j]%(tokens[j]-1);
       a=q;
       }
   len=l[i];
   
       while(len<=N){
           
           if(flag==0){
        //     cout << v[i];
            lines.push_back(v[i]);
               check+=l[i];
               num++;
               flag=1;
           }
           else{
               while(a){
        //      cout << " ";
               lines[nline]+= " ";
                   a--;
                   num++;
                   check++;
               }
               a=q;
               
               if(r){
        //           cout << " ";
                  lines[nline]+= " ";
                   r--;
                   num++;
                   check++;
               }
             //  cout << v[i];
                 lines[nline]+= v[i];
               check+=l[i];
           }
           len+=num;
           num=0;
           i++;
           if(i==v.size()){
                if(check<N){
           while(check!=N) {
           //    cout << " ";
               lines[nline]+= " ";
               check++;
           }
                }
           }
           len+=l[i];
       } 
       flag=0;
       numlines--;
       j++;
       if(check<N){
           while(check!=N) {
              // cout << " ";
              lines[nline]+=" ";
               check++;
           }
       }
       nline++;
  //     cout << endl;
       check = 0;
   }
/*for(int k=lines.size()-1; k>=0; k--){
    cout << lines[k] << endl;
}*/ 
}
// j ends here

// rl reader
void rl(int N, int &numlines, vector<string> &v, vector<int>&l, vector<int> &tokens, vector<int> & wspaces, vector<string> &lines){
 int  num=0;
 int  len=0;
   int nline=0;
   int i=0;
  int flag=0;
  int j=0;
   int check=0;
   int q, r, a;
   while(numlines){
       if(tokens[j]==1){
       q = wspaces[j]-1;
       if(q<0){ 
           q=0;
           check=1;
       }
       a=q;
       while(q){
      //     cout << " ";
      if(a==q) {
          lines.push_back(" ");
          flag=1;
      }
      else lines[nline]+=" ";
           q--;
           num++;
       }
   }
   else {
       q= wspaces[j] - tokens[j];
       a=q;
       if(q<0){ 
           q=0;
           a=0;
           check=1;
        }
         while(q){
         //  cout << " ";
    if(a==q) { 
        lines.push_back(" ");
        flag=1;
    }
    else lines[nline]+=" ";
           q--;
           num++;
       }
        }
   len=num;
   num=0;
   len+=l[i];
   while(len<=N){
       if(len==N) {
           //cout << v[i];
       if(tokens[j]==1) lines.push_back(v[i]);
        else {
            lines[nline]+= " ";
            len++;
            lines[nline]+=v[i];
        }
       }
       else{
      // cout << " ";
   if(flag==1)   lines[nline]+=" ";
   else{ 
       lines.push_back(" ");
       flag=1;
   }
       len++;
      // cout << v[i];
      lines[nline]+=v[i];
   }
   i++;
   if(i==v.size()){
      // cout << "\n";
       break;
   }
   len+=l[i];
   }
  // cout << "\n";
   flag=0;
   j++;
   numlines--;
   nline++;
   }
//cout << "\n";

/*for(int k=lines.size()-1; k>=0; k--){
    if(lines[k].length()==N)
    cout << lines[k] << endl;
    else cout << lines[k].substr(1)<< endl;
}*/
}
// rl ends

//c starts
void c (int N, int &numlines, vector<string> &v, vector<int> &l, vector<int> &tokens, vector<int> & wspaces, vector<string> &lines){
	int nline = 0;
 int  num=0;
 int  len=0;
   int i=0;
  int flag=0;
 int  j=0;
   int check=0;
   int q, r, a;
   while(numlines){
       if(tokens[j]==1){
       q = wspaces[j]/2;
       r = wspaces[j]%2;
       a=q;
       while(a){
        //   cout << " ";
           if(a==q) lines.push_back(" ");
           else lines[nline]+=" ";
           a--;
           num+=2;
       }
       if(r){
       //    cout << " ";
       if(q==0) lines.push_back(" ");
       else lines[nline]+= " ";
           r--;
           num+=2;
       }
   }
   else {
       q=(wspaces[j] - tokens[j]+1)/2;
       r=(wspaces[j] - tokens[j]+1)%2;
       a=q;
         while(a){
       //    cout << " ";
       if(a==q) lines.push_back(" ");
           else lines[nline]+=" ";
           a--;
           num+=2;
       }
       if(r){
      //     cout << " ";
      if(q==0) lines.push_back(" ");
           else lines[nline]+=" ";
           r--;
           num+=2;
       }
        }
   len=num;
   check=num;
   num=0;
   len+=l[i];
   while(len<=N){
       if(flag==0) {
        //   cout << v[i];
    if(check!=0)  lines[nline]+=v[i];
    else{ 
        lines.push_back(v[i]);
    }
          
           flag=1;
       }
       else{
    //   cout << " ";
    lines[nline]+=" ";
       len++;
     //  cout << v[i];
     lines[nline]+=v[i];
   }
   i++;
   if(i==v.size()){
       while(q){
     //      cout << " ";
     lines[nline]+= " ";
           q--;
       }
    //   cout << "\n";
       break;
   }
   len+=l[i];
   }
   while(q){
     //  cout << " ";
     lines[nline]+=" ";
       q--;
   }
   //cout << "\n";
   j++;
   numlines--;
   flag=0;
   nline++;
   }
  // for(int k=lines.size()-1; k>=0; k--) cout << lines[k] << endl;
}
// c ends

//function to read the input from file
void reader(int N, int & numlines, vector<string>& v, vector<int> & l, vector<int> &tokens, vector<int>& wspaces, string text){
 ifstream instream(text.c_str());
 int num=0;
	int len=0;
	int flag=0;
//	vector<string>v;
//	vector<int>l;
	//vector<int>wspaces; //whitespaces after every word in the line
	//vector<int>tokens;
//	int nline=0;
	string s;
	string old;
   while(instream >> s){
       
           if(s.length()+len>=N){
               len=0;
               flag=1;
           }
       if(s.length()+len>=N){
         if(flag==0){
           v.push_back(s.substr(0,N-len));
           l.push_back(N-len);
           len+=N-len;
       }
       else{
           v.push_back(s.substr(0,N));
           l.push_back(s.substr(0,N).length());
           len=N;
           flag=0;
       }
}
       else{
           v.push_back(s);
           l.push_back(s.length());
           len+=s.length();
       }
	   if(instream.eof()) break;
   }
   instream.close();
 //  int numlines=0;
   len=0;
   flag=0;
   int j=0;
   num=0;
   for(int i=0; i<v.size(); i++){
       num++;
       len+=l[i];
       if(len>N){
           len-=(num-1);
          
           tokens.push_back(num-1);
           wspaces.push_back(N-len+l[i]);
           num=1;
           len=l[i];
           numlines++;
       }
    len++;
    
   }
   len--;
   len-=(num-1);
   if(len<N){
       tokens.push_back(num);
       wspaces.push_back(N-len);
       numlines++;
   }
}
   // function ends here
   
 void printp(string &flow, vector<string> &lines){
	 if(flow=="f"){
		 for(int i=0; i<lines.size(); i++) cout<< lines[i] << endl;
	 }
	 else for(int i = lines.size()-1; i>=0; i--) cout << lines[i] << endl;
 } 

void printk(int k, string &flow, vector<string> &lines){
	if(flow=="f") cout << lines[k] << endl;
	else cout << lines[lines.size()-k] << endl;
}  

void prints(string s, string &flow, vector<string> &lines){
	if(flow=="f"){
		for(int i=0; i< lines.size();i++){
			 if(lines[i].find(s)!= string::npos) cout << lines[i] << endl;
		}
	}
	else{
		for(int i=lines.size()-1; i>=0;i--){
			 if(lines[i].find(s)!= string::npos) cout << lines[i] << endl;
	} 
}
}

int main(){
	int N;
	cin >> N;
	if(N<=0){
		cerr<< "Error, line length must be positive" << endl;
		return 0;
	}
	string textFileName;
	cin >> textFileName;
	ifstream my_file(textFileName.c_str());
     if (!my_file.is_open()){
       cerr << "Error, can't open specified text file.\n";
     return 0;
     }
	 my_file.close();
	int numlines = 0;
	vector<string> v;
	vector<int> l;
	vector<int> tokens;
	vector<int> wspaces;
	reader(N, numlines, v, l, tokens, wspaces, textFileName);
	string temp;
	string flow;
	string justification;
	vector<string>lines;
	int k;
	string s;
	int rrflag = 0;
	int rlflag = 0;
	int cflag = 0;
	int jflag = 0;
	int check = 0;
	while(cin >> temp){
		if(temp=="q") break;
		if(temp=="rr") {
			rrflag = 1;
			rlflag = 0;
			cflag = 0;
			jflag =0;
			check=0;
			justification = temp;
		}
		else if(temp=="rl"){
			rrflag = 0;
			rlflag = 1;
			cflag = 0;
			jflag =0;
			check=0;
			justification = temp;
		}
		else if(temp=="c"){
			rrflag = 0;
			rlflag = 0;
			cflag = 1;
			jflag =0;
			check=0;
			justification = temp;
		}
		else if(temp=="j"){
			rrflag = 0;
			rlflag = 0;
			cflag = 0;
			jflag =1;
			check=0;
			justification = temp;
		}
		else{
			if(justification.empty()){
				justification = "rr";
				rrflag = 1;
				check = 0;
			}
		 if(check == 0){
			 if(lines.size()!=0){
				 while(lines.size()!=0) lines.pop_back();
			 }
			 if(rrflag) rr(N, v, l, lines);
			 else if(rlflag) rl(N, numlines, v, l, tokens, wspaces, lines);
             else if(cflag) c(N, numlines, v, l, tokens, wspaces, lines);
             else j(N, numlines, v, l, tokens, wspaces, lines);
             check++;			 
		 }	
		 if(temp=="f") flow = "f";
         else if(temp == "r") flow = "r";
         else{
			if(flow.empty()) flow = "f";
           if(temp=="p") printp(flow, lines);
            else if(temp == "k"){
				cin >> k;
				printk(k, flow, lines);
			}		   
			else if(temp=="s"){
				cin >> s;
				prints(s, flow, lines);
			}
            else {
				cerr << "Error, command is illegal" << endl;
				return 0;
			}			
			}
			 
		 }		 
			if(cin.eof()) break;
		}	
	return 0;
}

