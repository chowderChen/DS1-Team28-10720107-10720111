// 10720111 陳少暉 10720107 陳丕中 

#include<iostream> 
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<string>
#include<cstring>


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
	~ClassList() {
		ClearList() ;
	}
	
	bool Load( string fileName ) ;
	void Print() ;
	vector< CollegeType > GetSet() ;
	void ClearList() ;
	void Remove( CollegeType aCollege ) ;
};

void ClassList::Remove( CollegeType aCollege ) {
	
	for ( int i = 0 ; i < collegeSet.size() ; i++ ) {
		if ( collegeSet.at( i ).nameSchool == aCollege.nameSchool && collegeSet.at( i ).nameMajor == aCollege.nameMajor 
			 && collegeSet.at( i ).division == aCollege.division && collegeSet.at( i ).level == aCollege.level )
			 collegeSet.erase( collegeSet.begin() + i ) ;
	} // for
	
} // remove list

void ClassList::ClearList() {
	collegeSet.clear() ;
}

vector< CollegeType > ClassList::GetSet() {
	return collegeSet ;	
} 

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
	
	TreeNode *head ;
	
	
	public:
		
	Tree() {
		head = NULL ;	
	}
	~Tree(){
		Clear( head ) ;
	} // ~tree
	
	TreeNode*& GetHead() {
		return head ;
	} // 
	
	bool IsEmpty() {
		if ( head == NULL )
			return true ;
			
		return false ;
		
	} // empty
	
	void CreateByName( vector< CollegeType > collegeSet ) {
		for ( int i = 0 ; i < collegeSet.size() ; i++ )	{
			InsertByName( head, collegeSet.at(i) ) ;
		} // for
		
		cout << "School Name: " << Height( head ) << "\n" ;
	} // 
	
	void CreateByGraduate( vector< CollegeType > collegeSet ) {
		
		for ( int i = 0 ; i < collegeSet.size() ; i++ )	{
			InsertByGraduate( head, collegeSet.at(i) ) ;
		} // for
		
		cout << "Number of graduates: " << Height( head ) << "\n" ;
		
	} // create by graduate
	
	void ClearTree() {
		Clear( head ) ;
		head = NULL ;
	} // clear
	
	void Clear( TreeNode* walk ) {
		
		if ( walk == NULL )
			;
		else {
			Clear( walk->left ) ;
			Clear( walk->right ) ;
			delete walk ;
		} // else
		
	} // clear
	
	int Height( TreeNode* walk ) {
		
		if ( walk == NULL )
			return 0 ;
		else {
			int leftDepth = Height( walk->left ) ;
			int rightDepth = Height( walk->right ) ;
			
			if ( leftDepth > rightDepth )
				return leftDepth + 1 ;
			else
				return rightDepth + 1 ;
		} // else
		
	} // height
	
	void InsertByGraduate( TreeNode *&walk, CollegeType aCollege ) {
		
		if ( walk == NULL ) {
			walk = new TreeNode ;
			walk->content = aCollege ;
			walk->left = NULL ;
			walk->right = NULL ;
		} // if
		else if ( aCollege.numGraduate < walk->content.numGraduate )
			InsertByGraduate( walk->left, aCollege ) ;
		else
			InsertByGraduate( walk->right, aCollege ) ;
			
	} // insert
	
	void InsertByName( TreeNode *&walk, CollegeType aCollege ) {
		
		if ( walk == NULL ) {
			walk = new TreeNode ;
			walk->content = aCollege ;
			walk->left = NULL ;
			walk->right = NULL ;
		} // if
		else if ( aCollege.nameSchool < walk->content.nameSchool )
			InsertByName( walk->left, aCollege ) ;
		else
			InsertByName( walk->right, aCollege ) ;
			
	} // insertName
	
	void SearchFor( int goal ) {
		bool found = false ;
		cout << "\nSearch result:\n" ;
		Search( goal, head, found ) ;
		if ( !found )
			cout << "There is no match.\n" ;
		
	} //  search graduate
	
	void Search( int goal, TreeNode *walk, bool &found ) {
		
		if ( walk == NULL )
			;
		else if ( walk->content.numGraduate >= goal ) {
			cout << walk->content.nameSchool << "\t" << walk->content.nameMajor << "\t"
				 << walk->content.division << "\t" << walk->content.level << "\t" 
				 << walk->content.numStudent << "\t" << walk->content.numTeacher << "\t"
				 << walk->content.numGraduate << "\n";
			
			found = true ;
			Search( goal, walk->left, found ) ;
			Search( goal, walk->right, found ) ;
		} // else if
		else{
			Search( goal, walk->left, found ) ;
			Search( goal, walk->right, found ) ;
		} // else
		
	} // search
	
	void SearchForName( string goal ) {
		bool found = false ;
		cout << "\nSearch result:\n" ;
		SearchName( goal, head, found ) ;
		if ( !found )
			cout << "There is no match.\n" ;
		
	} //  search Name
	
	void SearchName( string goal, TreeNode *walk, bool &found ) {
		if ( walk == NULL )
			;
		else if ( walk->content.nameSchool == goal ) {
			cout << walk->content.nameSchool << "\t" << walk->content.nameMajor << "\t"
				 << walk->content.division << "\t" << walk->content.level << "\t" 
				 << walk->content.numStudent << "\t" << walk->content.numTeacher << "\t"
				 << walk->content.numGraduate << "\n";
			
			found = true ;
			SearchName( goal, walk->left, found ) ;
			SearchName( goal, walk->right, found ) ;
		} // else if
		else{
			SearchName( goal, walk->left, found ) ;
			SearchName( goal, walk->right, found ) ;
		} // else
	} // SearchName()
	
	void DeleteNode( TreeNode* node ) {
		if ( node->left == NULL && node->right == NULL ) {
				delete node ;
				node = NULL ;
		} // if
		else if ( node->left == NULL ) {
			TreeNode* temp = node ;
			node = node->right ;
			delete temp ;
		} // else if
		else if ( node->right == NULL ) {
			TreeNode* temp = node ;
			node = node->left ;
			delete temp ;
		} // else if
		else if ( node->left != NULL && node->right != NULL ) {
			TreeNode* temp = node->right ;
			while( temp->left != NULL )
				temp = temp->left ;
					
			node->content = temp->content ;
			DeleteNode( temp ) ;
		} // two child
			
	} // delete node 
	
	void DeleteName( TreeNode*& walk, CollegeType aCollege ) {
		
		if ( walk == NULL )
			;
		else if ( walk->content.nameSchool == aCollege.nameSchool && walk->content.nameMajor == aCollege.nameMajor 
			 && walk->content.division == aCollege.division && walk->content.level == aCollege.level ) {
			DeleteNode( walk ) ;
		} // else if
		else {
			DeleteName( walk->left, aCollege ) ;
			DeleteName( walk->right, aCollege ) ;
		} // else
		
	} // delete tree of name
	
	void DeleteGraduate( TreeNode* walk, int goal, Tree& treeName, ClassList& classList ) {
		if ( walk == NULL )
			;
		else if ( walk->content.numGraduate <= goal ) {
			
			cout << walk->content.nameSchool << "\t" << walk->content.nameMajor << "\t"
				 << walk->content.division << "\t" << walk->content.level << "\t" 
				 << walk->content.numStudent << "\t" << walk->content.numTeacher << "\t"
				 << walk->content.numGraduate << "\n";
				 
			// classList.Remove( walk->content ) ;
			// treeName.DeleteName( treeName.GetHead(), walk->content ) ;
			DeleteNode( walk ) ;
			
			DeleteGraduate( walk, goal, treeName, classList ) ;
		} // else if
		else {
			DeleteGraduate( walk->left, goal, treeName, classList ) ;
			DeleteGraduate( walk->right, goal, treeName, classList ) ;
		} // else
		
	} // Delete graduate
	
}; // class tree

