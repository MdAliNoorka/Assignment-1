#pragma once

#include <iostream>
#include <string>
using namespace std;


class Block
{
private:
	int startByteId;
	int totalBytes;
public:

	Block(int tbid = 0, int ttb = 0)
	{
		startByteId = tbid;
		totalBytes = ttb;
	}

	friend ostream& operator << (ostream& op, const Block& obj1)
	{
		op << "Starting Byte : " << obj1.startByteId + 1
			<< "\t Ending Byte : " << obj1.startByteId + obj1.totalBytes
			<< "\t Total Bytes : " << obj1.totalBytes << endl;
		return op;
	}

	friend istream& operator >> (istream& ip, Block& obj1)
	{
		cout << "\nEntre Starting byte ID : ";
		ip >> obj1.startByteId;
		cout << "\nEntre Total bytes : ";
		ip >> obj1.totalBytes;
		return ip;
	}

	bool CheckContinuity(Block& obj)
	{
		if (startByteId + totalBytes == obj.startByteId)
			return true;
		return false;
	}

	bool operator > (const Block& obj)
	{
		return (startByteId > obj.startByteId);
	}

	bool operator < (const Block& obj)
	{
		return (startByteId < obj.startByteId);
	}

	void operator = (const Block& obj)
	{
		startByteId = obj.startByteId;
		totalBytes = obj.totalBytes;
	}

	bool operator == (const Block& obj) const
	{
		return (startByteId == obj.startByteId && totalBytes == obj.totalBytes);
	}

	bool operator != (const Block& obj) const
	{
		return (!(startByteId == obj.startByteId && totalBytes == obj.totalBytes));
	}

	int GetStartByteId() { return startByteId; }

	void SetStartByteId(int bid) { startByteId = bid; }

	void SetTotalBytes(int tb) { totalBytes = tb; }

	int GetTotalBytes() { return totalBytes; }

};


ostream& operator << (ostream& op, const Block& obj1);

istream& operator >> (istream& ip, Block& obj1);


template <class T>
class SLL
{
public:

	SLL()
	{
		tail = new Node;
		head = new Node(tail);
		size = 0;
	}

	SLL(T& obj)
	{
		size = 0;
		tail = new Node;
		head = new Node(tail);
		head->next = new Node(obj, head->next);
		size++;
	}

	bool IsEmpty()
	{
		if (size == 0 || head->next == tail)
			return true;
		else
			return false;
	}

	void InsertAtHead(T td)
	{
		head->next = new Node(td, head->next);
		size++;
	}

	void InsertAtTail(T td)
	{
		if (IsEmpty())
		{
			head->next = new Node(td, head->next);
		}
		else
		{
			SLL::Iterator itsl;
			itsl = SecondLast();
			itsl.iPtr->next = new Node(td, itsl.iPtr->next);
		}
		size++;
	}

	//bool InsertBefore(T tc, T tb)
	//{
	//	if (IsPresent(tc))
	//	{
	//		SLLIterator itb, ite;
	//		itb = Begin();
	//		ite = End();
	//		while ((*(itb.iPtr->next)) != tc)
	//			itb++;
	//		itb.iPtr->next = new Node(tb, itb.iPtr->next);
	//		return true;
	//	}
	//	return false;
	//}
	//bool InsertAfter(T tc, T ta)
	//{
	//	if (IsPresent(tc))
	//	{
	//		SLLIterator itb, ite;
	//		itb = Begin();
	//		ite = End();
	//		while ((*(itb.iPtr)) != tc)
	//			itb++;
	//		itb.iPtr->next = new Node(ta, itb.iPtr->next);
	//		return true;
	//	}
	//	return false;
	//}
	//void DeleteThat(T& obj)
	//{
	//	SLLIterator itb = BeginFromHead();
	//	SLLIterator ite = End();
	//	while (itb != ite)
	//	{
	//		SLLIterator I(itb.iPtr->next);
	//		cout << "\n12\n";
	//		if (*(I) == obj)
	//		{
	//			SLLIterator I1(itb.iPtr->next->next);
	//			delete itb.iPtr->next;
	//			itb.iPtr->next = I1.iPtr;
	//			return;
	//		}
	//		itb++;
	//	}
	//}

	bool IsPresent(const T& obj)
	{
		SLLIterator itb, ite;
		itb = Begin();
		ite = End();
		while (itb != ite)
		{
			if ((*itb) == obj)
				return true;
			itb++;
		}
		return false;
	}

