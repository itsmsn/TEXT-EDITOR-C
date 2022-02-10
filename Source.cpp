#include<iostream>
#include<fstream>
#include <stdlib.h>
#include "myconsole.h"
#include "editor.h"
//#include"20L-1121_SEC B.h"
using namespace std;


//-------------------------------Color Codes------------------------------//
// Color Codes Hexadecimal values for both Fore Ground and Back Ground //ForeGround|BackGround
int B_BLACK = 0x00;	int B_Royal_Blue = 0x10;	int B_Dark_Green = 0x20;
int B_Tale_Blue = 0x30;	int B_Dark_Red = 0x40;	int B_Purple = 0x50;
int B_Tale_Green = 0x60;	int B_Light_Grey = 0x70; int B_Dark_Gray = 0x80;
int B_Light_Blue = 0x90; int B_Light_Green = 0xA0;	int B_Sky_Blue = 0xB0;
int B_Red = 0xC0;	int B_Pink = 0xD0;	int B_Yellow = 0xE0;
int B_White = 0xF0;

int F_BLACK = 0x00;	int F_Royal_Blue = 0x01; int F_Dark_Green = 0x02;
int F_Tale_Blue = 0x03;	int F_Dark_Red = 0x04;	int F_Purple = 0x05;
int F_Tale_Green = 0x06;	int F_Light_Grey = 0x07; int F_Dark_Gray = 0x08;
int F_Light_Blue = 0x09; int F_Light_Green = 0x0A;	int F_Sky_Blue = 0x0B;
int F_Red = 0x0C;	int F_Pink = 0x0D;	int F_Yellow = 0x0E;
int F_White = 0x0F;

//-------------------------------POINT CLASS------------------------------//
//initialize MaxPoint
point point::MaxPoint(MAX_X, MAX_Y);
bool point::incrementX()
{
	bool returnValue = true;
	if (x < MaxPoint.x)
		x++;
	else if (y < MaxPoint.y)
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
	if (y < MaxPoint.y)
		y++;
	else
		returnValue = false;

	return returnValue;

}
bool point::decrementX()
{
	bool returnValue = true;
	if (x > 0)
		x--;
	else if (y > 0)
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
	if (y > 0)
		y--;
	else
		returnValue = false;

	return returnValue;

}

//-------------------------------END OF POINT CLASS------------------------------------------------//


//--------------------------The function Where you will write code--------------------------------//


template <typename t>
class linklist {
	class Node {
		t data;
		Node* next;
		Node* prev;
		friend class linklist<t>;
	public:
		Node() {
			data = NULL;
			next = NULL;
			prev = NULL;
		}
		Node(t val)
		{
			data = val;
			next = NULL;
			prev = NULL;
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
		if (head == NULL)
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
		if (head->next != NULL)
		{
			Node* curr = head->next;
			if (curr->next != NULL) {
				head->next = curr->next;
				curr->prev = head;
			}
			else
			{
				head->next = NULL;
			}
			delete curr;
		}

	}
	void delete_all(t val)
	{
		Node* n = head->next;
		while (n->next != NULL)
		{
			if (n->data == val)
			{
				Node* curr = n;
				if (n->next == NULL)
				{
					n->prev->next = NULL;
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
		Node* curr = head->next;
		while (curr->next != NULL)
		{
			cout << curr->data << " ";
			curr = curr->next;
		}
		cout << curr->data;
		cout << endl;
	}
	class iterators {
		Node* curr;
	public:
		friend class linklist<t>;
		iterators(Node* input = NULL)
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
			if (curr != NULL)
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
			if (curr != NULL)
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
	iterators end()
	{
		return NULL;
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
	void delete_at_anywhere(iterators & a, t val)
	{

		Node* current = a.curr;
		if (a.curr->next != nullptr)
		{
			a.curr->prev = a.curr->next;
			a.curr->next->prev = a.curr;

		}
		else if (a.curr->next == nullptr)
		{
			a.curr->prev->next = NULL;
		}
		delete current;
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
	iterators search(iterators x, t val)
	{

	}
	void search_replace(iterators & x, t val, t val1)
	{

	}
	iterators search_all(iterators & x, t val)
	{

	}
	void savetofile(iterators start, iterators end)
	{


	}
	~linklist()
	{

	}
};

int mainEditor()
{
	int key = 0;
	bool stop = false;
	point currentPosition(0, 0);
	point saveposition(0, 0);
	currentPosition.setMaxPoint(MAX_X, MAX_Y);
	bool specialKey = false;

	// these are some decleration of the linked list and to make the notepad smooth
	linklist<char> a;
	linklist<char> ::iterators start;
	linklist<char> ::iterators start1;
	linklist<char> ::iterators back;   //for backspace
	linklist<char> ::iterators end;
	start = a.begin();
	start1 = a.begin(); // for fixed pointer to head node
	end = a.end();

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
				a.insert_after_iterator(start, key);
				start++;
				cout << (char)key;
				//You can change color of text by calling this function
				SetColorAtPoint(currentPosition.getX(), currentPosition.getY(), F_BLACK | B_White);   //ForeGround|BackGround
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
		}
		else if (specialKey && key == RIGHTKEY)
		{
			currentPosition.incrementX();

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
			cout << ('\n');
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
			cout << '\0';
			//handle backspace here
			if (!currentPosition.decrementX() && currentPosition.getY() > 0) {
				cout << '\0';
				currentPosition.decrementY();
				currentPosition.setX(MAX_X);
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
			currentPosition.setY(MAX_Y);

			if (key == F1KEY) {

				//Search for one instance of string and move cursor there
			}
			else if (key == F2KEY)
			{
				//Search for one instance of string and move cursor there
			}
			else if (key == F3KEY)
			{
				//Search for all instances of string 
				//Take a second input string 
				//and replace all instances of first string with second string
			}
		}
		else if (key == F4KEY)
		{
			a.savetofile(start1, end);
		}
		PlaceCursor(currentPosition.getX(), currentPosition.getY());

	}
	cout << endl;
	a.display();
	return 0;
}

//-------------------------------------------End Main Editor--------------------------//
void main()
{
	mainEditor();
}