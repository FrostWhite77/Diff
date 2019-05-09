#!/bin/bash

TOTAL_ROWS=0

for F in ./src/*; do
	TMP=`wc -l < ${F}`
	# printf '%s %s\n' "${F}:" "${TMP} lines"
	TOTAL_ROWS=$((TOTAL_ROWS + TMP))
done

# printf '%s\n' "============================================"
printf '%s\n' "Rows Total: ${TOTAL_ROWS}"
