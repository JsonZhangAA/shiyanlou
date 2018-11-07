#include <ncurses.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string>
#include <sstream>

int key;
WINDOW * game_win;
WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win,0,0);
	wrefresh(local_win);
	return local_win;
}

class Piece{
public:
	Piece(){
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++)
				shape[i][j]=0;
		}
		shape_id=3;
		for(int i=0;i<30;i++){
			for(int j=0;j<40;j++)
				map[i][j]=0;
		}
		pos_x=1;
		pos_y=5;
	}
	void show();
	void nextShape();
	void changeShape();
	void clearShape();
	bool reachBottom();
	bool fullLine(int & i);
private:
	int pos_x,pos_y;
	int shape_x,shape_y,shape_id;
	int shape[4][4];
	int map[30][40];
};

bool Piece::fullLine(int & i){
	for(int j=0;j<8;j++){
		if(map[i+1][j+1]==0)
			return false;
	}
	return true;
}
bool Piece::reachBottom(){
	for(int i=0;i<shape_x;i++){
		for(int j=0;j<shape_y;j++){
			if(shape[i][j]==1){
				if(pos_x+i>27){
					return true;
				}
				if(pos_y+j>37||pos_y+j<0){
					return true;
				}
				if(map[pos_x+i+1][pos_y+j+1]==1){
					return true;
				}
			}
		}
	}
	return false;
}

void Piece::clearShape(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			mvwaddch(game_win,pos_x+i+1,pos_y+j+1,' ');
		}
	}
}
void Piece::changeShape(){
	int temp[4][4];
	int temp1[4][4];
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			temp[j][i]=shape[i][j];
		}
	}
	int temp2=shape_x;
	shape_x=shape_y;
	shape_y=temp2;
	for(int i=0;i<shape_x;i++){
		for(int j=0;j<shape_y;j++){
			temp1[i][shape_y-1-j]=temp[i][j];
		}
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++)
			shape[i][j]=temp1[i][j];
	}
}

void Piece::nextShape(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++)
			shape[i][j]=0;
	}
	switch(shape_id){
		case 0:
			shape[0][0]=1;
			shape[1][0]=1;
			shape[2][0]=1;
			shape[2][1]=1;
			shape_x=3,shape_y=2;
			break;
		case 1:
			shape[0][0]=1;
			shape[0][1]=1;
			shape[1][1]=1;
			shape[1][2]=1;
		    shape_x=2;
			shape_y=3;
			break;   
		case 2:
			shape[0][0]=1;
			shape[0][1]=1;
			shape[0][2]=1;
			shape[1][1]=1;
			shape_x=2;
			shape_y=3; 
			break; 
		case 3:
			shape[0][0]=1;
			shape[1][0]=1;
			shape[2][0]=1;
			shape[3][0]=1;
			shape_x=4;
			shape_y=1;
			break;
		case 4:
			shape[0][0]=1;
			shape[0][1]=1;
			shape[1][0]=1;
			shape[1][1]=1;
			shape_x=2;
			shape_y=2;
			break;                                                                                                                                                                                                                                                                                              
	}
}

