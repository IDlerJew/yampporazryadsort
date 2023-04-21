// yampporazryadsort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
struct StringItem {
    const char* str; //указатель на строку
    StringItem* next;
};

//pList - начало списка указателей на строки
//iDigit - разряд, по которому сортирует
//возвращает указатель на первый элемент отсортированной последовательности
StringItem* radix_sort_msd_for_string(StringItem* pList, unsigned int iDigit)
{
    // количество вариантов значения одного разряда (char)
    const int iRange = 256;

    //массив bucket-ов (под-списков)
    StringItem* front[iRange];
    memset(front, 0, sizeof(front));

    StringItem** ppNextItem[iRange];
    for (int i = 0; i < iRange; i++)
        ppNextItem[i] = &front[i];

    //разбиваем список на bucket-ты, в зависимости от значения разряда
    while (pList)
    {
        StringItem* temp = pList;
        pList = pList->next;

        temp->next = NULL; //отключаем от списка

        unsigned char c = (unsigned char)temp->str[iDigit];
        *ppNextItem[c] = temp;
        ppNextItem[c] = &temp->next;
    }

    //строим выходной список
    StringItem* pResult = NULL;
    StringItem** ppNext = &pResult;

    //нулевой bucket возвращаем весь - он уже отсортирован
    *ppNext = front[0];
    while (*ppNext)
        ppNext = &((*ppNext)->next);

    for (int i = 1; i < iRange; i++)
    {
        //пустые - пропускаем
        if (!front[i])
            continue;

        if (front[i]->next == NULL)// с одним элементом - сразу добавляем
            *ppNext = front[i];
        else    // остальные - на сортировку по следующему разряду
            *ppNext = radix_sort_msd_for_string(front[i], iDigit + 1);

        while (*ppNext)
            ppNext = &((*ppNext)->next);
    }

    return pResult;
}
void TestAlgorithm()
{
    // открываем, большой текстовый файл для теста
    ifstream file("C:\\Users\\IDler\\Desktop\\test1.txt");
    if (!file)
        return;

    //считываем все слова из файла в вектор
    istream_iterator<string> ii(file);
    istream_iterator<string> eos;
    vector<string> vecs(ii, eos);

    // заполняем список
    StringItem* pList = NULL;
    StringItem** ppCurr = &pList;
    for (unsigned int i = 0; i < vecs.size(); i++)
    {
        *ppCurr = new StringItem();
        (*ppCurr)->str = vecs[i].c_str();
        (*ppCurr)->next = NULL;
        ppCurr = &(*ppCurr)->next;
    }

    //сортируем
    pList = radix_sort_msd_for_string(pList, 0);

    //файл для вывода
    ofstream fo("C:\\Users\\IDler\\Desktop\\final.txt");
    ostream_iterator<string> oo(fo, " ");

    // в конце удаляем список
    while (pList)
    {
        oo = pList->str; // выводим в файл
        StringItem* tmp = pList;
        pList = pList->next;
        delete tmp;
    }
}
int main()
{
    TestAlgorithm();
    
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
