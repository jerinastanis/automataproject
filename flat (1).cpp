#include<bits/stdc++.h>
using namespace std;
const int NO_OF_STATES = 15;  
int n1,n;
                    
class states{
      public:
      char status;        
      int sno;  
      int gp;   
      int* ts;   
    
      states(){
           sno=gp=0;
           ts=NULL;}
      states(int state_no){
           gp=0;     
           sno=state_no;
           ts = new int[n];
           for(int i=0;i<n;i++)
              ts[i]=-1;}            
     void input(){
           char ch='a';
           if(sno==0)  
              cout<<"Initial ";
           cout<<"For state "<<sno<<"\n";
           for(int j=0;j<n;j++,ch++){
                cout<<"Enter output state for input "<<ch<<" : ";
                cin>>ts[j];}
           cout<<"Non-final or final state ? (N/F) : ";
           cin>>status;
           if(status=='n'||status=='N')
           gp=0;
           else
           gp=1;} 

void output(){
      if(sno==-1)
      return;
      cout<<"\n    "<<sno<<"|";
      for(int i=0;i<n;i++)
         if(ts[i]!=-1)
         cout<<"\t"<<ts[i];
         else
         cout<<"    N/A";}
};

int exists(int s[],int ref){
      for(int i=0;i<n1;i++)
           if(s[i]==ref)
             return i; 
      return -1;}

void check(states state[]){
      int array[NO_OF_STATES],temp,newgp[NO_OF_STATES],flag=0,count=2;
      for(int outerloop=0;outerloop<n1-2;outerloop++){
      for(int j=0;j<n;j++)                           {
            for(int z=0;z<NO_OF_STATES;z++)  
               array[z]=-1;  
            for(int i=0;i<n1;i++){  
                 temp=state[i].ts[j];  
                 for(int k=0;k<n1;k++)    
                     if(state[k].sno==temp){
                          array[i]=state[k].gp;
                          break;}}
        for(int i=0;i<n1-1;i++){
            for(int z=0;z<NO_OF_STATES;z++)  newgp[z]=-1;   
                 flag=0;
            for(int k=i+1;k<n1;k++){
                if(state[i].gp==state[k].gp){    
                if((array[i]!=array[k]) && ( (flag==0) || (exists(newgp,array[k])==-1))){
                    state[k].gp = count;
                    count++;
                    newgp[k] = array[k];
                    flag++; }
                else if(array[i]!=array[k]){
                    state[k].gp = state[exists(newgp,array[k])].gp;}}}}}} 

        for(int i=0;i<n1-1;i++){
        if(state[i].sno!=-1)  
            for(int j=i+1;j<n1;j++)   
                if(state[i].gp==state[j].gp){ 
                cout<<i<<" AND "<<j<<" ARE EQUIVALENT AND MERGED\n";}}                        
    for(int i=0;i<n1-1;i++){
        if(state[i].sno!=-1)  
        for(int j=i+1;j<n1;j++)   
            if(state[i].gp==state[j].gp){  
            for(int h=0;h<n1;h++) 
            for(int z=0;z<n;z++) 
                if(state[h].ts[z]==state[j].sno) 
                    state[h].ts[z]=state[i].sno; 
                    state[j].sno=-1; 
                    if((state[j].status=='f') || (state[j].status=='F'))
                    state[i].status='F';}}}

void print(vector<vector<vector<int> > > table){
	cout<<"\tSTATE/INPUT\n\t|";
	char a='a';
    cout<<"\t";
	for(int i=0;i<table[0].size()-1;i++){
		cout<<a++<<"\t|\t";}
	cout<<"^"<<endl;
	for(int i=0;i<table.size();i++){
		cout<<""<<i<<"";
		for(int j=0;j<table[i].size();j++){
			cout<<"\t|\t";
			for(int k=0;k<table[i][j].size();k++){ 
				cout<<table[i][j][k]<<" ";}}
		cout<<endl;}}

void printdfa(vector<vector<int>> states, vector<vector<vector<int>>> dfa){
	cout<<"\tSTATE/INPUT \n\t";
	char a='a';
	for(int i=0;i<dfa[0].size();i++){
		cout<<"|\t"<<a++<<"\t";}
	cout<<endl;
	for(int i=0;i<states.size();i++){
		cout<<"{";
		for(int h=0;h<states[i].size();h++)
			cout<<states[i][h]<<" ";
		if(states[i].empty()){
			cout<<"^";}
		cout<<"} ";
		for(int j=0;j<dfa[i].size();j++){
			cout<<"\t|\t";
			for(int k=0;k<dfa[i][j].size();k++){
				cout<<dfa[i][j][k]<<" ";}
			if(dfa[i][j].empty()){
				cout<<"^ ";}}
		cout<<endl;}}

