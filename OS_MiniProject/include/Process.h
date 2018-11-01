#ifndef PROCESS_H
#define PROCESS_H


/// States

#define     RUNNING     1
#define     READY       2
#define     BLOCKED     3

#define     QUANTUM     10      /// 10 seconds for example

/// ///////////////////////////////////

class Process
{
    public:
        Process();              /// create process

        /// Getters
        unsigned long getProcessID();
        char getState();
        unsigned long getPriority();
        unsigned long getArrivalTime();
        unsigned long getBurstTime();


        /// Setters
        void setProcessID(unsigned long);
        void setPriority(unsigned long);
        void setArrivalTime(unsigned long);
        void setBurstTime(unsigned long);

        /// changing states
        void Block();           /// move from RUNNING state to BLOCKED state.
        void Awaken();          /// move from BLOCKED state to READY state.
        void Switch();          /// move from RUNNING state to READY state.
        void Schedule();        /// move from READY state to RUNNING state.

        virtual ~Process();     /// terminate process

    private:
        unsigned long processID;
        char state;
        unsigned long priority;
        unsigned long arrivalTime;
        unsigned long burstTime;            /// time required for process to run.
};

#endif // PROCESS_H
