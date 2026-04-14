#!/bin/bash

exec "$1" ciao oaic | sort
exit ${PIPESTATUS[0]}


