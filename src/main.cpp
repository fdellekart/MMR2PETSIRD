#include <iostream>
#include "PETLINKStream.h"

#define ITIME 1000  // Integration time (interval between two time tags?)

int main(int argc, char **argv) {
    auto filename = "/home/recon/Documents/Thesis-Dellekart/SIRF-STIR-PET-Reconstruction/input/1.3.12.2.1107.5.2.38.51035.30000017121607191856600000009.bf";
    PETLINKStream input_stream(filename);

    int time_from_start;  // Time since acquisition start in seconds
    unsigned long n_prompts = 0;
    unsigned long n_delayeds = 0;
    unsigned long n_singles = 0;
    unsigned long n_timetags = 0;
    unsigned long n = 0;

    while (input_stream.good()) {
        EventOrTag* next = input_stream.get_next();
        
        if (next->is_event) {
            Event* event = next->value;
            if (event->is_prompt) {
                n_prompts++;
            } else { // delayeds
                n_delayeds++;
            };
        }
        else {
            Tag* tag = next->value;
            if (tag->is_timetag) {
                n_timetags++;
                time_from_start = tag->elapsed_millis / ITIME;
            }
        }

        n++;
        if ((n_timetags % 100000) == 0) {
            std::cout << "-------------------------------------" << std::endl;
            std::cout << "Time: " << time_from_start << std::endl;
            std::cout << "Prompts: " << n_prompts << std::endl;
            std::cout << "Delayeds: " << n_delayeds << std::endl;
            std::cout << "Singles: " << n_singles << std::endl;
            std::cout << "Timetags: " << n_timetags << std::endl;
            std::cout << "Iterations: " << n << std::endl;
        }
    }

    input_stream.close();

    return 0;
}