#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void even_odd(double* A, int n) {
    int step = 1, i, j;
    double temp;
    for (i = 0; i < n; ++i)
    {
        if (i % 2 == 0)
        {
            for (j = 2; j < n; j += 2) {
                step++;
                if (A[j - 1] > A[j])
                {
                    temp = A[j]; A[j] = A[j - 1]; A[j - 1] = temp;
                }
            }
        }
        else
        {
            for (j = 1; j < n; j += 2) {
                step++;
                if (A[j - 1] > A[j])
                {
                    temp = A[j]; A[j] = A[j - 1]; A[j - 1] = temp;
                }
            }
        }
    }
}


int main()
{
    setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы
    int n = 200;
    int m = 8; // количество интервалов
    double* stat_div = new double[n]; // массив для хранения погрешностей
    ifstream fin("input.txt"); // открыли файл для чтения
    for (int i = 0; i < n; i++) {
        fin >> stat_div[i];
    }
    fin.close(); // закрываем файл
    even_odd(stat_div, n); // в вариационный ряд
    //for (int i = 0; i < n; i++) {
      //  cout << setprecision(17) << stat_div[i] << endl;
    //}
    int disp = 0;
    double interv_size = (stat_div[199] - stat_div[0]) / 8.0;

    int n_size[8] = { 0 }; // размеры интервалов
    double midl_arifm[8]; // средние арифметические интервалов
    double borders[8]; // границы интервалов
    midl_arifm[0] = stat_div[0] + interv_size / 2.0;
    borders[0] = stat_div[0] + interv_size;
    for (int i = 1; i < m; i++)
    {
        borders[i] = borders[i - 1] + interv_size;
    }
    for (int i = 1; i < m; i++)
    {
        midl_arifm[i] = midl_arifm[i - 1] + interv_size;
    }
    for (int j = 0, b = 0; j < 199 && b < m; j++) // j is for elements, b is for borders
    {
        if (stat_div[j] < borders[b]) n_size[b]++;
        else {
            b++;
            n_size[b]++;
        }
    } 
    n_size[7]++;//нашли размеры интервалов
    for (int i = 0; i < m; i++)
    {
        cout << n_size[i] << endl;
        cout << midl_arifm[i] << endl;
    }
    double middle_arifm = 0; // среднее арифметическое 
    for (int i = 0; i < m; i++)
    {
        middle_arifm += n_size[i] * midl_arifm[i];
    }
    
    double sq_middle_arifm = 0; // x(i)^2 * n(i)
    for (int i = 0; i < m; i++)
    {
        sq_middle_arifm += n_size[i] * midl_arifm[i] * midl_arifm[i];
    }
    // 1 способ
    double dis = (sq_middle_arifm / 200.0 - (middle_arifm / 200.0)* (middle_arifm / 200.0));
    cout << "Dispersion ";
    cout << setprecision(17) << dis << endl;

    double dis1 = 0; // 2 способ
    for (int i = 0; i < 199; i++)
    {
        dis1 += ((stat_div[i] - middle_arifm) / 200.0) * ((stat_div[i] - middle_arifm) / 200.0);
    }
    
    cout << setprecision(17) << dis << endl; //совпадают

    cout << "Middle ar ";
    cout << setprecision(17) << middle_arifm / 200.0 << endl;
    double v3 = 0; // центральный момент 3-го порядка
    

    
    return 0;
}
