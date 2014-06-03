/**
*\file
*\brief timer
* Zawiera fukcje programu liczaca czas przeszukiwania poszczegolnych pomiarow.
* 
*/


#include "graf.h"
#include "przeszukiwanie.h"
#include <iostream>
#include <chrono>

   void timer(Graf& cos, int rozpoczecie, int zakonczenie, std::ostream& out) {

std::chrono::time_point<std::chrono::system_clock> start, end;

std::chrono::duration<double> elapsed_time(0);

start=std::chrono::system_clock::now();
list=breadth_first(cos, rozpoczecie, zakonczenie);
end=std::chrono::system_clock::now();
elapsed_time = end-start;
out << "BREADTH-FIRST time: " << elapsed_time.count()  << "s. ";
for( auto t : list ) std::cerr << t << " -> "; std::cerr << "\n";


start=std::chrono::system_clock::now();
auto list=depth_first(cos, rozpoczecie, zakonczenie);
end = std::chrono::system_clock::now();
elapsed_time = end-start;
out << "DEPTH-FIRST time: " << elapsed_time.count()  << "s. ";
for( auto t : list ) std::cerr << t << " -> "; std::cerr << "\n";


start=std::chrono::system_clock::now();
list=a_star(cos, rozpoczecie, zakonczenie );
end=std::chrono::system_clock::now();
elapsed_time = end-start;
out << "A* time: " << elapsed_time.count()  << "s. ";
for( auto t : list ) std::cerr << t << " -> "; std::cerr << "\n";

}
