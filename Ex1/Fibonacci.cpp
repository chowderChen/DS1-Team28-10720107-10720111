#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <math.h>

using namespace std ;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int GetUserInput() {
	// 取得用戶輸入，以確保格式 
	string input ; 
	cin >> input ;
	for ( int i = 0 ; i < input.size() ; i++ )
		if ( !isdigit( input[i] ) ) {
			cout << "格式錯誤，請輸入一個正整數: " ;
			cin >>  input ;
			i = 0 ;
		} // if
	
	int inputInt = 0 ;
	for ( int i = 0 ; i < input.size() ; i++ )
		inputInt = inputInt * 10 + input[i] - '0' ;
		
	return inputInt ;
	
} // GetUserInput()

vector<unsigned long long int> FindF_Loop( int n ) {
	// 用迴圈產生從1開始的費氏數列前n個數字 
	
	unsigned long long int f1 = 0, f2 = 1 ;       // f1, f2代表目前要計算的費氏數的前兩個費氏數 
	vector<unsigned long long int> FVector ;
	for ( int i = 0 ; i < n ; i++ ) {
		if ( f1 < f2 ) {
			f1 = f1 + f2 ;
			FVector.push_back( f1 ) ;
		} // if
		else {
			f2 = f1 + f2 ;
			FVector.push_back( f2 ) ;
		} // else
					
	} // for
	
	return FVector ;
	
} // FindF()

void FindClosestFactors_Loop( unsigned long long int num, int FNum ){        // 用來找num的兩最相近的因數，FNum為num在費氏數列中的順序 
	
	long long int num_Loop = 0 ;        // loop的次數 
	for ( long long int i = sqrt( num ) ; i > 0 ; i-- ) {		// 從平方根開始往1找 
		num_Loop++ ;
		if ( num % i == 0 ) {
			
			cout << FNum << ": " << num << " = " << i << " * " << num / i << "    ( Inner loop: " << num_Loop << " times )\n" ;
			i = 0 ;
			
		} // if
	} // for 
			
	
} // FindClosestFactors()

void FindF_Recursion( int n, long long int f1, long long int f2, vector<unsigned long long int> &FVector ) {       
	// 用遞迴找出從1開始的費氏數列的前n個數字 
	
	if ( n == 0 )
		;
	else{
		
		FVector.push_back( f1 + f2 ) ;
		FindF_Recursion( n - 1, f2, f1 + f2, FVector ) ;
		
	} // else
		
	
} // FindF()

bool FindClosestFactors_Recursion( unsigned long long int num, long long int factor, int num_F, int count  ){        
	// 用遞迴找num兩最相近的因數，num_F代表num是費氏數列中的第幾項 
	// factor用來計算因數，count用來記錄遞迴了多少次 

	if ( count >= 10000 || factor > sqrt( num ) )
		return false ;
	else if ( num % factor == 0 ) {
		if ( !FindClosestFactors_Recursion( num, factor + 1 , num_F, count + 1 ) ) {
			cout << num_F << ": " << num << " = " << factor << " * " << num / factor << "\n" ;
		} // if
			
		return true ;
	} // else if
	else {
		return FindClosestFactors_Recursion( num, factor + 1 , num_F, count + 1 ) ; 
	} // else
 	
} // FindClosestFactors()

int main(int argc, char** argv) {
	
	cout << "請輸入一個不大於92的正整數: " ;
	int n = -1 ;	// n用來存取費氏數列要的項數 
	n = GetUserInput() ;
	while ( n > 92 || n <= 0 ) {
		 cout << "錯誤，請輸入一個不大於92的正整數: " ;
		 n = GetUserInput() ; 
	} // while 
	cout << "(1)Loop\n(2)Recursion\n(3)Change the number\n(0)Exit\nEnter the number of the function you wanna use: " ;
	int cmd = -1 ;		// cmd用來記錄使用者要使用哪個功能
	// 0為退出，1為使用迴圈方法執行，2為使用遞迴方法執行，3用來改變目標(費氏數列項數)	
	cmd = GetUserInput() ;
	while ( cmd != 0 ) {
		
		if ( cmd == 1 ) {		// Loop
		
			vector<unsigned long long int> FVector = FindF_Loop( n ) ;
			for ( int i = 0 ; i < FVector.size() ; i++ )
				FindClosestFactors_Loop( FVector.at( i ), i+1 ) ;
				
			cout << "< Outer loop: " << n << " times >\n" ;
				
		} // if
		else if ( cmd == 2 ){		// Recursion
		
			vector<unsigned long long int> FVector ;
			long long int f1 = 0, f2 = 1 ;      // 預設費氏數列的開頭 
			FindF_Recursion( n, f1, f2, FVector ) ;
			for( int i = 0 ; i < FVector.size() ; i++ ) {
				long long int factor = 1 ;
				while ( !FindClosestFactors_Recursion( FVector.at( i ), factor, i + 1, 0 ) )
					factor = factor + 10000 ;
			} // for 
				
		} // else if
		else if ( cmd == 3 ) {
			
			cout << "Set target to: " ;
			n = GetUserInput() ;
			while ( n > 92 || n <= 0 ) {
		 		cout << "錯誤，請輸入一個不大於92的正整數: " ;
		 		n = GetUserInput() ; 
			} // while 
			
		} // else if
		else 	// 告訴使用者輸入錯誤
			cout << "incorrect command, try again.\n" ;
			
		cout << "(1)Loop\n(2)Recursion\n(3)Change the number\n(0)Exit\nEnter the number of the function you wanna use: " ;
		cmd = GetUserInput() ;
	
	} // while
	
	cout << "\nSee you" ;
	return 0;
	
} // main()
