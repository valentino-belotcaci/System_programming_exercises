#!/bin/bash

exec "$1" ciao | sort
exit ${PIPESTATUS[0]}


