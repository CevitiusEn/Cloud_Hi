
#include <iostream>
#include <queue>
struct ThreadSolve
{
    private:
        std::queue<solve*>* puzzle_qe=nullptr;
        std::queue<solve*>* print_qe=nullptr;
        bool work_flag=true;


    public:
        ThreadSolve()
        {
            puzzle_qe = new std::queue<solve*>;
            print_qe=new std::queue<solve*>;
        };

        void start();

        void append(solve*);

        void addThread(solve*);

        void stop();


        std::queue<solve*>* get_queue() {return puzzle_qe;};


       ~ThreadSolve()
       {
           delete puzzle_qe;
           delete print_qe;
       }
};