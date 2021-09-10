// ListCPP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
using namespace std;

/*
    Односвязный список
*/

template<typename T>
class List
{
public:
	List();
	~List();

	void pop_front();					// Удаляет первый эелемент списка
	void push_back(T data);				// затолкать назад в конец спика вставить
	void clear();
	int GetSize() { return Size; }		//геттер для сайз


	void push_front(T data);			// Добовление элемена в начало списка 
	void insert(T value, int index);	// Добавление элемента в любую точку цепи 
	void removeAt(int index);			// Удаление элем по индексу
	void pop_back();


	T& operator[](const int index);		//Перегруженый оператор возврощает данные по индексу из списка 



private:
	
	
	// Класс эелемента будет вложенный в Лист и в привате
	// Так как не должен быть просто доступен

	template<typename T>				//сделаем класс шаблонным, так как разные параметры могут хрнится в каждой ячейке
	class Node							// Узел - то есть звенья нашего списка с адресом и данными
	{
	public:

		Node *pNext;					// Указатель на след. элемент (adress)
		T data;

		Node(T data=T(), Node *pNext=nullptr)	//нал для того чтобы вдруг один элемент, и там только данные T-убираем муссор
		{
			this->data = data;					// Конструктор в котором просто присвоем
			this->pNext = pNext;				// Присвоем параметры соответвующем полям в паблик секции класса Node
		}
	};

	int Size;					// Кол-во элементов, чтобы не перебирать а удобно знать номер элемента
	Node<T> *head;				// Голова списка в динамической памяти от неё будем идти по списку всегде от нее адрес след элем получ.
};




// Методы, конструкторы, диструкторы вне класса
template<typename T>
List<T>::List()
{
	Size = 0;

	head = nullptr;			// Будем знать что список пуст
}



template<typename T>
List<T>::~List()
{
	clear();
}



template<typename T>
void List<T>::pop_front()
{
	Node<T> *temp = head;	// Первый элемент во временую капсулу

	head = head->pNext;		// Потом делаем второй элемент первым - гловой и удаляем в капсуле тот
	delete temp;

	Size--;

}





template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* toDelete = previous->pNext; //временная переменная удалить

		previous->pNext = toDelete->pNext;


		delete toDelete;
		Size--;
	}

}



template<typename T>
void List<T>::pop_back() 
{
	removeAt(Size - 1); // Формула индекс последнего элемента

}




template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr) // Проверим пустой ли хэд, ести ли первый элемент
	{
		head = new Node<T>(data); // Если пуст передаём в конструктор данные
	}
	else
	{
		Node<T> *current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;		// Перебераем пока не найдём то звено - ячейку которое указывает на NULL
		}	
											// Когда нашли звено, значит можем создать новое
		current->pNext = new Node<T>(data); //То есть объкт типа Node за место нал и удлинать цепочку с конца

	}

	Size++;
}



template<typename T>
void List<T>::clear()
{
	while (Size)
	{
		pop_front();
	}

}





template<typename T>
void List<T>::push_front(T data) // Добовление элемена в начало списка 
{
	head = new Node<T>(data);
	Size++;

}




template<typename T>
void List<T>::insert(T value, int index) // Добавление элемента в любую точку цепи 
{

	if (index == 0)
	{
		push_front(value);
	}
	else
	{
		Node<T>* previous = this->head;

		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* newNode = new Node<T>(value, previous->pNext);
		previous->pNext = newNode;

		Size++;
	}

	

}




template<typename T>
T& List<T>::operator[](const int index) //логика итерации, поиск по индексу и возвращение нужного индекса
{
	int counter = 0;
	Node<T>* current = this->head;		// смотрим в каком звене находимся
	while (current != nullptr)
	{
		if (counter == index)			//Если индекс совпал с счётчиком - выводим данные
		{
			return current->data;
		}
		current = current->pNext;		
		counter++;
	}
}






int main()
{
	setlocale(LC_ALL, "ru");

	List<int> lst;
	lst.push_back(5);
	lst.push_back(10);
	lst.push_back(22);

	cout << lst[0] << endl;

	return(0);
}
