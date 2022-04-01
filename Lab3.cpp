#include <iostream>
#include <ctime>
using namespace std;

class Anc //класс предка
{
public:
	Anc()
	{
		printf("Anc()\n");
	}
	virtual void showName()
	{
		printf("Anc\n");
	}
	virtual ~Anc()
	{
		printf("~Anc()\n");
	}
};

class First : public Anc //первый класс-потомок 
{
private:
	int x;
	int y;
public:
	First() //пустой конструктор
	{
		printf("First()\n");
		x = 0;
		y = 0;
	}

	First(int x, int y) //конструктор с параметрами
	{
		printf("First(int x, int y)\n");
		this->x = x;
		this->y = y;
	}

	First(const First& obj) //копирующий конструктор
	{
		printf("First(const Class1& obj)\n");
		x = obj.x;
		y = obj.y;
	}

	~First()
	{
		printf("~First()\n");
	}

	void showName()
	{
		printf("First\n");
	}
};

class Secnd : public Anc { //второй класс-потомок 
private:
	int x;
	int y;
	int color;
public:
	Secnd() //конструктор по умолчанию
	{
		printf("Secnd()\n");
		x = 0;
		y = 0;
		color = 0;
	}

	Secnd(int x, int y, int color) //конструктор с параметрами
	{
		printf("Secnd(int x, int y, int color)\n");
		this->x = x;
		this->y = y;
		this->color = color;
	}

	Secnd(const Secnd& obj) //копирующий коструктор
	{
		printf("Secnd(const Secnd& obj)\n");
		x = obj.x;
		y = obj.y;
		color = obj.color;
	}
	~Secnd()
	{
		printf("~Secnd()\n");
	}

	void showName()
	{
		printf("Secnd\n");
	}
};

class MyStorage //класс хранилища
{
private:
	int size;
	Anc** storage;//инициализация динамического массива
public:
	MyStorage(int size) //конструктор с параметром
	{
		printf("MyStorage\n");
		this->size = size;
		storage = new Anc * [size];
		for (int i = 0; i < size; i++)
			storage[i] = nullptr;//заполнение массива константой 0
	}
	MyStorage(MyStorage& storage_copy) //копирующий конструктор
	{
		printf("MyStorage(MyStorage& storage_copy)\n");
		size = storage_copy.size;
		storage = new Anc * [size];
		for (int i = 0; i < size; i++)
			*storage[i] = storage_copy.GetObject(i);
	}
	~MyStorage()
	{
		printf("~MyStorage()\n");
		for (int i = 0; i < size; i++)
			delete storage[i];//последовательное удаление содержимого ячеек
		delete storage; 	  //и самого массива
	}

	int StorageSize()
	{
		return size;
	}

	void GetCount() //подсчет количества элементов в хранилище
	{
		int count = 0;
		for (int i = 0; i < size; i++)
			if (storage[i] != nullptr)
				count = count + 1;
		printf("\nКоличество элементов: %d\nРазмер хранилища: %d\n\n", count, size);
	}

	void SetObj(int i, Anc* object) //помещение объекта в хранилище по индексу
	{
		printf("SetObj, i = %d\n", i);
		storage[i] = object;
	}

	void AddObj(Anc* object) //добавление элемента в хранилище
	{
		size = size + 1;
		printf("AddObj, size = %d\n", size);
		Anc** storage_copy = new Anc * [size];
		for (int i = 0; i < size - 1; i++)
			storage_copy[i] = storage[i];
		storage_copy[size - 1] = object;
		for (int j = 0; j < size - 1; j++)
			storage[j] = nullptr;
		delete storage;
		storage = storage_copy;
	}

	Anc& GetObject(int i) //вызов объекта по индексу
	{
		return *storage[i];
	}

	void DeleteObject(int i) //удаление элемента
	{
		printf("DeleteObject(int i), i = %d\n", i);
		storage[i] = nullptr;
	}

	void ShowMethod(int i) //вызов метода showName
	{
		printf("ShowMethod(int i), i = %d\n", i);
		if (storage[i] != nullptr)
			storage[i]->showName();
	}

	void ReplaceObject(int i, Anc* object) //замена элемента
	{
		printf("ReplaceObject(int i), i = %d\n", i);
		if (storage[i] == nullptr)
			storage[i] = object;
		else
		{
			delete storage[i];
			storage[i] = object;
		}
	}
	void ShowStorage() //вывод хранилища
	{
		for (int i = 0; i < size; i++)
			if (storage[i] != nullptr)
				storage[i]->showName();
			else printf("nullptr\n");
	}
};

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");
	MyStorage storage(10);

	for (int i = 0; i < storage.StorageSize(); i++)
	{
		int k = rand() % 2;
		if (k)
			storage.SetObj(i, new First);
		else storage.SetObj(i, new Secnd);
	}
	cout << endl << endl;
	for (int i = 0; i < storage.StorageSize(); i++)
		storage.GetObject(i).showName();
	unsigned int StartTime = clock();
	printf("\n\n");
	for (int i = 0; i < 100; i++)
	{
		printf("%d:\n", i);
		int action = rand() % 4;
		int randindx = rand() % storage.StorageSize();
		int c = rand() % 2;
		switch (action)
		{
		case 0:
			if (c)
			{
				storage.AddObj(new First);
				printf("AddObject: new Class1\n");
			}
			else
			{
				storage.AddObj(new Secnd);
				printf("AddObject: new Class2\n");
			}
			break;
		case 1:
			storage.DeleteObject(randindx);
			break;
		case 2:
			storage.ShowMethod(randindx);
			break;
		case 3:
			if (c)
			{
				storage.ReplaceObject(randindx, new First);
				printf("ReplaceObject: new Class1\n");
			}
			else
			{
				storage.ReplaceObject(randindx, new Secnd);
				printf("ReplaceObject: new Class2\n");
			}
			break;
		default:
			storage.GetCount();
			break;
		}
		cout << endl;
	}
	unsigned int EndTime = clock();
	printf("\nВремя работы = %d\n", EndTime - StartTime);
	storage.ShowStorage();
	storage.GetCount();
}
