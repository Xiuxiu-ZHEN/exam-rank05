#include "life.h"
//初始化 同时分配空间 同时处理leak
int init_game(t_game* game, char** av)
{
	game->width = atoi(av[1]);
	game->height = atoi(av[2]);
	game->iterations = atoi(av[3]);
	game->alive = 'O';//大写的O不是0
	game->dead = ' ';
	game->i = 0;//遍历行 board[i][j]当前位置的格子
	game->j = 0;//遍历列 x轴向右,y轴向下,(0,0)开始. i是y轴是第几行,j是x轴是第几列!!!
	game->draw = 0;//当前笔的状态, 0是抬着,1是放下
	//-----------分配行空间=分配棋盘空间------------------
	game->board = (char**)malloc((game->height) * sizeof(char *));//现在有board[i]来表示第几行
	if(!(game->board))
		return(-1);
	for (int i = 0; i < game->height; i++)//把每一行的指针都标记成悬空指针 = 每一行什么都没有
		game->board[i] = NULL;//分配不需要遍历,悬空需要//初始化每一行
	//-----------分配格子空间-------------
	for(int i = 0; i < game->height; i++)
	{
		game->board[i] = (char *)malloc((game->width) * sizeof(char));//现在有board[i][j]来表示第几行第几列
		if(!(game->board[i])) {//分配需要遍历,清空不需要
			free_board(game);
			return(-1);
		}
		for(int j = 0; j < game->width; j++){//初始化每个格子
			game->board[i][j] = ' ';
		}
	}
	//----------------------------------
	return(0);
}
//读取用户输入的命令，根据 w/a/s/d 移动笔，根据 x 控制是否画线，把画过的格子变成活细胞 'O'。
/*
棋盘:
game->i
game->j
当前笔的位置:game->draw
*/
void fill_board(t_game* game)
{
	char buffer;//保存一次读到的字符,比如dxss\n,第一次buffer = 'd'第二次buffer = 'x'
	int flag;//flag = 0有效,flag = 1当下这个字符是无效字符 比如dxss1234
			//从标准输入读取1个字符放进&buffer
	while(read(STDIN_FILENO, &buffer, 1) == 1)//成功读到1个字符
	{
		flag = 0;
		switch (buffer)//根据一个变量的值,选择执行不同的代码。
		{
		case 'w':
			if(game->i > 0)//i是行,行>0
			game->i--;
			break;
		case 's':
			if(game->i < (game->height - 1))//行<高度-1
			game->i++;
			break;
		case 'a':
			if(game->j > 0)//列>0
			game->j--;
			break;
		case 'd':
			if(game->j < (game->width - 1))//列<宽度-1
			game->j++;
			break;
		case 'x':
			game->draw = !(game->draw);//切换game->draw 的布尔值到另一个, 0变成1, 1变成0;
			break;
		default://不是wsadx的话,flag=1
			flag = 1;//记录一下flag=1,当下是无效字符比如dxss1234
			break;
		}
		//----------------------------------
		//如果draw是true,=1 && 当下这个是有效字符
		if(game->draw && (flag == 0))
		{	//就把当前位置画成活细胞,也就是'O'//fill其实就是把画过的格子变成'O'
			game->board[game->i][game->j] = game->alive;
		}
	}
}
//没被main调用不需要写进.h
/*
(-1,-1) (-1,0) (-1,1)

( 0,-1) ( 0,0) ( 0,1)

( 1,-1) ( 1,0) ( 1,1)
*/
//double for/ double if//算的是(i, j)的邻居数量
int count_neighbors(t_game* game, int i, int j)
{				         		//行     列
	int count = 0;//统计活邻居数量
	for(int di = -1; di < 2; di++)
	{
		for(int dj = -1; dj < 2; dj++)
		{
			if((di == 0) && (dj == 0))//如果是(0,0)就跳过
				continue;
			//传进来的i和j为中心不变,基础上+位移量,就是邻居真正的画板坐标
			int ni = i + di;
			int nj = j + dj;    //邻居的坐标在[0, width]和[0, height]这个范围
			if((ni >= 0) && (nj >=0) && (ni < game->height) && (nj < game->width)) {
				if(game->board[ni][nj] == game->alive)//如果这个邻居是活细胞
					count++;
			}
		}
	}
	return(count);
}
//分配这次迭代后的temp, 根据邻居数量更改temp状态,释放这次迭代前的game, 把迭代后的新棋盘交给释放了的game->board里
int play(t_game* game)//temp是迭代后的棋盘
{	//-----------分配行空间=分配棋盘temp空间------------------
	char** temp = (char**)malloc((game->height) * sizeof(char *));
	if(!temp)
		return(-1);
	//-----------分配格子空间-------------
	for(int i = 0; i < game->height; i++)
	{
		temp[i] = (char *)malloc((game->width) * sizeof(char));
		if (!temp[i]){//其中某个格子分配失败
    		for(int k = 0; k < i; k++)
        		free(temp[k]);//free掉前边已经分配过的temp[k]
    		free(temp);//free
    		return(-1);
		}
	}
	//-----------double for 从头开始一个个格子看活邻居数量,再根据活邻居数量看迭代后的这个格子是alive还是dead-----------------------
	for(int i = 0; i < game->height; i++)
	{
		for(int j = 0; j < game->width; j++)
		{
			int neighbors = count_neighbors(game, i, j);
			if(game->board[i][j] == game->alive) {//如果当下这个格子是O,活的
				if(neighbors == 2 || neighbors == 3) {//并且如果有2/3个活邻居
					temp[i][j] = game->alive;//迭代后的格子还是活
				}
				else
					temp[i][j] = game->dead;
			}
			else {//如果当下这个格子是' ',死的
				if(neighbors == 3) {//并且如果正好有3个活邻居
					temp[i][j] = game->alive;//迭代之后这个格子变成活的
				}
				else
					temp[i][j] = game->dead;
			}
		}
	}
	//----------------------------------
	free_board(game);//释放迭代前的game
	game->board = temp;//把这个临时的temp画板给释放后的board
	return(0);
}
//double for 这个时候game->board里边已经有了play里的temp
void print_board(t_game* game)
{
	for(int i = 0; i < game->height; i++)
	{
		for(int j = 0; j < game->width; j++)
		{
			putchar(game->board[i][j]);
		}
		putchar('\n');//每一行后边加
	}
}
//初始化画板失败 or 游戏结束时使用 if for 
void free_board(t_game* game)
{	//如果画板成立
	if(game->board)
	{	//遍历每一行->height
		for(int i = 0; i < game->height; i++)
		{	//如果这一行有东西,否则会double free
			if(game->board[i])
				free(game->board[i]);//释放这一行的所有指针,不用game->board[i]=NULL因为后边会NULL它的上层悬空指针
		}
		free(game->board);//再释放数组指针char**本身,把整个容器/书架拆掉
		game->board = NULL;//悬空指针,告诉操作系统：这块内存我不用了，可以回收,防止别人调用;
	}
}

int main(int ac, char** av){
	if(ac != 4)
		return (1);//检查参数必须是4个
	if(atoi(av[1]) <= 0 || atoi(av[2]) <= 0 || atoi(av[3]) < 0)
		return (1);//检查参数width height不能<=0, iterations不能<0;

	t_game game;//创建游戏结构体,但是里边还没有初始化

	if(init_game(&game, av) == -1)//初始化游戏结构体//里面一定要自我清理
		return(1);

	fill_board(&game);//填充画板

	for(int i = 0; i < game.iterations; i++) {//iterations控制下进行play
		if(play(&game) == -1) {//if
			free_board(&game);
			return(1);
		}
	}
	print_board(&game);//打印画板
	free_board(&game);//free的是最后一次迭代后的game

	return (0);
}
