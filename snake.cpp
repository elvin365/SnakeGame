#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
//нужен счетчик фруктов и его постоянный вывод на экран
//нужно написать случай 4

struct record 
{
	char name[20];
	int score;
};

void print(unsigned char *mas, int i, int j)//принимает икс игрек
{
	int a = 0;
	for (a = 0; a < 100 * j; a++)
	{
		if (a % 100 % (i - 1) == 0 && a % 100 != 0)
		{

			printf("%c", *(mas + a));
			printf("\n");
			a = (a / 100 + 1) * 100 - 1;
		}
		else
			printf("%c", *(mas + a));

	}
	return;
}

int main()
{
	
	record f[20],v;
	int try1 = 0;
	int nowwalls = 1;
	int d;//направление
	int wall[20][2];//массив стены
	int schu = 0, schd = 0;//счетчики высшего и низшего приоритетов
	int nowpoints;
	int quan = 0;// количество ветвящихся стен
	int size = 0;//размер ветвящейся стены
	int X = 0, Y = 0;// размеры поля
	int snake[100][2];//массив с коорд сегментов змеи, 0 игрек, 1 икс
	int snake_len = 1;//длина массива змеи
	int newx, newy;// координаты головы при движ на новую клетку
	int oldx, oldy;//координаты конца змеи
	int  z;//счетчик для перезаписи в массиве змеи
	int randx, randy;//случайные координаты еды
	int type = -1;//тип игры
	unsigned char a[100][100];//   поле игры,игрек,икс
	char key;//вводимая клавиша
	int i, j;//счетчики
	int fx, fy;//координаты фрукта
	int difficulty = 0;//сложность - промежуток времени между шагами
	printf("enter the size of field:\n1 - length\n2 - height\n");
	scanf_s("%i %i", &X, &Y);//счтитывание размеров поля икс игрек
	system("cls");
	printf("enter the difficulty:\n1 - Easy - 300 ms\n2 - hard - 130 ms\n3 - Insane - 70 ms\n4 - BADASS - 20 ms\n5 - for testers or lusers - 1500 ms\n");//выбор сложности
		scanf_s("%i", &difficulty);
	switch (difficulty)//запись сложности
	{
	case 1: 

		difficulty = 300;
		break;
	case 2:
		difficulty = 130;
		break;
	case 3:
		difficulty = 70;
		break;
	case 4:
		difficulty = 20;
		break;
	case 5:
		difficulty = 1500;
		break;
	}
	X++;
	system("cls");
	printf("enter the  type of field:\n1 - without borders\n2 - with borders\n3 - with random islands\n4 - with big random islands\n");
		scanf_s("%i", &type);
	system("cls");
	srand(time(0));
	srand(rand());
	switch (type)//заполнение поля по выбранным правилам
	{
	case 1:
		for (i = 0; i < (X + 2); i++)//заполнение поля
		{
			for (j = 0; j < (Y + 2); j++)
			{
				a[j][i] = ' ';
			}
		}
		break;
	case 2:
		for (i = 0; i < (X + 2); i++)//заполнение поля
		{
			for (j = 0; j < (Y + 2); j++)
			{
				a[j][i] = ' ';
			}
		}
		break;
	case 3:
	{
		for (i = 0; i < (X + 2); i++)//заполнение поля
		{
			for (j = 0; j < (Y + 2); j++)
			{
				if ((rand() % 10) == 0)
					a[j][i] = 219;
				else
					a[j][i] = ' ';
			}
		}
		break;
	}
	case 4:
	{for (i = 0; i < (X + 2); i++)//заполнение поля
	{
		for (j = 0; j < (Y + 2); j++)
		{
			a[j][i] = ' ';
		}
	}

	system("cls");
	printf("Enter the quantity of walls\n");
	scanf_s("%i", &quan);
	system("cls");
	printf("Enter the size of walls\n");
	scanf_s("%i", &size);
	system("cls");
	schu = size;
	schd = 0;//счетчик выс приоритета
	randx = rand() % X + 1;
	randy = rand() % Y + 1;
	while (a[randy][randx] != ' '&&schd < X*Y / 2)
	{
		randx = rand() % X + 1;
		randy = rand() % Y + 1;
		schd++;
	}
	if (schd == X*Y / 2)
	{
		printf("Error1 - nekuda stavit' pervuju tochku");
		_getch();
		return 0;//выход при отсутствии
	}
	a[randy][randx] = 219;//записал первый элемент первой стены
	nowpoints = 1;//количество напечатанных элементов стены
	wall[0][0] = randy;
	wall[0][1] = randx;//запись координат первого эл-та в массив стены
	schd = 0;
	//newy = wall[rand() % nowpoints][0];//выбор случайного эл-та стены
	//newx = wall[rand() % nowpoints][1];
	while (nowpoints<size && schd < size + 50)
	{
		d = rand() % 4;
		switch (d)
		{
		case 0:
			if (a[wall[nowpoints - 1][0] - 1][wall[nowpoints -

				1][1]] != '^' && a[wall[nowpoints - 1][0] - 1][wall[nowpoints - 1][1]] != 219)//если предполагаемый элемент - не стена и не граница, то
			{
				a[wall[nowpoints - 1][0] - 1][wall[nowpoints - 1][1]] = 219;//рисуем там стену
			nowpoints++;	//увеличиваем количество точек
				wall[nowpoints - 1][0] = wall[nowpoints -2][0] - 1;//запоминаем в новый элемент массива стены его собственные координаты
			wall[nowpoints - 1][1] = wall[nowpoints -

				2][1];
			break;
			}
		case 1:
			if (a[wall[nowpoints - 1][0]][wall[nowpoints -

				1][1] + 1] != '^' && a[wall[nowpoints - 1][0]][wall[nowpoints - 1][1] + 1] != 219)//если предполагаемый элемент - не стена и не граница, то
			{
				a[wall[nowpoints - 1][0]][wall[nowpoints- 1][1] + 1] = 219;//рисуем там стену
			nowpoints++;	//увеличиваем количество точек
				wall[nowpoints - 1][0] = wall[nowpoints -2][0];//запоминаем в новый элемент массива стены его собственные координаты
			wall[nowpoints - 1][1] = wall[nowpoints -2][1] + 1;
			break;
			}
		case 2:
			if (a[wall[nowpoints - 1][0] + 1][wall[nowpoints- 1][1]] != '^' && a[wall[nowpoints - 1][0] + 1][wall[nowpoints - 1][1]] != 219)//если предполагаемый элемент - не стена и не граница, то
			{
				a[wall[nowpoints - 1][0] + 1][wall

				[nowpoints - 1][1]] = 219;//рисуем там стену
			nowpoints++;	//увеличиваем количество точек
				wall[nowpoints - 1][0] = wall[nowpoints -2][0] + 1;//запоминаем в новый элемент массива стены его собственные координаты
			wall[nowpoints - 1][1] = wall[nowpoints -2][1];
			break;
			}
		case 3:
			if (a[wall[nowpoints - 1][0]][wall[nowpoints -1][1] - 1] != '^' && a[wall[nowpoints - 1][0]][wall[nowpoints - 1][1] - 1] != 219)//если 	предполагаемый элемент - не стена и не граница, то
			{
				a[wall[nowpoints - 1][0]][wall[nowpoints- 1][1] - 1] = 219;//рисуем там стену
			nowpoints++;	//увеличиваем количество точек
				wall[nowpoints - 1][0] = wall[nowpoints -

				2][0];//запоминаем в новый элемент массива стены его собственные координаты
			wall[nowpoints - 1][1] = wall[nowpoints -

				2][1] - 1;
			break;
			}
		default:schd++;
		}
	}
	if (schd == size + 50)
	{
		printf("Error2.1 - nekuda prodoljat'");
		_getch();
		return 0;//выход при отсутствии
	}
	//здесь продолжение для новых начальных точек

	while (nowwalls < quan && schu < quan + 50)
	{
		randx = rand() % X + 1;
		randy = rand() % Y + 1;
		while (a[randy][randx] != ' ' && schd < X*Y / 2)
		{
			randx = rand() % X + 1;
			randy = rand() % Y + 1;
			schd++;
		}
		if (schd == X*Y / 2)
		{
			schu++;
			continue;//выход при отсутствии на более высокий уровень цикла
		}
		a[randy][randx] = 219;//записал первый элемент стены
		nowpoints = 1;//количество напечатанных элементов стены
		wall[0][0] = randy;
		wall[0][1] = randx;//запись координат первого эл-та в массив стены
		schd = 0;
		while (nowpoints<size && schd < size + 50)
		{
			d = rand() % 4;
			switch (d)
			{
			case 0:
				if (a[wall[nowpoints - 1][0] - 1][wall[nowpoints - 1][1]]!= '^' && a[wall[nowpoints - 1][0] - 1][wall[nowpoints - 1][1]] != 219)//если предполагаемый элемент - не стена и не граница, то
				{
					a[wall[nowpoints - 1][0] - 1][wall[nowpoints -1][1]] = 219;//рисуем там стену
				nowpoints++;	//увеличиваем количество точек	
				wall[nowpoints - 1][0] = wall[nowpoints - 2][0] -1;//запоминаем в новый элемент массива стены его собственные координаты
				wall[nowpoints - 1][1] = wall[nowpoints - 2][1];
				break;
				}
			case 1:
				if (a[wall[nowpoints - 1][0]][wall[nowpoints - 1][1] + 1]!= '^' && a[wall[nowpoints - 1][0]][wall[nowpoints - 1][1] + 1] != 219)//если предполагаемый элемент - не стена и не граница, то
				{
					a[wall[nowpoints - 1][0]][wall[nowpoints - 1][1]+ 1] = 219;//рисуем там стену
				nowpoints++;	//увеличиваем количество точек		
				wall[nowpoints - 1][0] = wall[nowpoints - 2][0];//запоминаем в новый элемент массива стены его собственные координаты
				wall[nowpoints - 1][1] = wall[nowpoints - 2][1] +1;
				break;
				}
			case 2:
				if (a[wall[nowpoints - 1][0] + 1][wall[nowpoints - 1][1]]!= '^' && a[wall[nowpoints - 1][0] + 1][wall[nowpoints - 1][1]] != 219)//если предполагаемый элемент - не стена и не граница, то
				{
					a[wall[nowpoints - 1][0] + 1][wall[nowpoints -1][1]] = 219;//рисуем там стену
				nowpoints++;	//увеличиваем количество точек	
				wall[nowpoints - 1][0] = wall[nowpoints - 2][0] +1;//запоминаем в новый элемент массива стены его собственные координаты
				wall[nowpoints - 1][1] = wall[nowpoints - 2][1];
				break;
				}
			case 3:
				if (a[wall[nowpoints - 1][0]][wall[nowpoints - 1][1] - 1]!= '^' && a[wall[nowpoints - 1][0]][wall[nowpoints - 1][1] - 1] != 219)//если предполагаемый элемент - не стена и не граница, то
				{a[wall[nowpoints - 1][0]][wall[nowpoints - 1][1]- 1] = 219;//рисуем там стену
				nowpoints++;	//увеличиваем количество точек		
				wall[nowpoints - 1][0] = wall[nowpoints - 2][0];//запоминаем в новый элемент массива стены его собственные координаты
				wall[nowpoints - 1][1] = wall[nowpoints - 2][1] -1;
				break;
				}
			default:schd++;
			}
		}
		if (schd == size + 50)
		{
			schu++;
			continue;//выход при отсутствии на более высокий уровень цикла
		}
		nowwalls++;
	}

	if (schu == quan + 51)
	{
		printf("Error3 - nekuda stavit posledujuschuju tochku");
		_getch();
		return 0;//выход при отсутствии
	}
	break;
	}

	}//конец печати поля
	system("cls");
	for (i = 0; i <(X + 2); i++)//создание видимых границ поля
	{
		a[0][i] = '^';
	}
	for (i = 1; i < Y + 1; i++)
	{
		a[i][0] = a[i][X + 1] = '^';
	}
	for (i = 0; i < X + 2; i++)
	{
		a[Y + 1][i] = '^';
	}
	snake[0][0] = Y / 2 - 1;
	snake[0][1] = X / 2 - 1;
	a[snake[0][0]][snake[0][1]] = '@';//создание головы

	randx = rand() % X + 1;
	randy = rand() % Y + 1;
	while (a[randy][randx] != ' ')//создание фрукта по случайным координатам
	{
		randx = rand() % X + 1;
		randy = rand() % Y + 1;
	}
	a[randy][randx] = '$';
	fx = randx;//запоминание координат фрукта
	fy = randy;
	print(*a, X + 2, Y + 2);
	key = 0;
	while (key != 'q')
	{
		Sleep(difficulty);
		if (key != 10 && _kbhit() != 0)
			key = _getch();
		if (type != 1)
			switch (key)//случаи 2 - 4
			{
			case 'w':
			{
				newy = snake[0][0] - 1; newx = snake[0][1];//координаты новой точки
				if (a[newy][newx] == 219 || a[newy][newx] == 'o' || a[newy][newx] == '^')
				{
					printf("Game over\nPress Enter");  key = 10; system("cls");

					break;
				}
				else {
					if (a[newy][newx] == '$')//если еда
					{
						snake_len++;
						z = snake_len;// длина змеи(счетчик)
						a[newy][newx] = '@';//запись головы на новое место
							while (z > 1)//перезапись массива змейки
							{
								snake[z - 1][0] = snake[z - 2][0];
								snake[z - 1][1] = snake[z - 2][1];
								a[snake[z - 1][0]][snake[z - 1][1]] =

									'o';
								z--;
							}
						snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
							snake[0][1] = newx;
						randx = rand() % X + 1;
						randy = rand() % Y + 1;
						while (a[randy][randx] != ' ')
						{
							randx = rand() % X + 1;
							randy = rand() % Y + 1;
						}
						a[randy][randx] = '$';
						fx = randx;
						fy = randy;
					}


					else
					{
						oldy = snake[snake_len - 1][0];//запись координат конца змеи
							oldx = snake[snake_len - 1][1];
						z = snake_len;//уменьшенная на 1 длина змеи(счетчик)
							while (z > 1)//перезапись массива змейки
							{
								snake[z - 1][0] = snake[z - 2][0];
								snake[z - 1][1] = snake[z - 2][1];
								a[snake[z - 1][0]][snake[z - 1][1]] =

									'o';
								z--;
							}
						snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
							snake[0][1] = newx;
						a[newy][newx] = '@';//запись плюсика головы на новое место
							a[oldy][oldx] = ' ';






					}
					system("cls");
					print(*a, X + 2, Y + 2);
					printf("\n\tScore: %i\n", snake_len - 1);
				}
				break; }
			case 'a':
			{
				newy = snake[0][0]; newx = snake[0][1] - 1;//координаты новой точки
				if (a[newy][newx] == 219 || a[newy][newx] == 'o' || a[newy][newx] == '^')
				{
					printf("Game over\nPress Enter");  key = 10; system("cls");

					break;
				}
				else {
					if (a[newy][newx] == '$')//если еда
					{
						snake_len++;
						z = snake_len;// длина змеи(счетчик)
						a[newy][newx] = '@';//запись головы на новое место
						while (z > 1)//перезапись массива змейки
						{
							snake[z - 1][0] = snake[z - 2][0];
							snake[z - 1][1] = snake[z - 2][1];
							a[snake[z - 1][0]][snake[z - 1][1]] = 'o';
							z--;
						}
						snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
							snake[0][1] = newx;
						randx = rand() % X + 1;
						randy = rand() % Y + 1;
						while (a[randy][randx] != ' ')
						{
							randx = rand() % X + 1;
							randy = rand() % Y + 1;
						}
						a[randy][randx] = '$';
						fx = randx;
						fy = randy;
					}

					else
					{
						oldy = snake[snake_len - 1][0];//запись координат конца змеи
							oldx = snake[snake_len - 1][1];
						z = snake_len;//уменьшенная на 1 длина змеи(счетчик)
						while (z > 1)//перезапись массива змейки
						{
							snake[z - 1][0] = snake[z - 2][0];
							snake[z - 1][1] = snake[z - 2][1];
							a[snake[z - 1][0]][snake[z - 1][1]] = 'o';
							z--;
						}
						snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
							snake[0][1] = newx;
						a[newy][newx] = '@';//запись плюсика головы на новое место
							a[oldy][oldx] = ' ';


					}
					system("cls");
					print(*a, X + 2, Y + 2);
					printf("\n\tScore: %i\n", snake_len - 1);
				}
				break; }
			case 's':
			{
				newy = snake[0][0] + 1; newx = snake[0][1];//координаты новой точки
				if (a[newy][newx] == 219 || a[newy][newx] == 'o' || a[newy][newx] == '^')
				{
					printf("Game over\nPress Enter");  key = 10; system("cls");

					break;
				}
				else {
					if (a[newy][newx] == '$')//если еда
					{
						snake_len++;
						z = snake_len;// длина змеи(счетчик)
						a[newy][newx] = '@';//запись головы на новое место
						while (z > 1)//перезапись массива змейки
						{
							snake[z - 1][0] = snake[z - 2][0];
							snake[z - 1][1] = snake[z - 2][1];
							a[snake[z - 1][0]][snake[z - 1][1]] = 'o';
							z--;
						}
						snake[0][0] = newy;//запись в массив сегментов змейки 	новых коорд головы
							snake[0][1] = newx;
						randx = rand() % X + 1;
						randy = rand() % Y + 1;
						while (a[randy][randx] != ' ')
						{
							randx = rand() % X + 1;
							randy = rand() % Y + 1;
						}
						a[randy][randx] = '$';
						fx = randx;
						fy = randy;
					}

					else
					{
						oldy = snake[snake_len - 1][0];//запись координат конца змеи
							oldx = snake[snake_len - 1][1];
						z = snake_len;//уменьшенная на 1 длина змеи(счетчик)
						while (z > 1)//перезапись массива змейки
						{
							snake[z - 1][0] = snake[z - 2][0];
							snake[z - 1][1] = snake[z - 2][1];
							a[snake[z - 1][0]][snake[z - 1][1]] = 'o';
							z--;
						}
						snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
							snake[0][1] = newx;
						a[newy][newx] = '@';//запись плюсика головы на новое место
							a[oldy][oldx] = ' ';

					}
					system("cls");
					print(*a, X + 2, Y + 2);
					printf("\n\tScore: %i\n", snake_len - 1);

				}
				break; }
			case 'd':
			{

				newy = snake[0][0]; newx = snake[0][1] + 1;//координаты новой точки
				if (a[newy][newx] == 219 || a[newy][newx] == 'o' || a[newy][newx] == '^')
				{
					printf("Game over\nPress Enter");  key = 10; system("cls");

					break;
				}
				else {
					if (a[newy][newx] == '$')//если еда
					{
						snake_len++;
						z = snake_len;// длина змеи(счетчик)
						a[newy][newx] = '@';//запись головы на новое место
						while (z > 1)//перезапись массива змейки
						{
							snake[z - 1][0] = snake[z - 2][0];
							snake[z - 1][1] = snake[z - 2][1];
							a[snake[z - 1][0]][snake[z - 1][1]] = 'o';
							z--;
						}
						snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
							snake[0][1] = newx;
						randx = rand() % X + 1;
						randy = rand() % Y + 1;
						while (a[randy][randx] != ' ')
						{
							randx = rand() % X + 1;
							randy = rand() % Y + 1;
						}
						a[randy][randx] = '$';
						fx = randx;
						fy = randy;
					}

					else
					{
						oldy = snake[snake_len - 1][0];//запись координат конца змеи
							oldx = snake[snake_len - 1][1];
						z = snake_len;//уменьшенная на 1 длина змеи(счетчик)
						while (z > 1)//перезапись массива змейки
						{
							snake[z - 1][0] = snake[z - 2][0];
							snake[z - 1][1] = snake[z - 2][1];
							a[snake[z - 1][0]][snake[z - 1][1]] = 'o';
							z--;
						}
						snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
							snake[0][1] = newx;
						a[newy][newx] = '@';//запись головы на новое место
						a[oldy][oldx] = ' ';






					}
					system("cls");
					print(*a, X + 2, Y + 2);
					printf("\n\tScore: %i\n", snake_len - 1);
				}
				break; }

			case 10:
			{Sleep(500);
			 j = 0;
			 if (try1==0)
			 scanf_s("%c", &f[try1].name[j], 1);
			do
			{
				
				scanf_s("%c", &f[try1].name[j],1);
				j++;
			} while (f[try1].name[j-1] != 10 && j < 21);
			f[try1].score = snake_len;
			try1++;
			a[fy][fx] = ' ';//стирание фрукта
			while ((key = _getch()) != '1'&&key != '2')
			{
				printf("\nPlay again?\n1-Yes\n2-No");
				Sleep(2000);
				system("cls");
			}
			if (key == '2')
			{
				for (i = 0; i < try1; i++)
					for (j = i; j < try1; j++)
						if (f[j].score < f[i].score)
						{
							v = f[j];
							f[j] = f[i];
							f[i] = v;
						}
				for (i = try1-1; i >=0; i--)
						{
					j = 0;
					while (f[i].name[j] != 10)
					{
						printf("%c", f[i].name[j]);
						j++;
					}
					printf("\t\t%i\n", f[i].score);
						}
				_getch();
				return 0;
			}
			else
			{
				for (i = 0; i < snake_len; i++)
				{
					a[snake[i][0]][snake[i][1]] = ' ';
				}
				snake_len = 1;
				snake[0][1] = X / 2 + 1;//игрек икс
				snake[0][0] = Y / 2 + 1;//игрек икс
				a[snake[0][0]][snake[0][1]] = '@';
				randx = rand() % X + 1;
				randy = rand() % Y + 1;
				while (a[randy][randx] != ' ')
				{
					randx = rand() % X + 1;
					randy = rand() % Y + 1;
				}
				a[fy][fx] = ' ';
				a[randy][randx] = '$';
				fx = randx;
				fy = randy;
				print(*a, X + 2, Y + 2);
				printf("\n\tScore: %i\n", snake_len - 1);
			}
			}
			}
		else
			switch (key)//начало случая без границ
			{
			case 'w'://здесь проверку на столкновение со стеной
			{
				newy = snake[0][0] - 1; newx = snake[0][1];//координаты новой точки
					if (a[newy][newx] == 219 || a[newy][newx] == 'o')
					{
						printf("Game over\nPress Enter");  key = 10; break;
					}
					else if (a[newy][newx] == '^')
					{
						oldy = snake[snake_len - 1][0];//запись координат конца змеи
						oldx = snake[snake_len - 1][1];
						z = snake_len;//уменьшенная на 1 длина змеи(счетчик)
							while (z > 1)//перезапись массива змейки
							{
								snake[z - 1][0] = snake[z - 2][0];
								snake[z - 1][1] = snake[z - 2][1];
								if (a[snake[z - 1][0]][snake[z - 1][1]]

									!= '^')
									a[snake[z - 1][0]][snake[z - 1][1]] =

									'o';
								z--;
							}
						newy = Y;
						a[oldy][oldx] = ' ';
						snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
							snake[0][1] = newx;
						a[newy][newx] = '@';//запись плюсика головы на новое место
							system("cls");
						print(*a, X + 2, Y + 2);
						printf("\n\tScore: %i\n", snake_len - 1);
					}
					else {
						if (a[newy][newx] == '$')//если еда
						{
							snake_len++;
							z = snake_len;// длина змеи(счетчик)
							a[fy][fx] = ' ';//стирание фрукта
							fy = newy;
							fx = newx;
							a[newy][newx] = '@';//запись головы на новое место
								while (z > 1)//перезапись массива змейки
								{
									snake[z - 1][0] = snake[z - 2][0];
									snake[z - 1][1] = snake[z - 2][1];
									a[snake[z - 1][0]][snake[z - 1][1]] =

										'o';
									z--;
								}
							snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
								snake[0][1] = newx;
							randx = rand() % X + 1;
							randy = rand() % Y + 1;
							while (a[randy][randx] != ' ')
							{
								randx = rand() % X + 1;
								randy = rand() % Y + 1;
							}
							a[randy][randx] = '$';
							fy = randy;
							fx = randx;
						}

						else
						{
							oldy = snake[snake_len - 1][0];//запись координат конца змеи
								oldx = snake[snake_len - 1][1];
							z = snake_len;//уменьшенная на 1 длина змеи(счетчик)
								while (z > 1)//перезапись массива змейки
								{
									snake[z - 1][0] = snake[z - 2][0];
									snake[z - 1][1] = snake[z - 2][1];
									a[snake[z - 1][0]][snake[z - 1][1]] =

										'o';
									z--;
								}
							snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
								snake[0][1] = newx;
							a[newy][newx] = '@';//запись плюсика головы на новое место
								a[oldy][oldx] = ' ';

						}
						system("cls");
						print(*a, X + 2, Y + 2);
						printf("\n\tScore: %i\n", snake_len - 1);
					}
					break; }
			case 'a':
			{
				newy = snake[0][0]; newx = snake[0][1] - 1;//координаты новой точки
					if (a[newy][newx] == 219 || a[newy][newx] == 'o')
					{
						printf("Game over\nPress Enter");  key = 10; break;
					}
					else if (a[newy][newx] == '^')
					{
						oldy = snake[snake_len - 1][0];//запись координат конца змеи
							oldx = snake[snake_len - 1][1];
						z = snake_len;//уменьшенная на 1 длина змеи(счетчик)
						while (z > 1)//перезапись массива змейки
						{
							snake[z - 1][0] = snake[z - 2][0];
							snake[z - 1][1] = snake[z - 2][1];
							if (a[snake[z - 1][0]][snake[z - 1][1]] != '^')
								a[snake[z - 1][0]][snake[z - 1][1]] =

								'o';
							z--;
						}
						newx = X;
						a[oldy][oldx] = ' ';
						snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
							snake[0][1] = newx;
						a[newy][newx] = '@';//запись плюсика головы на новое место
							system("cls");
						print(*a, X + 2, Y + 2);
						printf("\n\tScore: %i\n", snake_len - 1);
					}
					else {
						if (a[newy][newx] == '$')//если еда
						{
							snake_len++;
							z = snake_len;// длина змеи(счетчик)
							a[newy][newx] = '@';//запись головы на новое место
								while (z > 1)//перезапись массива змейки
								{
									snake[z - 1][0] = snake[z - 2][0];
									snake[z - 1][1] = snake[z - 2][1];
									a[snake[z - 1][0]][snake[z - 1][1]] =

										'o';
									z--;
								}
							snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
								snake[0][1] = newx;
							randx = rand() % X + 1;
							randy = rand() % Y + 1;
							while (a[randy][randx] != ' ')
							{
								randx = rand() % X + 1;
								randy = rand() % Y + 1;
							}
							a[randy][randx] = '$';
							fy = randy;
							fx = randx;
						}

						else
						{
							oldy = snake[snake_len - 1][0];//запись координат конца змеи
								oldx = snake[snake_len - 1][1];
							z = snake_len;//уменьшенная на 1 длина змеи(счетчик)
								while (z > 1)//перезапись массива змейки
								{
									snake[z - 1][0] = snake[z - 2][0];
									snake[z - 1][1] = snake[z - 2][1];
									a[snake[z - 1][0]][snake[z - 1][1]] =

										'o';
									z--;
								}
							snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
								snake[0][1] = newx;
							a[newy][newx] = '@';//запись плюсика головы на новое место
								a[oldy][oldx] = ' ';

						}
						system("cls");
						print(*a, X + 2, Y + 2);
						printf("\n\tScore: %i\n", snake_len - 1);
					}
					break; }
			case 's':
			{
				newy = snake[0][0] + 1; newx = snake[0][1];//координаты новой точки
					if (a[newy][newx] == 219 || a[newy][newx] == 'o')
					{
						printf("Game over\nPress Enter");  key = 10; break;
					}
					else if (a[newy][newx] == '^')
					{
						oldy = snake[snake_len - 1][0];//запись координат конца змеи
							oldx = snake[snake_len - 1][1];
						z = snake_len;//уменьшенная на 1 длина змеи(счетчик)
						while (z > 1)//перезапись массива змейки
						{
							snake[z - 1][0] = snake[z - 2][0];
							snake[z - 1][1] = snake[z - 2][1];
							if (a[snake[z - 1][0]][snake[z - 1][1]] != '^')
								a[snake[z - 1][0]][snake[z - 1][1]] =

								'o';
							z--;
						}
						newy = 1;
						a[oldy][oldx] = ' ';
						snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
							snake[0][1] = newx;
						a[newy][newx] = '@';//запись плюсика головы на новое место
							system("cls");
						print(*a, X + 2, Y + 2);
						printf("\n\tScore: %i\n", snake_len - 1);
					}
					else {
						if (a[newy][newx] == '$')//если еда
						{
							snake_len++;
							z = snake_len;// длина змеи(счетчик)место
								while (z > 1)//перезапись массива змейки
								{
									snake[z - 1][0] = snake[z - 2][0];
									snake[z - 1][1] = snake[z - 2][1];
									a[snake[z - 1][0]][snake[z - 1][1]] =

										'o';
									z--;
								}
							snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
								snake[0][1] = newx;
							randx = rand() % X + 1;
							randy = rand() % Y + 1;
							while (a[randy][randx] != ' ')
							{
								randx = rand() % X + 1;
								randy = rand() % Y + 1;
							}
							a[randy][randx] = '$';
							fy = randy;
							fx = randx;
						}

						else
						{
							oldy = snake[snake_len - 1][0];//запись координат конца змеи
								oldx = snake[snake_len - 1][1];
							z = snake_len;//уменьшенная на 1 длина змеи(счетчик)
								while (z > 1)//перезапись массива змейки
								{
									snake[z - 1][0] = snake[z - 2][0];
									snake[z - 1][1] = snake[z - 2][1];
									a[snake[z - 1][0]][snake[z - 1][1]] =

										'o';
									z--;
								}
							snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
								snake[0][1] = newx;
							a[newy][newx] = '@';//запись плюсика головы на новое место
								a[oldy][oldx] = ' ';

						}
						system("cls");
						print(*a, X + 2, Y + 2);
						printf("\n\tScore: %i\n", snake_len - 1);
					}
					break; }
			case 'd':
			{

				newy = snake[0][0]; newx = snake[0][1] + 1;//координаты новой точки
					if (a[newy][newx] == 219 || a[newy][newx] == 'o')
					{
						printf("Game over\nPress Enter");  key = 10; break;
					}
					else if (a[newy][newx] == '^')
					{
						oldy = snake[snake_len - 1][0];//запись координат конца змеи
							oldx = snake[snake_len - 1][1];
						z = snake_len;//уменьшенная на 1 длина змеи(счетчик)
						while (z > 1)//перезапись массива змейки
						{
							snake[z - 1][0] = snake[z - 2][0];
							snake[z - 1][1] = snake[z - 2][1];
							if (a[snake[z - 1][0]][snake[z - 1][1]] != '^')
								a[snake[z - 1][0]][snake[z - 1][1]] =

								'o';
							z--;
						}
						a[oldy][oldx] = ' ';
						newx = 1;
						snake[0][0] = newy;//запись в массив сегментов змейки 	новых коорд головы
							snake[0][1] = newx;
						a[newy][newx] = '@';//запись плюсика головы на новое место
							system("cls");
						print(*a, X + 2, Y + 2);
						printf("\n\tScore: %i\n", snake_len - 1);
					}
					else {
						if (a[newy][newx] == '$')//если еда
						{
							snake_len++;
							z = snake_len;// длина змеи(счетчик)
							a[newy][newx] = '@';//запись головы на новое 	место
								while (z > 1)//перезапись массива змейки
								{
									snake[z - 1][0] = snake[z - 2][0];
									snake[z - 1][1] = snake[z - 2][1];
									a[snake[z - 1][0]][snake[z - 1][1]] =

										'o';
									z--;
								}
							snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
								snake[0][1] = newx;
							randx = rand() % X + 1;
							randy = rand() % Y + 1;
							while (a[randy][randx] != ' ')
							{
								randx = rand() % X + 1;
								randy = rand() % Y + 1;
							}
							a[randy][randx] = '$';
							fy = randy;
							fx = randx;
						}

						else
						{
							oldy = snake[snake_len - 1][0];//запись координат конца змеи
								oldx = snake[snake_len - 1][1];
							z = snake_len;//уменьшенная на 1 длина змеи(счетчик)
								while (z > 1)//перезапись массива змейки
								{
									snake[z - 1][0] = snake[z - 2][0];
									snake[z - 1][1] = snake[z - 2][1];
									a[snake[z - 1][0]][snake[z - 1][1]] =

										'o';
									z--;
								}
							snake[0][0] = newy;//запись в массив сегментов змейки новых коорд головы
								snake[0][1] = newx;
							a[newy][newx] = '@';//запись плюсика головы на 	новое место
								a[oldy][oldx] = ' ';

						}
						system("cls");
						print(*a, X + 2, Y + 2);
						printf("\n\tScore: %i\n", snake_len - 1);
					}
					break; }
			case 10:
			{Sleep(500); j = 0;
			if (try1 == 0)
			scanf_s("%c", &f[try1].name[j], 1);
			do
			{
				
				scanf_s("%c", &f[try1].name[j], 1);
				j++;
			} while (f[try1].name[j-1]!= 10 && j < 21);
			f[try1].score = snake_len;
			try1++;
			a[fy][fx] = ' ';//стирание фрукта
			while ((key = _getch()) != '1'&&key != '2')
			{
				printf("\nPlay again?\n1-Yes\n2-No");
				Sleep(2000);
				system("cls");
			}
			if (key == '2')
				//здесь сортировка и вывод
				if (key == '2')
				{
					for (i = 0; i < try1; i++)
						for (j = i; j < try1; j++)
							if (f[j].score < f[i].score)
							{
								v = f[j];
								f[j] = f[i];
								f[i] = v;
							}
					for (i = try1-1; i >=0; i--)
					{
						j = 0;
						while (f[i].name[j] != 10)
						{
							printf("%c", f[i].name[j]);
							j++;
						}
						printf("\t\t%i\n", f[i].score);
					}
					_getch();
					return 0;
				}
			else
			{
				for (i = 0; i < snake_len; i++)
				{
					a[snake[i][0]][snake[i][1]] = ' ';
				}
				snake_len = 1;
				snake[0][0] = Y / 2 + 1;
				snake[0][1] = X / 2 + 1;
				a[snake[0][0]][snake[0][1]] = '@';
				randx = rand() % X + 1;
				randy = rand() % Y + 1;
				while (a[randy][randx] != ' ')
				{
					randx = rand() % X + 1;
					randy = rand() % Y + 1;
				}
				a[fy][fx] = ' ';
				a[randy][randx] = '$';
				fx = randx;
				fy = randy;
				print(*a, X + 2, Y + 2);
				printf("\n\tScore: %i\n", snake_len - 1);
			}
			}
			}
	}
	_getch();
	return 0;
}