	void Sort()
	{
		SLLIterator itb, ite, itb1;
		itb = Begin();
		ite = End();
		while (itb != ite)
		{
			itb1 = itb;
			while (itb1 != ite)
			{
				if ((*itb) > (*itb1))
					Swap((*itb), (*itb1));
				itb1++;
			}
			itb++;
		}
		Merge();
	}

	void Merge()
	{
		SLLIterator itb, itb1, ite;
		itb = Begin();
		ite = End();
		bool merged = false;
		int a = 0;
		while (itb != ite && a < size)
		{
			++a;
			itb1 = itb;
			itb1++;
			if ((*itb).CheckContinuity(*itb1))
			{
				SLLIterator itb2(itb1.iPtr->next);
				(*itb).SetTotalBytes((*itb).GetTotalBytes() + (*itb1).GetTotalBytes());
				delete itb1.iPtr;
				itb.iPtr->next = itb2.iPtr;
				merged = true;
				if (itb2 == ite)
					break;
			}
			if (!merged)
			{
				itb++;
				merged = false;
			}

		}
	}




	bool Remove(T& obj)
	{
		SLL::Iterator itb, ite;
		itb = Begin();
		ite = End();
		while (itb != ite)
		{
			if ((*itb) == obj)
			{
				SLL::Iterator itb1 /*ite1*/;
				itb1 = BeginFromHead();
				while (itb1.iPtr->next != itb.iPtr) { itb1++; }
				SLL::Iterator I(itb.iPtr->next);
				delete itb.iPtr;
				itb1.iPtr->next = I.iPtr;
				--size;
				return true;
			}
			itb++;
		}
		return false;
	}

	friend ostream& operator << (ostream& op, SLL<T>& obj)
	{
		if (!obj.IsEmpty())
		{
			Node* temp = obj.head->next;
			while (temp != obj.tail)
			{
				cout << temp->data << endl;
				temp = temp->next;
			}

		}


		return op;
	}

	friend istream& operator >> (istream& ip, SLL<T>& obj)
	{
		cout << "\nEntre number of objects you wanna add\t";
		int x;
		cin >> x;

		for (int i = 0; i < x; i++)
		{
			T tobj;
			cout << "Entre " << i + 1 << '\n';
			cin >> tobj;
			obj.InsertAtTail(tobj);
			cout << '\n' << i + 1 << " is inserted\n";
		}
		return ip;
	}

	bool Swap(T& first, T& second)
	{
		if (!IsEmpty())
		{
			Iterator itb, ite, itb1;
			itb = this->Begin();
			ite = this->End();
			for (; itb != ite; ++itb)
			{
				if ((*itb) == first)
				{
					itb1 = this->Begin();
					while (itb1 != ite)
					{
						if ((*itb1) == second)
						{
							T temp = itb1.iPtr->data;
							itb1.iPtr->data = itb.iPtr->data;
							itb.iPtr->data = temp;
							return true;
						}
						++itb1;
					}
				}
			}
		}
		else
			return false;
		return false;
	}


private:

	class Node
	{
	public:
		T data;
		Node* next;
		Node(Node* tnext = 0)
		{
			next = tnext;
		}
		Node(T tdata, Node* tnext = 0)
		{
			data = tdata;
			next = tnext;
		}
	};

	class SLLIterator
	{
		Node* iPtr;
	public:
		Node* GetIPtr() { return iPtr; }

		friend SLL;
		SLLIterator(Node* tIPtr = 0)
		{
			iPtr = tIPtr;
		}

		SLLIterator(SLLIterator& obj)
		{
			iPtr = obj.iPtr;
		}

		void operator = (SLLIterator& obj)
		{
			iPtr = obj.iPtr;
		}

		bool operator == (const SLLIterator& obj)const
		{
			return (iPtr == obj.iPtr);
		}

		bool operator != (SLLIterator& obj)
		{
			return (!(iPtr == obj.iPtr));
		}

		T& operator * ()
		{
			return (iPtr->data);
		}

		SLLIterator& operator ++ ()
		{
			if (iPtr->next != 0)
				iPtr = iPtr->next;
			return (*this);
		}

		SLLIterator& operator ++ (int)
		{
			SLLIterator* I = new SLLIterator;
			(*I) = (*this);
			if (iPtr->next != 0)
				iPtr = iPtr->next;
			return (*I);
		}

	};
	Node* head;
	Node* tail;
	int size = 0;



public:
	typedef SLLIterator Iterator;

