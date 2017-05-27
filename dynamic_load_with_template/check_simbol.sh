#!/bin/bash
nm -C -A libmy_class.so | grep "Blast"
nm -C -A a.out | grep "Blast"
