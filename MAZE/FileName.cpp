#include <iostream>
#include <queue>
#include <utility>
#include <random>
#include <stack>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <conio.h>

using namespace std;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int n;
int r[4] = { 0, 1, 2, 3 };
vector<vector<int>> v;

void CursorView(BOOL b)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = b; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

enum Color
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};

void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

bool exist(int x, int y)
{
	if (x < 0 || y < 0 || x >= 2 * n - 1 || y >= 2 * n - 1 || v[x][y] == 1)
		return false;
	else
		return true;
}

void random()
{
	int ran = rand() % 1000;
	int idx1, idx2;
	for (int i = 0; i < ran; i++)
	{
		idx1 = rand() % 4;
		idx2 = rand() % 4;
		swap(r[idx1], r[idx2]);
	}
	return;
}

void play();

int main(void)
{
	system("title MAZE");
	cout << "미로의 크기 입력(N × N): ";
	cin >> n;
	cin.ignore();
	if (n == 0)
	{
		cout << "미로의 크기가 0입니다.\n다시 입력하려면 아무 키나 누르세요.";
		while (1)
		{
			if (kbhit())
			{
				getch();
				break;
			}
		}
		system("cls");
		main();
	}
	CursorView(FALSE);
	srand((unsigned)time(NULL));
	play();
	return 0;
}

void play()
{
	vector<int> ve;
	queue<pair<int, int>> q;
	for (int i = 0; i < 2 * n - 1; i++)
		ve.push_back(0);
	for (int i = 0; i < 2 * n - 1; i++)
		v.push_back(ve);
	q.push({ 0,0 });
	v[0][0] = 1;
	pair<int, int> p;
	int x, y;
	stack<pair<int, int>> st;
	st.push({ 0, 0 });
	while (!st.empty())
	{
		p = st.top();
		x = p.first;
		y = p.second;
		random();
		for (int i = 0; i < 5; i++)
		{
			if (i == 4 || (x == 2 * n - 2 && y == 2 * n - 2))
			{
				st.pop();
				break;
			}
			else if (exist(x + 2 * dx[r[i]], y + 2 * dy[r[i]]))
			{
				st.push({ x + 2 * dx[r[i]], y + 2 * dy[r[i]] });
				v[x + dx[r[i]]][y + dy[r[i]]] = 1;
				v[x + 2 * dx[r[i]]][y + 2 * dy[r[i]]] = 1;
				break;
			}
		}
	}
	clock_t start, finish;
	cout << '\n';
	system("cls");
	for (int i = 0; i < 2 * n + 1; i++)
	{
		textcolor(BLACK, WHITE);
		cout << "  ";
	}
	cout << '\n';
	for (int i = 0; i < 2 * n - 1; i++)
	{
		textcolor(BLACK, WHITE);
		cout << "  ";
		for (int j = 0; j < 2 * n - 1; j++)
		{
			if ((i == 2 * n - 2 && j == 2 * n - 2) || (i == 0 && j == 0))
			{
				textcolor(WHITE, BLACK);
				cout << "♭ ";
			}
			else
			{
				if (v[i][j] == 0)
				{
					textcolor(BLACK, WHITE);
					cout << "  ";
				}
				else
				{
					textcolor(WHITE, BLACK);
					cout << "  ";
				}
			}
		}
		textcolor(BLACK, WHITE);
		cout << "  ";
		cout << '\n';
	}
	for (int i = 0; i < 2 * n + 1; i++)
	{
		textcolor(BLACK, WHITE);
		cout << "  ";
	}
	x = 3;
	y = 2;
	start = clock();
	int a = 1;
	while (x != 4 * n - 1 || y != 2 * n)
	{
		gotoxy(x, y);
		cout << "  ";
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && (x - 3) / 2 - 1 >= 0 && v[y - 2][(x - 3) / 2 - 1] != 0) //왼쪽
		{
			x -= 2;
			a = 0;
		}
		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && x + 2 <= 4 * n && v[y - 2][(x - 3) / 2 + 1] != 0) //오른쪽
		{
			x += 2;
			a = 1;
		}
		if ((GetAsyncKeyState(VK_UP) & 0x8000) && y - 1 >= 2 && v[(y - 2) - 1][(x - 3) / 2] != 0) //위
		{
			y--;
			a = 2;
		}
		if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && y + 1 <= 2 * n && v[(y - 2) + 1][(x - 3) / 2] != 0) //아래
		{
			y++;
			a = 3;
		}
		gotoxy(x, y);
		textcolor(RED, BLACK);
		switch (a)
		{
		case 0:
			cout << "◀";
			break;
		case 1:
			cout << "▶";
			break;
		case 2:
			cout << "▲";
			break;
		case 3:
			cout << "▼";
			break;
		}
		Sleep(100);
	}
	finish = clock();
	system("cls");
	for (int i = 0; i < 2 * n + 1; i++)
	{
		textcolor(BLACK, WHITE);
		cout << "  ";
	}
	cout << '\n';
	for (int i = 0; i < 2 * n - 1; i++)
	{
		textcolor(BLACK, WHITE);
		cout << "  ";
		for (int j = 0; j < 2 * n - 1; j++)
		{
			if ((i == 2 * n - 2 && j == 2 * n - 2))
			{
				textcolor(RED, BLACK);
				cout << "★ ";
			}
			else
			{
				if (v[i][j] == 0)
				{
					textcolor(BLACK, WHITE);
					cout << "  ";
				}
				else
				{
					textcolor(WHITE, BLACK);
					cout << "  ";
				}
			}
		}
		textcolor(BLACK, WHITE);
		cout << "  ";
		cout << '\n';
	}
	for (int i = 0; i < 2 * n + 1; i++)
	{
		textcolor(BLACK, WHITE);
		cout << "  ";
	}
	finish -= start;
	textcolor(YELLOW, BLACK);
	int h, m;
	double s;
	h = ((int)finish / CLOCKS_PER_SEC) / 3600;
	m = (((int)finish / CLOCKS_PER_SEC) / 60) % 60;
	s = (finish / CLOCKS_PER_SEC) % 60;

	cout << "\n\n당신의 기록은 ";
	if (h != 0)
		cout << h << "시간 " << m << "분 ";
	else if (m != 0)
		cout << m << "분 ";
	cout << s << "초 입니다.";
	cout << "\n\n다시 플레이하시겠습니까? (Y / N): ";
	char ans;
	cin >> ans;
	if (ans == 'Y' || ans == 'y')
		main();
	else
		return;
}
