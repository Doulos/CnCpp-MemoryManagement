#!/usr/bin/env bash
#
# source this file to setup project
#
(return 0 2>/dev/null) && SOURCED=1 || SOURCED=0
if [[ ${SOURCED} == 0 ]]; then
  echo "Don't run $0, source it" >&2
  exit 1
fi

function Realpath()
{
  if [[ $# == 0 ]]; then set - .; fi
  # shellcheck disable=SC2016
  local PERLSCRIPT='$p=abs_path(join(q( ),@ARGV));print $p if -e $p'
  /usr/bin/env perl '-MCwd(abs_path)' -le "${PERLSCRIPT}" "$*"
}

export ACTION

function Project_setup()
{
  # @brief does the real work of setup
  export ACTION
  if [[ "$2" =~ --rm || "${ACTION}" == "rm" ]]; then
    ACTION="rm"
    Remove_path PATH "${PROJECT_BIN}"
  else
    ACTION="add"
    SETUP_PATH="$(Realpath "$1")"
    PROJECT_DIR="$(dirname "${SETUP_PATH}")"
    PROJECT_NAME="$(basename "${PROJECT_DIR}")"
    PROJECT_BIN="${PROJECT_DIR}/extern/bin"
    # shellcheck disable=SC1091
    source "${PROJECT_DIR}/extern/bin/Essential-IO"
    # shellcheck disable=SC1091
    source "${PROJECT_DIR}/extern/bin/Essential-manip"

    Prepend_path PATH "${PROJECT_BIN}"

    export ACTION PROJECT_NAME SETUP_PATH PROJECT_DIR
    echo "$1: ${PROJECT_NAME} environment set up"
  fi
}

function Check_version()
{
  # @brief return the version of tool
  local version
  if command -v "$1" 1>/dev/null 2>&1; then
    echo -n "$1 "
    version="$1 $(command "$1" --version)"
    # shellcheck disable=SC2312
    perl -e 'printf qq{%s\n},$& if "@ARGV" =~ m{\b[1-9]+([.][0-9]+)+}' "${version}"
  fi
}

function Check_environment()
{
  # @brief test for a few critical bits
  # - Only invoked if -v is passed when sourcing
  export PROJECT_DIR
  cd "${PROJECT_DIR}" 2>/dev/null || return 1
  Reset-errors
  local dir
  for dir in cmake extern; do
    if [[ ! -d "${PROJECT_DIR}/${dir}" ]]; then
      Report_warning "Missing ${dir}/ directory -- suspicious"
    fi
  done
  # What tools are available
  local tool version
  for tool in make ninja cmake ctest; do
    Check_version "${tool}"
  done
}

if [[ "$0" =~ sh$ ]]; then
  Project_setup "setup.profile" "$@"
else
  Project_setup "$0" "$@"
fi
if [[ "$1" == "-v" ]]; then
  ( Check_environment )
  Summary setup.profile
fi

# vim:nospell
