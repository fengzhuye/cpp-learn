#!/bin/bash
g++ my_class.cpp -fPIC -shared -z defs -o libmy_class.so
g++ main.cpp -fPIC -ldl
