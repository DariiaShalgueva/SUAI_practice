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

// функция countWordsLengthAmount для подсчитывания количества слов одинаковой длиныы
void countWordsLengthAmount(vector<string>& Words, map<int, int>& worldsLengthMap) {
    for (int i = 0; i < Words.size(); i++) {
        int length = Words[i].length();
        worldsLengthMap[length] = worldsLengthMap[length] + 1;
    }
}

// функция PrintInfo для вывода количества слов определенной длины
void PrintInfo(map<int, int>& worldsLengthMap, ofstream & fout) {
    map <int, int> ::iterator it = worldsLengthMap.begin();
    for (int i = 0; it != worldsLengthMap.end(); it++, i++) {  
        fout << it->first << " - " << it->second << endl;
    }
}

//функция для вывода слов различной длины по убыванию
void printWords(vector<string>& Words, map<int, int> worldsLengthMap, ofstream & fout1) {
    for (int i = 0; i < Words.size(); i++) {
        fout1 << Words[i] << " ";
        int length = Words[i].length();
        worldsLengthMap[length] = worldsLengthMap[length] - 1;
        if (worldsLengthMap[length] == 0) {
            fout1 << endl;
        }
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
    countWordsLengthAmount(Words, wordLengthsMap); // вызов функции countWordsLengthAmount для подсчитывания количества слов одинаковой длиныы
    ofstream fout("analysis.txt"); // запись статистики в текстовый файл analysis.txt 
    if (fout.is_open()) {
        fout << "Введенный текст: " << endl;
        fout << S << endl; // вывод введенного текста
        fout << endl << "Варинат 2: латиница, по количеству символов в слове, по убыванию, игнорировать числа, сортировка расческой." << endl;
        fout << "Количество слов: " << S.length(); // вывод количества слов
        fout << endl <<"Время сортировки: " << duration << " микросекунд" << endl; // вывод времени затраченного на сортировку
        fout << "Статистика (количесвто слов каждой длины, числа после них): " << endl;
        PrintInfo(wordLengthsMap, fout);// вызов функции PrintInfo для вывода количества слов определенной длины
    }
    ofstream fout1("result.txt");//запись результата программы в текстовый файл result.txt
    if (fout1.is_open()) {
        fout1 << "Текст с отсортированными по длине словами: " << endl;
        printWords(Words, wordLengthsMap, fout1);// вызов функции printWords для вывода слов различной длины по убыванию
    }
}

int main()
{ 
    setlocale(LC_ALL, "ru");
    Run();// вызов функции Run

}
  