#!/bin/bash

BOLD='\033[1m'
RED='\033[1;31m'
GREEN='\033[1;32m'
BLUE='\033[1;34m'
RESET='\033[0m'

# Add counters for test statistics
TOTAL_TESTS=0
PASSED_TESTS=0

# Set number of parallel jobs (adjust as needed for your system)
PARALLEL_JOBS=8

MYSHELL="$PWD/42sh"
REFER="/bin/tcsh -f"
TRAPSIG=0

CAT=`which cat`
GREP=`which grep`
SED=`which sed`
RM=`which rm`
TR=`which tr`
HEAD=`which head`
TAIL=`which tail`
WC=`which wc`
CHMOD=`which chmod`
EXPR=`which expr`
MKDIR=`which mkdir`
CP=`which cp`

for i in `env | grep BASH_FUNC_ | cut -d= -f1`; do
    f=`echo $i | sed s/BASH_FUNC_//g | sed s/%%//g`
    unset -f $f
done

# Create temp directory for parallel test outputs
TEMP_DIR=$(mktemp -d /tmp/minishell_tests.XXXXXX)
RESULTS_FILE="$TEMP_DIR/results.txt"

disp_test()
{
  id=$1
  $CAT tests/tests.sample | $GREP -A1000 "\[$id\]" | $GREP -B1000 "^\[$id-END\]" | $GREP -v "^\[.*\]"
}

run_script()
{
  SC="$1"
  echo "$SC" > /tmp/.tmp.$$
  . /tmp/.tmp.$$
  $RM -f /tmp/.tmp.$$
}

prepare_test()
{
  local testfn="$TEMP_DIR/.tester.$id"
  local runnerfn="$TEMP_DIR/.runner.$id"
  local refoutfn="$TEMP_DIR/.refer.$id"
  local shoutfn="$TEMP_DIR/.shell.$id"

  # Get the appropriate reference shell for this test
  local ref_shell=$(get_reference_shell "$id")

  WRAPPER="$runnerfn"

  echo "#!/bin/bash" > $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "/bin/bash -c '"$testfn" | "$MYSHELL" ; echo Shell exit with code \$?' > "$shoutfn" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "$TCSHUPDATE" >> $runnerfn
  echo "/bin/bash -c '"$testfn" | "$ref_shell" ; echo Shell exit with code \$?' > "$refoutfn" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn

  echo "#!/bin/bash" > $testfn
  echo "$TESTS" | $TR "²" "\n" >> $testfn

  chmod 755 $testfn
  chmod 755 $runnerfn
}

# Determine which shell to use as reference for a specific test
get_reference_shell()
{
  local test_id="$1"
  
  # Use bash for the tests that tcsh doesn't support
  if [[ "$test_id" -ge 274 && "$test_id" -le 318 ]]; then
    echo "/bin/bash"
  else
    # Use tcsh for everything else
    echo "/bin/tcsh -f"
  fi
}

