// 10720107 陳丕中 10720111 陳少暉 

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
	
	bool Load( string fileName ) ;
	void Export() ;
	void Print() ;
	void Merge( int first, int mid, int last ) ;
	void MergeSort( int first, int last );
	void QuickSort( int first, int last ) ;
	void Partition( int first, int last, int &pivotIndex ) ;
	void DoMSort() ;
	void DoQSort() ;
	void DoBSort() ;
	void DoSSort() ;
	bool IsSorted() ;
	void swap( CT item1, CT item2 ) ;
	
}; // class ClassList

bool ClassList::Load( string fileName ) {
    // Load a file, turn it into a vector
    
    fileNum = fileName ;
    FILE *infile = NULL ;
    bool success = false ;
    fileName = "input" + fileName + ".txt" ;
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

void ClassList::Export() {
    // Export sorted list to .txt

    FILE *outFile = NULL ;
    string fileName ;
    fileName = sortType + "_sort" + fileNum + ".txt" ; 
    outFile = fopen( fileName.c_str(), "w" ) ;
    if ( outFile == NULL )
        ;
    else {

        for ( int i = 0 ; i < collegeSet.size() ; i++ ) {
            fprintf( outFile, "%s\n", collegeSet.at( i ).content.c_str() ) ;
        } // for

        fclose( outFile ) ;

    } // else

} // Export

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

void ClassList::DoMSort() {
	
	sortType = "merge" ;
	sortTime = clock() ;
	MergeSort( 0, collegeSet.size() - 1 ) ;
	sortTime = clock() - sortTime ;
	cout << "Merge sort: " << sortTime << "ms\n" ;
	Export() ;
	
} // Sort

void ClassList::DoQSort() {
	
	sortType = "quick" ;
	sortTime = clock() ;
	QuickSort( 0, collegeSet.size() - 1 ) ;
	sortTime = clock() - sortTime ;
	cout << "Quick sort: " << sortTime << "ms\n" ;
	Export() ;
	
} // DoQ

//void ClassList::swap( CT item1, CT item2 ) {
//	CT temp ;
//	temp = item1 ;
//	item1 = item2 ;
//	item2 = temp ;
//} // swap


bool ClassList::IsSorted() {
	for( int i = 0 ; i < collegeSet.size() - 1 ; i++ ) {
		if ( collegeSet.at(i).numGraduate > collegeSet.at(i+1).numGraduate ) {
			return false ;
		} // if
	} // for
	
	return true ;
} // isSorted()




void ClassList::DoBSort() { // 泡沫排序
    sortType = "bubble" ;
	if ( IsSorted() ) {
		sortTime = 0 ;
	} // if
	else {
		sortTime = clock() ;
   		for ( int i = collegeSet.size() - 1 ; i > 0 ; i -- ) {
  	    	for ( int j = 0 ; j < i ; j ++ ) {
    			if ( collegeSet.at(j+1).numGraduate > collegeSet.at(j).numGraduate ) {
    				//swap( collegeSet.at(j), collegeSet.at(j+1) ) ;
    				CT tempItem ;
    				tempItem = collegeSet.at(j) ;
    				collegeSet.at(j) = collegeSet.at(j+1) ;
    				collegeSet.at(j+1) = tempItem ;
				} // if
        	} // for
    	} // for
    	
    	sortTime = clock() - sortTime ;
    } // else
	
	cout << "Bubble sort: " << sortTime << "ms\n" ;
	Export() ;
} // DoB

void ClassList::DoSSort() { // 選擇排序 
    sortType = "selection" ;
	sortTime = clock() ;
	if ( IsSorted() ) {
		sortTime = 0 ;
	} // if
	else {
		for ( int i = 0 ; i < collegeSet.size() ; i++ ) {
			int j = i ;
			int smallAt = j ;
			int smallNum = collegeSet.at(j).numGraduate ;
			j++ ;
			while ( j < collegeSet.size() ) {
				if ( smallAt > collegeSet.at(j).numGraduate ) {
					smallAt = j ;
					smallNum = collegeSet.at(j).numGraduate ;
				} // if
				
				j++ ;
			} // while
			
			if ( smallNum < collegeSet.at(i).numGraduate ) {
				// swap( collegeSet.at(i), collegeSet.at(j) ) ;
				CT temp = collegeSet.at(smallAt) ;
            	collegeSet.at(smallAt) = collegeSet.at(i) ;
            	collegeSet.at(i) = temp ; 
            } // if
		} // for
		
		sortTime = clock() - sortTime ;

	} // else
	
	cout << "Selection sort: " << sortTime << "ms\n" ;
	Export() ;
	
} // DoS

int main() {

	int cmd = -1 ;
	cout << "(0)Exit\n(1)Selection & Bubble sort\n(2)Merge & Quick sort\nCommand: " ;
	cin >> cmd ;
	while ( cmd != 0 ) {
		
		if ( cmd == 1 ) {
			cout << "File Number" ;
			string fileNum ;
			cin >> fileNum ;
			ClassList classListB ; // BubbleSort
			ClassList classListS ; // SelectionSort
			if ( classListS.Load( fileNum ) ) {
				classListB.Load( fileNum ) ;
				classListS.DoBSort() ;
				classListB.DoSSort() ;
				
			} // if
			else {
				cout << "File not found.\n" ;
			} // else
		} //if
		else if ( cmd == 2 ) {
			cout << "File number: " ;
			string fileNum ;
			cin >> fileNum ;
			ClassList classListM ;
			ClassList classListQ ;
			if ( classListM.Load( fileNum ) ) {
				
				classListQ.Load( fileNum ) ;
				classListM.DoMSort() ;
				classListQ.DoQSort() ;
				
			} // if
			else
				cout << "File not found.\n" ;
			
		} // else if
		else
			cout << "Command not found.\n" ;
			
		cout << "(0)Exit\n(1)Selection & Bubble sort\n(2)Merge & Quick sort\nCommand: " ;
		cin >> cmd ;
			
	} // while cmd != 0
	
	return 0 ;

} // main
