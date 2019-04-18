#include <iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;
struct node
{
	char name;
	double pa,pb,pt; // P(a)   P(b)   P(turn)
	double bend[4]; // f(i) ,f(i+1),f(i+2),f(i+3)
	node *next;
	node *previous;
	
	char alpha;
	char beta;
	int alpha_class;
	int beta_class;
	int turn_class;
	
	
	int p4_alpha;
	int p4_beta;
	int p4_turn;
	double turn_prod;

};
class list 
{
	node *head;
	node *tail;
	node *start;
	node *end;
	public:
		list()
		{
			head=NULL;
			tail=NULL;
		}
		add_tail(char name,int index,double arr[][8])
		{
			node *newnode=new node;
			newnode->name=name;
			newnode->pa=arr[index][1];
			newnode->pb=arr[index][2];
			newnode->pt=arr[index][3];
			
			for(int i = 0;i < 4; i++)
				newnode->bend[i] = arr[index][4+i];
			 
			
			
			newnode->next=NULL;
			newnode->previous=NULL;
			node *current=new node;
			current=head;
			if(head==NULL)
			{
				head=newnode;
				tail =newnode;
				newnode=NULL;
			}
			else
			{
				while(current->next!=NULL)
				{
					current=current->next;
				}
				newnode->previous=current;
				current->next=newnode;
				tail=newnode;
			}
		}
	/*
		bool search(int n)
		{
			int flag=0;
			node * current=new node;
			current =head;
			while(current!=NULL)
			{
				if(current->name==n)
				{
					flag=1;
				}
				current=current->next;
			}
			if(flag==1)
			{
				return true;
			}
			if(flag==0)
			{
				return false;
			}
		}
		*/
		void display()
		{
			ofstream out("OUTPUT.txt");
			node *current =head;
			cout << "Name " <<'\t' <<"P(a)" << '\t' << "P(b)" << '\t' 
				 << "P(Turn)" << '\t' << "f(i)" << '\t' << "f(i+1)" << '\t'<< "f(i+2)" << '\t'
				 << "f(i+3)" << '\t' << "<Pa>" << '\t' << "<Pb>" << '\t' << "<Pt>" <<'\t'<< "<pt(product)>"<< endl;
			cout << endl;
			out << "Name " <<'\t' <<"P(a)" << '\t' << "P(b)" << '\t' 
				 << "P(Turn)" << '\t' << "f(i)" << '\t' << "f(i+1)" << '\t'<< "f(i+2)" << '\t'
				 << "f(i+3)" << '\t' << "<Pa>" << '\t' << "<Pb>" << '\t' << "<Pt>" <<'\t'<< "<pt(product)>"<< endl;
			out << endl;
				 
			int total_alpha = 0,total_beta = 0, temp_a = 0, temp_b = 0;
			char char_a,char_b,char_prod;
 			while(current!=NULL)
			{
				
				cout<<(char)current->name<<"\t"
					<<current->pa;
					cout<<"\t"
					<<current->pb;
					cout<<"\t"
					<<current->pt<<"\t";
					
				out<<(char)current->name<<"\t"
					<<current->pa;
				out<<"\t"
					<<current->pb;
				out<<"\t"
					<<current->pt<<"\t";
					
					for(int i =0; i < 4; i++){
						cout << current->bend[i] << "\t";
						out << current->bend[i] << "\t";
						
					}
						
					cout << current->p4_alpha ;
					out << current->p4_alpha ;
					if(current->p4_alpha >=100){
						char_a = '*';
						cout <<"*";
						out <<"*";
						temp_a++;
					}
					else{
						char_a = '_';
						cout << "_";
						out <<"*";
						if(temp_a > total_alpha){ // Longest Chain
							total_alpha = temp_a;
						}
						temp_a =0;
					}
				cout << '\t';
				cout << current->p4_beta;
				out << '\t';
				out << current->p4_beta;
					if(current->p4_beta >=100){
						char_b = '*';
						cout <<"*";
						out <<"*";
						temp_b++;
					}
					else{
						char_b = '_';
						cout << "_";
						out << "_";
						if(temp_b > total_beta){ // Longest Chain
							total_beta = temp_b;
						}
						temp_b =0;
					}
				cout << '\t';
				cout << current->p4_turn << '\t'
					 << current->turn_prod;
				out << '\t';
				out << current->p4_turn << '\t'
					 << current->turn_prod;
					 
					 if(current->turn_prod >0.000075){
						char_prod = '*';
						cout <<"*";
						out << "*";
					}
					else{
						char_prod = '_';
						cout << "_";
						out <<"_";
					}
				
				cout <<'\t' << char_a << char_b << char_prod;	 
				out <<'\t' << char_a << char_b << char_prod;
					 
				/*
				 If: (1) p(t) > 0.000075; (2) the average value for P(turn) > 1.00 
				 in the tetrapeptide; and (3) the averages for the tetrapeptide obey 
				 the inequality P(a-helix) < P(turn) > P(b-sheet), then a beta-turn 
				 is predicted at that location. 
				*/
				
					 
					 
				current=current->next;
				cout<<endl;
				out << endl;
			}
			if(total_alpha > total_beta){
				cout << endl << "Structure : Alpha-Helix";
				out << endl << "Structure : Alpha-Helix";
			}
			else{
				cout << endl << "Structure : Beta-Sheet";
				out << endl << "Structure : Beta-Sheet";
			}
			cout<<endl<<endl;
		}
		void calc_avg(){
			node *traverser = this->head;
			node **next_three = new node*[3];
			node *temp = traverser;
			for (int i = 0; i < 3 && temp != NULL; i++){
				next_three[i] = temp->next;
				temp = temp->next;
			}
			while(next_three[2] != NULL){
				int a_tsum = 0,b_tsum = 0,turn_tsum=0;
				double tprod = 1;
				a_tsum += traverser->pa;
				b_tsum += traverser->pb;
				turn_tsum += traverser->pt;
				tprod *= traverser->bend[0];
				
				for (int i = 0; i < 3 && next_three[i] != NULL; i++){
					a_tsum += next_three[i]->pa;
					b_tsum += next_three[i]->pb;
					turn_tsum += next_three[i]->pt;
					tprod *= next_three[i]->bend[i+1];
				}
				traverser->p4_alpha = a_tsum/4;
				traverser->p4_beta = b_tsum/4;
				traverser->p4_turn = turn_tsum/4;
				traverser->turn_prod = tprod;
				
				traverser = traverser->next;	
				node *temp = traverser;
				for (int i = 0; i < 3 && temp != NULL; i++){
					next_three[i] = temp->next;
					temp = temp->next;
				}	
				 
			}
		}
		string alpha_helix(){
			string helix;
			node *traverser = this->head;
			node **next_five = new node*[5];
			node *temp = traverser;
			for (int i = 0; i < 5 && temp != NULL; i++){
				next_five[i] = temp->next;
				temp = temp->next;
			}
			while(traverser!=NULL && next_five[4] != NULL&& next_five[3] != NULL&& next_five[2] != NULL&& next_five[1] != NULL){
				cout << helix <<endl;
				int a_helix_cnt= 0;
				
				if(traverser->pa > 100)
					a_helix_cnt++;
				for (int i = 0; i < 5 && next_five[i] != NULL; i++){
					if(next_five[i]->pa > 100){
						a_helix_cnt++;
					}
				}
				
				if(a_helix_cnt >= 4){
					helix +="HHHHHH";
					//traverser = next_five[4]->next;
					if(traverser == NULL)
						break;
					int less_than_100_cnt = 0;
					int residue = 0;
					int sum_a = 0,sum_b=0;
					while(traverser!=NULL){
						if(traverser->p4_alpha < 100){
							less_than_100_cnt++;
						}
						residue++;
						
						sum_a += traverser->pa;
						sum_b += traverser->pb;
						if(less_than_100_cnt >= 4){
							
							break;
						}	
						traverser=traverser->next;
						
					}
					if(residue>5 && ((double)sum_a/residue) > ((double)sum_b/residue)){
						for(int i =0; i< 5; i++){
							helix+="H";
						}
					}
					else{
						for(int i =0; i< 5; i++){
							helix+="_";
						}
					}
				}
				else{
					helix+="_";
				}
				
				
				traverser = traverser->next;	
				node *temp = traverser;
				for (int i = 0; i < 5 && temp != NULL; i++){
					next_five[i] = temp->next;
					temp = temp->next;
				}
			}
			return helix;
		}
		
		
		
