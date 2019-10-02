#include <stdio.h>
#include <string>
#include <iostream>

using namespace std ;

/* rat in a maze - by Peter */

char maze[20][20] ;
char sol[20][20] ;

struct Maze {
	char ch = '0' ;
	Maze* right = NULL ;
	Maze* left = NULL ;
	Maze* up = NULL ;
	Maze* down = NULL ;
	
};

bool SolveMaze( int m, int n ) {
	if ( maze[m][n] == 'G' ){
		return true ;
	} // if
	else {
		if ( maze[m][n] == 'E' ) {
			maze[m][n] = 'V' ;
			if ( SolveMaze( m, n + 1 ) ) {
				return true ;
			} // if 
			else if ( SolveMaze( m+1, n ) ) {
				return true ;
			} // else if
			else if ( SolveMaze( m, n - 1 ) ) {
				return true ;
			} // else if
			else if ( SolveMaze( m-1, n ) ) {
				return true ;
			} // else if
			else {
				maze[m][n] = 'E' ;
				return false ;
			} // else
			
		} // if
		else {
			return false ;
		} // else
		
	} // else
} ;


int main() {
	int x = 0 ;
	int y = 0 ;
	cin >> x ;
	cin >> y ;
	for( int j = 0 ; j < y ; j ++ ) {
		for( int i = 0 ; i < x ; i ++ ) {
			cin >> maze[i][j];
			sol[i][j] = maze[i][j] ;
		} // for
	} // for

    if ( SolveMaze( x, y ) ) {
    	for( int a = 0 ; a < y ; a++ ){
    		for ( int b = 0 ; b < x ; b++ ){
    			cout << sol[a][b] ;
			} // for
		} // for
	} // if
    else {
        for ( int c = 0 ; c < y ; c++ ) {
		for ( int d = 0 ; d < x ; d++ ) {
		    cout << maze[x][y] ;
	        } // for
	} // for
    } // else 
}
