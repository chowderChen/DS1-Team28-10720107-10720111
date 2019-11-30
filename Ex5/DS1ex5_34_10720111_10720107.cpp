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
	void Merge() ;
	void MergeSort();
	void QuickSort() ;
	
}; //

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
		cout << "[" << i + 1 << "] " 
			<< collegeSet[i].content << "\n" ;
		
} // Print

void ClassList::Merge() {
	
} // Merge

void ClassList::MergeSort() {
	
	// if only one left in list
	
	// else 
	// devide into two list, call itself
	// compare from the first, take out the small one, compare again
	// if the same, take out the front one of original list 
	
} // 

void ClassList::QuickSort(){
	
	
	
} // 

int main() {

	ClassList classList ;
	classList.Load() ;
	classList.Print() ;
	return 0 ;

} // main
