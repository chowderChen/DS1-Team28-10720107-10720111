// 10720111 陳少暉 10720107 陳丕中

#include<iostream> 
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<string>

using namespace std ;

typedef struct CT {
	string nameSchool ; // All the content from the school
	string nameMajor ;
	string division ;
	string level ;
	int numStudent ;
	int numTeacher ;
	int numGraduate ; // number of graduates
} CollegeType ;

class ClassList {
	
	vector< CollegeType > collegeSet ; 
	
	public:
		
	ClassList(){
		
	} // ClassList
	
	bool Load( string fileName ) ;
	void Print() ;
};

void ClassList::Print() {
	
	for ( int i = 0 ; i < collegeSet.size() ; i++ ) {
			cout << collegeSet[i].nameSchool << "\t" << collegeSet[i].nameMajor << "\t"
				 << collegeSet[i].division << "\t" << collegeSet[i].level << "\t" 
				 << collegeSet[i].numStudent << "\t" << collegeSet[i].numTeacher << "\t"
				 << collegeSet[i].numGraduate << "\n";
	} // for
		
} // Print

bool ClassList::Load( string fileName ) {
    // Load a file, turn it into a vector
    
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
        aCollege.nameSchool = "" ;
        aCollege.nameMajor = "" ;
        aCollege.division = "" ;
        aCollege.level = "" ;
        aCollege.numStudent = 0 ;
        aCollege.numTeacher = 0 ;
        aCollege.numGraduate = 0 ;
        
		int numTab = 0 ;
		string stringStudent = "" ;
		string stringTeacher = "" ;
		string stringGraduate = "" ;
		
        while ( fscanf( infile, "%c", &tempChar ) != EOF ) {
        	while ( fscanf( infile, "%c", &tempChar ) != EOF && tempChar != '\n' ) {
        		if ( tempChar == '\t' )
        			numTab++ ;
        		else if ( numTab == 1 )
        			aCollege.nameSchool = aCollege.nameSchool + tempChar ;
        		else if ( numTab == 3 )
        			aCollege.nameMajor = aCollege.nameMajor + tempChar ;
        		else if ( numTab == 4 )
        			aCollege.division = aCollege.division + tempChar ;
        		else if ( numTab == 5 )
        			aCollege.level = aCollege.level + tempChar ;
        		else if ( numTab == 6 )
        			stringStudent = stringStudent + tempChar ;
        		else if ( numTab == 7 )
        			stringTeacher = stringTeacher + tempChar ;
        		else if ( numTab == 8 )
        			stringGraduate = stringGraduate + tempChar ;
        		
        	} //while
        		
        	aCollege.numStudent = atoi( stringStudent.c_str() ) ;
        	aCollege.numTeacher = atoi( stringTeacher.c_str() ) ;
        	aCollege.numGraduate = atoi( stringGraduate.c_str() ) ;
        	
            collegeSet.push_back( aCollege ) ;
            
            aCollege.nameSchool = "" ;
	        aCollege.nameMajor = "" ;
	        aCollege.division = "" ;
	        aCollege.level = "" ;
	        aCollege.numStudent = 0 ;
	        aCollege.numTeacher = 0 ;
	        aCollege.numGraduate = 0 ;
	        
            stringStudent = "" ;
            stringTeacher = "" ;
            stringGraduate = "" ;
            numTab = 0 ;
            
        } // while not EOF

        success = true ;
        fclose( infile ) ;

	} // else

	return success ;

} // Load

struct TreeNode {
	CollegeType content ;
	TreeNode *left ;
	TreeNode *right ;
};

class Tree {
	
	
};

int main() {
	
	ClassList classList ;
	classList.Load( "601" ) ;
	classList.Print() ;
	
	return 0 ;
	
} // main
