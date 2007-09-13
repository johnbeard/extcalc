
//////////////////////////////////////////////////////////////////
//																//
//					DOPPELT VERKETTETE LISTE					//
//																//
//////////////////////////////////////////////////////////////////



#ifndef LISTH
#define LISTH
template<class T>
struct ListItem
{
	ListItem * nextItem;
	ListItem * lastItem;

	T inhalt;

};



template<class T>
class List
{
private:
	int actualPosition;
	ListItem<T> * actualItem;
	ListItem<T> * firstItem;

	int NumItems;




public:

	List(int num, T * ListInhalt)
	{

//		if(num == 0) { NumItems = 0; break;}


		firstItem = new ListItem<T>;


		firstItem->inhalt = ListInhalt[0];
		NumItems = num;
		actualItem = firstItem;
		actualPosition = 0;

		ListItem<T> * pLI;

		for(int c=1; c<num; c++)
		{
			pLI = actualItem;
			actualItem->nextItem = new ListItem<T>;
			actualItem = actualItem->nextItem;

			actualItem->lastItem = pLI;

			actualItem->inhalt = ListInhalt[c];

			actualPosition = c;
		}

	}


	List() { NumItems =0; actualPosition = 0;}

	~List()
	{
		actualItem = firstItem;
		actualPosition = 0;
		ListItem<T> * KillItem;

		for(int c=0; c<NumItems; c++)
		{
			KillItem = actualItem;

			actualItem = actualItem->nextItem;
			delete KillItem;
		}
	}






	bool NewItems(int num,T *Items);
	bool NewItems(int num);
	bool NewItem(T Item);

	T & operator [] (int index);

	bool DeleteItem(int num);




	int GetLen() {return NumItems;}

};



typedef List<int> iList;







template <class T>
bool List<T>::DeleteItem(int num)
	{
		if(num >= NumItems || num<0) return false;

		if(NumItems == 1) {
			delete firstItem;
			actualPosition = 0;
			NumItems = 0;
			return true;
		}

		if(num >= actualPosition)
		{
			for(int c = actualPosition; c<num; c++)
				{
				actualItem = actualItem->nextItem;
				actualPosition++;
			}

		}
		else
			{
			for(int c=actualPosition; c>num; c--)
			{
				actualItem = actualItem->lastItem;
				actualPosition--;
			}	

		}

		ListItem<T> * ptLast = actualItem->lastItem;
		ListItem<T> * ptNext = actualItem->nextItem;



		if(num >0)
		{
			actualItem = actualItem->lastItem;
			delete actualItem->nextItem;

			if(num != (NumItems-1))
			{	
				actualItem->nextItem = ptNext;
				actualItem=actualItem->nextItem;
				actualItem->lastItem = ptLast;
			}
			else actualPosition--;

		}
		else
		{
			actualItem = actualItem->nextItem;	
			delete actualItem->lastItem;
	
			actualPosition = 0;

			firstItem = actualItem;

		}
		NumItems--;		

		return true;
	}





template <class T>
T & List<T>::operator [] (int index)
	{
		

		if(index >= NumItems)
			return *((T*)NULL);
		if(index < 0)
			return *((T*)NULL);
		


		if(index >= actualPosition)
		{
			for(int c=actualPosition; c<index && c<NumItems; c++)
			{
				actualItem = actualItem->nextItem;
				actualPosition++;
			}
			return actualItem->inhalt;
		}
		else
		{
			for(int c=actualPosition; c>index && c>0; c--)
			{
				actualItem = actualItem->lastItem;
				actualPosition--;
			}
			return actualItem->inhalt;
		}
		
}



template <class T>
bool List<T>::NewItems(int num,T* Items)
{

	if(num <=0 ) return false;
	if(NumItems <= 0) {

		firstItem = new ListItem<T>;
		firstItem->nextItem = actualItem;
	
		firstItem->inhalt = Items[0];
		NumItems = 0;
		actualItem = firstItem;

		actualPosition = -1;
	}




	for(int c=actualPosition; c<NumItems-1; c++)
	{
		actualItem = actualItem->nextItem;
		actualPosition++;
	}



	ListItem<T> * ptLast;

	for(int c=actualPosition; c<NumItems+num-1; c++)
	{

		ptLast = actualItem;
		actualItem->nextItem = new ListItem<T>;
		actualItem = actualItem->nextItem;
		actualPosition++;
		actualItem->lastItem = ptLast;


		actualItem->inhalt = Items[c-NumItems+1];


	}
	NumItems +=num;

	return true;
}




template <class T>
bool List<T>::NewItems(int num)
{

	if(num <=0 ) return false;
	if(NumItems <= 0) {

		firstItem = new ListItem<T>;
		firstItem->nextItem = actualItem;	

//		firstItem->inhalt = Items[0];
		NumItems = 0;
		actualItem = firstItem;

		actualPosition = -1;
	}




	for(int c=actualPosition; c<NumItems-1; c++)
	{
		actualItem = actualItem->nextItem;
		actualPosition++;
	}



	ListItem<T> * ptLast;

	for(int c=actualPosition; c<NumItems+num-1; c++)
	{

		ptLast = actualItem;
		actualItem->nextItem = new ListItem<T>;
		actualItem = actualItem->nextItem;
		actualPosition++;
		actualItem->lastItem = ptLast;





	}
	NumItems +=num;

	return true;
}

template <class T>
bool List<T>::NewItem(T Item)
{


	if(NumItems <= 0) {

		firstItem = new ListItem<T>;
		firstItem->nextItem = actualItem;

		firstItem->inhalt = Item;
		NumItems = 0;
		actualItem = firstItem;

		actualPosition = -1;
	}

	for(int c=actualPosition; c<NumItems-1; c++)
	{
		actualItem = actualItem->nextItem;
		actualPosition++;
	}
	
	ListItem<T> * ptLast;




	ptLast = actualItem;
	actualItem->nextItem = new ListItem<T>;
	actualItem = actualItem->nextItem;
	actualPosition++;
	actualItem->lastItem = ptLast;

	actualItem->inhalt = Item;
		


	NumItems ++;

	return true;
} 
#endif
