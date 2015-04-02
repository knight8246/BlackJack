#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int gvcd(int card_hd[21]){												//give one different card.
	int card;
	bool unique =1;
	
	if(card_hd[0]!=0){
		do {
			unique = 1;
			card=rand()%52+1;
			for (int j=0;card_hd[j]!=0;++j){
				if (card_hd[j]==card) {
				unique=0; break;
				}
			}
		}
		while(!unique);
	}	
		else card=rand()%52+1;
	
	return(card);
}

int ctcd(int card_hd[21]){												//cout all cards in hands
	for(int i=0;card_hd[i]!=0;++i) {
		switch((card_hd[i]-1)/13){										//cout colors.
			case 3 : cout<<"clubs "; break;
			case 2 : cout<<"diamonds "; break;
			case 1 : cout<<"spades "; break;
			default : cout<<"hearts "; break;
		}
		switch((card_hd[i]-1)%13){										//cout points.
			case 0 : cout<<"A\t"; break;
			case 10: cout<<"J\t"; break;
			case 11: cout<<"Q\t"; break;
			case 12: cout<<"K\t"; break;
			default: cout<<(card_hd[i]-1)%13+1<<"\t"; break;
		}
	}
}

double u_turn(int cdn_u[2]){											//user turn
	int card_u[21] = {0};
	int k=2;
	double num_u=0.0;
	char judge;
	
	card_u[0] = gvcd(card_u);											//give first and second card
	card_u[1] = gvcd(card_u);

	cout<<"User Turn"<<endl;
	cout<<"User's cards:";
	ctcd(card_u);														//cout the cards in user's hand.

	while (true) {														//giving cards process
		num_u = 0.0;
		
		for (int i=0; i<k; ++i) {										//calculate the points of cards.
			switch (card_u[i]%13){
				case 0: num_u += 0.5; break;
				case 11:num_u += 0.5; break;
				case 12:num_u += 0.5; break;
				default : num_u += card_u[i]%13; break;
			}
		}
		if(num_u > 21.0) return 0.0;									//if bigger than 21, then means lose
		
		cout<<"\nWant another card(y/n)?";								//give one card if user wants.
		cin>>judge;
		cin.sync();
		while (judge!='Y' && judge!='y' && judge!='N' && judge!='n'){
			cout<<"Your input is illegal, please input again!";
			cin>>judge;
			cin.sync();
		}
	
		if(judge=='Y' || judge=='y'){
			card_u[k] = gvcd(card_u);
			cout<<"User's another cards:";
			ctcd(card_u);
			++k;
		}
			else break;
	}	
	cdn_u[0] = k;														//record the number of cards of user
	
	return num_u;
}

double c_turn(double num_u, int cdn){
	double num_c=0;
	int k=2;
	int card_c[21] = {0};
	
	card_c[0] = gvcd(card_c);											//give first and second card
	card_c[1] = gvcd(card_c);
	
	cout<<"Computer Turn"<<endl;										//show the cards of computer
	cout<<"Computer's' cards:";
	ctcd(card_c);
	
	for (int i=0; i<k; ++i) {											//calculater the points
		switch (card_c[i]%13){
			case 0: num_c += 0.5; break;
			case 11:num_c += 0.5; break;
			case 12:num_c += 0.5; break;
			default : num_c += card_c[i]%13; break;
		}
	}
	
	while(num_c < num_u || (num_c == num_u && k <= cdn)) {				//give card to computer if it cannot win
		card_c[k] = gvcd(card_c);
		cout<<"\nComputer's another cards:";
		ctcd(card_c);
		++k;
		num_c = 0.0;
		for (int i=0; i<k; ++i) {										
			switch (card_c[i]%13){
				case 0: num_c += 0.5; break;
				case 11:num_c += 0.5; break;
				case 12:num_c += 0.5; break;
				default : num_c += card_c[i]%13; break;
			}
		}
		if(num_c > 21.0) return 0.0;
	}
	cout<<"\nUser lose."<<endl;											//if computer donot lose, then user lose
	
	return num_c;
}

int main(){
	double num_u, num_c;
	int cdn_u[2]={0};
	char cont;
	bool conti = 1;														//record whether to continue
	
	srand(time(NULL));
	do{
		num_u = u_turn(cdn_u);											//user turn
		if (num_u == 0.0) cout<<"\nUser lose."<<endl;					
			else {
				num_c = c_turn(num_u,cdn_u[0]);							//computer turn
				if (num_c == 0.0) cout<<"\nUser win."<<endl;
			}
			
		cout<<"Continue(y/n)?";											//judge whether to continue
		cin>>cont;
		cin.sync();
		while (cont!='Y' && cont!='y' && cont!='N' && cont!='n'){
			cout<<"Your input is illegal, please input again!";
			cin>>cont;
			cin.sync();
		}
		if(cont=='N' || cont=='n') conti = 0;
	}	
	while (conti);
		
	return 0;
}
