#include <fstream>
#include <iostream>
#include <stdlib.h>
# include "myconsole.h"
# include "editor.h"
using namespace std;


//-------------------------------Color Codes------------------------------//
// Color Codes Hexadecimal values for both Fore Ground and Back Ground //ForeGround|BackGround
int B_BLACK			= 0x00;	int B_Royal_Blue	= 0x10;	int B_Dark_Green	= 0x20;
int B_Tale_Blue		= 0x30;	int B_Dark_Red		= 0x40;	int B_Purple		= 0x50;
int B_Tale_Green	= 0x60;	int B_Light_Grey	= 0x70; int B_Dark_Gray		= 0x80;	
int B_Light_Blue	= 0x90; int B_Light_Green	= 0xA0;	int B_Sky_Blue		= 0xB0;
int B_Red			= 0xC0;	int B_Pink			= 0xD0;	int B_Yellow		= 0xE0;
int B_White			= 0xF0;

int F_BLACK			= 0x00;	int F_Royal_Blue	= 0x01; int F_Dark_Green = 0x02;
int F_Tale_Blue		= 0x03;	int F_Dark_Red		= 0x04;	int F_Purple	 = 0x05;
int F_Tale_Green	= 0x06;	int F_Light_Grey	= 0x07; int F_Dark_Gray	 = 0x08;
int F_Light_Blue	= 0x09; int F_Light_Green	= 0x0A;	int F_Sky_Blue	 = 0x0B;
int F_Red			= 0x0C;	int F_Pink			= 0x0D;	int F_Yellow	 = 0x0E;
int F_White			= 0x0F;

//-------------------------------POINT CLASS------------------------------//
//initialize MaxPoint
point point::MaxPoint(MAX_X, MAX_Y);
bool point::incrementX()
{
	bool returnValue = true;
	if (x<MaxPoint.x)
		x++;
	else if (y<MaxPoint.y)
	{
		x = 0;
		y = y + 1;
	}
	else
		returnValue = false;

	return returnValue;
}
bool point::incrementY()
{
	bool returnValue = true;
	if (y<MaxPoint.y)
		y++;
	else
		returnValue = false;

	return returnValue;

}
bool point::decrementX()
{
	bool returnValue = true;
	if (x>0)
		x--;
	else if (y>0)
	{
		y--;
		x = MaxPoint.x;
	}
	else
		returnValue = false;

	return returnValue;
}
bool point::decrementY()
{
	bool returnValue = true;
	if (y>0)
		y--;
	else
		returnValue = false;

	return returnValue;

}

//-------------------------------END OF POINT CLASS------------------------------------------------//

point currentPosition(0, 0);

#include<iostream>
#include<fstream>
using namespace std;

