#!/bin/bash

strace -o lsof.strace lsof -p $@
