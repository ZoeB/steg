#!/bin/sh

echo 'Test\c' | ./caseswap | ./charstocolumns | ./fontread
