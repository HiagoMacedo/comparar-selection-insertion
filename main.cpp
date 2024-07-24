#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using std::cerr;
using std::cin;
using namespace std::chrono;

void insertionSort(long arr[], int size)
{
    long aux;
    int i, j;
    for (i = 1; i < size; i++)
    {
        aux = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > aux)
        {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = aux;
    }
}

void selectionSort(long arr[], int size)
{
    int minValueIndex;
    long aux;
    for (int i = 0; i < (size-1); i++)
    {
        minValueIndex = i;
        for (int j = (i+1); j < size; j++)
        {
            if (arr[j] < arr[minValueIndex])
            {
                minValueIndex = j;
            }
        }
        if (arr[i] != arr[minValueIndex])
        {
            aux = arr[i];
            arr[i] = arr[minValueIndex];
            arr[minValueIndex] = aux;
        }
    }
}

bool readFile(std::ifstream &inputStream, long arr[])
{
    long line;
    int i = 0;
    if (!inputStream.is_open())
    {
        cerr << "Nao conseguiu abrir o arquivo!" << endl;
        return false;
    }
    
    while(inputStream >> line)
    {
        arr[i] = line;
        i++;
    }
    return true;
}

int getNumLines(std::ifstream &inputStream)
{
    int numLines;
    if (!inputStream.is_open())
    {
        return -1;
    }
    inputStream >> numLines;
    return numLines;
}

void printArray(const long arr[], int size)
{
    cout << "[ ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "]" << endl;
}

void copyArray(const long src[], long dest[], int size)
{
    for (int i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
}

void compararNumeros(const int size, std::ifstream &inputStream)
{
    long *toSortSelection = new long[size];
    long *toSortInsertion = new long[size];

    readFile(inputStream, toSortSelection);
    copyArray(toSortSelection, toSortInsertion, size);
    
    cout << "\nAntes de ordenar:\n";
    printArray(toSortSelection, size);

    auto startSelectionTimer = high_resolution_clock::now();
    
    selectionSort(toSortSelection, size);
    
    auto stopSelectionTimer = high_resolution_clock::now();
    auto durationSelection = duration_cast<microseconds>(stopSelectionTimer - startSelectionTimer);

    auto startInsertionTimer = high_resolution_clock::now();

    insertionSort(toSortInsertion, size);
    
    auto stopInsertionTimer = high_resolution_clock::now();
    auto durationInsertion = duration_cast<microseconds>(stopInsertionTimer - startInsertionTimer);

    cout << "\nDepois de ordenar com Selection Sort:\n";
    printArray(toSortSelection, size);

    cout << "\nDepois de ordenar com Insertion Sort:\n";
    printArray(toSortSelection, size);

    cout << "\nTempo para ordernar com Selection Sort: " << durationSelection.count() << " microsegundos\n";
    cout << "Tempo para ordernar com Insertion Sort: " << durationInsertion.count() << " microsegundos\n";

    delete [] toSortSelection;
    delete [] toSortInsertion;
}

void menuComparar()
{
    int opcao = -1;
    while (opcao < 1 || opcao > 4) 
    {
        cout << "-----------------------------------------------\n";
        cout << "| COMPARAR SELECTION SORT E INSERTION SORT\n";
        cout << "| Escolha um arquivo:\n";
        cout << "| 1. Arquivo com 1000 numeros\n";
        cout << "| 2. Arquivo com 10000 numeros\n";
        cout << "| 3. Arquivo com 100000 numeros\n";
        cout << "| 4. Sair do programa\n";
        cout << "-----------------------------------------------\n";
        cin >> opcao;
    }
    switch (opcao)
    {
    case 1: 
    {
        std::ifstream inputStream("./instancias-num/num.1000.2.in");
        int numLines = getNumLines(inputStream);
        compararNumeros(numLines, inputStream);
        break;
    }
    case 2:
    {
        std::ifstream inputStream("./instancias-num/num.10000.4.in");
        int numLines = getNumLines(inputStream);
        compararNumeros(numLines, inputStream);
        break;
    }
    case 3:
    {
        std::ifstream inputStream("./instancias-num/num.100000.1.in");
        int numLines = getNumLines(inputStream);
        compararNumeros(numLines, inputStream);
        break;
    }
    default:
        cout << "Finalizando o programa...\n";
        // cout << "Opcao invalida...\n";
        break;
    }
}

int main()
{
    menuComparar();  
    return 0;
}