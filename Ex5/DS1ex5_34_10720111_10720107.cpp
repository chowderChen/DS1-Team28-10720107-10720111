#include<iostream>
#include<string>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<ctime>

using namespace std ;

class ClassList {
	
	typedef struct CT {
		string content ; // All the content from the school
		int numGraduate ; // number of graduates
	} CollegeType ;
	
	vector< CollegeType > collegeSet ; 
	string fileNum ; 
	string sortType ;
	clock_t sortTime ;
	
	public:
		
	ClassList(){
		fileNum = "" ;
		sortType = "" ;
		sortTime = 0 ;
	} // ClassList
	
	bool Load() ;
	void Export() ;
	void Print() ;
	void Merge( int first, int mid, int last ) ;
	void MergeSort( int first, int last );
	void QuickSort( int first, int last ) ;
	void Partition( int first, int last, int &pivotIndex ) ;
	void Sort() ;
	
}; // class ClassList

bool ClassList::Load( ) {
    // Load a file, turn it into a vector
    
    cout << "File number: " ;
    cin >> fileNum ;
    
    FILE *infile = NULL ;
    bool success = false ;
	string fileName = "" ;
    fileName = "input" + fileNum + ".txt" ;
    infile = fopen(fileName.c_str(), "r" ) ;

	if ( infile == NULL )
		;
	else{

        char tempChar ;
        for ( int i = 0 ; i < 3 ; i++ )
        	while ( fscanf( infile, "%c", &tempChar ) != EOF && tempChar != '\n' )
            	;

        CollegeType aCollege ;
        aCollege.content = "" ;
        aCollege.numGraduate = 0 ;
        
		int numTab = 0 ;
		string numGraduate = "" ;
		
        while ( fscanf( infile, "%c", &tempChar ) != EOF ) {
        	aCollege.content = aCollege.content + tempChar ;
        	while ( fscanf( infile, "%c", &tempChar ) != EOF && tempChar != '\n' ) {
        		aCollege.content = aCollege.content + tempChar ;
        		if ( tempChar == '\t' )
        			numTab++ ;
        		else if ( numTab == 8 )
        			numGraduate = numGraduate + tempChar ;
        		
        	} //while
        		
        	aCollege.numGraduate = atoi( numGraduate.c_str() ) ;
        	
            collegeSet.push_back( aCollege ) ;
            
            aCollege.content = "" ;
            aCollege.numGraduate = 0 ;
            numGraduate = "" ;
            numTab = 0 ;
            
        } // while

        success = true ;
        fclose( infile ) ;

	} // else

	return success ;

} // Load
/*
void ClassList::Export() {
    // Export sorted list to .txt

    FILE *outFile = NULL ;
    bool success = false ;
    fileName = sortType + "_sort" + fileNum + ".txt" ; 
    outFile = fopen( fileName.c_str(), "w" ) ;
    if ( outFile == NULL )
        ;
    else {

        fprintf( outFile, "OID\tArrival\tDuration\tTimeOut\n" ) ;
        for ( int i = 0 ; i < aList.size() ; i++ ) {
            fprintf( outFile, "%d\t%d\t%d\t%d\n", aList.at( i ).ID, aList.at( i ).arrival
                    , aList.at( i ).duration, aList.at( i ).timeout ) ;
        } // for

        success = true ;
        fclose( outFile ) ;

    } // else

} // Export
*/
void ClassList::Print() {
	
	for ( int i = 0 ; i < collegeSet.size() ; i++ )
		cout << collegeSet[i].content << "\n" ;
		
} // Print

void ClassList::Merge( int first, int mid, int last ) {
	
	vector< CollegeType > tempList ;
	
	int first1 = first, last1 = mid 
		, first2 = mid + 1, last2 = last
		, index = first ;
		
	for ( ; ( first1 <= last1 ) && ( first2 <= last2 ) ; ++index ) {
		// compare the smallest one of eacg list
		// take the smaller one 
		if ( collegeSet[first1].numGraduate >=  collegeSet[first2].numGraduate ) {
			
			tempList.push_back( collegeSet[first1] ) ;
			++first1 ;
			
		} // if
		else {
			
			tempList.push_back( collegeSet[first2] )  ;
			++first2 ;
			
		} // else
		
	} // for
	
	// attach  
	for ( ; first1 <= last1 ; ++first1, ++index )
		tempList.push_back( collegeSet[first1] ) ;
		
	for ( ; first2 <= last2 ; ++first2, ++index )
		tempList.push_back( collegeSet[first2] ) ;
		
	// replace the original one with new one
	
	for ( index = first ; index <= last ; ++index ) { 
		collegeSet[index] = tempList[index - first] ;
	} // for 
	 
	
} // Merge

void ClassList::MergeSort( int first, int last ) {
	
	// if only one left in list, do nothing
	// else 
	// devide into two list, sort each one
	// compare from the first index of each, take out the smaller one, compare again
	// if the same, take out the front list one 

	if ( first < last ) {
		
		int mid = ( first + last ) / 2 ;
		MergeSort( first, mid ) ;
		MergeSort( mid + 1, last ) ;
		Merge( first, mid, last ) ;
	} // if
	
} // 

void ClassList::Partition( int first, int last, int &pivotIndex ) {
	
	int lastS1 = first, firstUnknown = first + 1 ;
	CollegeType tempCollege ;
	while ( firstUnknown <= last ) {
		if ( collegeSet.at( firstUnknown ).numGraduate > collegeSet.at( pivotIndex ).numGraduate ) {
			++lastS1 ;
			tempCollege = collegeSet.at( firstUnknown ) ;
			collegeSet.at( firstUnknown ) = collegeSet.at( lastS1 ) ;
			collegeSet.at( lastS1 ) = tempCollege ;
		} // if
		
		firstUnknown++ ;
	} // while
	
	tempCollege = collegeSet.at( lastS1 ) ;
	collegeSet.at( lastS1 ) = collegeSet.at( pivotIndex ) ;
	collegeSet.at( pivotIndex ) = tempCollege ;
	
	pivotIndex = lastS1 ;
	
} // Partition

void ClassList::QuickSort( int first, int last ){
	
	if ( first < last ) {
		int pivotIndex = first ;
		Partition( first, last, pivotIndex ) ;
		QuickSort( first, pivotIndex - 1 ) ;
		QuickSort( pivotIndex + 1, last ) ;
		
	} // if
	
} // Qsort

void ClassList::Sort() {
	
	sortTime = clock() ;
	MergeSort( 0, collegeSet.size() - 1 ) ;
	sortTime = clock() - sortTime ;
	cout << "Merge sort: " << sortTime << "ms\n" ;
	
	Print() ;
	
} // Sort

int main() {

	int cmd = -1 ;
	ClassList classList ;
	classList.Load() ;
	classList.Sort() ;
	return 0 ;

} // main
