#include <iostream>


using namespace std;





#pragma once

#ifndef _B_TREE_H_

#define _B_TREE_H_

#include <iostream>

using namespace std;



struct Node {

	int* e;

	Node** p;

	int a;

	Node* otac;

	Node(int u)

	{

		e = new int[u - 1];

		p = new Node * [u];

		for (int i = 0; i < u; i++)

		{

			p[i] = 0; a = 0; otac = 0;

		}

	}

};



class Queue

{

private:





	struct Elemm {

		Node* podatak;

		Elemm* sled;

		Elemm(Node* x, Elemm* y = 0)

		{

			podatak = x;

			sled = y;

		}

	};



	Elemm* f, * r;



public:



	Queue()

	{

		f = 0;

		r = 0;

	}



	Queue& uneti(Node* w);

	Node* izbrisati();

	bool prazanRed() const

	{

		return (!f);

	}



	~Queue();

};





class Stack {



private:





	struct Elem {

		Node* podatak;

		Elem* sled;

		Elem(Node* y = 0, Elem* x = 0)

		{

			podatak = y;

			sled = x;

		}

	};



	Elem* m;



public:



	Stack()

	{

		m = 0;

	}



	Stack& gurnuti(Node* x);

	Node* pop();

	bool prazanStack()

	{



		if (m == 0)

			return true;

		else return false;

	}





	~Stack();

};









class BStablo

{



private:

	int u;

	Node* koren;

	BStablo(const BStablo& b) {}

	BStablo& operator= (const BStablo& b) {}

	static Node* nadjiNode(Node* v, int u);

	static void sortKeys(int* arrayz, int m);

	void uppointers();



public:



	BStablo(int uu)

	{

		u = uu;

		koren = 0;

	}



	int levelNode(int e) const;



	bool insert(int e);



	int heightStabla() const;



	/*bool izbrisiIzStabla(int e);*/



	int numOfKeys() const;



	bool uStabluJe(int e) const;







	friend ostream& operator<< (ostream& er, BStablo& tr);





	~BStablo();





};



#endif



Queue& Queue::uneti(Node* x)

{

	Queue::Elemm* novi = new Elemm(x);

	if (r == 0)

	{

		f = novi;

	}

	else r->sled = novi;

	r = novi;

	return *this;

}



Node* Queue::izbrisati() {

	if (f == 0)

	{

		exit(1);

	}

	else {

		Queue::Elemm* p;

		p = f;

		Node* x = p->podatak;

		f = p->sled;

		if (f == 0) r = 0;

		delete p;





		return x;

	}

}





Queue::~Queue() {

	Queue::Elemm* old;

	old = f;

	while (old)

	{

		f = f->sled;

		delete old;

		old = f;

	}

}





Stack& Stack::gurnuti(Node* x)

{

	Elem* p = new Elem(x, m);

	m = p;



	return *this;

}



Node* Stack::pop() {

	if (m == 0)

	{

		return 0;

	}

	else {

		Elem* p;

		p = m;

		m = p->sled;

		Node* x = p->podatak;

		delete p;





		return x;

	}

}



Stack::~Stack() {

	Stack::Elem* old;

	old = m;

	while (old)

	{

		m = m->sled;

		delete old;

		old = m;

	}

}









int BStablo::numOfKeys() const {



	Node* sled;

	sled = koren;

	Queue q;

	int br = 0;





	if (sled != 0)

	{

		q.uneti(sled);

		while (!q.prazanRed())

		{

			sled = q.izbrisati();

			br += sled->a;

			for (int i = 0; i < sled->a + 1; i++)

			{

				if (sled->p[i] != 0)

				{

					q.uneti(sled->p[i]);

				}

			}

		}

		return br;

	}

	else return 0;

}



bool BStablo::uStabluJe(int k) const

{

	Node* q;

	q = koren;

	while (q != 0)

	{

		int i = 0;

		while ((i < q->a) && (q->e[i] < k))

			i++;

		if (i == q->a)

		{

			q = q->p[i];

		}

		else {

			if (q->e[i] == k)

			{

				return 1;

			}

			else q = q->p[i];

		}

	}

	return 0;

}