template <typename t>
class linklist {
	class Node {
		friend class linklist<t>;
	public:
		t data;
		Node* next;
		Node* prev;
		Node() {
			data = 0;
			next = nullptr;
			prev = nullptr;
		}
		Node(t val)
		{
			data = val;
			next = nullptr;
			prev = nullptr;
		}
	};
	Node* head;
public:
	linklist()
	{
		head = new Node;
	}
	void insert_at_head(t val)
	{
		Node* n = new Node(val);
		if (head == nullptr)
		{
			n->prev = head;
			head->next = n;
		}
		else
		{
			n->next = head->next;
			n->prev = head;
			head->next = n;
		}
	}
	void delete_from_head()
	{
		if (head->next != nullptr)
		{
			Node* curr = head->next;
			if (curr->next != nullptr) {
				head->next = curr->next;
				curr->prev = head;
			}
			else
			{
				head->next = nullptr;
			}
			delete curr;
		}

	}
	void delete_all(t val)
	{
		Node* n = head->next;
		while (n->next != nullptr)
		{
			if (n->data == val)
			{
				Node* curr = n;
				if (n->next == nullptr)
				{
					n->prev->next = nullptr;
					return;
				}
				else
				{
					n->prev->next = n->next;
					n->next->prev = n->prev;
				}
				n = n->next;
				delete curr;
			}
			else
				n = n->next;
		}
	}
	void swap_nodes(Node* a, Node* b)
	{
		Node* curr = a->prev;
		a->next = b->next;
		a->prev = b;
		b->next = a;
		a->next->prev = a;
		b->prev = curr;
	}
	void display()
	{
		int count = 0;
		int flag[100] = { 0 };
		int flagi = 0;
		int y = 0;
		point pt(0, 0);
		iterators i = begin();
		if (i.curr != nullptr)
		{
			while (i.curr != nullptr)
			{
				cout << i.curr->data;
				if (i.curr->data == '\n')
					{
						flag[flagi] = count;
						flagi++;
					}
					i++;
				count++;
			}

			//if (flag == 1)
			//{
			//	pt.incrementY();
			//	//PlaceCursor(0, y++);
			//	flag = 0;
			//}
			flagi = 0;
			for (int o = 0; o < count; o++)
			{
				SetColorAtPoint(pt.getX(), pt.getY(), B_BLACK | B_White); //ForeGround|BackGround
				pt.incrementX();

			    if (o == flag[flagi])
				{
					if (flag[flagi] != 0)
					{
						pt.incrementY();
						pt.setX(0);
						flagi++;
					}
					//PlaceCursor(0, 1);
				}
			}
			//cout << i.curr->data;
		}

	}
	class iterators {
	public:
		friend class linklist<t>;
		Node* curr;
		iterators(Node* input = nullptr)
		{
			curr = input;
		}
		t& operator *()const
		{
			return curr->data;
		}
		t& operator -> ()const
		{
			return curr->data;
		}
		iterators& operator ++()
		{
			if (curr != nullptr)
			{
				curr = curr->next;
			}
			return *this;
		}
		iterators operator ++(int) {
			iterators it(curr);
			curr = curr->next;
			return it;
		}
		iterators operator --(int) {
			iterators it(curr);
			curr = curr->prev;
			return it;
		}
		iterators& operator --()
		{
			if (curr != nullptr)
			{
				curr = curr->prev;
			}
			return *this;
		}
		bool operator ==(iterators& l)
		{
			if (curr == l.curr)
				return true;
			return false;
		}
		bool operator !=(iterators & l)
		{
			if (curr != l.curr)
				return true;
			return false;
		}
	};
	iterators begin()
	{
		return head;
	}
	void insert_it(t element, iterators itr)
	{
		if (itr.curr != nullptr)
		{
			Node* n = new Node;
			n->data = element;
			if (itr.curr->next == nullptr)
			{
				n->next = nullptr;
			}
			else
			{
				n->next = itr.curr;
			}
			n->prev = itr.curr->prev;
			itr.curr->prev->next = n;
			itr.curr->prev = n;
		}
	}
	iterators end()
	{
		return nullptr;
	}
	void insert_after_iterator(iterators & a, t val)
	{
		Node* n = new Node(val);
		if (a.curr != nullptr)
		{
			if (a.curr->next == nullptr)
			{
				a.curr->next = n;
				n->prev = a.curr;
			}
			else
			{
				Node* current = a.curr->next;
				a.curr->next = n;
				n->next = current;
				current->prev = n;
				n->prev = a.curr;
			}
		}
		else
		{
			n->next = nullptr;
			n->prev = a.curr;
		}
	}
	void insert_multiple(iterators & a)
	{
		int c = 0;
		t val;
		cout << "Enter the number of values you want to insert:";
		cin >> c;
		for (int i = 0; i < c; i++)
		{
			cout << "Enter the value:";
			cin >> val;
			insert_after_iterator(a, val);
			a++;
		}
	}
	void delete_at_anywhere(iterators &itr)
	{

		iterators i = begin();
		iterators temp = begin();
		if (i.curr != nullptr)
		{
			while (i.curr != itr.curr)
			{
				++i;
				if (i.curr != itr.curr)
				{
					++temp;
				}

			}
			temp.curr->next = i.curr->next;
			itr.curr->prev = temp.curr;
			//node* tempit = temp.curr->next;
			//delete tempit;
		}

	}
	void delete_multiple(iterators & a)
	{
		int c = 0;
		t val;
		cout << "Enter the number of values you want to delete:";
		cin >> c;
		for (int i = 0; i < c; i++)
		{
			cout << "Enter the value:";
			cin >> val;
			delete_at_anywhere(a, val);
			a++;
		}
	}
	void delete_in_range(iterators & a, iterators & b)
	{
		while (a != b)
		{
			delete_at_anywhere(a, a.curr->data);
			a++;
		}
	}
	iterators search(iterators x, t arr[100])
	{
		x = begin();
		iterators its = begin();
		int i = 0, c = 0, z = 0;
		while (its.curr != nullptr)
		{
			if ((arr[c] == its.curr->data) && arr[c] != '\0')
			{
				//cout << "DATA IS : " << its.curr->data;
				c++;
				if (c == strlen(arr))
				{
					cout << "Word found at : " << z - strlen(arr) + 1 << "," << z << endl;
					for (int i = 0; i < strlen(arr); i++)
					{
						--its;
					}
					x = its;
					return x;
				}
			}
			else
			{
				c = 0;
			}
			++its;
			z++;
		}
		
	}
	void insert_multiple(char arr[100], char rep[100])
	{
		iterators its = begin();
		iterators it = begin();
		int i = 0, c = 0, z = 0;
		while (its.curr != nullptr)
		{
			if ((arr[c] == its.curr->data) && arr[c] != '\0')
			{
				//cout << "DATA IS : " << its.curr->data;
				c++;
				if (c == strlen(arr))
				{
					cout << "Word found at : " << z - strlen(arr) + 1 << "," << z << endl;
					for (int i = 0; i < z; i++)
					{
						++it;
					}
					for (int i = 0; i < strlen(arr) - 1; i++)
					{
						delete_at_anywhere(it);
						--it;
					}
					for (int i = 0; i < strlen(rep); i++)
					{
						insert_it(rep[i],it);
						// ++it;
					}
					delete_at_anywhere(it);
					c = 0;
					it = begin();
				}
			}
			else
			{
				c = 0;
			}
			++its;
			z++;
			//cout << "\nWord not found" << endl;
		}
	}
	iterators *search_all(t arr[100],int &instace)
	{
		iterators *x = new iterators[100];
		iterators its = begin();
		int i = 0, c = 0, z = 0, m = 0;
		while (its.curr != nullptr)
		{
			if ((arr[c] == its.curr->data) && arr[c] != '\0')
			{
				//cout << "DATA IS : " << its.curr->data;
				c++;
				if (c == strlen(arr))
				{
					cout << "Word found at : " << z - strlen(arr) + 1 << "," << z << endl;
					for (int i = 0; i < strlen(arr); i++)
					{
						--its;
					}
					x[m] = its;
					m++;
				}
			}
			else
			{
				c = 0;
			}
			++its;
			z++;
		}
		return x;
	}
	void savetofile(iterators start)
	{

	}
	void highlight(iterators* arr, int instances,t key[100])
	{
		int h = 0;
		int p = 0;
		int l = 0;
		point pt(0, 0);
		pt.setX(0);
		pt.setY(0);
		iterators i = begin();
		while (i.curr != nullptr)
		{
			//cout << "hello";
			if (arr[h] == i)
			{
				p = pt.getX();
				for (int k = 0; k < strlen(key); k++)
				{
					//cout << "hello";
					SetColorAtPoint(pt.getX(), pt.getY(), F_White | B_Light_Green); //ForeGround|BackGround
					pt.incrementX();
				}
				h++;
			    pt.setX(p);
			}

			if (i.curr->data == '\n')
			{
				pt.setX(0);
				pt.incrementY();
			}
			else 
				pt.incrementX();

			i++;
		}
	}
	~linklist()
	{
		Node* current1 = head;
		while (head->next != nullptr)
		{
			delete head;
			head = head->next;
		}
		cout << "\nDESTRUCTOR CALLED :\n\n\n";
	}
};

