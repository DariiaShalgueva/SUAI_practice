#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <map>

using namespace std;

// сортировка расческой
void raschoska(vector<string>& Words) {
    int step = Words.size() - 1;
    for (step; step >= 1; step /= 1.2473309) {
        for (int i = 0; i + step < Words.size(); i++) {
            if (Words[i].length() < Words[i + step].length()) {
                swap(Words[i], Words[i + step]);
            }
        }
    }
}

// функция для разделения текста на слова
void FindWords(string S, vector<string>& Words) {
    istringstream stream(S);
    string word;
    bool flag;
    while (stream >> word) {
        flag = true;
        for (int i = 0; i < word.length(); i++) {
            flag = true;
            if (((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z'))) {
                flag = false;
            }
            if (flag) {
                word.erase(i, 1);
                i--;
            }
        }
        if(!word.empty())
            Words.push_back(word);
    }
}


void Run() {
    bool checkTransfer = false;
    ifstream fin1("Start.txt"); // чтение текста из файла Start.txt
    string line;
    string S;
    while (getline(fin1, line)) {
        if (checkTransfer)
            S += '\n';
        S += line;
        checkTransfer = true;
    }
    vector <string> Words;
    FindWords(S, Words); // вызов функции FindWords для разделения текста на слова
    auto start = chrono::steady_clock::now();// начальное время сортировки
    raschoska(Words);// вызов функции raschoska, где происходит сортировка расческой
    auto end = chrono::steady_clock::now();// конечное время сортировки
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count(); // время сортировки
    map <int, int> wordLengthsMap;
    ofstream fout("analysis.txt"); // запись статистики в текстовый файл analysis.txt 
    if (fout.is_open()) {
        fout << "Введенный текст: " << endl;
        fout << S << endl; // вывод введенного текста
        fout << endl << "Варинат 2: латиница, по количеству символов в слове, по убыванию, игнорировать числа, сортировка расческой." << endl;
        fout << "Количество слов: " << S.length(); // вывод количества слов
        fout << endl <<"Время сортировки: " << duration << " микросекунд" << endl; // вывод времени затраченного на сортировку
        fout << "Статистика (количесвто слов каждой длины, числа после них): " << endl;
       // PrintInfo(wordLengthsMap);
    }
    ofstream fout1("result.txt");//запись результата программы в текстовый файл result.txt
    if (fout1.is_open()) {
        fout1 << "Текст с отсортированными по длине словами: " << endl;
        //printWords(Words);
    }
}

int main()
{ 
    setlocale(LC_ALL, "ru");
    Run();// вызов функции Run

}
  