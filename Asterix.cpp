#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>

using namespace std;

bool prover(string& a)
{
	return all_of(a.begin(), a.end(), isdigit) || all_of(a.begin(), a.end(), isspace);
}

bool islatter(char c)
{
	return((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я'));
}

string shifr(string& text, string& key)
{
	string entext = text;
	int keyLength = key.length();
	int j = 0;
	for (int i = 0; i < text.length(); i++)
	{
		if (islatter(text[i]) && text[i] != ' ')
		{
			char base;
			int module;
			if (isupper(text[i]))
			{
				base = 'А';
				module = 26;
			}
			else if (islower(text[i]))
			{
				base = 'a';
				module = 26;
			}
			else if (text[i] >= 'А' && text[i] <= 'Я')
			{
				base = 'А';
				module = 32;
			}
			else if (text[i] >= 'а' && text[i] <= 'я')
			{
				base = 'а';
				module = 32;
			}
			else 
			{
				continue;
			}
			int shift = key[j % keyLength] - '0';
			entext[i] = base + (text[i] - base + shift) % module;
			j++;
		}
	}
	return entext;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");


	string text;
	int key;


	while (true)
	{
		cout << "Введите текст: ";
		getline(cin, text);
		cout << "Введите ключ: ";
		cin >> key;
		if (cin.fail() || text.empty() || prover(text))
		{
			cout << "Неверный ввод" << endl << endl;
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		}
		else
		{
			break;
		}
	}


	string strkey = to_string(key);

	string entext = shifr(text, strkey);
	cout << "Зашифрованый текст: " << entext << endl;
}