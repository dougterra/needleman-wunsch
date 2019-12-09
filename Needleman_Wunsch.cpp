#include <iostream>
#include <string>
#include <vector>

using namespace std;

const size_t DNA = 30;


 // Retorna o score do melhor alinhamento entre as sequências a e b

int align(const string &a, const string &b, int gap,
        int alpha[DNA][DNA], string &a_alinhado,
        string &b_alinhado);

void print2DVector(const vector<vector<int> > &A);

int min(int a, int b, int c);

int main()
{
    // O input das sequências que serão alinhadas
    string a1 = "AAATCAG";
    string b1 = "AATCAT";

    // Penalidade para string em match com gap
    int penaliade_gap = 2;

    /*
     * alpha[i][j] = penalidade por combinar o i-ésimo alfabeto com o j-ésimo alfabeto.
     * Aqui: mismatch == 1
     *       match == 0
     */
    int alpha[DNA][DNA];
    for (size_t i = 0; i < DNA; ++i)
    {
        for (size_t j = 0; j < DNA; ++j)
        {
            if (i == j) alpha[i][j] = 0;
            else alpha[i][j] = 1;
        }
    }

    // Sequências alinhadas
    string a2, b2;
    int penalidade = align(a1, b1, penaliade_gap, alpha, a2, b2);

    cout << "a: " << a1 << endl;
    cout << "b: " << b1 << endl;
    cout << "Score de Needleman-Wunsch: " << penalidade << endl;
    cout << "Sequencias Alinhadas: " << endl;
    cout << a2 << endl;
    cout << b2 << endl;

    return 0;
}


int align(const string &a, const string &b, int gap,
        int alpha[DNA][DNA], string &a_alinhado,
        string &b_alinhado)
{
    size_t n = a.size();
    size_t m = b.size();

    vector<vector<int> > A(n + 1, vector<int>(m + 1));

    for (size_t i = 0; i <= m; ++i)
        A[0][i] = gap * i;
    for (size_t i = 0; i <= n; ++i)
        A[i][0] = gap * i;

    for (size_t i = 1; i <= n; ++i)
    {
        for (size_t j = 1; j <= m; ++j)
        {
            char x_i = a[i-1];
            char y_j = b[j-1];
            A[i][j] = min(A[i-1][j-1] + alpha[x_i - 'A'][y_j - 'A'],
                          A[i-1][j] + gap,
                          A[i][j-1] + gap);
        }
    }

    // print2DVector(A);

    a_alinhado = "";
    b_alinhado = "";
    size_t j = m;
    size_t i = n;
    for (; i >= 1 && j >= 1; --i)
    {
        char x_i = a[i-1];
        char y_j = b[j-1];
        if (A[i][j] == A[i-1][j-1] + alpha[x_i - 'A'][y_j - 'A'])
        {
            a_alinhado = x_i + a_alinhado;
            b_alinhado = y_j + b_alinhado;
            --j;
        }
        else if (A[i][j] == A[i-1][j] + gap)
        {
            a_alinhado = x_i + a_alinhado;
            b_alinhado = '-' + b_alinhado;
        }
        else
        {
            a_alinhado = '-' + a_alinhado;
            b_alinhado = y_j + b_alinhado;
            --j;
        }
    }

    while (i >= 1 && j < 1)
    {
        a_alinhado = a[i-1] + a_alinhado;
        b_alinhado = '-' + b_alinhado;
        --i;
    }
    while (j >= 1 && i < 1)
    {
        a_alinhado = '-' + a_alinhado;
        b_alinhado = b[j-1] + b_alinhado;
        --j;
    }

    return A[n][m];
}


int min(int a, int b, int c)
{
    if (a <= b && a <= c)
        return a;
    else if (b <= a && b <= c)
        return b;
    else
        return c;
}


void print2DVector(const vector<vector<int> > &A)
{
    for (auto& i : A)
        {
        for (auto& j : i)
            cout << j << " ";
        cout << endl;
    }
}
