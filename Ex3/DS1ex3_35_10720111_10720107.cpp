// 10720111 陳少暉  10720107 陳丕中

#include<stdio.h>
#include<iostream>
#include<string.h>

using namespace std ;

int GetInput() {
	// 取得用戶輸入，以確保格式
	string input, temp ;
	getline( cin, input ) ;
	
	for ( int i = 0 ; i < input.size() || input.size() == 0 ; i++ )
		if ( input.size() == 0 || !isdigit( input[i] ) ) {
			cout << "格式錯誤，請輸入一個不為負的整數: " ;
			getline( cin, input ) ;
			i = 0 ;
		} // if

	int inputInt = 0 ;
	for ( int i = 0 ; i < input.size() ; i++ )
		inputInt = inputInt * 10 + input[i] - '0' ;

	return inputInt ;

} // GetInput()

struct Data {

  string str ;
  char ch ;
  Data * next ;

} ;

class Stack {

	Data* top ;

	public:

	Stack() {
		top = NULL ;
	} // Stack
	~Stack() {
		while( !IsEmpty() )
			Pop() ;
		delete top ;
	} // ~Stack

	void Push( char ch ) ;
	Data* GetTop() ;
	void Pop() ;
	char ShowTop() ;
	bool IsEmpty() ;

}; // class Stack

void Stack::Push( char ch ) {
	// 把東西放進stack 
	Data* temp = new Data() ;
	temp->ch = ch ;
	temp->next = NULL ;

	if ( !IsEmpty() ) {
    	temp->next = top ;
   	 	top = temp ;
  	} // if
 	else {
    	top = temp ;
	} // else

} // Push()

Data* Stack::GetTop() {
	// 拿出stack頂端的東西 
	if ( IsEmpty() )
		cout << "There is nothing can be get.\n" ;
	else {
		Data* temp = new Data() ;
		temp = top ;
		top = top->next ;
		return temp ;
	} // else

	return NULL ;

} // Pop()

void Stack::Pop() {
	// 將stack頂端彈掉 
	if ( IsEmpty() )
		cout << "There is nothing can be pop.\n" ;
	else {
		Data* temp = new Data() ;
		temp = top ;
		top = top->next ;
		delete temp ;
	} // else

} // Pop()

char Stack::ShowTop() {
	// 看stack頂端是什麼 
	if ( IsEmpty() )
		cout << "There is nothing can be show\n" ;
	else
		return top->ch ;

    return '\0' ;

} // ShowTop

bool Stack::IsEmpty() {

	if ( top == NULL )
		return true ;

	return false ;

} // IsEmpty()

class List {

	Data* head ;

	public:

	List() {
		head = NULL ;
	} // List
	~List() {
		while ( head != NULL ) {
			Data* walk = head ;
			head = head->next ;
			delete walk ;
		} // while
		delete head ;
	} // ~List

	void Add( string str ) ;
	bool IsEmpty() ;
	void PrintList() ;
};

void List::Add( string str ) {
	// 加一節點到鏈結串列尾端，其值為string str 
	Data* temp = new Data() ;
	temp->str = str ;
	temp->next = NULL ;
	if ( IsEmpty() )
		head = temp ;
	else {
		Data* walk = new Data() ;
		walk = head ;
		while ( walk->next != NULL )
			walk = walk->next ;

		walk->next = temp ;
	} // else

} // Add()

bool List::IsEmpty() {

	if( head == NULL )
		return true ;

	return false ;

} // IsEmpty()

void List::PrintList() {
	// 從頭印出每個節點的值 
    Data* walk = head ;
    while ( walk != NULL ) {
        cout << walk->str ;
        if ( walk->next != NULL )
            cout << ", " ;
        walk = walk->next ;
    } // while
    cout << "\n" ;

} // PrintList