//--------------------------The function Where you will write code--------------------------------//
//-------------------------------END OF POINT CLASS------------------------------------------------//


//--------------------------The function Where you will write code--------------------------------//
int mainEditor()
{
	int key = 0;
	int count = 0;
	bool stop = false;
	point currentPosition(0, 0);
	point saveposition(0, 0);
	currentPosition.setMaxPoint(MAX_X, MAX_Y);
	bool specialKey = false;
	int instace = 0;

	// these are some decleration of the linked list and to make the notepad smooth
	linklist<char> a;
	linklist<char> ::iterators start;
	linklist<char> ::iterators *s_s;
	linklist<char> ::iterators s_e;
	linklist<char> ::iterators null;
	linklist<char> ::iterators To_Save;
	//linklist<char> ::iterators back;   //for backspace
	//linklist<char> ::iterators end;
	start = a.begin();
	s_s = new linklist<char> ::iterators [100];
	s_e = a.begin();
	To_Save = a.begin(); // for fixed pointer to head node
	//end = a.end();

	while (!stop)
	{
		key = CheckWhichKeyPressed(specialKey);
		//escape key
		if (key == ESCKEY)
			stop = true;
		//printable character...only adds to the end of text
		//this will not do insertions in between text
		//add code here to insert characters within text
		else if (!specialKey && key >= 32 && key <= 126)
		{

			if (currentPosition.getX() < MAX_X)
			{
				ClearScreen();
				PlaceCursor(0, 0);
				a.insert_after_iterator(start, key);
				start++;
				count++;
				//cout << (char)key;
				//cout << endl << endl << endl << endl << endl << endl;
				a.display();
				//You can change color of text by calling this function

				currentPosition.incrementX();
			}
			else if (currentPosition.getY() < MAX_Y)
			{
				/*a.insert_after_iterator(start, key);
				start++;*/
				currentPosition.incrementY();
				currentPosition.setX(0);
			}
		}
		else if (specialKey && key == LEFTKEY)
		{
			currentPosition.decrementX();
			start--;
			count--;
		}
		else if (specialKey && key == RIGHTKEY)
		{
			if (start.curr->next != nullptr)
			{
				currentPosition.incrementX();
				start++;
				count++;
			}
		}
		else if (specialKey && key == UPKEY)
		{
			currentPosition.decrementY();

		}
		else if (specialKey && key == DOWNKEY)
		{	//Update it so that cursur not move downword if it is at last line of text.
			currentPosition.incrementY();

		}
		else if (key == ENTERKEY) {
			//cout << ('\n');
			ClearScreen();
			a.insert_after_iterator(start, '\n');
			start++;
			currentPosition.setX(0);
			currentPosition.incrementY();
		}
		else if (key == DELKEY)
		{
			//call a function to handle 
			//a.delete_at_anywhere(start, key);
		}
		else if (key == BACKSPACE)
		{
			if (start.curr->prev != nullptr)
			{
				//handle backspace here
				PlaceCursor(0, 0);
				a.delete_at_anywhere(start);
				start--;
				count--;
				ClearScreen();
				a.display();
				if (!currentPosition.decrementX() && currentPosition.getY() > 0) {
					cout << '\0';
					currentPosition.decrementY();
					currentPosition.setX(MAX_X);
				}
			}
		}
		else if (key == F1KEY || key == F2KEY || key == F3KEY)
		{
			PlaceCursor(0, MAX_Y);
			for (int i = 0; i < MAX_X; i++)
			{
				cout << '\0';
				currentPosition.incrementX();
			}

			PlaceCursor(0, MAX_Y);
			cout << "Enter Search Query: " << endl;
			currentPosition.setX(0 + strlen("Enter Search Query: "));
			//currentPosition.setY(MAX_Y);

			if (key == F1KEY) {

				char arr[100] = { 0 };
				cout << "ENTER ELEMENT YOU WANT TO SEARCH : ";
				cin.getline(arr, 100);
				//Search for one instance of string and move cursor there
				start = a.search(start, arr);
			}
			else if (key == F2KEY)
			{
				char arr[100] = { 0 };
				//cout << "ENTER ELEMENT YOU WANT TO SEARCH : ";
				cin.getline(arr, 100);
				s_s = a.search_all(arr, instace);
				ClearScreen();
				PlaceCursor(0, 0);
				currentPosition.setX(0);
				currentPosition.setY(0);
				a.display();
				a.highlight(s_s, instace, arr);
				for (int i = 0; i < count; i++)
				{
					currentPosition.incrementX();
				}


				//Search for one instance of string and move cursor there
			}
			else if (key == F3KEY)
			{
				char arr[100] = { 0 };
				char arr2[100] = { 0 };
				cin.getline(arr, 100);
				cin.getline(arr2, 100);
				a.insert_multiple(arr, arr2);
				ClearScreen();
				PlaceCursor(0, 0);
				currentPosition.setX(0);
				currentPosition.setY(0);
				a.display();
				for (int i = 0; i < count; i++)
				{
					currentPosition.incrementX();
				}
				//Search for all instances of string 
				//Take a second input string 
				//and replace all instances of first string with second string
			}
		}
			//a.savetofile(To_Save);
		else if (key == F4KEY)
		{
			linklist <char>::iterators p = a.begin();
			ofstream myfile("save.txt");
			while (p.curr != NULL)
			{
				myfile << p.curr->data;
				++p;
			}
			myfile.close();
			cout << "\nFILE SAVED\n";
		}
		PlaceCursor(currentPosition.getX(), currentPosition.getY());
	}
		//PlaceCursor(currentPosition.getX(), currentPosition.getY());
	cout << endl;
	a.display();
	return 0;
}

//-------------------------------------------End Main Editor--------------------------//
void main()
{
	mainEditor();
}
