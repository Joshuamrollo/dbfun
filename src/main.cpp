#include <cassert>
#include <iostream>
#include "klikedb/core/front_end/FrontEnd.h"

int main() {
    klikedb::Catalog catalog; 
    klikedb::IOManager io_manager;
    klikedb::BufferManager buffer_mgr(io_manager, 64 * 1024);  
    klikedb::ExecutionEngine exec_engine(buffer_mgr); 
    klikedb::QueryScheduler scheduler(exec_engine); 
    klikedb::Binder binder(catalog);
    klikedb::Rewriter rewriter;
    klikedb::Optimizer optimizer;
    klikedb::QueryPlanner planner(scheduler, binder, rewriter, optimizer); 
    klikedb::FrontEnd front_end(planner); 

    while (true) {
        std::string input;
        std::cout << "db> ";
        std::getline(std::cin, input);
        if (input == "exit" || input == "quit") break;

        front_end.processQuery(input);  // handles full lifecycle
    }
}

