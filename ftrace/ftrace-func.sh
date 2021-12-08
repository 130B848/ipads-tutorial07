#!/bin/bash

dir=/sys/kernel/debug/tracing

sysctl kernel.ftrace_enabled=1

echo function > ${dir}/current_tracer

echo 1 > ${dir}/tracing_on

$@

echo 0 > ${dir}/tracing_on

less ${dir}/trace
