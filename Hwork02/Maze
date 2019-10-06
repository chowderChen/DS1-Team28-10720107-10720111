#include<iostream>
#include<cstdio>
#include<cstring> 


using namespace std ;

typedef enum { Copy = -1, Right, Down, Left, Up } Moves ;

class CoXY {
	
	int y ;
	int x ;
	
	public:
		
	CoXY(): y(0), x(0) {
	} ;
		
	CoXY( int py, int px ){
		y = py ;
		x = px ;
	} // CoXY
	
	void setXY( const int py, const int px ) {
		y = py ;
		x = px ;
	}
	
	int getX() const {
		return x ;
	}
	int getY() const {
		return y ;
	}
	
	CoXY nextXY( Moves dir ) const {
	
		CoXY pt( y, x ) ;
		switch( dir ) {
			
			case Right: 
				pt.x++ ;
				break ;
			case Down:
				pt.y-- ;
				break ;
			case Left:
				pt.x-- ;
				break ;
			case Up:
				pt.y++ ;
				break ;
			default:
				;
				
		} // switch
		
		return pt ;
	
	} // nextXY
	
	bool match( const CoXY &pt ) {
		
		if ( y == pt.y && x == pt.x )
			return true ;
		
		return false ;	
		
	} // match()
	
	bool inRange( const CoXY &maxLimit ) {
		
		if ( y >= 0 && y < maxLimit.y && x >= 0 && x < maxLimit.x )
			return true ;
			
		return false ;
		
	} // inRange
	
}; // class CoXY

class Maze {
			
	char **mArray ;	  // 放迷宮、裝V路徑
	char **mArrayR ;  // 裝R路徑
	
	CoXY coMax ;
	
	public:
		
	bool Load( string fileName ) ;
	
	void Print() ;    // 印出V路徑
	void PrintR() ;   // 印出R路徑
	
	void GetGBack() ;   // 把V路徑被蓋掉的G找回來
	
	bool SolveMaze( CoXY pt, int &numGoal ) ;   // 跑迷宮
	
}; // class Maze

void Maze::GetGBack() {
	
	for ( int i = 0 ; i < coMax.getY() ; i++ )
		for ( int j = 0 ; j < coMax.getX() ; j++ )
			if ( mArrayR[i][j] == 'G' )    // 當R路徑這格是G時
				mArray[i][j] = 'G' ;   // V路徑這格也該是G
	
} //GetGBack

void Maze::Print() {
	
	for ( int i = 0 ; i < coMax.getY() ; i++ ){
		for( int j = 0 ; j < coMax.getX() ; j++ )
			cout << mArray[i][j] ;
			
		cout << "\n" ;
	} // for
	
} // Print

void Maze::PrintR() {
	
	for ( int i = 0 ; i < coMax.getY() ; i++ ){
		for( int j = 0 ; j < coMax.getX() ; j++ )
			cout << mArrayR[i][j] ;
			
		cout << "\n" ;
	} // for
	
} // Print

bool Maze::Load( string fileName ){
	
	FILE *infile = NULL ;
	bool success = false ;
	coMax.setXY(0, 0) ;
	
	fileName = "input" + fileName + ".txt" ;
	infile = fopen(fileName.c_str(), "r") ;
	if ( infile == NULL )
		;
	else{
		
		int arg1 = 0, arg2 = 0 ;
		fscanf( infile, "%d %d", &arg1, &arg2 ) ;
		coMax.setXY( arg2, arg1 ) ;
		if ( coMax.getY() > 0 && coMax.getX() > 0 ){
			
			int line = 0 ;
			char *temp = new char[coMax.getX() + 1] ;
			mArray = new char *[coMax.getY()] ;
			mArrayR = new char *[coMax.getY()] ;
			
			while( fscanf( infile, "%s", temp ) != EOF ){
		
				mArray[line] = new char [coMax.getX() + 1] ;
				mArrayR[line] = new char [coMax.getX() + 1] ;
				strcpy( mArray[line], temp ) ;
				strcpy( mArrayR[line++], temp ) ;
				
			} // while
			
			if ( line == coMax.getY() ) {
				success = true ;
			} // if
				
		} // if
		
		fclose( infile ) ;	
		
	} // else
	
	return success ;
	
} // Load()

