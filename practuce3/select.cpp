#include "select.hpp"

// поиск точки
void splitDot(const string &word, string &table, string &column, TableJson &tableJS)
{
    bool dot = false;
    for (size_t i = 0; i < word.size(); i++)
    {
        if (word[i] == '.')
        {
            dot = true;
            continue;
        }
        if (word[i] == ',')
        {
            continue;
        }
        if (!dot)
        { // разделяем таблицу и колонку
            table += word[i];
        }
        else
        {
            column += word[i];
        }
    }
    if (!dot)
    {
        cerr << "Incorrect command10.\n";
        return;
    }
    if (isTableExist(table, tableJS.tablehead) == false)
    {
        cerr << "There is no table.\n";
        return;
    }
    if (isColumnExist(table, column, tableJS.tablehead) == false)
    {
        cerr << "There is no column.\n";
        return;
    }
}

// отделение от кавычек строки
string ignoreQuotes(const string &word)
{
    string word_without;
    for (size_t i = 0; i < word.size(); i++)
    {
        if (word[i] != '\'')
        {
            word_without += word[i];
        }
    }
    return word_without;
}

// наличие точки в слове
bool findDot(const string &word)
{
    bool dot = false;
    for (size_t i = 0; i < word[i]; i++)
    {
        if (word[i] == '.')
        {
            dot = true;
        }
    }
    return dot;
}

// количество созданных csv файлов
int countCsv(TableJson &tableJS, const string &table)
{
    std::filesystem::path currentDirectory = std::filesystem::current_path();
    currentDirectory = currentDirectory.parent_path().string();
    string currentDir = currentDirectory.string();

    int amountCsv = 1;
    while (true)
    {
        string filePath = currentDir + "/" + table + "/" + to_string(amountCsv) + ".csv";
        ifstream file(filePath);
        if (!file.is_open())
        {
            break;
        }
        file.close();
        amountCsv++;
    }
    return amountCsv;
}

// объединение 2 таблиц
void crossJoin(TableJson &tableJS, const string &table1,
               const string &table2, const string &column1, const string &column2, char *buffer)
{
    ostringstream oss(buffer);
    std::filesystem::path currentDirectory = std::filesystem::current_path();
    currentDirectory = currentDirectory.parent_path().string();
    string currentDir = currentDirectory.string();

    int amountCsv1 = countCsv(tableJS, table1);
    int amountCsv2 = countCsv(tableJS, table2);
    for (size_t iCsv1 = 1; iCsv1 < amountCsv1; iCsv1++)
    {
        string filePath1 = currentDir + "/" + table1 + "/" + to_string(iCsv1) + ".csv";
        rapidcsv::Document doc1(filePath1);
        int columnIndex1 = doc1.GetColumnIdx(column1);
        size_t amountRow1 = doc1.GetRowCount();

        for (size_t i = 0; i < amountRow1; ++i)
        { // проходимся по строкам 1 таблицы

            for (size_t iCsv2 = 1; iCsv2 < amountCsv2; iCsv2++)
            {
                string filePath2 = currentDir + "/" + table2 + "/" + to_string(iCsv2) + ".csv";
                rapidcsv::Document doc2(filePath2);
                int columnIndex2 = doc2.GetColumnIdx(column2);
                size_t amountRow2 = doc2.GetRowCount();

                for (size_t j = 0; j < amountRow2; ++j)
                { // проходимся по строкам 2 таблицы
                    oss << doc1.GetCell<string>(0, i) << ": ";
                    oss << doc1.GetCell<string>(columnIndex1, i) << "  |   ";
                    oss << doc2.GetCell<string>(0, j) << ": ";
                    oss << doc2.GetCell<string>(columnIndex2, j) << "\n";
                }
                strcpy(buffer, oss.str().c_str());
            }
        }
    }
}