		void print_seq()
		{
			node *current =head;
			while(current!=NULL)
			{
				
				cout<<(char)current->name;
				current=current->next;
			}
			cout<<endl;
		}
		
		void print_inp()
		{
			node *current =head;
			while(current!=NULL)
			{
				
				cout<<current->name;
				current=current->next;
			}
			cout<<endl;
		}
		
		void find_alpha()
		{
			list::print_seq();
			int cnt=0;
			node *t1=new node;
			node *t2=new node;
			node *s=new node;
			node *e=new node;
			node *print=new node;

			t1=head;
			t1->previous=head->previous;
			t2=head;
			t2->previous=head->previous;
			print=head;
			print->previous=NULL;
			loop:
				int c=0;
				cnt=0;
				s=t1;
			//	s->previous=t1->previous;
			// s->next=t1->next;
				while(c<6 && t1!=NULL)
				{
					if(t1->pa>=100)
					{
						cnt=cnt+1;
					}
					t1=t1->next;
					c=c+1;
				}
				if(cnt<4 && t1!=NULL)
				{
					t1=t2->next;
					t2=t2->next;
					goto loop;
				}
				if(t1==NULL && cnt<4)	
				{
					goto loop2;
				}
				t2=t1;
			loop2:
				int cc=0;
				cnt=0;
				e=t1;
			//	e->previous=t1->previous;
				while(cc<4 && t1!=NULL)
				{
					if(t1->pa<100)
					{
						cnt=cnt+1;
					}
					t1=t1->next;
					cc=cc+1;
				}
				if (t1==NULL)
				{
					end =tail;
					goto part;
				}
				if(cnt<4)
				{
					t1=t2->next;
					t2=t2->next;
					goto loop2;
				}
				end=e;
				part:
				t2=t1;
				start=s;
				
			//	cout<<(char)s->previous->name<<"    "<<(char)s->name<<" **"<<(char)e->previous->name<<"    "<<(char)e->name;
			//	cout<<endl<<endl;
				list::print_alpha(print,start,end);
				print=end;
				if(t1==NULL)
				{
					return;
				}
				goto loop;
		}
		void print_alpha(node *temp,node * s, node *e)
		{
			if (temp==NULL || s== NULL)
			{
				return;
			}
			while(temp->next!=s)
			{
				//cout<<"_";
				temp=temp->next;
			}
			//cout<<"_";
			while(s->next!=e->next)
			{
				//cout<<"H";
				s->alpha_class = 1;
				s=s->next;
			}
			return;
		}
		void find_beta()
		{
			int cnt=0;
			node *t1=new node;
			node *t2=new node;
			node *s=new node;
			node *e=new node;
			node *print=new node;

			t1=head;
		
			t2=head;
		
			print=head;
			
			loop_beta:
				int c=0;
				cnt=0;
				s=t1;
			//	s->previous=t1->previous;
			// s->next=t1->next;
				while(c<5 && t1!=NULL)
				{
					if(t1->pb>=100)
					{
						cnt=cnt+1;
					}
					t1=t1->next;
					c=c+1;
				}
				if(cnt<3 && t1!=NULL)
				{
					t1=t2->next;
					t2=t2->next;
					goto loop_beta;
				}
				if(t1==NULL && cnt<3)	
				{
					goto loop2_beta;
				}
				t2=t1;
			loop2_beta:
				int cc=0;
				cnt=0;
				e=t1;
			//	e->previous=t1->previous;
				while(cc<4 && t1!=NULL)
				{
					if(t1->pb<100)
					{
						cnt=cnt+1;
					}
					t1=t1->next;
					cc=cc+1;
				}
				if (t1==NULL)
				{
					end =tail;
					goto part_beta;
				}
				if(cnt<4)
				{
					t1=t2->next;
					t2=t2->next;
					goto loop2_beta;
				}
				end=e;
				part_beta:
				t2=t1;
				start=s;
				
			//	cout<<(char)s->previous->name<<"    "<<(char)s->name<<" **"<<(char)e->previous->name<<"    "<<(char)e->name;
			//	cout<<endl<<endl;
				list::print_beta(print,start,end);
				print=end;
				if(t1==NULL)
				{
					return;
				}
				goto loop_beta;
				
				return;
		}
		void print_beta(node *temp,node * s, node *e)
		{
			if (temp==NULL || s== NULL)
			{
				return;
			}
			
			while(temp!=s && temp->next!=s)
			{
				//cout<<"_";
				temp=temp->next;
			}
			
			//cout<<"_";
		
			while(s->next!=e->next)
			{
				//cout<<"B";
				s->beta_class = 1;
				s=s->next;
			}
			
			return;
		}
		string alpha_string(){
			string helix_string;
			node* traverser = this->head;
			
			while(traverser!=NULL){
				if(traverser->alpha_class == 1){
					helix_string += "H";
				}
				else{
					helix_string += "_";
				}
				traverser = traverser->next;
			}
			ofstream out("OUTPUT.txt",std::ios::app);
			out << endl <<"Helix : " << endl;
			out << helix_string;
			cout << endl <<"Helix : " << endl;
			cout << helix_string;
			return helix_string;
		}
		string sheet_string(){
			string helix_string;
			node* traverser = this->head;
			
			while(traverser!=NULL){
				if(traverser->beta_class == 1){
					helix_string += "B";
				}
				else{
					helix_string += "_";
				}
				traverser = traverser->next;
			}
			ofstream out("OUTPUT.txt",std::ios::app);
			out << endl <<"Sheet : " << endl;
			out << helix_string;
			cout << endl <<"Sheet : " << endl;
			cout << helix_string;
			return helix_string;
		}
		string beta_turn(){
			string turn_string;
			node* traverser = this->head;
			
			while(traverser!=NULL){
				if(traverser->pt > 0.000075){
					if(traverser->p4_alpha < traverser->p4_turn && traverser->p4_turn > traverser->p4_beta){
						traverser->turn_class = 1;
						turn_string+="T";
					}
					else{
						traverser->turn_class = 0;
						turn_string+="_";
					}
				}
				traverser = traverser->next;
			}
			ofstream out("OUTPUT.txt",std::ios::app);
			out << endl <<"Turns : " << endl;
			out << turn_string;
			cout <<endl <<"Turns : " << endl;
			cout << turn_string;
			return turn_string;
			
	}
	string struct_string(){
		string turn_string;
			node* traverser = this->head;
			
			while(traverser!=NULL){
				if(traverser->turn_class==1){
					turn_string += "T";
				}
				else if(traverser->alpha_class==1 && traverser->beta_class==1){
					if(traverser->pa > traverser->pb){
						turn_string += "H";
					}
					else{
						turn_string += "B";
					}
				}
				else if(traverser->alpha_class){
					turn_string += "H";
				}
				else if(traverser->beta_class){
					turn_string += "B";
				}
				else{
					turn_string += "C";
				}
				
				
				traverser = traverser->next;
			}
			ofstream out("OUTPUT.txt",std::ios::app);
			out << endl <<"Struct : " << endl;
			out << turn_string;
			cout <<endl <<"Struct : " << endl;
			cout << turn_string;
			return turn_string;
	}
		
		
};
int main()
{
	char temp;
	char name[] = {'A', 'R', 'D', 'N', 'C', 'E', 'Q', 'G', 'H', 'I', 'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V'};
	double data[20][8]={{'A', 142,   83,   66,   0.06,   0.076,  0.035,  0.058},
						{'R',  98,   93,   95,   0.070,  0.106,  0.099,  0.085},
						{'D', 101,   54,  146,   0.147,  0.110,  0.179,  0.081},
						{'N',  67,   89,  156,   0.161,  0.083,  0.191,  0.091},
						{'C',  70,  119,  119,   0.149,  0.050,  0.117,  0.128},
						{'E', 151,   37,   74,   0.056,  0.060,  0.077,  0.064},
						{'Q', 111,  110,   98,   0.074,  0.098,  0.037,  0.098},
						{'G',  57,   75,  156,   0.102,  0.085,  0.190,  0.152},
						{'H', 100,   87,   95,   0.140,  0.047,  0.093,  0.054},
						{'I', 108,  160,   47,   0.043,  0.034,  0.013,  0.056},
						{'L', 121,  130,   59,   0.061,  0.025,  0.036,  0.070},
						{'K', 114,   74,  101,   0.055,  0.115,  0.072,  0.095},
						{'M', 145,  105,   60,   0.068,  0.082,  0.014,  0.055},
						{'F', 113,  138,   60,   0.059,  0.041,  0.065,  0.065},
						{'P',  57,   55,  152,   0.102,  0.301,  0.034,  0.068},
						{'S',  77,   75,  143,   0.120,  0.139,  0.125,  0.106},
						{'T',  83,  119,   96,   0.086,  0.108,  0.065,  0.079},
						{'W', 108,  137,   96,   0.077,  0.013,  0.064,  0.167},
						{'Y',  69,  147,  114,   0.082,  0.065,  0.114,  0.125},
						{'V', 106,  170,   50,   0.062,  0.048,  0.028,  0.053}};
	
	list obj;
	int index;
	ifstream in;
	in.open("input_file.txt");

	while (!in.eof())
	{	
		int flag = 0;
		if (!(in >> temp)){
			break;
		}
		temp = toupper(temp);
		for(int i=0; i<20 ;i++)
		{
			if ((double)temp==(double)data[i][0])
			{
				flag = 1;
				index=i;
				break;
			}
		}
		if(flag==0){
			cout << "INVALID INPUT";
			break;
		}
		obj.add_tail(name[index],index,data);
	}
	cout << "Input String : ";
	obj.print_inp();
	cout << endl;
	in.close();
	
	
	obj.calc_avg();
	obj.display();

	obj.find_alpha();
	cout << endl;
	obj.find_beta();
	
	obj.alpha_string();
	obj.sheet_string();
	obj.beta_turn();
	obj.struct_string();
	
}
