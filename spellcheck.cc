#include <iostream> 
#include <fstream> 
#include <string> 
#include <set>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

void OpenUserFile(ifstream& input);
void LoadWords(ifstream& input, set<string>& wordList);
void PrintWords(set<string>& wordList);
void Spellchecker(set<string>& wordList);
bool LookupWord(set<string>& wordList, string word);
string CorrectSpelling(set<string>& wordList, string word);
void ToLowerCase(string& str);
void GenWordsVowels(string word, vector<string>& words_vowels);
bool Vowel(char ch);
string RemoveRepeatLetters(string word);

int main()	{
	ifstream input;
	set<string> wordList;
	OpenUserFile(input);
	LoadWords(input, wordList);
	PrintWords(wordList);
	Spellchecker(wordList);
}

void OpenUserFile(ifstream& input)	{
	while(true)	{
		cout << "Enter filename for list of words: " << endl;
		string filename;
		getline(cin, filename);

		input.open(filename.c_str());
		if(input.is_open()) break;

		cout << "Sorry, I can't find the file " << filename << endl;
		input.clear();
	}
}

void LoadWords(ifstream& input, set<string>& wordList)	{	
	while(true)	{
		string word;
		input >> word;

		if(input.fail()) break;

		wordList.insert(word);
	}
}

void PrintWords(set<string>& wordList)	{
	for(set<string>::iterator itr = wordList.begin(); itr != wordList.end(); itr++)	{
		cout << *itr << endl;
	}
}

void Spellchecker(set<string>& wordList)	{
	string correct_word;

	while(true)	{
		cout << "> ";
		string word;
		getline(cin, word);

		bool found = LookupWord(wordList, word);
		if (found == true)
			cout << "found!" << endl;
		else	{
			correct_word = CorrectSpelling(wordList, word);
			cout << correct_word << endl;
		}
	}
}

bool LookupWord(set<string>& wordList, string word)	{
	return wordList.find(word) != wordList.end();
}

string CorrectSpelling(set<string>& wordList, string word)	{
	//Check #1: Downcase "APPLE" to "apple"
	ToLowerCase(word);
	if (LookupWord(wordList, word))
		return word;
	
	//Check #3: Incorrect vowels: "weke" => "wake"
	vector<string> words_vowels;
	GenWordsVowels(word, words_vowels);
	for (vector<string>::iterator itr = words_vowels.begin(); itr < words_vowels.end(); itr++)	{
		if (LookupWord(wordList, *itr))
			return *itr;
	}

	//Check #2: Repeated letters: "jjoobbb" => "job"
	string new_word = RemoveRepeatLetters(word);
	if (LookupWord(wordList, new_word))
		return new_word;
	
	return "NO SUGGESTION";
}

void ToLowerCase(string& str)	{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void GenWordsVowels(string word, vector<string>& words_vowels)	{
	int length = word.length();
	for (int i = 0; i < length; i++) {
		if(Vowel(word[i]))	{
				word[i] = 'a';
				words_vowels.push_back(word);
				word[i] = 'e';
				words_vowels.push_back(word);
				word[i] = 'i';
				words_vowels.push_back(word);
				word[i] = 'o';
				words_vowels.push_back(word);
				word[i] = 'u';
				words_vowels.push_back(word);
		}
	}
}

bool Vowel(char ch)	{
	return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

string RemoveRepeatLetters(string word)	{
	int length = word.length();
	string new_word;
	new_word.append(word, 0, 1);
	for (int i = 1, j = 0; i < length; i++)	{
		if (new_word[j] != word[i])	{
			new_word.append(word, i, 1);
			j++;
		}
	}
	return new_word; 
}
