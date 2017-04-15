#!/bin/bash

echo -n $1 | ./caseswap | ./petsciitorom | ./charstocolumns | ./columnstosines
