// 10720111 陳少暉 10720107 陳丕中

#include<iostream> 
#include<cstdio>
#include<vector>
#include<string>

using namespace std ;

class ClassList {
	
	typedef struct CT {
		string content ; // All the content from the school
		int numGraduate ; // number of graduates
	} CollegeType ;
	
	vector< CollegeType > collegeSet ; 
	
	public:
		
	ClassList(){
		fileNum = "" ;
		sortType = "" ;
		sortTime = 0 ;
	} // ClassList
	
	bool Load( string fileName ) ;
};

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

struct TreeType {
	
};

struct TreeNode {
	TreeType item ;
	TreeNode *left ;
	TreeNode *right ;
};

class Tree {
	
	
};

int main() {
	
	ClassList classList ;
	classList.Load() ;
	
	return 0 ;
	
} // main
