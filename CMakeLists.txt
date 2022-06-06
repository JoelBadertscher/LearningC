cmake_minimum_required(VERSION 3.22)
project(LearningC C)

set(CMAKE_C_STANDARD 11)

add_executable(LearningC
        BookExamples/Chapter01/celsFahr.c
        BookExamples/Chapter01/Excersise1-2.c
        BookExamples/Chapter01/helloWorld.c
        fs19_4bb2_p2/aufgabe10_yesterday.c
        fs19_4bb2_p2/aufgabe2_stackmutex.c
        fs19_4bb2_p2/aufgabe3_childrenpipe.c
        fs19_4bb2_p2/aufgabe8_vendors.c
        fs19_4bb2_p2/aufgabe8_vendors_alternative.c
        fs19_4bb2_p2/aufgabe9_signaltimer.c
        uebungen/parking.c
        uebungen/time.c)
