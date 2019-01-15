# @Author: Cody Craig <codycraig>
# @Date:   08-Jan-2019, 5:21:07 pm
# @Email:  cody.craig500@gmail.com
# @Filename: testCount.sh
# @Last modified by:   codycraig
# @Last modified time: 14-Jan-2019, 9:40:23 pm

# bash

TEST_DATA_FOLDER=$(pwd)/test_data
OUTPUT_FOLDER=$(pwd)/output

make

testProgram()
{
    # Remove old program output
    rm -rf $OUTPUT_FOLDER/$3

    # Run the program with the provided parameters
    ./count $TEST_DATA_FOLDER/$1 "$2" $OUTPUT_FOLDER/$3

    # Compare output files
    if [ -n "$(cmp $OUTPUT_FOLDER/$3 $OUTPUT_FOLDER/expected/$3)" ]
    then
        echo "WARNING: Files are different $3"
    else
        echo "SAME! $3"
    fi
}

testProgram example1 "Sly Fox" example1_fox
testProgram example1 the example1_the
testProgram example2 tomato example2_tomato
testProgram example2 potato example2_potato
testProgram example3 the example3_the
testProgram example3 "I want" example3_want
testProgram example3 "I want to" example3_want_to
testProgram example4 $'f\xA' example4
testProgram foo CDEFGHIJSTUVWXYZ fooOut