load_test()
{
  id=$1
  debug=$2
  SETUP=`disp_test "$id" | $GREP "SETUP=" | $SED s/'SETUP='// | $SED s/'"'//g`
  CLEAN=`disp_test "$id" | $GREP "CLEAN=" | $SED s/'CLEAN='// | $SED s/'"'//g`
  NAME=`disp_test "$id" | $GREP "NAME=" | $SED s/'NAME='// | $SED s/'"'//g`
  TCSHUPDATE=`disp_test "$id" | $GREP "TCSHUPDATE=" | $SED s/'TCSHUPDATE='// | $SED s/'"'//g`
  TESTS=`disp_test "$id" | $GREP -v "SETUP=" | $GREP -v "CLEAN=" | $GREP -v "NAME=" | $GREP -v "TCSHUPDATE=" | $GREP -v "TESTS=" | $TR "\n" "²" | $SED s/"²$"//`
  prepare_test
  $WRAPPER
  nb=`$CAT $TEMP_DIR/.refer.$id | $GREP -v '^_=' | $GREP -v '^\[1\]' | $WC -l`
  i=1
  ok=1
  while [ $i -le $nb ]
  do
    l=`$CAT $TEMP_DIR/.refer.$id | $GREP -v '^_=' | $GREP -v '^\[1\]' | $HEAD -$i | $TAIL -1`
    a=`$CAT $TEMP_DIR/.shell.$id | $GREP -v '^_=' | $GREP -v '^\[1\]' | $GREP -- "$l$" | $WC -l`
    if [ $a -eq 0 ]
    then
      ok=0
    fi
    i=`$EXPR $i + 1`
  done

  if [ $ok -eq 1 ]
  then
    if [ $debug -ge 1 ]
    then
      printf "${BOLD}Test $id${RESET} → $NAME: %*s${GREEN}OK${RESET}\n" $((55 - ${#NAME} - ${#id} - 5)) ""
      if [ $debug -eq 2 ]
      then
        echo "Output $MYSHELL :"
        $CAT -e $TEMP_DIR/.shell.$id
        echo ""
        echo "Output $REFER :"
        $CAT -e $TEMP_DIR/.refer.$id
        echo ""
      fi
    else
      echo "OK"
    fi
    PASSED_TESTS=$((PASSED_TESTS + 1))
  else
    if [ $debug -ge 1 ]
    then
      printf "${BOLD}Test $id${RESET} → $NAME: %*s${RED}KO${RESET} - Check output in /tmp/test.$$/$id/\n" $((55 - ${#NAME} - ${#id} - 5)) ""
      $MKDIR -p /tmp/test.$$/$id 2>/dev/null
      $CP $TEMP_DIR/.shell.$id /tmp/test.$$/$id/mysh.out
      $CP $TEMP_DIR/.refer.$id /tmp/test.$$/$id/tcsh.out
    else
      echo "KO"
    fi
  fi
  TOTAL_TESTS=$((TOTAL_TESTS + 1))
}

load_test_parallel()
{
  id=$1
  debug=$2
  SETUP=`disp_test "$id" | $GREP "SETUP=" | $SED s/'SETUP='// | $SED s/'"'//g`
  CLEAN=`disp_test "$id" | $GREP "CLEAN=" | $SED s/'CLEAN='// | $SED s/'"'//g`
  NAME=`disp_test "$id" | $GREP "NAME=" | $SED s/'NAME='// | $SED s/'"'//g`
  TCSHUPDATE=`disp_test "$id" | $GREP "TCSHUPDATE=" | $SED s/'TCSHUPDATE='// | $SED s/'"'//g`
  TESTS=`disp_test "$id" | $GREP -v "SETUP=" | $GREP -v "CLEAN=" | $GREP -v "NAME=" | $GREP -v "TCSHUPDATE=" | $GREP -v "TESTS=" | $TR "\n" "²" | $SED s/"²$"//`
  prepare_test
  $WRAPPER
  nb=`$CAT $TEMP_DIR/.refer.$id | $GREP -v '^_=' | $GREP -v '^\[1\]' | $WC -l`
  i=1
  ok=1
  while [ $i -le $nb ]
  do
    l=`$CAT $TEMP_DIR/.refer.$id | $GREP -v '^_=' | $GREP -v '^\[1\]' | $HEAD -$i | $TAIL -1`
    a=`$CAT $TEMP_DIR/.shell.$id | $GREP -v '^_=' | $GREP -v '^\[1\]' | $GREP -- "$l$" | $WC -l`
    if [ $a -eq 0 ]
    then
      ok=0
    fi
    i=`$EXPR $i + 1`
  done

  # Format output directly to a temp file for this test
  if [ $ok -eq 1 ]
  then
    if [ $debug -ge 1 ]
    then
      printf "${BOLD}Test $id${RESET} → $NAME: %*s${GREEN}OK${RESET}\n" $((55 - ${#NAME} - ${#id} - 5)) "" > "$TEMP_DIR/.output.$id"
      if [ $debug -eq 2 ]
      then
        echo "Output $MYSHELL :" >> "$TEMP_DIR/.output.$id"
        $CAT -e $TEMP_DIR/.shell.$id >> "$TEMP_DIR/.output.$id"
        echo "" >> "$TEMP_DIR/.output.$id"
        echo "Output $REFER :" >> "$TEMP_DIR/.output.$id"
        $CAT -e $TEMP_DIR/.refer.$id >> "$TEMP_DIR/.output.$id"
        echo "" >> "$TEMP_DIR/.output.$id"
      fi
    else
      echo "OK" > "$TEMP_DIR/.output.$id"
    fi
    # Mark as passing test for counting later
    echo "1" > "$TEMP_DIR/.pass.$id"
  else
    if [ $debug -ge 1 ]
    then
      printf "${BOLD}Test $id${RESET} → $NAME: %*s${RED}KO${RESET} - Check output in /tmp/test.$$/$id/\n" $((55 - ${#NAME} - ${#id} - 5)) "" > "$TEMP_DIR/.output.$id"
      $MKDIR -p /tmp/test.$$/$id 2>/dev/null
      $CP $TEMP_DIR/.shell.$id /tmp/test.$$/$id/mysh.out
      $CP $TEMP_DIR/.refer.$id /tmp/test.$$/$id/tcsh.out
    else
      echo "KO" > "$TEMP_DIR/.output.$id"
    fi
    echo "0" > "$TEMP_DIR/.pass.$id"
  fi
}

# Export functions for parallel execution
export -f disp_test run_script prepare_test load_test_parallel get_reference_shell
export BOLD RED GREEN BLUE RESET
export CAT GREP SED RM TR HEAD TAIL WC CHMOD EXPR MKDIR CP
export MYSHELL REFER TRAPSIG TEMP_DIR

if [ $TRAPSIG -eq 1 ]
then
  for sig in `trap -l`
  do
    echo "$sig" | grep "^SIG" >/dev/null 2>&1
    if [ $? -eq 0 ]
    then
      trap "echo Received signal $sig !" $sig
    fi
  done
fi

if [ ! -f tests/tests.sample ]
then
  echo "No tests file. Please read README.ME" >&2
  exit 1
fi

if [ ! -f $MYSHELL ]
then
  echo "$MYSHELL not found" >&2
  exit 1
fi

if [ $# -eq 2 ]
then
  echo "Debug mode" >&2
  echo "Shell : $MYSHELL" >&2
  echo "Reference : $REFER" >&2
  echo ""
fi

# Cleanup function
cleanup() {
  # Remove any temporary files in current directory or visualize directory
  rm -f .tester.* .runner.* .refer.* .shell.* .output.*
  rm -f visualize/.tester.* visualize/.runner.* visualize/.refer.* visualize/.shell.* visualize/.output.*
  
  # Clean up our temp directory
  rm -rf "$TEMP_DIR"
}

# Set trap to clean up on exit
trap cleanup EXIT INT TERM

# Check if GNU Parallel is available
if command -v parallel > /dev/null 2>&1; then
  PARALLEL_AVAILABLE=1
else
  PARALLEL_AVAILABLE=0
  echo "GNU Parallel not found, running sequentially"
fi

# Run tests
if [ $# -eq 0 ]
then
  if [ $PARALLEL_AVAILABLE -eq 1 ]; then
    # Create a list of tests to run
    > "$TEMP_DIR/tests_list.txt"  # Initialize empty file
    for lst in `cat tests/tests.sample | grep "^\[.*\]$" | grep -vi end | sed s/'\['// | sed s/'\]'//`
    do
      echo "$lst" >> "$TEMP_DIR/tests_list.txt"
    done
    
    # Run tests in parallel
    cat "$TEMP_DIR/tests_list.txt" | parallel -j $PARALLEL_JOBS "path_backup=\$PATH; load_test_parallel {} 1; export PATH=\$path_backup"
    
    # Count and display results in test order
    TOTAL_TESTS=0
    PASSED_TESTS=0
    
    # Sort test IDs numerically if possible
    for lst in `cat "$TEMP_DIR/tests_list.txt" | sort -V`
    do
      # Increment counters
      TOTAL_TESTS=$((TOTAL_TESTS + 1))
      if [ -f "$TEMP_DIR/.pass.$lst" ]; then
        PASS_STATUS=`cat "$TEMP_DIR/.pass.$lst"`
        if [ "$PASS_STATUS" = "1" ]; then
          PASSED_TESTS=$((PASSED_TESTS + 1))
        fi
      fi
      
      # Print test output if available
      if [ -f "$TEMP_DIR/.output.$lst" ]; then
        cat "$TEMP_DIR/.output.$lst"
      fi
    done
  else
    # Run sequentially as before
    for lst in `cat tests/tests.sample | grep "^\[.*\]$" | grep -vi end | sed s/'\['// | sed s/'\]'//`
    do
      path_backup=$PATH
      load_test $lst 1
      export PATH=$path_backup
    done
  fi
else
  if [ $# -eq 1 ]
  then
    load_test $1 0
  else
    if [ "X$1" = "X-d" ]
    then
      load_test $2 2
    else
      load_test $1 2
    fi
  fi
fi

# Display test summary with percentage
if [ $TOTAL_TESTS -gt 0 ]; then
  # Calculate percentage (using bc for floating point)
  if command -v bc > /dev/null; then
    PERCENTAGE=$(echo "scale=2; ($PASSED_TESTS * 100) / $TOTAL_TESTS" | bc)
    # Remove decimal part for comparison
    PERCENTAGE_INT=${PERCENTAGE%.*}
  else
    # Fallback to integer calculation if bc is not available
    PERCENTAGE=$(( ($PASSED_TESTS * 100) / $TOTAL_TESTS ))
    PERCENTAGE_INT=$PERCENTAGE
  fi
  
  # Choose color based on percentage
  if [ $PERCENTAGE_INT -lt 50 ]; then
    COLOR=$RED
  else
    COLOR=$GREEN
  fi
  
  echo -e "============================"
  echo -e "Passed: ${BOLD}$PASSED_TESTS/$TOTAL_TESTS${RESET} tests (${COLOR}$PERCENTAGE%${RESET})"
  echo -e "============================"
else
  echo -e "\n${BOLD}No tests were executed!${RESET}"
fi
