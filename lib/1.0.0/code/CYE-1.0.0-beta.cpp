#include <iostream>
#include <raylib.h>
using namespace std;
int const windowx=1009,windowy=807;
int const piece_x=100,piece_y=100;
int color_piece_color_R=200,color_piece_color_G=200,color_piece_color_B=200;
int answer_color_R=254,answer_color_G=200,answer_color_B=15;

int game_num=0;
int answerx,answery;

bool mouse=true;

int heart=1;

void choice_and_draw_ans(int pcz){
	if(mouse){
		answerx=GetRandomValue(0,windowx/piece_x)*101%1010;
		answery=GetRandomValue(0,windowy/piece_y)*101%808;
		answer_color_R=(color_piece_color_R+pcz)%256;
		answer_color_G=(color_piece_color_G+pcz)%256;
		answer_color_B=(color_piece_color_B+pcz)%256;
	}
	Color answer_piece_color={(unsigned char)answer_color_R,(unsigned char)answer_color_G,(unsigned char)answer_color_B,255};
	//cout<<"答案坐标"<<" x:"<<answerx<<" y:"<<answery<<endl;//调试TODO
	DrawRectangle(answerx,answery,piece_x,piece_y,answer_piece_color);
}

void color_piece(int R,int G,int B){
	//cout << "绘制颜色: " << R << "," << G << "," << B << endl;  // 调试 TODO
	Color piece_color={(unsigned char)R,(unsigned char)G,(unsigned char)B,255};
	//int count;//调试 TODO
	for(int i=0;i<=windowx;i+=piece_x+1){
		for(int j=0;j<=windowy;j+=piece_y+1){
			DrawRectangle(i,j,piece_x,piece_y,piece_color);
			//count++;//调试 TODO
		}
	}
	//cout<<"绘制了"<<count<<"块"<<endl;//调试 TODO
	int pcz=max(1,100-game_num*2);
	choice_and_draw_ans(pcz);
}
void add_window(int x,int y,const string& name,int fps){
	InitWindow(x,y,name.c_str());
	SetTargetFPS(fps);
}

void game_main(){
	add_window(windowx,windowy,"Challenge your eyes!",60);
	/*
	if (!IsWindowReady()) {
		cout << "窗口创建失败！" << endl;
		return;
	}
	cout << "窗口创建成功！" << endl;
	*/
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLACK);
		
		mouse=false;
		
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			int mouseX=GetMouseX();
			int mouseY=GetMouseY();
			if(answerx<=mouseX&&answerx+100>=mouseX&&answery<=mouseY&&answery+100>=mouseY){
				
				game_num++;
				heart++;
				
				ClearBackground(BLACK);
				
				mouse=true;
				SetRandomSeed(GetTime()*1000);
				int a=GetRandomValue(0,1000);
				SetRandomSeed((GetTime()*a-10)*(GetTime()));
			}else{
				heart--;
			}
		}
		
		if(!heart){
			while(heart+300){
				ClearBackground(BLACK);
				DrawText("YOU ARE FAILURE!",450,350,15,RED);
				heart--;
			}
			WaitTime(0.5);
			return;
		}
		
		if(mouse){
			color_piece_color_R=GetRandomValue(0,255);
			color_piece_color_G=GetRandomValue(0,255);
			color_piece_color_B=GetRandomValue(0,255);
		}
		
		/*
		cout << "绘制前颜色: R=" << color_piece_color_R 
		<< " G=" << color_piece_color_G 
		<< " B=" << color_piece_color_B << endl;
		*/
		color_piece(color_piece_color_R,color_piece_color_G,color_piece_color_B);
		
		EndDrawing();
	}
}

int main(){
	game_main();
	return 0;
}