// проверка условий
bool checkCond(TableJson &tableJS, const string &table, const string &column, const string &tcond, const string &ccond, const string &s)
{
    std::filesystem::path currentDirectory = std::filesystem::current_path();
    currentDirectory = currentDirectory.parent_path().string();
    string currentDir = currentDirectory.string();

    if (s != "")
    {
        int amountCsv = countCsv(tableJS, table);

        for (size_t iCsv = 1; iCsv < amountCsv; iCsv++)
        {
            string filePath = currentDir + "/" + table + "/" + to_string(iCsv) + ".csv";
            rapidcsv::Document doc(filePath);
            int columnIndex = doc.GetColumnIdx(column);
            size_t amountRow = doc.GetRowCount();

            for (size_t i = 0; i < amountRow; ++i)
            { // проходимся по строкам
                if (doc.GetCell<string>(columnIndex, i) == s)
                { // извлекаем значение
                    return true;
                }
            }
        }
    }
    else
    {
        bool condition = true;
        int amountCsv = countCsv(tableJS, table);
        for (size_t iCsv = 1; iCsv < amountCsv; iCsv++)
        {
            string pk1, pk2;
            string pk1Path = currentDir + "/" + table + "/" + table + "_pk_sequence.txt";
            string pk2Path = currentDir + "/" + tcond + "/" + tcond + "_pk_sequence.txt";
            ifstream file1(pk1Path);
            if (!file1.is_open())
            {
                cerr << "1Fail to open file.\n";
                return false;
            }
            file1 >> pk1;
            file1.close();
            ifstream file2(pk2Path);
            if (!file2.is_open())
            {
                cerr << "2Fail to open file.\n";
                return false;
            }
            file2 >> pk2;
            file2.close();

            string filePath1 = currentDir + "/" + table + "/" + to_string(iCsv) + ".csv";
            rapidcsv::Document doc1(filePath1);
            int columnIndex1 = doc1.GetColumnIdx(column);
            size_t amountRow1 = doc1.GetRowCount();

            string filePath2 = currentDir + "/" + tcond + "/" + to_string(iCsv) + ".csv";
            rapidcsv::Document doc2(filePath2);
            int columnIndex2 = doc2.GetColumnIdx(ccond);
            for (size_t i = 0; i < amountRow1; ++i)
            { // проходимся по строкам
                if (doc1.GetCell<string>(columnIndex1, i) != doc2.GetCell<string>(columnIndex2, i))
                {
                    condition = false;
                }
            }
        }
        if (condition)
        {
            return true;
        }
    }
    return false;
}

// выборка
int select(char *buffer, int BUFFER_SIZE, TableJson &tableJS)
{
    istringstream iss(buffer);
    memset(buffer, 0, BUFFER_SIZE); // очистка буфера
    string word;
    iss >> word;
    iss >> word;
    string table1, column1;
    splitDot(word, table1, column1, tableJS); // разделяем таблицу1 и колонку1

    iss >> word;
    string table2, column2;
    splitDot(word, table2, column2, tableJS); // разделяем таблицу2 и колонку2


    iss >> word;
    if (word != "FROM")
    {
        cerr << "Incorrect command1.\n";
        return 1;
    }
    iss >> word;
    string tab1;
    for (size_t i = 0; i < word.size(); i++)
    {
        if (word[i] != ',')
        {
            tab1 += word[i];
        }
    }
    if (tab1 != table1)
    {
        cerr << "Incorrect command2.\n";
        return 1;
    }
    iss >> word;
    if (word != table2)
    {
        cerr << "Incorrect command3.\n";
        return 1;
    }

    iss >> word;
    if (word != "WHERE")
    { // если нет условий, то объединяем таблицы
        crossJoin(tableJS, table1, table2, column1, column2, buffer);
        return 0;
    }

    iss >> word; // таблица1 и колонка1
    string t1, c1;
    splitDot(word, t1, c1, tableJS);
    iss >> word;
    if (word != "=")
    {
        cerr << "Incorrect command4.\n";
        return 1;
    }

    iss >> word; // первое условие
    string t1cond = "", c1cond = "", s1 = "";
    if (findDot(word))
    {
        splitDot(word, t1cond, c1cond, tableJS);
    }
    else
    {
        s1 = ignoreQuotes(word);
    }

    string oper;
    iss >> oper;
    if (oper != "AND" && oper != "OR")
    {
        if (checkCond(tableJS, t1, c1, t1cond, c1cond, s1))
        {
            crossJoin(tableJS, table1, table2, column1, column2, buffer);
            return 0;
        }
        else
        {
            cout << "Conduction not fulfilled.\n";
            return 0;
        }
    }

    iss >> word; // таблица2 и колонка2
    string t2, c2;
    splitDot(word, t2, c2, tableJS);
    iss >> word;
    if (word != "=")
    {
        cerr << "Incorrect command5.\n";
        return 1;
    }

    iss >> word; // второе условие
    string t2cond = "", c2cond = "", s2 = "";
    if (findDot(word))
    {
        splitDot(word, t2cond, c2cond, tableJS);
    }
    else
    {
        s2 = ignoreQuotes(word);
    }
    if (oper == "AND")
    {
        if (checkCond(tableJS, t1, c1, t1cond, c1cond, s1) == true && checkCond(tableJS, t2, c2, t2cond, c2cond, s2) == true)
        {
            crossJoin(tableJS, table1, table2, column1, column2, buffer);
            return 0;
        }
        else
        {
            cout << "Condition not fulfilled.\n";
            return 0;
        }
    }
    if (oper == "OR")
    {
        if (checkCond(tableJS, t1, c1, t1cond, c1cond, s1) == true || checkCond(tableJS, t2, c2, t2cond, c2cond, s2) == true)
        {
            crossJoin(tableJS, table1, table2, column1, column2, buffer);
            return 0;
        }
        else
        {
            cout << "Condition not fulfilled.\n";
            return 0;
        }
    }
    return 0;
}