#include <iostream> 
#include <fstream> 
#include <string> 
#include <map>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

void OpenUserFile(ifstream& input);
void LoadWords(ifstream& input, map<string,string>& wordList_dynamic, map<string,string>& wordList_original);
void Spellchecker(map<string,string>& wordList_dynamic, map<string,string>& wordList_original);
void ToLowerCase(string& str);
void StarVowels(string& word);
bool Vowel(char ch);
void RemoveRepeatLetters(string& word);

int main()	{
	ifstream input;

	//Word is JoB. Maps j*b to job (shortened, no vowels)
	map<string,string> wordList_dynamic;
	//Word is JoB. Maps job to JoB (original form) 
	map<string,string> wordList_original;

	OpenUserFile(input);
	LoadWords(input, wordList_dynamic, wordList_original);
	
	Spellchecker(wordList_dynamic, wordList_original);
}

void OpenUserFile(ifstream& input)	{
	while (true)	{
		cout << "Enter filename for list of words: " << endl;
		string filename;
		getline(cin, filename);

		input.open(filename.c_str());
		if(input.is_open()) break;

		cout << "Sorry, I can't find the file " << filename << endl;
		input.clear();
	}
}

void LoadWords(ifstream& input, map<string,string>& wordList_dynamic, map<string,string>& wordList_original)	{	
	while (true)	{
		string word;
		input >> word;

		if(input.fail()) break;

		string word_starred = string(word);

		ToLowerCase(word_starred);
		RemoveRepeatLetters(word_starred);
		StarVowels(word_starred);

		string word_simple = string(word);
		ToLowerCase(word_simple);

		//Original word: JoB
		//Dynamic map: j*b => job
		//Original map: job => JoB
		wordList_dynamic.insert(make_pair(word_starred, word_simple));
		wordList_original.insert(make_pair(word_simple, word));
	}
}

void Spellchecker(map<string,string>& wordList_dynamic, map<string,string>& wordList_original)	{

	while(true)	{
		cout << "> ";
		string word;
		getline(cin, word);

		ToLowerCase(word);
		RemoveRepeatLetters(word);
		StarVowels(word);

		map<string,string>::iterator word_simple_itr = wordList_dynamic.find(word);

		if (word_simple_itr == wordList_dynamic.end())	{
			cout << "NO SUGGESTION" << endl;
		} else {
			pair<string,string> word_simple = *word_simple_itr;
			map<string,string>::iterator result_itr = wordList_original.find(word_simple.second);
			pair<string,string> result = *result_itr;
			cout << result.second << endl;
		}


	}
}

void ToLowerCase(string& str)	{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void StarVowels(string& word)	{
	int length = word.length();
	for (int i = 0; i < length; i++) {
		if(Vowel(word[i]))	
				word[i] = '*';
	}
}


bool Vowel(char ch)	{
	return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

void RemoveRepeatLetters(string& word)	{
	int length = word.length();
	string new_word; 

	new_word.push_back(word[0]);
	for (int i = 1, j = 0; i < length; ++i)	{
		if ((word[i] == '*') || (new_word[j] != word[i]))	{
			new_word.push_back(word[i]);
			++j;
		}
	}

	word = new_word;
}
