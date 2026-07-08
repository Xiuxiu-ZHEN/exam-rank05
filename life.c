#include "life.h"

int init_game(t_game* game, char* av[])
{
	game->width = atoi(av[1]);
	game->height = atoi(av[2]);
	game->iterations = atoi(av[3]);
	game->alive = 'O';//大写的O不是0
	game->dead = ' ';
	game->i = 0;//遍历行 board[i][j]当前位置的格子
	game->j = 0;//遍历列 x轴向右,y轴向下,(0,0)开始. i是y轴是第几行,j是x轴是第几列!!!
	game->draw = 0;//当前笔的状态, 0是抬着,1是放下
	game->board = (char**)malloc((game->height) * sizeof(char *));
	if(!(game->board))
		return(-1);
	for (int i = 0; i < game->height; i++)////每一行都标记成空指针=每一行什么都没有
		game->board[i] = NULL;

	for(int i = 0; i < game->height; i++)
	{	//每一行都分配game->width个空间
		//如果这一行分配失败,free_board
		game->board[i] = (char *)malloc((game->width) * sizeof(char));
		if(!(game->board[i])) {
			free_board(game);
			return(-1);
		}
		//把每一行的空间都初始化为' '
		for(int j = 0; j < game->width; j++){//
			game->board[i][j] = ' ';
		}
	}
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
	int flag;//用来判断这个字符是不是wsad。flag = 0有效,flag = 1无效 比如dxss1234
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
			game->draw = !(game->draw);//
			break;
		default://其他情况:忽略,记录一下flag=1遇到了无效字符比如dxss1234
			flag = 1;
			break;
		}
		//如果draw是1 && 没有无效字符
		if(game->draw && (flag == 0))
		{	//就把当前位置画成活细胞,也就是'O'
			game->board[game->i][game->j] = game->alive;
		}
	}
}
//没被main调用不需要写进.h
int count_neighbors(t_game* game, int i, int j)
{
	int count = 0;
	for(int di = -1; di < 2; di++)
	{
		for(int dj = -1; dj < 2; dj++)
		{
			if((di == 0) && (dj == 0))
				continue;

			int ni = i + di;
			int nj = j + dj;
			if((ni >= 0) && (nj >=0) && (ni < game->height) && (nj < game->width)) {
				if(game->board[ni][nj] == game->alive)
					count++;
			}
		}
	}
	return(count);
}

int play(t_game* game)
{
	char** temp = (char**)malloc((game->height) * sizeof(char *));
	if(!temp)
		return(-1);
	for(int i = 0; i < game->height; i++)
	{
		temp[i] = (char *)malloc((game->width) * sizeof(char));
		if (!temp[i]){
    		for(int k = 0; k < i; k++)
        		free(temp[k]);
    		free(temp);
    		return(-1);
		}
	}

	for(int i = 0; i < game->height; i++)
	{
		for(int j = 0; j < game->width; j++)
		{
			int neighbors = count_neighbors(game, i, j);
			if(game->board[i][j] == game->alive) {
				if(neighbors == 2 || neighbors == 3) {
					temp[i][j] = game->alive;
				}
				else
					temp[i][j] = game->dead;
			}
			else {
				if(neighbors == 3) {
					temp[i][j] = game->alive;
				}
				else
					temp[i][j] = game->dead;
			}
		}
	}

	free_board(game);
	game->board = temp;
	return(0);
}

void print_board(t_game* game)
{
	for(int i = 0; i < game->height; i++)
	{
		for(int j = 0; j < game->width; j++)
		{
			putchar(game->board[i][j]);
		}
		putchar('\n');
	}
}
//初始化画板失败 or 游戏结束时使用
void free_board(t_game* game)
{	//如果画板里有东西
	if(game->board)
	{	//遍历每一行
		for(int i = 0; i < game->height; i++)
		{	//如果这一行有东西
			if(game->board[i])
				free(game->board[i]);//释放这一行,不用game->board[i]=NULL因为后边会NULL它的上层悬空指针
		}
		free(game->board);//再释放数组指针char**本身,把整个容器/书架拆掉
		game->board = NULL;//悬空指针,告诉操作系统：这块内存我不用了，可以回收,防止别人调用;
	}
}

int main(int ac, char** av)
{
	if(ac != 4)
		return (1);//检查参数必须是4个
	if(atoi(av[1]) <= 0 || atoi(av[2]) <= 0 || atoi(av[3]) < 0)
		return (1);//检查参数width height不能<=0, iterations不能<0;

	t_game game;//创建游戏结构体,但是里边还没有初始化

	if(init_game(&game, av) == -1)//初始化游戏结构体,用av
		return(1);

	fill_board(&game);//读取画板
	//--------------------------------------------
	for(int i = 0; i < game.iterations; i++) {//进行迭代
		if(play(&game) == -1) {
			free_board(&game);
			return(1);
		}
	}
	print_board(&game);//打印画板
	free_board(&game);//free内存

	return (0);
}
