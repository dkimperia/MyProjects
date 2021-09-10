#include <iostream>
#include <string> //for getline 

#include <regex> //Regular Expression (Регулярные выражения)
// regex hello(".*hello.*"); // шаблон слова hello

#include <algorithm> //transform

#include <map> // добовляем самую простую структуру данных


using namespace std;


string toLower(string text) {
	transform(text.begin(), text.end(), text.begin(), ::tolower);//пройтись по коллекции и сделать с ней что-то
	return text;
}



map<string, string> database { 
	
	/*
	{"hello", "Hello, human!"},
	{"what is your name", "My name is ChatBot!"},
	{"what are you doing", "Answering stoopid questions"},
	{"how are you", "Do some work :D"},
	*/

};



void loadPhrases() {
	ifstream phrases("database.txt"); // ifstream - файловый поток, помогает читать из файла
	string line;
	int len = 0;

	while (getline(phrases, line)) { // line = question $ answer 
		//cout << line << endl;
		string delimiter = " $ ";
		int pos = line.find(delimiter); // сколько символов с начала занимает вопрос
		string question = line.substr(0, pos);
		string answer = line.substr(pos + delimiter.length);
		database.insert(pair<string, string>(answer, question));
		len++;



	}
	return len;
}


void bot(string msg) {
	cout << "[Bot]: " << msg << endl;
}


string user() {
	string question;
	cout << "[User]: ";
	getline(cin, question);
	question = toLower(question);
	return question;
}


int main()
{
	int phraseCount = loadPhrases();

	bot("Hi, I'm ChatBot, I can answer " + to_string(phraseCount) + " question");


	string question;

	while (question != "exit") {
		

		question = user();
		// Для каждой записи в БД, проверить совподает ли она с вопросом 

		for (auto entry : database) {  //тип данных auto пофиг на разные данные в коллекции
			//entry = {"hello", "Hello, human!"} ... first-вопрос second-ответ
			regex pattern(".*" + entry.first + ".*");
			if (regex_match(question, pattern)) {
				bot(entry.second);
			}
		}
	}










	//std::cout << "Hello World!\n";
	//cout << "Hello world" << endl;
	/*
	getline(cin, question);
	/////////////////////////////
	question = toLower(question); // Метод уменьшения регистра
	/////////////////////////////
	*/
	/*regex hello(".*hello.*");
	if (regex_match(question, hello)) {

		cout << "Hello hooman!" << endl;

	}
	regex whatname(".*what is your name.*");
	if (regex_match(question, whatname)) {

		cout << "My name is ChatBot" << endl; 
		
	}*/

}


// Вопросы в файл
// Обучение на ходу 

// Запишем все вопросы и все ответы
// в какую-нибудь структуру данных, чтобы не было по 4 строчки на каждый вопрос ответ