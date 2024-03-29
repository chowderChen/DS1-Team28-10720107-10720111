// 10720111 ���ַu 10720107 ���A��

#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<ctime>

using namespace std ;

struct Job {

    int ID ;
    int arrival ;
    int duration ;
    int timeout ;
    int wait ;

};

struct DoneJob {

    int ID ;
    int outTime ;
    int delay ;

};

class JobList {
    // list for jobs

    vector<Job> aList ;

    public:

    void Sort( clock_t &t ) ;
    bool Load( string fileName, clock_t &t ) ;
    bool Load( string fileName ) ;
    void PrintAll() ;
    bool Export( string fileName, clock_t &t ) ;
    Job At( int i ) ;
    int Size() ;

}; // class JobList

int JobList::Size() {
    return aList.size() ;
} // Size

Job JobList::At( int i ) {
    return aList.at( i ) ;
} // At

bool JobList::Export( string fileName, clock_t &t ) {
    // Export sorted list to .txt

    t = clock() ;
    FILE *outFile = NULL ;
    bool success = false ;
    fileName = "sorted" + fileName + ".txt" ;
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

    t = clock() - t ;
    return success ;

} // Export

void JobList::PrintAll(){

    cout << "OID\tArrival\tDuration\tTimeOut\n" ;
    for ( int i = 0 ; i < aList.size() ; i++ ) {
        cout << aList.at(i).ID << "\t" << aList.at(i).arrival << "\t" ;
        cout << aList.at(i).duration << "\t" << aList.at(i).timeout << "\n" ;
    } // for
    cout << "\n" ;

} // PrintAll

void JobList::Sort( clock_t &t ){
    // use Shell sort to make the list sort from small to large
	// according to arrival, ID 
	
    t = clock() ;
    for ( int gap = aList.size()/2 ; gap > 0 ; gap = gap / 2 )
        for ( int i = gap ; i < aList.size() ; i++ ) {
            Job tempJob = aList.at( i ) ;
            int j = -1 ;
            for ( j = i ; j >= gap && ( tempJob.arrival < aList.at( j - gap ).arrival
                || ( tempJob.arrival == aList.at( j - gap ).arrival
                    && tempJob.ID < aList.at( j - gap ).ID ) ) ; j = j - gap ) {
                aList.at( j ) = aList.at( j -  gap ) ;
            } // for

            aList.at(j) = tempJob ;
        } // for
    t = clock() - t ;

} // Sort

bool JobList::Load( string fileName, clock_t &t ) {
    // Load a file, turn it into a list of jobs 
    FILE *infile = NULL ;
    bool success = false ;
    t = clock() ;
    fileName = "input" + fileName + ".txt" ;
    infile = fopen(fileName.c_str(), "r" ) ;

	if ( infile == NULL )
		;
	else{

        char temp ;

        while ( fscanf( infile, "%c", &temp ) != EOF && temp != '\n' )
            ;

        Job aJob ;
        while ( fscanf( infile, "%d %d %d %d", &aJob.ID, &aJob.arrival, &aJob.duration, &aJob.timeout ) != EOF )
            aList.push_back( aJob ) ;

        success = true ;
        fclose( infile ) ;

	} // else

    t = clock() - t ;

	return success ;

} // Load

bool JobList::Load( string fileName ) {
    // Load a file, turn it into a list of jobs 
    
    FILE *infile = NULL ;
    bool success = false ;

    fileName = "sorted" + fileName + ".txt" ;
    infile = fopen(fileName.c_str(), "r" ) ;

	if ( infile == NULL )
		;
	else{

        char temp ;

        while ( fscanf( infile, "%c", &temp ) != EOF && temp != '\n' )
            ;

        Job aJob ;
        while ( fscanf( infile, "%d %d %d %d", &aJob.ID, &aJob.arrival, &aJob.duration, &aJob.timeout ) != EOF )
            aList.push_back( aJob ) ;

        success = true ;
        fclose( infile ) ;

	} // else

	return success ;

} // Load


class JobQueue {

    struct QueueNode {
		Job aJob ;
		QueueNode * next ;
	};

	QueueNode * backPtr ;
	QueueNode * frontPtr ;
	int length ;

	public :