	Iterator& Begin()
	{
		Iterator* I = new Iterator(head->next);
		return (*I);
	}

	Iterator& BeginFromHead()
	{
		Iterator* I = new Iterator(head);
		return (*I);
	}

	Iterator& End()
	{
		Iterator* I = new Iterator(tail);
		return (*I);
	}

	Iterator& SecondLast()
	{
		if (IsEmpty())
		{
			Iterator* I = new Iterator(head->next);
			return (*I);
		}
		else
		{
			Node* temp = head->next;
			for (; temp->next != tail; temp = temp->next);
			Iterator* I = new Iterator(temp);
			return (*I);
		}
	}

	
};



template <class T>
ostream& operator << (ostream& op, const SLL<T>& obj);


template <class T>
istream& operator >> (istream& ip, const SLL<T>& obj);

class Program
{
	string id;
	int memory;
	int noOfBlocks;
	SLL <Block>* blocks;

public:
	string GetId() { return id; }

	int GetMemory() { return memory; }

	int GetNoOfBlocks() { return noOfBlocks; }

	void SetId(string tid) { id = tid; }

	void SetMemory(int tm) { memory = tm; }

	void SetNoOfBlocks(int tno) { noOfBlocks = tno; }

	void SetBlocks(SLL<Block>* obj = 0) { blocks = obj; }

	SLL<Block>* Getblocks() { return blocks; }


	Program(string tid = "\0", int tmemory = 0, int tblocks = 0)
	{
		id = tid;
		memory = tmemory;
		blocks = 0;
		noOfBlocks = tblocks;
		if (noOfBlocks > 0)
		{
			blocks = new SLL<Block>;
		}
	}

	friend ostream& operator << (ostream& op, const Program& obj)
	{
		op << "ID : " << obj.id
			<< "\tMemory : " << obj.memory
			<< "\n";
		SLL<Block>::Iterator itb, ite;
		if (obj.noOfBlocks == 0)
			return op;
		itb = obj.blocks->Begin();
		ite = obj.blocks->End();
		for (; itb != ite; )
		{
			op << (*itb) << endl;
			itb++;
		}
		return op;
	}

	friend istream& operator >> (istream& ip, Program& obj)
	{
		cout << "\nEntre ID : ";
		cin.ignore();
		getline(cin, obj.id);
		cin.ignore();

		cout << "\nEntre Total Memory : ";
		cin >> obj.memory;
		cout << "\nEntre Number of blocks : ";
		cin >> obj.noOfBlocks;
		int i = 0;
		if (obj.noOfBlocks > i)
		{
			cout << "Entre " << i + 1 << " : ";

			obj.blocks = new SLL <Block>;
			Block tobj;
			cin >> tobj;
			obj.blocks->InsertAtTail(tobj);
			++i;
		}
		while (i < obj.noOfBlocks)
		{
			Block tobj;
			cout << "Entre " << i + 1 << " : ";
			cin >> tobj;
			obj.blocks->InsertAtTail(tobj);
			i++;
		}


		return ip;
	}

	bool CheckContinuity(Program& obj)
	{
		return false;
	}

	void DeleteAllBlocks()
	{
		SLL<Block>::Iterator itb = blocks->Begin(), ite = blocks->SecondLast();
		while (itb != ite)
		{
			SLL<Block>::Iterator itb1(itb);
			itb1++;
			delete itb.GetIPtr();
			itb = itb1;
		}
	}

	void AddBlock(int tid = 0, int tsize = 0)
	{
		if (noOfBlocks == 0)
		{
			blocks = new SLL <Block>;
			Block tb(tid, tsize);
			blocks->InsertAtTail(tb);
		}
		else
		{
			Block tb(tid, tsize);
			blocks->InsertAtTail(tb);
		}
		noOfBlocks++;
		memory += tsize;
	}

	void operator = (const Program& obj)
	{
		id = obj.id;
		memory = obj.memory;
		noOfBlocks = obj.noOfBlocks;
		blocks = obj.blocks;
	}

	bool operator == (const Program& obj)const
	{
		return (id == obj.id && memory == obj.memory && noOfBlocks == obj.noOfBlocks && blocks == obj.blocks);
	}

