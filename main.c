/*
 * sorted-list.c
 */

#include	<string.h>
#include	<stdio.h>
#include	"sorted-list.h"

int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

//Destructor functions
void destroyBasicTypeAlloc(void *p){
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for allocated memory (malloc,calloc,etc.)
	free(p);
}

void destroyBasicTypeNoAlloc(void *p) {
	//For pointers to basic data types (int*,char*,double*,...)
	//Use for memory that has not been allocated (e.g., "int x = 5;SLInsert(mylist,&x);SLRemove(mylist,&x);")
	return;
}


int main()
{
	SortedListPtr intList = SLCreate(compareInts, destroyBasicTypeNoAlloc);
	SortedListPtr strList = SLCreate(compareStrings, destroyBasicTypeNoAlloc);
    SortedListPtr dblList = SLCreate(compareDoubles, destroyBasicTypeNoAlloc);

	int a = 3;
    int b = 7;
    int c = 12;
    int d = 1;
    int e = 8;
    int f = 18;
    int q = 25;
    int z = 10;

    char * str1 = "apple";
    char * str2 = "bob";
    char * str3 = "cake";
    char * str4 = "fast";
    char * str5 = "zebra";
    char * str6 = "moses";

    ///////////////* TEST CASE 1 *///////////////

    printf("TESTCASE 1 \n \n \n");

    SLInsert(intList, &a);
    SLInsert(intList, &b);
    SLInsert(intList, &c);
    SLInsert(intList, &d);
    SLInsert(intList, &e);

    SortedListIteratorPtr iter = SLCreateIterator(intList);

    printf(" %d \n", *(int*)SLGetItem(iter));              /* to retieve first/head node, use getItem rather than NextItem */
    printf(" %d \n", *(int*)SLNextItem(iter));
    printf(" %d \n", *(int*)SLNextItem(iter));
    printf(" %d \n", *(int*)SLNextItem(iter));
    printf(" %d \n \n \n", *(int*)SLNextItem(iter));

    ///////////////* TEST CASE 1 *///////////////

    printf("TESTCASE 1.5 \n \n \n");

    SLInsert(intList, &a);                            // duplicate data insertion test

    printf("\n \n");




    ///////////////* TEST CASE 2 *///////////////

    iter->curr = intList->head;                                   /* reset iter to head */

    printf("TESTCASE 2 \n \n");

    SortedListIteratorPtr iter2 = SLCreateIterator(intList);

    printf(" %d \n", *(int*)SLGetItem(iter));              /* to retieve first/head node, use getItem rather than NextItem */
    printf(" %d \n", *(int*)SLNextItem(iter));
    printf(" %d \n", *(int*)SLNextItem(iter));

    SLRemove(intList, &b);                               /* delete 7, while iterator is pointing to it */

    printf(" %d \n", *(int*)SLNextItem(iter));         /* should be able to advance */
    printf(" %d \n \n \n", *(int*)SLNextItem(iter));

   /************************************************/

    printf(" %d \n", *(int*)SLGetItem(iter2));              // use second iterator, should be missing node "7"
    printf(" %d \n", *(int*)SLNextItem(iter2));
    printf(" %d \n", *(int*)SLNextItem(iter2));
    printf(" %d \n", *(int*)SLNextItem(iter2));





    ///////////////* TEST CASE 3 *///////////////

    iter->curr = intList->head;                                   /* reset iter to head */

    printf("TESTCASE 3 \n \n");


    printf(" %d \n", *(int*)SLGetItem(iter));               //iterate to 8
    printf(" %d \n", *(int*)SLNextItem(iter));

    SLDestroy(intList);                               // destroy entire list while iterator is working on it. no need for reference counts, everything is being freed from memory.

  

    iter->curr = intList->head; 
    printf("%d \n \n \n", SLGetItem(iter));   // shouldn't cause program to blow up
   
    SLDestroyIterator(iter);
    

    ///////////////* TEST CASE 4 *///////////////

    printf("TESTCASE 4 \n \n");


    SLInsert(strList, str1);
    SLInsert(strList, str2);
    SLInsert(strList, str3);
    SLInsert(strList, str4);
    SLInsert(strList, str5);
    SLInsert(strList, str6);

    SortedListIteratorPtr striter = SLCreateIterator(strList);

    printf(" %s \n", SLGetItem(striter));              
    printf(" %s \n", SLNextItem(striter));
    printf(" %s \n", SLNextItem(striter));
    printf(" %s \n", SLNextItem(striter));
    printf(" %s \n", SLNextItem(striter));
    printf(" %s \n \n \n", SLNextItem(striter));

    SLDestroyIterator(striter);


    ///////////////* TEST CASE 5 *///////////////

    printf("TESTCASE 5 \n \n");

    char* str7 = "killjoy";
    char* str8 = "giant";

    SortedListIteratorPtr striter2 = SLCreateIterator(strList);
    

    printf(" %s \n", SLGetItem(striter2));
    SLInsert(strList, str8);                        // insert giant          
    printf(" %s \n", SLNextItem(striter2));
    printf(" %s \n", SLNextItem(striter2));
    printf(" %s \n", SLNextItem(striter2));
    printf(" %s \n", SLNextItem(striter2));

    SLInsert(strList, str7);                       // insert killjoy

    printf(" %s \n \n", SLNextItem(striter2));

    SortedListIteratorPtr striter3 = SLCreateIterator(strList);

    SLDestroyIterator(striter2);

    printf("Next iterator \n \n");

    printf(" %s \n", SLGetItem(striter3));
    printf(" %s \n", SLNextItem(striter3));
    printf(" %s \n", SLNextItem(striter3));

    SLRemove(strList, str2);                     // remove bob and apple
    SLRemove(strList, str1);

    printf(" %s \n", SLNextItem(striter3));
    printf(" %s \n", SLNextItem(striter3));  
    printf(" %s \n", SLNextItem(striter3)); 
    SLNextItem(striter3);                            // try to iterate to deleted node



    SLDestroyIterator(striter3);

    printf("\n \n");


    ///////////////* TEST CASE 6 *///////////////

    printf("TESTCASE 6 \n \n");

    double aa = 5.1;
    double bb = 5.2;
    double cc = 5.3;
    double dd = 5.4;
    double ee = 5.5;

    SLInsert(dblList, &aa);
    SLInsert(dblList, &bb);
    SLInsert(dblList, &cc);
    SLInsert(dblList, &dd);
    SLInsert(dblList, &ee);


    SortedListIteratorPtr dbliter = SLCreateIterator(dblList);

    printf(" %f \n", *(double*)SLGetItem(dbliter));
    printf(" %f \n", *(double*)SLNextItem(dbliter));
    printf(" %f \n", *(double*)SLNextItem(dbliter));
    printf(" %f \n", *(double*)SLNextItem(dbliter));
    printf(" %f \n \n \n \n", *(double*)SLNextItem(dbliter));


    SLDestroyIterator(dbliter);
    SLDestroyIterator(iter2);

    SLDestroy(strList);
    SLDestroy(dblList);



    return 0;

}
