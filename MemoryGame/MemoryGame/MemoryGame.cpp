#include <iostream>
#include<Windows.h>
#include <cstdlib>
#include<sstream>
#include<string>
#include<ctime>

using namespace std;

int Start(int &size,int &rows,int &columns) {//старт игры.ввод выбор размера игрового поля и вычисление размера будущих массивов(скрытого,видимого и числового)
	cout << "Insert quantity of rows: ";
	cin >> rows;
	cout << "Insert quantity of columns: ";
	cin >> columns;
	size = columns * rows;
	return size;
	return rows;
	return columns;
}
void PrintBoard(string str[], int size, int columns) {//вывод на экран игрового поля(массив vsibleDoard)
	cout << "    ";
	int num_of_row = 1;
	for (int i = 1; i <= columns; i++) {
		cout << i << "  ";		
	}
	cout << endl;
	for (int i = 1; i <= columns; i++) {
		cout << "____";
	}
	cout << endl;
	for (int j = 0; j < size; j++) {
		if (j == 0)cout << num_of_row << " |";
		cout << " "<<str[j] << " ";
		if (((j + 1) % columns == 0)&&((j+1))<size) {
			cout << endl; 
			num_of_row++;
			cout << num_of_row << " |";
			
		}
	}
	cout << endl << endl;
}
void MusicVin() {//музыка если угадал
	int C = 523; 
	int D = 587; 
	int E = 659; 
	int F = 698; 
	Beep(C, 382);
	Beep(C, 382);
	Beep(D, 340);
	Beep(C, 382);
	Beep(F, 286);
	Beep(E, 304);
}
void MusicLoose() {//музыка если не угадал
	float B = 493.88,A = 440.00;
	Beep(B, 300);
	Beep(A, 300);
	Beep(B, 600);

	Beep(A, 300);
}
string Convert_Int_String( int num) {/*первод числового массива в строковый
нужен для того чтоб занчения числового массива можно было
передавать в строковый массив и выводить на экран*/
	stringstream ss;
	ss << num;
	string str = ss.str();
	return str;
}
void CreateMainBoard(string *& hiddenBoard,int *& numBoard,int size) {//создание скрытого массива. занчения из массива будут передаватся в видимый массив по координатам
	int n = 0;
	srand(time(0));
	for (int i = 0; i < size; i++) {
		n++;
		numBoard[i] = n;//заполняем половину массива
		if (i == (size / 2) - 1) {//дублируем первую половину массива во вторую, чтоб у нас были дубликаты(одинаковые карты)
			n = 0;
		}
	}
	for (int i = 0; i < size; i++) {//перемешивание элементов массива
		swap(numBoard[i], numBoard[rand() % size]);
	}
	for (int i = 0; i < size; i++) {
		hiddenBoard[i] = Convert_Int_String(numBoard[i]);
	}
	
}


int main(){
	int rows = 0;
	int columns = 0;
	int size;	
	Start(size, rows, columns);
	int attempts = 0;
	int counter = 0;

	string * visibleBoard = new string[size];//видимый массив
	for (int i = 0; i < size; i++) {
		visibleBoard[i] = "#";
	}
	string * hiddenBoard = new string[size];//скрытый массив
	int* numBoard = new int[size];//чиловой массив
	CreateMainBoard(hiddenBoard, numBoard,size);//заполняем числовой массив, перемешиваем элементы,конвертируем числовой массив в строчный и передаем его в строчный массив

	/*for (int i = 0; i < size; i++) {//просмотр скрытого массива. в игровом процессе не используется
		
		cout << hiddenBoard[i] << " ";
		if ((i + 1) % columns == 0)cout << endl;
	}
	cout << endl << endl;
	Sleep(5000);*/
	while (counter < size - 1) {//соновной цикл.
		//выполняется пока на поле не останется ноль карт(если размер поля чётный)
		//или пока не останется одна карта(если размер поля нечётный)
		system("cls");
		PrintBoard(visibleBoard, size, columns);
		cout << "Choose card 1.\n\n";//выбор координат первой карты
		int coord_Y_card1;
		cout << "Input number of row: ";
		cin >> coord_Y_card1;
		cout << endl;
		int coord_X_card1;
		cout << "Input number of column: ";
		cin >> coord_X_card1;
		cout << endl << endl;
		int card1 = (columns * (coord_Y_card1-1)) + coord_X_card1;//вычисляем индекс элемента скрытого массива который соответствует выбранным координатам
		if(visibleBoard[card1-1]!=".")visibleBoard[card1-1] = hiddenBoard[card1-1];//если карта ранее не была угадана,передаем выбранный элемент в видимый массив
		system("cls");
		PrintBoard(visibleBoard, size, columns);//выводим на экран игровое поле с открытой картой на которую указал игрок
		cout << "Choose card 2.\n\n";//выбор второй карты(алгоритм аналогичен выбору первой карты)
		int coord_Y_card2;
		cout << "Input number of row: ";
		cin >> coord_Y_card2;
		cout << endl;
		int coord_X_card2;
		cout << "Input number of column: ";
		cin >> coord_X_card2;
		cout << endl << endl;
		int card2 = (columns * (coord_Y_card2 - 1)) + coord_X_card2;
		if (visibleBoard[card2 - 1] != ".")visibleBoard[card2 - 1] = hiddenBoard[card2 - 1];
		
		attempts++;//количество попыток
		if (hiddenBoard[card1 - 1] == hiddenBoard[card2 - 1]) {//если карты совпали
			system("cls");
			cout << "You guessed!!!\n\n";
			PrintBoard(visibleBoard, size, columns);
			MusicVin();
			Sleep(3000);
			visibleBoard[card1 - 1] = ".";//отгаданные карты заменяются точками идалее в игровом процессе не используются
			visibleBoard[card2 - 1] = ".";
			counter += 2;//счетчик отгаданных карт. использется в основном цикле как условие окончания игры
			
		}
		else {//если карты не совпали
			system("cls");
			cout << "Oh no. Dont guessed. Try again.\n\n";
			PrintBoard(visibleBoard, size, columns);
			MusicLoose();
			Sleep(3000);
			if(visibleBoard[card1 - 1]!=".")visibleBoard[card1 - 1] = "#";//не угаданные карты снова заменяются на закрытые карты
			if (visibleBoard[card2 - 1] != ".")visibleBoard[card2 - 1] = "#";
			

		}


	}
	if (counter >= size - 1) {//конец игры. если на поле осталась одна или ноль карт
		system("cls");
		cout << "			Congratulations!!!\n			You win!!!\n\n";
		cout << "Attempts: " << attempts<<endl<<endl;
		MusicVin();
	}




	delete[]visibleBoard;
	delete[]hiddenBoard;
	delete []numBoard;
	
	
}