int main() {
	
	ClassList classList ;
	Tree treeGraduate ;
	Tree treeName ; 
	int cmd = 0 ;
	cout << "(1)Build Tree\n(2)Search by Number of Graduates\n(3)Search by School Name\n(4)Removal by Number of Graduates(not working)\n(0)Exit\nCommand:" ;
	cin >> cmd ;
	
	while ( cmd != 0 ) {
		
		if ( cmd == 1 ) {
			
			classList.ClearList() ;
			treeGraduate.ClearTree() ;
			treeName.ClearTree() ;
			cout << "File name: " ;
			string fileName ;
			cin >> fileName ;
			if ( classList.Load( fileName ) ) {
				classList.Print() ;
				cout << "\n[Tree heights]\n" ;
				treeGraduate.CreateByGraduate( classList.GetSet() ) ;
				treeName.CreateByName( classList.GetSet() ) ;
			} // if
			else
				cout << "File not found.\n" ;
				
		} // cmd 1
		else if ( cmd == 2 ) {
			if ( treeGraduate.IsEmpty() )
				cout << "Need to build a tree first.\n" ;
			else {
				cout << "Number of graduates you want to find: " ;
				int numGraduate = -1 ;
				cin >> numGraduate ;
				while ( numGraduate < 0 ) {
					cout << "Number has to be 0 or positive.\nNumber of graduates you want to find: " ;
					cin >> numGraduate ;
				} // while
				treeGraduate.SearchFor( numGraduate ) ;
			} // else
		} // cmd 2
		else if ( cmd == 3 ) {
			if ( treeName.IsEmpty() ) 
			    cout << "Need to build a tree first.\n" ;
			else {
				cout << "School name you want to find: " ;
				string schoolName ;
				cin >> schoolName ;	
				treeName.SearchForName( schoolName ) ;
			} // else
			
		} // cmd 3
		else if ( cmd == 4 ) {
			int goal = -1 ;
			cout << "Number of graduates: " ;
			cin >> goal ;
			treeGraduate.DeleteGraduate( treeGraduate.GetHead(), goal, treeName, classList ) ;
			cout << "\n[Tree heights]\nNumber of graduates: " << treeGraduate.Height( treeGraduate.GetHead() ) << "\nSchool name: " << treeName.Height( treeName.GetHead() ) << "\n" ;
		} // cmd 4
		else
			cout << "Command not found.\n" ;
			
		cout << "\n(1)Build Tree\n(2)Search by Number of Graduates\n(3)Search by School Name\n(4)Removal by Number of Graduates(not working)\n(0)Exit\nCommand:" ;
		cin >> cmd ;
		
	} // while
	
	return 0 ;
	
} // main