	bool operator != (const Program& obj)const
	{
		return (!(id == obj.id && memory == obj.memory && noOfBlocks == obj.noOfBlocks && blocks == obj.blocks));
	}

};

ostream& operator << (ostream& op, const Program& obj);

istream& operator >> (istream& ip, Program& obj);

class MemoryManagementSystem
{
	SLL <Program> listOfPrograms;
	int sizeOfMemory;
	int noOfPrograms;
	int sizeOfFreeMemory;
	SLL <Block> freeMemory;
	bool strategy; // will use first fit when true, and best fit when false
public:
	MemoryManagementSystem(int tm = 0, int tfm = 0, bool tst = true)
		: listOfPrograms(), freeMemory()
	{
		noOfPrograms = 0;
		sizeOfMemory = tm;
		sizeOfFreeMemory = tfm;
		strategy = tst;
		if (sizeOfFreeMemory == sizeOfMemory)
		{
			Block temp(0, tm);
			freeMemory.InsertAtTail(temp);
		}
	}

	void Dest()
	{
		SLL<Program>::Iterator itb, ite;
		itb = listOfPrograms.Begin();
		ite = listOfPrograms.End();
		while (itb != ite)
		{
			string tid = (*itb).GetId();
			SLL<Program>::Iterator itb1(itb);
			itb1++;
			DeleteAProgram(tid);
			itb = itb1;
			cout << tid << "\t is deleted\n";
		}
	}

	friend ostream& operator << (ostream& op, MemoryManagementSystem& obj)
	{
		op << "\n\n\n\n\n\nThe total size of memory is : ";
		op << obj.sizeOfMemory;
		op << "\nFree Memory : " << obj.sizeOfFreeMemory;
		op << "\n\n\t\t Track of taken Memory\n\n";
		op << (obj.listOfPrograms);
		cout << "\n\n\t\t Track of free Memory\n\n";
		op << obj.freeMemory;
		return op;
	}

	friend istream& operator >> (istream& ip, MemoryManagementSystem& obj)
	{
		cout << "\nEntre total memory : ";
		cin >> obj.sizeOfMemory;
		cout << "\nEntre Free Memorry : ";
		ip >> obj.sizeOfFreeMemory;
		return ip;
	}

	void AddAProgram(Program& obj)
	{
		if (obj.GetMemory() <= sizeOfFreeMemory)
		{
			listOfPrograms.InsertAtTail(obj);
			int a = obj.GetMemory();
			SLL<Block> ::Iterator itb = freeMemory.Begin(), ite = freeMemory.End();
			while (itb != ite)
			{
				int x = (*itb).GetTotalBytes();
				if (x == a)
				{
					freeMemory.Remove(*itb);
					break;
				}
				else if (x > a)
				{
					int b = x - a;
					int c = (*itb).GetStartByteId();
					(*itb).SetTotalBytes(b);
					(*itb).SetStartByteId(c + a);
				}
				itb++;
			}
		}
	}

