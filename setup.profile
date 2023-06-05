#!/usr/bin/env bash
#
# source this file to setup project
#
(return 0 2>/dev/null) && SOURCED=1 || SOURCED=0
if [[ ${SOURCED} == 0 ]]; then
  echo "Don't run $0, source it" >&2
  exit 1
fi

TITLE="Environment setup for C/C++ Memory Management"
export ACTION

#-------------------------------------------------------------------------------
# Display current project "title"
if [[ "${ACTION}" == add ]]; then
  Report_info "${TITLE}"
fi

# vim:nospell
