#ifndef LINEAR_HASHING_H
#define LINEAR_HASHING_H
//
// #include <vector>
// #include <algorithm>
// #include <functional>
// #include <string>
#include "nextPrime.cpp"
//CHANGING TO PRACTICE COMMIT

using namespace std;

// extern int currentProbes_Linear;
// //
// extern vector<int>NumSearches1;
// extern int NumSearches1[5];


// int SearchCount_TRUE1;  //0->0.1
// int SearchCount_TRUE2;  //0.1->0.2
// int SearchCount_TRUE3;  //0.2->0.3
// int SearchCount_TRUE4;  //0.3->0.4
// int SearchCount_TRUE5;  //0.4->0.5
// extern vector<int>NumSearches2;
//
// extern vector<int>NumProbes1;
// extern vector<int>NumProbes2;




int nextPrime( int n );

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable_Linear
{
public:
    explicit HashTable_Linear( int size = 101 ) : array( nextPrime( size ) )
    { makeEmpty( ); }

    bool contains( const HashedObj & x)
    {

      bool temp = isActive( findPos( x) );

      int L_factor = currentSize/array.size();
      /*---------------------------------------------*/
      /*                                             */
      /*              SUCCESSFUL                     */
      /*                                             */
      /*---------------------------------------------*/
      if(temp == true){
        if(L_factor > 0 && L_factor < 0.10)
        {
          SearchCount_TRUE1 += 1;
          NumSearches1[0] = SearchCount_TRUE1;
        }
        if(L_factor >  0.10 && L_factor < 0.20)
        {
          SearchCount_TRUE2 += 1;
          NumSearches1[1] = SearchCount_TRUE2;

        }

        if(L_factor >  0.20 && L_factor < 0.30)
        {
          SearchCount_TRUE3 += 1;
          NumSearches1[2] = SearchCount_TRUE3;
        }

        if(L_factor >  0.30 && L_factor < 0.40)
        {
          SearchCount_TRUE1 += 1;
          NumSearches1[3] = SearchCount_TRUE4;
        }
        if(L_factor >  0.40 && L_factor < 0.50)
        {
          SearchCount_TRUE5 += 1;
          NumSearches1[4] = SearchCount_TRUE5;
        }
    }
    /*---------------------------------------------*/
    /*                                             */
    /*              NOT SUCCESSFUL                 */
    /*                                             */
    /*---------------------------------------------*/
      else if(temp == false){
        if(L_factor > 0 && L_factor < 0.10)
        {
          SearchCount_FALSE1 += 1;
          NumSearches2[0] = SearchCount_FALSE1;
        }
        if(L_factor >  0.10 && L_factor < 0.20)
        {
          SearchCount_FALSE2 += 1;
          NumSearches2[1] = SearchCount_FALSE2;

        }

        if(L_factor >  0.20 && L_factor < 0.30)
        {
          SearchCount_FALSE3 += 1;
          NumSearches2[2] = SearchCount_FALSE3;
        }

        if(L_factor >  0.30 && L_factor < 0.40)
        {
          SearchCount_FALSE4 += 4;
          NumSearches2[3] = SearchCount_FALSE4;
        }
        if(L_factor >  0.40 && L_factor < 0.50)
        {
          SearchCount_FALSE5 += 1;
          NumSearches2[4] = SearchCount_FALSE5;
        }
    }
     return isActive( findPos( x ) );

    }

    void makeEmpty( )
    {
        currentSize = 0;
        for( auto & entry : array )
            entry.info = EMPTY;
    }

    bool insert( const HashedObj & x )
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ].element = x;
        array[ currentPos ].info = ACTIVE;

        // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    bool insert( HashedObj && x )
    {
        // Insert x as active
        int currentPos = findPos( x );
        if( isActive( currentPos ) )
            return false;

        if( array[ currentPos ].info != DELETED )
            ++currentSize;

        array[ currentPos ] = std::move( x );
        array[ currentPos ].info = ACTIVE;

        // Rehash; see Section 5.5
        if( currentSize > array.size( ) / 2 )
            rehash( );

        return true;
    }

    bool remove( const HashedObj & x )
    {
        int currentPos = findPos( x );
        if( !isActive( currentPos ) )
            return false;

        array[ currentPos ].info = DELETED;
        return true;
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };



    int getSize(){

      return currentSize;
    }

    vector<int> getNumSearches1() {

      return NumSearches1;

    }
    //
    //
    // vector<int> getSearchCount_2(){
    //   return NumSearches2;
    // }
    //
    // int returnLoadFactor() {
    //   return (currentSize / array.size());
    //
    // }

    int returnArraySize() {

      return array.size();

    }



private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;


        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
        : element{ e }, info{ i } { }

        HashEntry( HashedObj && e, EntryType i = EMPTY )
        : element{ std::move( e ) }, info{ i } { }
    };

    vector<HashEntry> array;
    int currentSize;

    // counters for each load factor for TRUE SEARCHES
    int SearchCount_TRUE1;  //0->0.1
    int SearchCount_TRUE2;  //0.1->0.2
    int SearchCount_TRUE3;  //0.2->0.3
    int SearchCount_TRUE4;  //0.3->0.4
    int SearchCount_TRUE5;  //0.4->0.5

    // // counters for each load factor for FALSE SEARCHES
    int SearchCount_FALSE1; //0->0.1
    int SearchCount_FALSE2; //0.1->0.2
    int SearchCount_FALSE3; //0.2->0.3
    int SearchCount_FALSE4; //0.3->0.4
    int SearchCount_FALSE5; //0.4->0.5

    // //for SUCCESSFUL SEARCHES
    vector<int>NumSearches1;

    //for UNSUCCESSFUL SEARCHES
    vector<int>NumSearches2;



    //for SUCCESSFUL PROBES
    vector<int>NumProbes1;

    //for UNSUCCESSFUL Probes
    vector<int>NumProbes2;



    bool isActive( int currentPos ) const
    { return array[ currentPos ].info == ACTIVE; }

    int findPos( const HashedObj & x ) const
    {
        int offset = 1;
        int currentPos = myhash( x );

        while( array[ currentPos ].info != EMPTY &&
              array[ currentPos ].element != x )
        {
            currentPos += offset;  // Compute ith probe

            //offset += 2; REMOVED REMOVED REMOVED

            if( currentPos >= array.size( ) )
                currentPos -= array.size( );
        }

        return currentPos;
    }

    void rehash( )
    {
        vector<HashEntry> oldArray = array;

        // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( auto & entry : array )
            entry.info = EMPTY;

        // Copy table over
        currentSize = 0;
        for( auto & entry : oldArray )
            if( entry.info == ACTIVE )
                insert( std::move( entry.element ) );
    }

    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }
};

#endif