    JobQueue() {
        frontPtr = NULL ;
        backPtr = NULL ;
        length = 0 ;
    } // queue
    ~JobQueue() {
        while( !IsEmpty() )
            DeQueue() ;
    } // ~queue

	bool IsEmpty() ;
	void EnQueue( Job newJob ) ;
	void DeQueue() ;
	void DeQueue( Job &aJob ) ;
	void GetFront( Job &aJob ) ;
	void GetBack( Job &aJob ) ;
    int Length() ;
    bool Load( string fileName ) ;
    void Print() ;
    void PutWaitInFront( int wait ) ;

};

void JobQueue::PutWaitInFront( int wait ) {
	// put the waiting time into the front of the queue
    if ( !IsEmpty() )
        frontPtr->aJob.wait = wait ;

} //

void JobQueue::Print() {
	// Shows what is in the queue
    cout << "OID\tArrival\tDuration\tTimeOut\n" ;
    for ( QueueNode *walk = frontPtr ; walk != NULL ; walk = walk->next ) {
        cout << walk->aJob.ID << "\t" <<  walk->aJob.arrival << "\t" ;
        cout <<  walk->aJob.duration << "\t" <<  walk->aJob.timeout << "\n" ;
    } // for
    cout << "\n" ;

}

bool JobQueue::Load( string fileName ) {
	// Load a file into the queue
    FILE *infile = NULL ;
    bool success = false ;

    fileName = "sorted" + fileName + ".txt" ;
    infile = fopen(fileName.c_str(), "r" ) ;

	if ( infile == NULL )
		;
	else{

        char temp ;

        while ( fscanf( infile, "%c", &temp ) != EOF && temp != '\n' )
            ;

        Job aJob ;
        while ( fscanf( infile, "%d %d %d %d", &aJob.ID, &aJob.arrival, &aJob.duration, &aJob.timeout ) != EOF )
            EnQueue( aJob ) ;

        success = true ;
        fclose( infile ) ;

	} // else

	return success ;


} // Load

bool JobQueue::IsEmpty() {

	if ( frontPtr == NULL )
	    return true ;
	else if ( backPtr == NULL )
	    return true ;
    else
        return false ;
} // isEmpty()

void JobQueue::EnQueue ( Job newJob ) { 
   // put sth to the back of the queue
	QueueNode * newPtr = new QueueNode ;
	newPtr->aJob = newJob ;
	newPtr->aJob.wait = 0 ;
	newPtr->next = NULL ;

	if ( IsEmpty() )
	    frontPtr = newPtr ;
	else
	    backPtr->next = newPtr ;

    backPtr = newPtr ;
    length++ ;
} // enQueue()

void JobQueue::DeQueue () { 
    // take sth from the front of the queue

	if ( IsEmpty() ) {
		printf( "is Empty!") ;
	} // if
	else {
	    
	    if ( frontPtr == backPtr ) {
	    	frontPtr = NULL ;
	    	backPtr = NULL ;
	    } // if
	    else {
	    	QueueNode * tempPtr = frontPtr ;
	    	frontPtr = frontPtr->next ;
	    	tempPtr->next = NULL ;
    		delete tempPtr ;
	    } // else
    	length--;
    } // else

} //deQueue()

void JobQueue::DeQueue( Job &aJob ) { 
	// take sth out of the queue from the front of the queue
    if( IsEmpty() ) {
    	printf("is Empty!") ;
	} // if
	else {
		aJob = frontPtr->aJob ;
		DeQueue() ;
	} // else

} // DeQueue

void JobQueue::GetFront ( Job &aJob ) { 
    // See what is in the front of the queue

	if ( IsEmpty() )
	    printf("is Empty!!") ;

    else
        aJob = frontPtr->aJob ;

} // getFront()

void JobQueue::GetBack( Job &aJob ) {
	// See what is in the back of the queue
    if ( IsEmpty() )
        cout << "There is nothing.\n" ;
    else
        aJob = backPtr->aJob ;
} // GetBack

int JobQueue::Length() {
    return length ;
} // Length


struct DepartureEvent {
    int departure ;
};

struct Event {
    char type ;
    Job AEvent ;
    DepartureEvent DEvent ;
};

struct EventNode {
    Event event ;
    EventNode* next ;
};

class EventList {

    EventNode* eventList ;

    public:

    EventList(){
        eventList = NULL ;
    }
    ~EventList() {
        while( !IsEmpty() )
            Pop() ;
    }
    void PutEventIn( Event newEvent );
    bool IsEmpty() ;
    Event Pop() ;

}; // class EventList

Event EventList::Pop(){
	// Pop from the front
    Event tempEvent = eventList->event ;
    EventNode* tempNode = eventList ;
    eventList = eventList->next ;
    delete tempNode ;
    return tempEvent ;

} // Pop

void EventList::PutEventIn( Event newEvent ) {
	// insert a Event into event list
	// according to the timing
	
    EventNode* tempEvent = new EventNode ;
    tempEvent->event = newEvent ;
    tempEvent->next = NULL ;
    if ( IsEmpty() )
        eventList = tempEvent ;
    else if ( newEvent.type == 'a' && newEvent.AEvent.arrival < eventList->event.DEvent.departure ) {
        tempEvent->next = eventList ; //insert infront of it
        eventList = tempEvent ;
    } // else if
    else if ( newEvent.type == 'd' && newEvent.DEvent.departure <= eventList->event.AEvent.arrival ) {
        tempEvent->next = eventList ; // front insert
        eventList = tempEvent ;
    } // else if
    else
        eventList->next = tempEvent ;

} // Put

bool EventList::IsEmpty() {
    if ( eventList == NULL )
        return true ;

    return false ;
} // Empty


class Simulation {
	// Simulate how solo queue work
	 
    JobQueue jobQueue ; // sorted jobs 
    JobQueue workQueue ; // simulate 
    EventList eventList ; // keeps events
    vector<DoneJob> abortList ;  
    vector<DoneJob> doneList ;  

    public:

    bool Simulate() ;
    void ProccessArrival( Event newEvent ) ;
    void ProccessDeparture( Event newEvent ) ;
    void PrintResult();
    void Export( string fileName ) ;

}; // class Simulation

void Simulation::PrintResult() {
	// Shows abort jobs and jobs done
	cout << "\t[Abort Jobs]\n" ;
    cout << "OID\tAbort\tDelay\n" ;
    for ( int i = 0 ; i < abortList.size() ; i++ ) {
        cout << abortList[i].ID << "\t" << abortList[i].outTime << "\t" << abortList[i].delay << "\n" ;
    } // for
    cout << "\t[Jobs Done]\n" ;
    cout << "OID\tDeparture\tDelay\n" ;
    for ( int i = 0 ; i < doneList.size() ; i++ ) {
        cout << doneList[i].ID << "\t" << doneList[i].outTime << "\t" << doneList[i].delay << "\n" ;
    } // for
    
    // CAL average delay
    float averageDelay = 0 ;
    float successRate = 0.0 ;
    for ( int i = 0 ; i < abortList.size() ; i++ )
    	averageDelay = averageDelay + abortList[i].delay ;
    for ( int i = 0 ; i < doneList.size() ; i++ )
    	averageDelay = averageDelay + doneList[i].delay ;
    	
    averageDelay = (float) averageDelay / ( abortList.size() + doneList.size() ) ;
    printf( "[Average Delay] %.2f ms\n", averageDelay ) ;
    
    // CAL success rate
    successRate = ( float ) doneList.size() / ( abortList.size() + doneList.size() ) ;
    successRate = successRate * 100 ;
    printf( "[Success Rate] %.2f %\n", successRate ) ;
    
    cout << "\n" ;
    
} // Print