	bool GetMemory(string tid, int tmem, bool nonContigious = false)
	{
		bool Notalloted = true;
		bool ProgramPresent = false;
		int memoryAlloted = 0;
		SLL<Program>::Iterator tIdProgram;
		bool memoryGiven = false;
		if (IsMemoryAvailable(tmem))
		{
			memoryGiven = true;
			SLL<Program>::Iterator itb, ite;
			itb = listOfPrograms.Begin();
			ite = listOfPrograms.End();
			bool f = false;
			while (itb != ite)
			{
				if ((*itb).GetId() == tid)
				{
					f = true;
					ProgramPresent = true;
					tIdProgram = itb;
					break;
				}
				itb++;
			}
			if (strategy)
			{
				SLL<Block>::Iterator itb1 = FirstFit(tmem);
				int BlockStarter = (*itb1).GetStartByteId();
				int BlockSize = (*itb1).GetTotalBytes();
				(*itb1).SetStartByteId(BlockStarter + tmem);
				(*itb1).SetTotalBytes(BlockSize - tmem);
				if (f)
					(*itb).AddBlock(BlockStarter, tmem);
				else
				{
					Program tp(tid);
					tp.AddBlock(BlockStarter, tmem);
					listOfPrograms.InsertAtTail(tp);
				}
				sizeOfFreeMemory -= tmem;
				memoryGiven = true;
				return true;
			}
			else
			{
				SLL<Block>::Iterator itb1, ite1;
				itb1 = freeMemory.BeginFromHead();
				ite1 = freeMemory.End();

				int a;
				bool firstFreeBlock = true;

				SLL<Block>::Iterator leastMemory;

				while (itb1 != ite1)
				{
					if ((itb1.GetIPtr()->next->data).GetTotalBytes() == tmem)
					{
						SLL<Block>::Iterator I(itb1.GetIPtr()->next->next);
						sizeOfFreeMemory -= tmem;
						int BlockStarter = (itb1.GetIPtr()->next->data).GetStartByteId();
						if (f)
							(*itb).AddBlock(BlockStarter, tmem);
						else
						{
							Program tp(tid);
							tp.AddBlock(BlockStarter, tmem);
							listOfPrograms.InsertAtTail(tp);
						}
						delete itb1.GetIPtr()->next;
						itb1.GetIPtr()->next = I.GetIPtr();
						Notalloted = false;
						memoryGiven = true;
						return true;
					}
					else if ((itb1.GetIPtr()->next->data).GetTotalBytes() > tmem)
					{
						if (firstFreeBlock)
						{
							a = (itb1.GetIPtr()->next->data).GetTotalBytes();
							SLL<Block>::Iterator tLeastMemory(itb1.GetIPtr()->next);
							leastMemory = tLeastMemory;
							firstFreeBlock = false;
						}
						int b = (itb1.GetIPtr()->next->data).GetTotalBytes();

						if (b < a)
						{
							SLL<Block>::Iterator tLeastMemory(itb1.GetIPtr()->next);

							cout << (*leastMemory);
							leastMemory = tLeastMemory;
							cout << (*leastMemory);
						}
						Notalloted = false;
					}
					itb1++;
				}
				int blockStartId = (*leastMemory).GetStartByteId();
				int blockMemory = (*leastMemory).GetTotalBytes();
				if (f)
					(*itb).AddBlock(blockStartId, tmem);
				else
				{
					Program tp(tid);
					tp.AddBlock(blockStartId, tmem);
					listOfPrograms.InsertAtTail(tp);
				}
				memoryGiven = true;
				((*leastMemory).SetStartByteId(blockStartId + tmem));
				((*leastMemory).SetTotalBytes(blockMemory - tmem));
				sizeOfFreeMemory -= tmem;
			}
		}
		if (sizeOfFreeMemory >= tmem && (Notalloted) && (!strategy) && (nonContigious))
		{
			memoryGiven = true;
			while (memoryAlloted < tmem)
			{
				SLL<Program>::Iterator itpb, itpe;
				itpb = listOfPrograms.Begin();
				itpe = listOfPrograms.End();
				bool f = false;
				while (itpb != itpe)
				{
					if ((*itpb).GetId() == tid)
					{
						f = true;
						ProgramPresent = true;
						tIdProgram = itpb;
						break;
					}
					itpb++;
				}
				SLL<Block>::Iterator itb, ite1, itb1;
				itb = freeMemory.BeginFromHead();
				ite1 = freeMemory.End();
				int a = (*itb).GetTotalBytes();
				itb1 = itb;
				while (itb != ite1)
				{
					if ((itb.GetIPtr()->next->data).GetTotalBytes() > a)
					{
						itb1 = itb;
						a = (itb.GetIPtr()->next->data).GetTotalBytes();
					}
					itb++;
				}
				int startByteId = (itb1.GetIPtr()->next->data).GetStartByteId();
				int totalBytes = (itb1.GetIPtr()->next->data).GetTotalBytes();
				if (tmem - memoryAlloted >= totalBytes)
				{
					if (ProgramPresent)
						(*tIdProgram).AddBlock(startByteId, totalBytes);
					else
					{
						Program P(tid);
						P.AddBlock(startByteId, totalBytes);
						listOfPrograms.InsertAtTail(P);
					}
					memoryAlloted += totalBytes;
					sizeOfFreeMemory -= totalBytes;

					SLL<Block>::Iterator I(itb1.GetIPtr()->next->next);
					delete itb1.GetIPtr()->next;
					itb1.GetIPtr()->next = I.GetIPtr();
				}
				else
				{
					if (ProgramPresent)
						(*tIdProgram).AddBlock(startByteId, tmem - memoryAlloted);
					else
					{
						Program P(tid);
						P.AddBlock(startByteId, tmem - memoryAlloted);
						listOfPrograms.InsertAtTail(P);
					}
					sizeOfFreeMemory -= tmem - memoryAlloted;

					(itb1.GetIPtr()->next->data).SetStartByteId(startByteId + (tmem - memoryAlloted));
					(itb1.GetIPtr()->next->data).SetTotalBytes(totalBytes - (tmem - memoryAlloted));
					memoryAlloted += tmem - memoryAlloted;
				}
			}
			memoryGiven = true;
		}
		return memoryGiven;
	}

