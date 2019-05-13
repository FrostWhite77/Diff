#!/bin/bash

TOTAL_ROWS_HPP=0
for F in ./src/*.hpp; do
	TMP=`wc -l < ${F}`
	TOTAL_ROWS_HPP=$((TOTAL_ROWS_HPP + TMP))
done

TOTAL_ROWS_CPP=0
for F in ./src/*.cpp; do
	TMP=`wc -l < ${F}`
	TOTAL_ROWS_CPP=$((TOTAL_ROWS_CPP + TMP))
done

TOTAL_ROWS=$((TOTAL_ROWS_HPP + TOTAL_ROWS_CPP))

printf '%s\n' "Rows HPP Total: ${TOTAL_ROWS_HPP}"
printf '%s\n' "Rows CPP Total: ${TOTAL_ROWS_CPP}"
printf '%s\n' "Rows ALL Total: ${TOTAL_ROWS}"