void Piece::show(){
	fd_set set;
	FD_ZERO(&set);
	FD_SET(0, &set);
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec= 500000;
	if (select(1, &set, NULL, NULL, &timeout) == 0){
		//clearShape();
		mvwprintw(game_win,21,20,"+");
		pos_x++;
		if(reachBottom()){
			pos_x--;
			mvwprintw(game_win,21,20,"=");
			std::string tempS;
			std::ostringstream ex_msg;
			ex_msg<<"shape: "<<shape_x<<" "<<shape_y;
			tempS=ex_msg.str();
			mvwprintw(game_win,20,20,tempS.c_str());
			int x=10;
			for(int i=0;i<shape_x;i++){
				for(int j=0;j<shape_y;j++){
					if(shape[i][j]==1){
						//列上的移动
						//mvwaddch(game_win,pos_x+i,pos_y+j,' ');
						//mvwaddch(game_win,pos_x+i,pos_y+j+1,'#');

						//行上的移动
						//mvwaddch(game_win,pos_x+i,pos_y+1+j,' ');
						//ex_msg<<"i: "<<pos_x+i+1<<" j: "<<pos_y+j+1;
						//tempS=ex_msg.str();
						//mvwprintw(game_win,x++,10,tempS.c_str());
						map[pos_x+i+1][pos_y+j+1]=1;
						mvwaddch(game_win,pos_x+i+1,pos_y+j+1,'#');
					}
				}
			}
			pos_x=1;
			pos_y=5;
			shape_id=3;
			nextShape();
			wrefresh(game_win);
			int flag=1;
			if(flag==1){
				for(int i=27;i>=2;i--){
					while(fullLine(i)){
							int k=i;
							while(fullLine(k)){
								k--;
							}
							for(int j=0;j<8;j++){
								map[k+2][j+1]=0;
								mvwaddch(game_win,k+2,j+1,' ');
							}
							int kk=k+1;
							for(;kk>=2;kk--){
								for(int jj=0;jj<8;jj++){
									if(map[kk][jj+1]==1){
										map[kk+1][jj+1]=1;
										mvwaddch(game_win,kk+1,jj+1,'#');
									}else{
										map[kk+1][jj+1]=0;
										mvwaddch(game_win,kk+1,jj+1,' ');
									}
								}
							}
							//mvwaddch(game_win,k+1,j,' ');
							wrefresh(game_win);
					}
				}
			}
		}else{
			mvwprintw(game_win,21,20,"-");
			for(int i=3;i>=0;i--){
				for(int j=3;j>=0;j--){
					if(shape[i][j]==1){
						//列上的移动
						//mvwaddch(game_win,pos_x+i,pos_y+j,' ');
						//mvwaddch(game_win,pos_x+i,pos_y+j+1,'#');

						//行上的移动
						std::string tempS;
						std::ostringstream ex_msg;
						ex_msg<<"pos_x: "<<pos_x<<"\n";
						tempS=ex_msg.str();
						mvwprintw(game_win,9,10,tempS.c_str());
						int x=11;
						/*for(int k=0;k<shape_x;k++){
							for(int kk=0;kk<shape_y;kk++){
								if(shape[k][kk]==1){
									ex_msg<<"i: "<<k<<" j: "<<kk<<" "<<shape[k][kk];
									tempS=ex_msg.str();
									mvwprintw(game_win,x++,10,tempS.c_str());
								}
							}
						}*/
						mvwaddch(game_win,pos_x+i,pos_y+1+j,' ');
						mvwaddch(game_win,pos_x+i+1,pos_y+1+j,'#');
					}
				}
			}
			//pos_x++;
			//pos_y++;
			wrefresh(game_win);
		}
	}
	if(FD_ISSET(0,&set)){
		while((key=getch())==-1);

		if(key==KEY_RIGHT){
			//clearShape();
			pos_y++;
			if(reachBottom()){
				pos_y--;
			}else{
				for(int i=0;i<=3;i++){
					for(int j=3;j>=0;j--){
						if(shape[i][j]==1){
							//列上的移动
							mvwaddch(game_win,pos_x+i+1,pos_y+j,' ');
							mvwaddch(game_win,pos_x+i+1,pos_y+j+1,'#');
						}
					}
				}
				wrefresh(game_win);
			}
		}

		if(key==KEY_LEFT){
			//clearShape();
			pos_y--;
			if(reachBottom()){
				pos_y++;
			}else{
				for(int i=0;i<=3;i++){
					for(int j=0;j<=3;j++){
						if(shape[i][j]==1){
							//列上的移动
							mvwaddch(game_win,pos_x+i+1,pos_y+j+2,' ');
							mvwaddch(game_win,pos_x+i+1,pos_y+j+1,'#');
						}
					}
				}
				wrefresh(game_win);
			}
		}

		if(key==KEY_UP){
			changeShape();
			clearShape();
			for(int i=3;i>=0;i--){
				for(int j=3;j>=0;j--){
					if(shape[i][j]==1){
						//列上的移动
						//mvwaddch(game_win,pos_x+i,pos_y+j,' ');
						//mvwaddch(game_win,pos_x+i,pos_y+j+1,'#');

						//mvwaddch(game_win,pos_x+i,pos_y+1+j,' ');
						mvwaddch(game_win,pos_x+i+1,pos_y+1+j,'#');
					}
				}
			}
			wrefresh(game_win);
		}
	}
}

int main()
{
	initscr();
	//raw();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr,TRUE);

	refresh();
/*	printw("Hello world!");
	refresh();
	getch();
	endwin();*/
	game_win=create_newwin(30,40,0,0);
	//wprintw(game_win,"Hello World!");
	wborder(game_win, '*', '*', '*', '*', '*', '*', '*', '*');

	Piece pce;
	pce.nextShape();
	while(1){
		pce.show();
	}

	wrefresh(game_win);
	getch();
	endwin();
	return 0;
}
