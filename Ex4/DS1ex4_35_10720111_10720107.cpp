// 10720111 陳少暉 10720107 陳丕中

#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<ctime>

using namespace std ;

struct Job {

    // 每個工作所帶有的資料
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
    // 存放工作的清單

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
    // Export sorted job list to .txt

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
    // 用shell sort將其變為從小到大排序
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
    // 讀檔
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
    // 讀檔
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

    if ( !IsEmpty() )
        frontPtr->aJob.wait = wait ;

} //

void JobQueue::Print() {

    cout << "OID\tArrival\tDuration\tTimeOut\n" ;
    for ( QueueNode *walk = frontPtr ; walk != NULL ; walk = walk->next ) {
        cout << walk->aJob.ID << "\t" <<  walk->aJob.arrival << "\t" ;
        cout <<  walk->aJob.duration << "\t" <<  walk->aJob.timeout << "\n" ;
    } // for
    cout << "\n" ;

}

bool JobQueue::Load( string fileName ) {

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

void JobQueue::EnQueue ( Job newJob ) { // enQueue() 新增
   // 將東西放入queue
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

void JobQueue::DeQueue () { // deQueue 移除
    // 將東西拿出queue

	if ( IsEmpty() ) {
		printf( "is Empty!") ;
	} // if
	else {
	    QueueNode * tempPtr = frontPtr ;
	    if ( frontPtr == backPtr ) {
	    	frontPtr = NULL ;
	    	backPtr = NULL ;
	    } // if
	    else {
	    	frontPtr = frontPtr->next ;
	    } // else

	    tempPtr->next = NULL ;
    	delete tempPtr ;
    	length--;
    } // else

} //deQueue()

void JobQueue::GetFront ( Job &aJob ) { // getFront() 擷取
    // 看queue最前面是什麼

	if ( IsEmpty() )
	    printf("is Empty!!") ;

    else
        aJob = frontPtr->aJob ;

} // getFront()

void JobQueue::GetBack( Job &aJob ) {
    if ( IsEmpty() )
        cout << "There is nothing.\n" ;
    else
        aJob = backPtr->aJob ;
} // GetBack

void JobQueue::DeQueue( Job &aJob ) { // deQueue() 擷取後刪除
    if( IsEmpty() ) {
    	printf("is Empty!") ;
	} // if
	else {
		aJob = frontPtr->aJob ;
		DeQueue() ;
	} // else

} // 擷取後刪除

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

    Event tempEvent = eventList->event ;
    EventNode* tempNode = eventList ;
    eventList = eventList->next ;
    delete tempNode ;
    return tempEvent ;

} // Pop

void EventList::PutEventIn( Event newEvent ) {

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

    JobQueue jobQueue ;
    JobQueue workQueue ;
    EventList eventList ;
    vector<DoneJob> abortList ;
    vector<DoneJob> doneList ;

    public:

    bool Simulate() ;
    void ProccessArrival( Event newEvent ) ;
    void ProccessDeparture( Event newEvent ) ;
    void PrintDoneList() ;
    void PrintAbortList() ;
    void Export( string fileName ) ;

}; // class Simulation

void Simulation::Export( string fileName ) {

    FILE *outFile = NULL ;
    bool success = false ;
    fileName = "output" + fileName + ".txt" ;
    outFile = fopen( fileName.c_str(), "w" ) ;
    if ( outFile == NULL )
        ;
    else {

        fprintf( outFile, "\tAbort Jobs\n" ) ;
        fprintf( outFile, "OID\tAbort\tDelay\n" ) ;
        for ( int i = 0 ; i < abortList.size() ; i++ ) {
            fprintf( outFile, "%d\t%d\t%d\n", abortList.at( i ).ID, abortList.at( i ).outTime
                    , abortList.at( i ).delay ) ;
        } // for

        fprintf( outFile, "\tJobs Done\n" ) ;
        fprintf( outFile, "OID\tDeparture\tDelay\n" ) ;
        for ( int i = 0 ; i < doneList.size() ; i++ ) {
            fprintf( outFile, "%d\t%d\t%d\n", doneList.at( i ).ID, doneList.at( i ).outTime
                    , doneList.at( i ).delay ) ;
        } // for

        success = true ;
        fclose( outFile ) ;

    } // else

}

void Simulation::PrintAbortList() {

    cout << "\tAbort Jobs\n" ;
    cout << "OID\tAbort\tDelay\n" ;
    for ( int i = 0 ; i < abortList.size() ; i++ ) {
        cout << abortList[i].ID << "\t" << abortList[i].outTime << "\t" << abortList[i].delay << "\n" ;
    } // for

} // PrintAbort

void Simulation::PrintDoneList() {

    cout << "\tJobs Done\n" ;
    cout << "OID\tDeparture\tDelay\n" ;
    for ( int i = 0 ; i < doneList.size() ; i++ ) {
        cout << doneList[i].ID << "\t" << doneList[i].outTime << "\t" << doneList[i].delay << "\n" ;
    } // for

} // Print Done

void Simulation::ProccessArrival( Event newEvent ) {

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
        if ( workQueue.Length() == 3 ) {
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

    // check if it is time out
    Job aJob ;
    workQueue.GetFront( aJob ) ;
    // if it is time out before it it done
    if ( aJob.timeout < newEvent.DEvent.departure ) {
        // abort
        workQueue.DeQueue() ;
        DoneJob abortOne ;
        abortOne.ID = aJob.ID ;
        abortOne.outTime = newEvent.DEvent.departure ;
        abortOne.delay = abortOne.outTime - aJob.arrival ;
        abortList.push_back( abortOne ) ;
    } // if
    else {
        // it is done
        DoneJob doneOne ;
        doneOne.ID = aJob.ID ;
        doneOne.outTime = aJob.wait + aJob.arrival + aJob.duration ;
        doneOne.delay = aJob.wait ;
        doneList.push_back( doneOne ) ;
        // remove the job
        workQueue.DeQueue() ;
        // CAL the wait of new job
        workQueue.GetFront( aJob ) ;
        int wait = newEvent.DEvent.departure - aJob.arrival ;
        workQueue.PutWaitInFront( wait ) ;
    } // else

    if ( !workQueue.IsEmpty() ) {
        // proccess new departure
        Event tempEvent ;
        workQueue.GetFront( aJob ) ;
        tempEvent.type = 'd' ;
        tempEvent.DEvent.departure = aJob.arrival + aJob.wait +aJob.duration ;
        eventList.PutEventIn( tempEvent ) ;
    } // if

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

    PrintDoneList() ;
    PrintAbortList() ;
    Export( fileName ) ;

    return true ;

} // Simulate

int main(){

    cout << "(0)Exit\n(1)Sort file\n(2)Simulate(not yet)\n" ;
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

        cout << "(0)Exit\n(1)Sort file\n(2)Simulate(not yet)\n" ;
        cout << "Command: " ;
        cin >> cmd ;

    } // while

    return 0 ;

} // main()