int BStablo::heightStabla() const

{

	Node* to;

	int h = 0, i;

	if (koren == 0)

	{

		return 0;

	}

	to = koren;

	while (to != 0)

	{

		i = 0;

		while ((i < to->a) && (to->p[i] == 0)) i++;

		if (i == to->a)

		{

			to = 0;

		}

		else

			to = to->p[i];

		h++;

	}

	return h - 1;

}



int BStablo::levelNode(int k) const

{

	Node* q;

	q = koren;

	int h = 0;



	while (q != 0)

	{

		int i = 0;

		while ((i < q->a) && (q->e[i] < k))

			i++;

		if (i == q->a)

		{

			q = q->p[i];

		}

		else {

			if (q->e[i] == k)

			{

				return h;

			}

			else

				q = q->p[i];

		}

		h++;

	}

	return -1;

}











void BStablo::sortKeys(int* lol, int n)

{

	for (int i = 0; i < n - 1; i++)

		for (int j = i + 1; j < n; j++)

		{

			if (lol[i] > lol[j])

			{

				int t = lol[i];

				lol[i] = lol[j];

				lol[j] = t;

			}

		}

}



void BStablo::uppointers()

{

	Queue q;

	Node* sled;

	sled = koren;

	if (sled != 0)

	{

		q.uneti(sled);

		while (!q.prazanRed())

		{

			sled = q.izbrisati();

			for (int i = sled->a + 1; i < u; i++)

			{

				sled->p[i] = 0;

			}

			for (int i = 0; i < sled->a + 1; i++)

			{

				if (sled->p[i] != 0) q.uneti(sled->p[i]);

			}

		}

	}

}