bool IsLegalEx( string ex ) {
	// 看陣列中的式子是否為合法的中序式 
	
	if ( ex.size() == 0 ) {
		cout << "給我式子我才能看啊!\n" ; 
		return false ;
	} // if
		
	int numOpenP = 0, numCloseP = 0 ;   // 記錄這式子有幾個'('和')'
	bool wasOprator = false, wasOpenP = false, wasCloseP = false ;
	bool wasNum = false ;
	for ( int i = 0 ; i < ex.size() ; i++ ) {

		if ( ex[i] == '+' || ex[i] == '-' || ex[i] == '*' || ex[i] == '/' ) {
			if ( wasOprator ) {
				// 如果運算符號前是運算符號，表示這個運算符號是多餘的 
				cout << "Error 3: there is one extra operator.\n" ;
				return false ;
			} // if
			else if ( wasOpenP ) {
				// 如果運算符號前是'('，表示這個括弧內的式子不為中序 
				cout << "Error 3: it is not infix in the parentheses.\n" ;
				return false ;
			} // else if
			else if ( !wasNum && !wasCloseP ) {
				// 式子開頭為運算符號是錯的 
				cout << "Error 3: there is one extra operator.\n" ;
				return false ;
			}
				
			wasOprator = true ;
			wasOpenP = false ;
			wasCloseP = false ;
			wasNum = false ;
		} // if
		else if ( '0' <= ex[i] && ex[i] <= '9' ) {
			if ( wasCloseP ) {
				// 如果數字前是')'，表示式子內有多餘的數字 
				cout << "Error 3: there is one extra operand.\n" ;
				return false ;
			}
			wasOprator = false ;
			wasOpenP = false ;
			wasCloseP = false ;
			wasNum = true ;
		} // else if
		else if ( ex[i] == ')' ) {
			if ( wasOpenP || wasOprator ) {
				// 如果)前面是(或運算符號，就代表括號內的式子不為中序
				cout << "Error 3: it is not infix in the parentheses.\n" ;
				return false ;
			}

			if ( numOpenP > numCloseP )
				// 如果前面記錄到'('的數量大於')'，正常記錄')'數量增加
				numCloseP ++ ;
			else {
				// 如為非，表示這式子多了')'
				cout << "Error 2: there is one extra close parenthesis.\n" ;
				return false ;
			} // else
			wasOprator = false ;
			wasOpenP = false ;
			wasCloseP = true ;
			wasNum = false ;
		} // else if
		else if ( ex[i] == '(' ) {
			numOpenP ++ ;
			wasOprator = false ;
			wasOpenP = true ;
			wasCloseP = false ;
			wasNum = false ;
		} // else if
		else if ( ex[i] == ' ' )
			;
		else {   // 不是+-*/()也不是數字也不是空格，是非法字元
			cout << "Error 1: " << ex[i] << " is not a legitimate character.\n" ;
			return false ;
		}

	} // for

	if ( wasOprator ) {
		// 式子尾端為運算符號時是錯的 
		cout << "Error 3: there is one extra operator.\n" ;
		return false ;
	} // if
	
	if ( numOpenP > numCloseP ) {
		// 如果式子中'('的數量大於')'，表示有多的'('
		cout << "Error 2: there is one extra open parenthesis.\n" ;
		return false ;
	} // if
	else if ( numOpenP < numCloseP ) {
		cout << "Error 2: there is one extra close parenthesis.\n" ;
		return false ;
	} // else if

	return true ;

} // IsLegalEx()

void InfixToPostfix( string ex, List& postfixEx ) {
	// 將中序式轉為後序式 
	Stack stack ;    // stack用來儲存運算符號 
	string token ;   // token用來 
	int i = 0 ;
	while ( i < ex.size() ) {    

		if ( '0' <= ex[i] && ex[i] <= '9' ) {
			// 碰到數字時，把它全抓下來做成string型別的token放入postfixEx 
			token = ex[i] ;
			i ++ ;
			while ( i < ex.size() && (( '0' <= ex[i] && ex[i] <= '9' ) || ex[i] == ' ' ) ) {
				if ( ex[i] != ' ' )
					token = token + ex[i] ;

				i ++ ;
			} // while
			postfixEx.Add( token ) ;
			token = "" ;
		} // if
		else if ( ex[i] == '+' || ex[i] == '-' ) {
			// 碰到+, -時，將stack裡的符號拿出放入後序式，直到碰到 ( 或stack為空
			// 再將 +, -放入stack 
            while ( !stack.IsEmpty() && stack.ShowTop() != '(' ) {
                token = stack.GetTop()->ch ;
                postfixEx.Add( token ) ;
                token = "" ;
            } // while
			stack.Push( ex[i] );
			i ++ ;
        } // else if
		else if ( ex[i] == '*' || ex[i] == '/' ) {
			// 碰到 * , / 時，將stack頂端的所有 *, / 拿出放入後序式 
			// 再將 *, / 放入stack 
            while ( !stack.IsEmpty() && ( stack.ShowTop() == '*' || stack.ShowTop() == '/' ) ) {
                token = stack.GetTop()->ch ;
                postfixEx.Add( token ) ;
                token = "" ;
            } // while
            stack.Push( ex[i] ) ;
            i++ ;
		} // else if
		else if ( ex[i] == '(' ) {
			// 碰到 ( 時，將其放入stack 
			stack.Push( ex[i] ) ;
			i ++ ;
		} // else if
		else if ( ex[i] == ')' ) {
			// 碰到 ) 時，取出stack的內容物，直到碰到 (  
			while ( stack.ShowTop() != '(' ) {
                token = stack.GetTop()->ch ;
                postfixEx.Add( token ) ;
                token = "" ;
            } // while

            stack.Pop() ;  // pop '(' out
            i ++ ;
        } // else if
		else if ( ex[i] == ' ' )
			i ++ ;

	} // while

	while ( !stack.IsEmpty() ) {
		// 如果stack內還有東西，就都取出 
        token = stack.GetTop()->ch ;
        postfixEx.Add( token ) ;
        token = "" ;
	} // while

} // InfixToPostfix

int main() {

	int cmd = -1 ;
	cout << "1. 執行中序轉後序\n0. 退出\n請輸入指令:" ;
	cmd = GetInput() ;
	while ( cmd != 0 ) {

		if ( cmd == 1 ) {
		
			string ex ;
			cout << "輸入式子:" ;
			getline( cin, ex ) ;
			
			if ( IsLegalEx( ex ) ) {   // 判斷式子是否為合法 
       	    	cout << "\nIt's a infix expression.\n" ;
				List postfixEx ;
				InfixToPostfix( ex, postfixEx ) ;  // 將式子由中序轉為後序 
				postfixEx.PrintList() ;
			} // if
	
		} // if cmd == 1
		else
			cout << "沒這個指令\n" ;

		cout << "1. 執行中序轉後序\n0. 退出\n請輸入指令:" ;
		cmd = GetInput() ;

	} // while

  	return 0 ;

} // main()