vector<int> closure(int s,vector<vector<vector<int>>> v){
	vector<int> t;
	queue<int> q;
	t.push_back(s);
	int a=v[s][v[s].size()-1].size();
	for(int i=0;i<a;i++){
		t.push_back(v[s][v[s].size()-1][i]);
		q.push(t[i]);}
	while(!q.empty()){
		int f=q.front();
		q.pop();
		if(!v[f][v[f].size()-1].empty()){
			int u=v[f][v[f].size()-1].size();
			for(int i=0;i<u;i++){
				int y=v[f][v[f].size()-1][i];
				if(find(t.begin(),t.end(),y)==t.end()){
					t.push_back(y);
					q.push(y);}}}}
	return t;}

int main(){
int choice;
cout<<"\t1.NFA TO DFA\n\t2.MINIMIZATION OF DFA\n\t3.EXIT";
do{
	cout<<"\nchoice: ";
	cin>>choice;
	if(choice==1){
	int n,alpha;
	cout<<" \t\t\tNFA to DFA "<<endl<<endl;
	cout<<"Enter total number of states in NFA : ";
	cin>>n;
	cout<<"Enter number of elements in alphabet : ";
	cin>>alpha;
	vector<vector<vector<int>>>table;
	for(int i=0;i<n;i++){
		cout<<"For state "<<i<<endl;
		vector<vector<int>>v;
		char a='a';
		int y,yn;
		for(int j=0;j<alpha;j++){
			vector<int> t;
			cout<<"Enter no. of output states for input "<<a++<<" : ";
			cin>>yn;
            if(yn!=0)
			cout<<"Enter output states :"<<endl;
			for(int k=0;k<yn;k++){
				cin>>y;
				t.push_back(y);}
			v.push_back(t);}
		vector<int> t;
		cout<<"Enter no. of output states for input ^ : ";
		cin>>yn;
		cout<<"Enter output states :"<<endl;
		for(int k=0;k<yn;k++){
			cin>>y;
			t.push_back(y);}
		v.push_back(t);
		table.push_back(v);}
        int num,ini;
    cout<<"enter the initial state";cin>>ini;
	cout<<"Enter the no of final states : ";cin>>num;
    int f[num];
	cout<<"Enter the final states : ";
    for(int i=0;i<num;i++)cin>>f[i];
	cout<<"\tTRANSITION TABLE OF NFA "<<endl;
	print(table);
	cout<<endl<<"\tTRANSITION TABLE OF DFA"<<endl;
	vector<vector<vector<int>>>dfa;
	vector<vector<int>> states;
	states.push_back(closure(0,table));
	queue<vector<int>> q;
	q.push(states[0]);
	while(!q.empty()){
		vector<int> f=q.front();
		q.pop();
		vector<vector<int> > v;
		for(int i=0;i<alpha;i++){
			vector<int> t;
			set<int> s;
			for(int j=0;j<f.size();j++){
				
				for(int k=0;k<table[f[j]][i].size();k++){
					vector<int> cl= closure(table[f[j]][i][k],table);
					for(int h=0;h<cl.size();h++){
						if(s.find(cl[h])==s.end())
						s.insert(cl[h]);}}}
			for(set<int >::iterator u=s.begin(); u!=s.end();u++)
				t.push_back(*u);
			v.push_back(t);
			if(find(states.begin(),states.end(),t)==states.end()){	
				states.push_back(t);
				q.push(t);}}
		dfa.push_back(v);}
	printdfa(states,dfa);
    cout<<"\nInitial state: "<<ini;
	cout<<"The states containing ";
    for(int i=0;i<num;i++){cout<<f[i];
    if(i!=num-1) cout<<" , ";}
    cout<<" are final states";}

	
	else if(choice==2){
        cout<<"\t\t\tMINIMIZATION OF DFA\n\n";
	    char ch='a';  
        cout<<"Enter total number of states in NFA : ";
	    cin>>n1;      
        cout<<"Enter number of elements in alphabet : ";
        cin>>n;
      states state[NO_OF_STATES]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
      for(int i=0;i<n1;i++)
      state[i].input();
      check(state);
    	cout<<"\tSTATE/INPUT \n";
      for(int i=0;i<n;i++,ch++)cout<<"\t"<<ch;             
      for(int i=0;i<n1;i++)
          state[i].output();
      for(int i=0;i<n1;i++){
          if(state[i].status=='f' || state[i].status=='F')
      cout<<"\nFinal state: "<<i;
          if(state[i].sno==0)   
      cout<<"\nInitial state: "<<i;}}

	else if(choice==3){
	    cout<<"\n\tEXITINGGGG.....!!!!\n";}
	else
	 cout<<"INVALID CHOICE";	
	}while(choice!=3);}