bool BStablo::insert(int k) {



	int i;

	Node* to, * q;

	to = koren;

	q = 0;





	while (to != 0) {

		q = to;

		i = 0;

		while ((i < to->a) && (to->e[i] < k))

			i++;

		if (i == to->a)

		{

			to = to->p[i];

		}

		else {

			if (to->e[i] == k)

			{

				return 0;

			}

			else to = to->p[i];

		}

	}



	if (koren == 0)

	{

		koren = new Node(u);

		koren->e[0] = k;

		koren->a++;

		uppointers();







		return 1;

	}



	if ((q == koren) && (koren->a == u - 1))



	{

		Node* p1;

		Node* r;



		int* lol = new int[u + 1];

		for (int i = 0; i < koren->a; i++)

			lol[i] = koren->e[i];

		lol[u - 1] = k;





		sortKeys(lol, u);





		int midl;

		if (u % 2 == 1)

		{

			midl = u / 2;

		}

		else

			midl = u / 2 - 1;



		r = new Node(u);

		p1 = new Node(u);



		r->e[0] = lol[midl];

		r->p[0] = koren;

		r->p[1] = p1;

		r->a++;

		koren->a = 0;

		for (int i = 0; i < midl; i++)

		{

			koren->e[i] = lol[i];

			koren->a++;

		}

		for (int i = midl + 1; i < u; i++)

		{

			p1->e[i - midl - 1] = lol[i];

			p1->a++;

		}

		for (int i = 0; i < u; i++)

		{

			p1->p[i] = 0;

			koren->p[i] = 0;

		}

		p1->otac = r;

		koren->otac = r;

		koren = r;

		uppointers();

		return 1;

	}



	if (q->a != u - 1) {

		i = q->a - 1;

		while ((i >= 0) && (q->e[i] > k))

		{

			q->e[i + 1] = q->e[i];

			i--;

		}

		if (i < 0) q->e[0] = k;

		else q->e[i + 1] = k;

		q->a++;

		uppointers();

		return 1;

	}



	if (q->a == u - 1)

	{



		Node* pp = new Node(u);

		int* lol = new int[u];



		for (int i = 0; i < q->a; i++)

			lol[i] = q->e[i];

		lol[u - 1] = k;

		sortKeys(lol, u);





		int midl;

		if (u % 2 == 1)

		{

			midl = u / 2;

		}

		else

			midl = u / 2 - 1;

		q->a = 0;

		for (int i = 0; i < midl; i++)

		{

			q->e[i] = lol[i];

			q->a++;

		}

		for (int i = midl + 1; i < u; i++)

		{

			pp->e[i - midl - 1] = lol[i];

			pp->a++;

		}



		while (1)

		{

			Node* to = q->otac;

			if (to->a < u - 1)

			{

				int i = to->a - 1;

				while ((i >= 0) && (to->e[i] > lol[midl]))

				{

					to->e[i + 1] = to->e[i];

					to->p[i + 2] = to->p[i + 1];

					i--;

				}

				if (i < 0)

				{

					to->e[0] = lol[midl];

					to->p[1] = pp;

				}

				else

				{

					to->e[i + 1] = lol[midl];

					to->p[i + 2] = pp;

				}

				pp->otac = to;

				to->a++;

				uppointers();







				return 1;

			}

			else {

				if (to == koren)

				{

					Node* p1, * r;

					int* lol1 = new int[u + 1];

					for (int i = 0; i < koren->a; i++)

						lol1[i] = koren->e[i];

					lol1[u - 1] = lol[midl];

					sortKeys(lol1, u);





					int srednji1;

					if (u % 2 == 1)

					{

						srednji1 = u / 2;

					}

					else

						srednji1 = u / 2 - 1;

					r = new Node(u);

					p1 = new Node(u);





					r->e[0] = lol1[srednji1];

					r->p[0] = koren;

					r->p[1] = p1;

					r->a++;

					koren->a = 0;

					for (int i = 0; i < srednji1; i++)

					{

						koren->e[i] = lol1[i];

						koren->a++;

					}

					pp->otac = p1;

					for (int i = srednji1 + 1; i < u; i++)

					{

						p1->e[i - srednji1 - 1] = lol1[i];

						p1->a++;

					}



					if (pp->e[0] < to->p[to->a]->e[0])

					{

						for (int i = to->a; i <= to->a + p1->a; i++)

						{

							p1->p[i - to->a] = to->p[i];

							p1->p[i - to->a]->otac = p1;

						}

						to->p[to->a] = pp;

						pp->otac = to;

					}



					else if (p1->e[0] > pp->e[0])

					{

						p1->p[0] = pp;

						for (int i = to->a + 1; i <= to->a + p1->a; i++)

						{

							p1->p[i - to->a] = to->p[i];

							p1->p[i - to->a]->otac = p1;

						}

						pp->otac = p1;

					}



					else

					{

						for (int i = to->a + 1; i <= to->a + p1->a; i++)

						{

							p1->p[i - to->a - 1] = to->p[i];

							to->p[i]->otac = p1;

						}

						p1->p[p1->a] = pp;

						pp->otac = p1;

					}



					p1->otac = r;

					koren->otac = r;

					koren = r;

					uppointers();







					return 1;

				}

				else

				{

					Node* p1 = new Node(u);

					int* lol1 = new int[u];

					for (int i = 0; i < to->a; i++) lol1[i] = to->e[i];

					lol1[u - 1] = lol[midl];

					sortKeys(lol1, u);





					int srednji1;

					if (u % 2 == 1)

					{

						srednji1 = u / 2;

					}

					else

						srednji1 = u / 2 - 1;

					to->a = 0;

					for (int i = 0; i < srednji1; i++)

					{

						to->e[i] = lol1[i];

						to->a++;

					}

					for (int i = srednji1 + 1; i < u; i++)

					{

						p1->e[i - srednji1 - 1] = lol1[i];

						p1->a++;

					}



					if (pp->e[0] < to->p[to->a]->e[0])

					{

						for (int i = to->a; i <= to->a + p1->a; i++)

						{

							p1->p[i - to->a] = to->p[i];

							p1->p[i - to->a]->otac = p1;

						}

						to->p[to->a] = pp;

						pp->otac = to;

					}



					else if (p1->e[0] > pp->e[0])

					{

						p1->p[0] = pp;

						for (int i = to->a + 1; i <= to->a + p1->a; i++)

						{

							p1->p[i - to->a] = to->p[i];

							p1->p[i - to->a]->otac = p1;

						}

					}



					else {

						for (int i = to->a + 1; i <= to->a + p1->a; i++)

						{

							p1->p[i - to->a - 1] = to->p[i];

							p1->p[i - to->a - 1]->otac = p1;

						}

						p1->p[p1->a] = pp;

					}



					pp->otac = p1;

					p1->otac = to->otac;



					q = to;

					pp = p1;

					lol[midl] = lol1[srednji1];

				}

			}

		}

	}

}