bool Maze::SolveMaze( CoXY pt, int &numGoal ) {
	
	if ( !pt.inRange( coMax ) )    // 當下一格超出迷宮時，不做事
		return false ;
	else if ( mArray[pt.getY()][pt.getX()] == 'G' ) {    // 當下一格是G時
		
		numGoal-- ;   // 找到一個目標了，所以要找的目標數減一
			
		mArray[pt.getY()][pt.getX()] = 'V' ;   // 走上這格並標記
		// G可以在跑完迷宮後用GetRBack()來取回
		
		if ( numGoal > 0 )   // 當還要找目標時，繼續走
			SolveMaze( pt.nextXY( Right ), numGoal ) ;
		if ( numGoal > 0 ) 
			SolveMaze( pt.nextXY( Down ), numGoal ) ;
		if ( numGoal > 0 ) 
			SolveMaze( pt.nextXY( Left ), numGoal ) ;
		if ( numGoal > 0 ) 
			SolveMaze( pt.nextXY( Up ), numGoal ) ;
				
		return true ;   // 有找到目標就回傳true
		
	} // else if
	else if ( mArray[pt.getY()][pt.getX()] == 'E' ) {    // 當下一格是E時
		
		mArray[pt.getY()][pt.getX()] = 'V' ;    // 走上去並標記
		bool success = false ;     // 只要之後有一條回傳true，就表示有找到目標G
		
		if ( numGoal > 0 )
			if ( SolveMaze( pt.nextXY( Right ), numGoal ) ) {
				// 如果SolveMaze回傳true，則這條是正確路徑的一格，標為R
				mArrayR[pt.getY()][pt.getX()] = 'R' ;  
				success = true ;
			} // if
		if ( numGoal > 0 )   // 因為每一條路都可能找到目標G，所以走每條路前都要確認是否還要找G
			if ( SolveMaze( pt.nextXY( Down ), numGoal ) ) {
				mArrayR[pt.getY()][pt.getX()] = 'R' ; 
				success = true ;
			} // if
		if ( numGoal > 0 )
			if ( SolveMaze( pt.nextXY( Left ), numGoal ) ) {
				mArrayR[pt.getY()][pt.getX()] = 'R' ; 
				success = true ;
			} // if
		if ( numGoal > 0 )
			if ( SolveMaze( pt.nextXY( Up ), numGoal ) ) {
				mArrayR[pt.getY()][pt.getX()] = 'R' ; 
				success = true ;
			} // if
			
		return success ;
		
	} // else if
	else
		return false ;
	
} // SolveMaze

int GetInput() {
	// 取得用戶輸入，以確保格式 
	string input ; 
	cin >> input ;
	for ( int i = 0 ; i < input.size() ; i++ )
		if ( !isdigit( input[i] ) ) {
			cout << "格式錯誤，請輸入一個不為負的整數: " ;
			cin >>  input ;
			i = 0 ;
		} // if
	
	int inputInt = 0 ;
	for ( int i = 0 ; i < input.size() ; i++ )
		inputInt = inputInt * 10 + input[i] - '0' ;
		
	return inputInt ;
	
} // GetInput()

int main() {
	
	Maze maze ;
	int cmd = -1 ;
	cout << "(1)One Goal\n(2)More Goals\n(0)Exit\nChoose a command: " ;
	cmd = GetInput() ;   // cmd讓你選要執行哪個任務
	while ( cmd != 0 ) {
	
		if ( cmd == 1 || cmd == 2 ) {
		
			string fileName ;
			cout << "要讀哪個檔: " ;
			cin >> fileName ; 
			while ( !maze.Load( fileName ) ) {
				cout << "Not working, try again: " ;
				cin >> fileName ;
			} // while
	
			int numGoal = 1 ;
			if ( cmd == 2 ) {
				cout << "要找幾個Goal: " ;
				numGoal = GetInput() ;
			} // if
	
			CoXY pt(0, 0) ;
	
			if ( maze.SolveMaze( pt, numGoal ) ) {
				maze.GetGBack() ;   // 把走迷宮時擦掉的G找回來
				maze.Print() ;    // 印出V路徑
				if ( numGoal == 0 ) {    // 如果找到的目標數是對的
					cout << "\n" ;
					maze.PrintR() ;   // 印出R路徑
				} // if
			} // if
			else {     // 如果一個G都沒找到
				maze.GetGBack() ;    
				maze.Print() ;   // 印出V路徑
			} // else 
		
		} // if
		else 
			cout << "Incorrect command.\n" ;
		
		cout << "(1)One Goal\n(2)More Goals\n(0)Exit\nChoose a command: " ;
		cmd = GetInput() ; 
	
	} // while
	
	cout << "See you~" ;
	
} // main
