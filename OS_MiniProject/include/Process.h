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
        double getPriority();
        double getArrivalTime();
        double getBurstTime();


        /// Setters
        void setProcessID(unsigned long);
        void setPriority(double);
        void setArrivalTime(double);
        void setBurstTime(double);

        /// changing states
        void Block();           /// move from RUNNING state to BLOCKED state.
        void Awaken();          /// move from BLOCKED state to READY state.
        void Switch();          /// move from RUNNING state to READY state.
        void Schedule();        /// move from READY state to RUNNING state.

        virtual ~Process();     /// terminate process

    private:
        unsigned long processID;
        char state;
        double priority;
        double arrivalTime;
        double burstTime;            /// time required for process to run.
};

#endif // PROCESS_H