ostream& operator<< (ostream& os, BStablo& bt) {

	Queue q;

	int a, b;

	Node* next, * prethodni;

	if (bt.koren == 0) return cout << "Stablo je prazno." << endl;

	next = bt.koren;

	prethodni = 0;

	q.uneti(next);

	while (!q.prazanRed()) {

		next = q.izbrisati();

		if (prethodni) a = bt.levelNode(prethodni->e[0]);

		b = bt.levelNode(next->e[0]);

		if ((prethodni != 0) && (bt.levelNode(prethodni->e[0]) == bt.levelNode(next->e[0]))) cout << ' ';

		else if ((prethodni != 0) && (bt.levelNode(prethodni->e[0]) != bt.levelNode(next->e[0]))) cout << endl;

		cout << '|'; // ispis jednog cvora

		for (int i = 0; i < next->a; i++) cout << next->e[i] << '|';

		prethodni = next;

		for (int i = 0; i < next->a + 1; i++)

			if (next->p[i] != 0) q.uneti(next->p[i]);

	}

	return cout << endl;

}



BStablo::~BStablo() {

	Queue q;

	Stack st;

	Node* sled;

	sled = koren;

	if (sled != 0) {

		q.uneti(sled);

		while (!q.prazanRed())

		{

			sled = q.izbrisati();

			st.gurnuti(sled);

			for (int i = 0; i < sled->a + 1; i++)

			{

				if (sled->p[i] != 0) q.uneti(sled->p[i]);

			}

		}

		while (!st.prazanStack())

		{

			sled = st.pop();

			delete sled;

		}

	}

}








#include <iostream>


using namespace std;



int main() {



	cout << "****************************" << endl;

	cout << "Koji zelite stepen cvora ? ";

	int t;

	cin >> t;



	BStablo f(t);

	int u;

	int end = 0;







	while (!end) {



		cout << "1. Umetanje kljuca u B stablo:" << endl;

		cout << "2. Da li je zadati kljuc u  B stablu:" << endl;

		cout << "3. Visine B stabla:" << endl;

		cout << "4. Broja kljuceva u B stablu:" << endl;

		cout << "5. Ispis B stabla:" << endl;

		cout << "6. EXIT" << endl;







		cout << "Izaberi opciju? ";



		int p;



		cin >> p;





		switch (p) {



		case 1: cout << "Unesite kljuc koji zelite da umetnete u B stablo: ";

			cin >> u;

			f.insert(u);

			break;





		case 2: cout << "Unesite kljuc koji zelite da pretrazite: ";

			cin >> u;

			if (f.uStabluJe(u))

				cout << "Kljuc postoji u B stablu." << endl;

			else cout << "Kljuc ne postoji u B stablu." << endl;

			cout << endl;

			break;



		case 3: cout << "Visina B stabla je : " << f.heightStabla() << endl;

			cout << endl;

			break;



		case 4: cout << "Broj kljuceva u B stablu je: " << f.numOfKeys() << endl;

			cout << endl;

			break;




		case 5: cout << f;

			break;



		case 6:

			end = 1;

			break;



		default: cout << "LOS UNOS" << endl;

			cout << endl;

			break;



		}



	}



	return 0;

}