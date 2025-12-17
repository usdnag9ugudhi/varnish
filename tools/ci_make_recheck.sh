#!/bin/sh

find . -name test-suite.log |
xargs awk '
	/^# ERROR:/ {errs += $3}
	/^# FAIL:/ {fails += $3}
	END {exit(errs > 0 || fails >= 20)}
' &&
make VERBOSE=1 recheck