void Simulation::Export( string fileName ) {
	// Export result to .txt
    FILE *outFile = NULL ;
    bool success = false ;
    fileName = "output" + fileName + ".txt" ;
    outFile = fopen( fileName.c_str(), "w" ) ;
    if ( outFile == NULL )
        ;
    else {

        fprintf( outFile, "\t[Abort Jobs]\n" ) ;
        fprintf( outFile, "OID\tAbort\tDelay\n" ) ;
        for ( int i = 0 ; i < abortList.size() ; i++ ) {
            fprintf( outFile, "%d\t%d\t%d\n", abortList.at( i ).ID, abortList.at( i ).outTime
                    , abortList.at( i ).delay ) ;
        } // for

        fprintf( outFile, "\t[Jobs Done]\n" ) ;
        fprintf( outFile, "OID\tDeparture\tDelay\n" ) ;
        for ( int i = 0 ; i < doneList.size() ; i++ ) {
            fprintf( outFile, "%d\t%d\t%d\n", doneList.at( i ).ID, doneList.at( i ).outTime
                    , doneList.at( i ).delay ) ;
        } // for

		// CAL average delay
  	  	float averageDelay = 0 ;
   		float successRate = 0.0 ;
  	  	for ( int i = 0 ; i < abortList.size() ; i++ )
    		averageDelay = averageDelay + abortList[i].delay ;
    	for ( int i = 0 ; i < doneList.size() ; i++ )
    		averageDelay = averageDelay + doneList[i].delay ;
    	
    	averageDelay = (float) averageDelay / ( abortList.size() + doneList.size() ) ;
    	fprintf( outFile, "[Average Delay] %.2f ms\n", averageDelay ) ;
    	// CAL success rate
    	successRate = ( float ) doneList.size() / ( abortList.size() + doneList.size() ) ;
    	successRate = successRate * 100 ;
    	fprintf( outFile, "[Success Rate] %.2f %\n", successRate ) ;

        success = true ;
        fclose( outFile ) ;

    } // else

}

void Simulation::ProccessArrival( Event newEvent ) {
	// Deal with arrival event
    Event tempEvent ;
    if ( workQueue.IsEmpty() ) {
        // put it into the work queue
        Job tempJob = newEvent.AEvent ;
        workQueue.EnQueue( tempJob );
        // proccess it
        tempEvent.type = 'd' ;
        tempEvent.DEvent.departure = tempJob.arrival + tempJob.duration ;
        eventList.PutEventIn( tempEvent ) ;

    } // if
    else {
        // something is in the queue
        
        if ( workQueue.Length() == 4 ) {
            // work queue is full, abort the job
            DoneJob abortOne ;
            abortOne.ID = newEvent.AEvent.ID ;
            abortOne.outTime = newEvent.AEvent.arrival ;
            abortOne.delay = 0 ;
            abortList.push_back( abortOne ) ;
        } // if
        else{
            // put it into the queue
            Job tempJob = newEvent.AEvent ;
            workQueue.EnQueue( tempJob );

        } // else

    } // else

    // take another job into event list
    if ( !jobQueue.IsEmpty() ) {
        tempEvent.type = 'a' ;
        tempEvent.DEvent.departure = -1 ;
        // draw job from job queue for event
        jobQueue.DeQueue( tempEvent.AEvent ) ;
        eventList.PutEventIn( tempEvent ) ;
    } // if

} // ProccessArrival