	bool DeleteProgramMemoryOnly(string tid)
	{
		// Removes the program memory only

		if (!IsIdPresent(tid))
			return false;
		SLL<Program>::Iterator itb = ProgramIdFinder(tid);
		if ((*itb).GetMemory() == 0)
			return true;
		DeAllocatingMemory(itb);
		freeMemory.Sort();
		(*itb).SetMemory(0);
		(*itb).DeleteAllBlocks();
		freeMemory.Sort();
		(*itb).SetBlocks();
		(*itb).SetNoOfBlocks(0);

		freeMemory.Sort();

		return true;
	}

	bool DeleteAProgram(string tid)
	{
		// Removes the program memory and data as well

		SLL<Program>::Iterator itb, ite;
		itb = listOfPrograms.BeginFromHead();
		ite = listOfPrograms.End();
		while (itb != ite)
		{
			if ((itb.GetIPtr()->next->data).GetId() == tid)
			{
				if ((itb.GetIPtr()->next->data).GetMemory() == 0)
				{

					SLL<Program>::Iterator I1(itb.GetIPtr()->next);
					SLL<Program>::Iterator I(itb.GetIPtr()->next->next);
					itb.GetIPtr()->next = I.GetIPtr();

					freeMemory.Sort();
					return true;
				}
				SLL<Program>::Iterator I1(itb.GetIPtr()->next);
				DeAllocatingMemory(I1);
				SLL<Program>::Iterator I(itb.GetIPtr()->next->next);
				itb.GetIPtr()->next->data.DeleteAllBlocks();
				itb.GetIPtr()->next = I.GetIPtr();
				freeMemory.Sort();
				return true;
			}
			itb++;
			freeMemory.Sort();
		}
		return false;

	}

	void DeAllocatingMemory(SLL<Program>::Iterator& itb)
	{
		Program tempp = (*itb);
		SLL<Block>* tempb = (tempp.Getblocks());
		SLL<Block>::Iterator itb1, ite;
		itb1 = tempb->Begin();
		ite = tempb->End();
		int a = 0;
		while (itb1 != ite)
		{
			++a;
			int x = (*itb1).GetStartByteId();
			int y = (*itb1).GetTotalBytes();
			Block b1(x, y);
			freeMemory.InsertAtTail(b1);
			sizeOfFreeMemory += y;

			itb1++;
		}
		SLL<Block>::Iterator itb2, ite1;
		itb2 = tempb->Begin();
		ite1 = tempb->End();

	}

	bool IsIdPresent(string tid)
	{
		SLL<Program> ::Iterator itb, ite;
		itb = listOfPrograms.Begin();
		ite = listOfPrograms.End();
		while (itb != ite)
		{
			if ((*itb).GetId() == tid)
				return true;
			itb++;
		}
		return false;
	}

	SLL<Program>::Iterator& ProgramIdFinder(string tid)
	{
		SLL<Program> ::Iterator itb, ite;
		itb = listOfPrograms.Begin();
		ite = listOfPrograms.End();
		while ((*itb).GetId() != tid)
			++itb;
		SLL<Program> ::Iterator* itb1 = new SLL<Program>::Iterator(itb);

		return (*itb1);
	}

	SLL<Block>::Iterator& FirstFit(int tmem)
	{
		SLL<Block> ::Iterator itb, ite;
		itb = freeMemory.Begin();
		ite = freeMemory.End();
		while (itb != ite)
		{
			if ((*itb).GetTotalBytes() >= tmem)
				break;
			itb++;
		}
		return itb;
	}

	bool IsMemoryAvailable(int mem)
	{
		SLL<Block> ::Iterator itb, ite;
		itb = freeMemory.Begin();
		ite = freeMemory.End();
		while (itb != ite)
		{
			if ((*itb).GetTotalBytes() >= mem)
				return true;
			++itb;
		}
		return false;
	}

};

ostream& operator << (ostream& op, MemoryManagementSystem& obj);

