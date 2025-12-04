#include "main.h"

int SelectedMember=EMPTY;
void init()
{
	initgraph(WIN_WIDTH,WIN_HEIGHT);
	loadimage (&imgs[0][0],		"img\\back.jpg",	WIN_WIDTH,WIN_HEIGHT);//背景
	loadimage (&imgs[1][0],		"img\\1_1.jpg",	  BLOCK,2*BLOCK);//马超图
	loadimage (&imgs[2][0],		"img\\2_1.jpg",	2*BLOCK,2*BLOCK);//曹操图
	loadimage (&imgs[3][0],		"img\\3_1.jpg",	  BLOCK,2*BLOCK);//赵云图
	loadimage (&imgs[4][0],		"img\\4_1.jpg",	  BLOCK,2*BLOCK);//黄忠图
	loadimage (&imgs[5][0],		"img\\5_1.jpg",	2*BLOCK,  BLOCK);//关羽图
	loadimage (&imgs[6][0],		"img\\6_1.jpg",	  BLOCK,2*BLOCK);//张飞图
	loadimage (&imgs[7][0],		"img\\7_1.jpg",	  BLOCK,  BLOCK);//士兵图
	loadimage (&imgs[8][0],		"img\\8_1.jpg",	  BLOCK,  BLOCK);//士兵图
	loadimage (&imgs[9][0],		"img\\9_1.jpg",	  BLOCK,  BLOCK);//士兵图
	loadimage (&imgs[10][0],	"img\\10_1.jpg",  BLOCK,  BLOCK);//士兵图
	loadimage (&imgs[1][1],		"img\\1_2.jpg",	  BLOCK,2*BLOCK);//马超2图
	loadimage (&imgs[2][1],		"img\\2_2.jpg",	2*BLOCK,2*BLOCK);//曹操2图
	loadimage (&imgs[3][1],		"img\\3_2.jpg",	  BLOCK,2*BLOCK);//赵云2图
	loadimage (&imgs[4][1],		"img\\4_2.jpg",	  BLOCK,2*BLOCK);//黄忠2图
	loadimage (&imgs[5][1],		"img\\5_2.jpg",	2*BLOCK,  BLOCK);//关羽2图
	loadimage (&imgs[6][1],		"img\\6_2.jpg",	  BLOCK,2*BLOCK);//张飞2图
	loadimage (&imgs[7][1],		"img\\7_2.jpg",	  BLOCK,  BLOCK);//士兵2图
	loadimage (&imgs[8][1],		"img\\8_2.jpg",	  BLOCK,  BLOCK);//士兵2图
	loadimage (&imgs[9][1],		"img\\9_2.jpg",	  BLOCK,  BLOCK);//士兵2图
	loadimage (&imgs[10][1],	"img\\10_2.jpg",  BLOCK,  BLOCK);//士兵2图
	
		
}

void music()//背景音乐
{
	mciSendString("close bgm\\bg.mp3",0,0,0);
	mciSendString("open bgm\\bg.mp3",0,0,0);
	mciSendString("play bgm\\bg.mp3",0,0,0);
}

void paint()
{
	BeginBatchDrawEx();

	putimage(0,0,&imgs[0][0]);

	for(int i=1;i<=10;i++){//地图上一共有十个人物，一个曹操、五虎将、四个兵
		for(int row=0;row<5;row++){//遍历数组
			for(int col=0;col<4;col++){
				if(Board[row][col]==i){
					int x=col*BLOCK;
					int y=row*BLOCK;
					if(SelectedMember==i){//遍历到的当前人物若被选择则高亮
						putimage(x,y,&imgs[i][1]);
					}
					else{
						putimage(x,y,&imgs[i][0]);
					}
					goto NEXT;//goto语句直接连续跳出两个循环，i++，即开始绘制下一个人物
				}
			}
		}
NEXT:
		continue;
	}
	EndBatchDraw();//批量处理防止闪烁
}
bool able(struct direction direct)//判断移动是否合法
{
	for(int row=0;row<5;row++){
		for(int col=0;col<4;col++){
			if(Board[row][col]==SelectedMember){
				if(Board[row+direct.row_off][col+direct.col_off]!=EMPTY&&
					Board[row+direct.row_off][col+direct.col_off]!=SelectedMember)//如果要移到的位置被别的人物占据
					return false;
			}
		}
	}
	return true;
}

void move(struct direction direction)
{
	if(able(direction)==false){
		SelectedMember=EMPTY;
		return;
	}
	mciSendString("close bgm\\clicks.mp3",0,0,0);
	mciSendString("open bgm\\clicks.mp3",0,0,0);
	mciSendString("play bgm\\clicks.mp3",0,0,0);//移动音效
	struct position blocks[4];
	int cnt=0;
	/*存入当前人物占据的所有坐标*/
	for(int row=0;row<5;row++){
		for(int col=0;col<4;col++){
			if(Board[row][col]==SelectedMember){
				Board[row][col]=EMPTY;
				blocks[cnt].row=row;
				blocks[cnt].col=col;
				cnt++;
			}
		}
	}
	for(int i=0;i<cnt;i++)//人物的每一部分都要打上横纵坐标偏移量，不用分析上下左右，大大减少代码量
	{
		int row=blocks[i].row+direction.row_off;
		int col=blocks[i].col+direction.col_off;
		Board[row][col]=SelectedMember;
	}
	

	SelectedMember=EMPTY;//移动完毕，当前选择人物置空
}


void game()
{
	music();
	MOUSEMSG msg;
    int pmx,pmy;
    while(true)
    {	
		paint();//绘制
        while(MouseHit())//检测到有鼠标按下执行以下循环
        {	
	
            msg=GetMouseMsg();
            if(msg.uMsg==WM_LBUTTONDOWN)//第一次按下左键时高亮显示选择的人物
            {
				pmx=msg.y/150;
				pmy=msg.x/150;
				if(SelectedMember==EMPTY)//选择人物
				{
					SelectedMember=Board[pmx][pmy];
				}
				else
				{
					if(Board[pmx][pmy]!=EMPTY)
					{
						SelectedMember=Board[pmx][pmy];//如果已经选好一个人物，再次按下会更新人物
						return;
					}
					//第二次按下，找移到位置
					if(pmx-1>=0&&Board[pmx-1][pmy]==SelectedMember)
					//如果第二次选择的位置的上方是已选定的人物，则人物下移一
						move(GO_DOWN);

					if(pmx+1<5&&Board[pmx+1][pmy]==SelectedMember)
						move(GO_UP);

					if(pmy+1<4&&Board[pmx][pmy+1]==SelectedMember)
						move(GO_LEFT);

					if(pmy-1>=0&&Board[pmx][pmy-1]==SelectedMember)
						move(GO_RIGHT);	
				}

			}
		}
	}
}

void win()
{
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);//黑字
	settextstyle(40, 0, _T("黑体"));
	outtextxy(150, 600, _T("你成功放跑了曹操!"));
}

void main()
{
	init();
	
	while(Board[4][1]!=CAO_CAO&&Board[4][2]!=CAO_CAO)//判断获胜的标志
	{
		game();

	}
	win();
	getch();
}