void Simulation::ProccessDeparture( Event newEvent ) {
    // delete the job in the queue
    // check if the next job is time out
    // CAL the next job's waiting time
    // remove the departure event
    // proccess the next job
    
    Job aJob ;
    workQueue.GetFront( aJob ) ;
    int wait = 0 ;
    // check if it is time out while in cpu
    bool cpuTimeout = false ;
    if ( aJob.timeout < newEvent.DEvent.departure ) {
        // time out in CPU, abort
        cpuTimeout = true ;
        DoneJob abortOne ;
        abortOne.ID = aJob.ID ;
        abortOne.outTime = newEvent.DEvent.departure ;
        abortOne.delay = abortOne.outTime - aJob.arrival ;
        abortList.push_back( abortOne ) ;
        // hold the new departure time
        int lastTimeout = aJob.timeout ;
        // remove from running section
        workQueue.DeQueue() ;
        // CAL the wait of next job
        if ( !workQueue.IsEmpty() ) {
    		workQueue.GetFront( aJob ) ;
    		wait = lastTimeout - aJob.arrival ;
   	 		workQueue.PutWaitInFront( wait ) ;
   	 		// new departure event
   	 		Event tempEvent ;
        	tempEvent.type = 'd' ;
       	 	tempEvent.DEvent.departure = lastTimeout + aJob.duration ;
        	eventList.PutEventIn( tempEvent ) ;
   	 	} // if
        
    } // if
    else {
        // done, jobs done increase
        DoneJob doneOne ;
        doneOne.ID = aJob.ID ;
        doneOne.outTime = aJob.wait + aJob.arrival + aJob.duration ;
        doneOne.delay = aJob.wait ;
        doneList.push_back( doneOne ) ;
        // remove the job
        workQueue.DeQueue() ;
		// CAL the wait of new job
		if ( !workQueue.IsEmpty() ) {
    		workQueue.GetFront( aJob ) ;
   			wait = newEvent.DEvent.departure - aJob.arrival ;
   	 		workQueue.PutWaitInFront( wait ) ;
   	 	} // if
		// if there is still sth waiting to be executed
		// check whether it has been time out
		// if not, execute it, make new departure event
		bool gotDEvent = false ;
    	while ( !workQueue.IsEmpty() && !gotDEvent ) {
        	
        	workQueue.GetFront( aJob ) ;
        	if ( aJob.timeout < newEvent.DEvent.departure ) {
        		// find it time out while being taken from the work queue 
        		// abort it
        		DoneJob abortOne ;
      	 		abortOne.ID = aJob.ID ;
      	 		cout << aJob.ID << " in queue abort\n" ;
        		abortOne.outTime = newEvent.DEvent.departure ;
        		abortOne.delay = abortOne.outTime - aJob.arrival ;
        		abortList.push_back( abortOne ) ;
        		// remove 
        		workQueue.DeQueue() ;
        		// CAL the wait of next job
        		if ( !workQueue.IsEmpty() ) {
        			workQueue.GetFront( aJob ) ;
    				wait = newEvent.DEvent.departure - aJob.arrival ;
    				workQueue.PutWaitInFront( wait ) ;
    			} // if
        		
        	} // if
			else { 
				gotDEvent = true ;
				Event tempEvent ;
        		tempEvent.type = 'd' ;
        		tempEvent.DEvent.departure = aJob.arrival + aJob.wait +aJob.duration ;
        		eventList.PutEventIn( tempEvent ) ;
    		} // else
    	
    	} // while
    } // else



} // Proccess Departure

bool Simulation::Simulate() {
	
    string fileName ;
    cout << "File name: " ;
    cin >> fileName ;
    if ( !jobQueue.Load( fileName ) ) {
        cout << "Can not find the file.\n" ;
        return false ;
    } // if
    else {
    	// Load file success
    	// Make the first job a arrival event, put it into the event list
        Event event ;
        event.type = 'a' ;
        jobQueue.DeQueue( event.AEvent ) ;
        eventList.PutEventIn( event ) ;

        while ( !eventList.IsEmpty() ) {

            Event newEvent = eventList.Pop() ;
            if ( newEvent.type == 'a' )
                ProccessArrival( newEvent ) ;
            else
                ProccessDeparture( newEvent ) ;

        } // while

    } // else

	PrintResult() ;
    Export( fileName ) ;

    return true ;

} // Simulate

int main(){

    cout << "(0)Exit\n(1)Sort file\n(2)Simulate(still working)\n" ;
    cout << "Command: " ;
    int cmd = -1 ;
    cin >> cmd ;
    while ( cmd != 0 ) {
        if ( cmd == 1 ) {

            JobList aList ;
            string fileName ;
            cout << "file name:" ;
            cin >> fileName ;
            clock_t tLoad, tSort, tExport ;
            if ( !aList.Load( fileName, tLoad ) )
                cout << "Can not find the file.\n" ;
            else {
                aList.PrintAll() ;
                aList.Sort( tSort ) ;
                aList.Export( fileName, tExport ) ;
                float msLoad = (float)tLoad / CLOCKS_PER_SEC * 1000 ,
                      msSort = (float)tSort / CLOCKS_PER_SEC * 1000 ,
                      msExport = (float)tExport / CLOCKS_PER_SEC * 1000  ;

                printf( "Reading data: %d clocks (%.2f ms).\n", tLoad, msLoad ) ;
                printf( "Sorting data: %d clocks (%.2f ms).\n", tSort, msSort ) ;
                printf( "Writing data: %d clocks (%.2f ms).\n", tExport, msExport ) ;

                aList.PrintAll() ;
            } // else

        } // if
        else if( cmd == 2 ) {
            Simulation cpu ;
            cpu.Simulate() ;

        } // else if cmd == 2
        else
            cout << "Unknown command.\n" ;

        cout << "(0)Exit\n(1)Sort file\n(2)Simulate(still working)\n" ;
        cout << "Command: " ;
        cin >> cmd ;

    } // while

    return 0 ;

} // main()

