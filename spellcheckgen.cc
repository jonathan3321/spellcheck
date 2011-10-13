#include <iostream> 
#include <fstream> 
#include <string> 
#include <map>
#include <vector>
#include <cstdlib>

using namespace std;

void GenWords(string word, ofstream& myfile);
void ToUpperCase(string& str);
void ToLowerCase(string& str);
void ChangeVowels(string& str);
bool Vowel(char ch);
void ChangeRepeat(string& word);

int main()	{
	vector<string> words;
	ofstream myfile;
	myfile.open("words.txt");

	words.push_back("apple");
	words.push_back("banana");
	words.push_back("conspiracy");
	words.push_back("inside");
	words.push_back("job");
	words.push_back("orange");
	words.push_back("wake");

	for (vector<string>::iterator itr = words.begin(); itr < words.end(); ++itr)	{
		string word = *itr;
		GenWords(word, myfile);
	}

	myfile.close();
}

void GenWords(string word, ofstream& myfile)	{
	ToUpperCase(word);
	myfile << word << endl;
	ToLowerCase(word);
	myfile << word << endl;
	ChangeVowels(word);
	myfile << word << endl;
	ChangeRepeat(word);
	myfile << word << endl;
}

void ToUpperCase(string& str)	{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
}
void ToLowerCase(string& str)	{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
}

//Change all vowels to U
void ChangeVowels(string& str)	{
	int length = str.length();
	for (int i = 0; i < length; ++i)	{
		if(Vowel(str[i]))
			str[i] = 'U';
	}
}

bool Vowel(char ch)	{
	return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

//Repeats all characters in a string 4 times
void ChangeRepeat(string& word)	{
	int length = word.length();
	string new_word; 

	new_word.push_back(word[0]);
	for (int i = 1, j = 0; i < length; ++i)	{
		new_word.push_back(word[i]);
		new_word.push_back(word[i]);
		new_word.push_back(word[i]);
		new_word.push_back(word[i]);
		++j;
	}

	word = new_word;
}
