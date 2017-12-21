#!/bin/sh
# executed by: /bin/bash PA2_grader.sh

gcc -o check_thread ./check_thread.c
gcc -o check_sorting ./check_sorting.c

cp sorter "./test1/test1.1"
cp sorter "./test1/test1.2"
cp sorter "./test2/test2.1"
cp sorter "./test2/test2.2"
cp sorter "./test3/test3.1"
cp sorter "./test4/test4.1"
cp sorter "./test5/test5.2"
cp sorter "./test6/test6.1"



echo -e "\n###############################################################################"
echo -e "########################## TEST 1: Basic test #################################"
echo -e "\n*** test1.1  15pts: sorting by movie_title, with -c, -d, -o, involving a few sub-directories, each contains a few files ***"

############# reset value ############
real_threads_number=10   # reset value to handle special case
real_movies_num=140      # reset value to handle special case
######################################

score_test_1_1=0
column_item="movie_title"
input_dir="./test1/test1.1"
output_dir="./collections_for_output_files/output1/output1.1"

# obtain the final single output file
$input_dir/sorter -c $column_item -d $input_dir -o $output_dir

# check whether the reported number of threads is correct
echo -e "\n"
echo -n "Enter the reported number of threads and press [ENTER]: "
read reported_threads_number
if [ $reported_threads_number -eq $real_threads_number ]; then
    echo -e "The reported number of threads is correct.\n"
    ((score_test_1_1+=5))
else
    echo -e "The reported number of threads is incorrect.\n"
fi

final_sorted_file="$output_dir/AllFiles-sorted-$column_item.csv"
if [ -f "$final_sorted_file" ]; then 
    
    # check whether all files are integrated (a potential test for mutex synchronization)
    reported_movies_num=$(cat $final_sorted_file | ./check_thread)
    echo -e "The total number of movies in the integrated file is $reported_movies_num"
    
    if [ $reported_movies_num -eq $real_movies_num ]; then
        echo -e "The total number of movies in the integrated file is correct.\n"
        ((score_test_1_1+=5))  
    else
        echo -e "The total number of movies in the integrated file is incorrect. Might miss file or need mutex during caching.\n"
    fi
    
    # check whether the final single output file is correctly sorted
    cat $final_sorted_file | ./check_sorting -c $column_item
    return_code=$(echo $?)
    echo -e "The return code is $return_code"
    
    if [ $return_code -eq 0 ]; then
        echo -e "The final output file is fully correctly sorted.\n"
        ((score_test_1_1+=5))  
    else
        echo -e "The final output file is not fully correctly sorted.\n"
        ((score_test_1_1+=2))
    fi
else
	echo -e "Can not find the final output file."
fi

echo -e "########### Score for test1_1 = $score_test_1_1 ###############\n"


###############################################################################################################################################
echo -e "\n*** test1.2  15pts: sorting by movie_title, with -c, -d, -o, involving a few sub-directories, but some of them contains no file ***"

############# reset value ############
real_threads_number=8    # reset value to handle special case
real_movies_num=100      # reset value to handle special case
######################################

score_test_1_2=0
column_item="movie_title"
input_dir="./test1/test1.2"
output_dir="./collections_for_output_files/output1/output1.2"

# obtain the final single output file
$input_dir/sorter -c $column_item -d $input_dir -o $output_dir

# check whether the reported number of threads is correct
echo -e "\n"
echo -n "Enter the reported number of threads and press [ENTER]: "
read reported_threads_number
if [ $reported_threads_number -eq $real_threads_number ]; then
    echo -e "The reported number of threads is correct.\n"
    ((score_test_1_2+=5))
else
    echo -e "The reported number of threads is incorrect.\n"
fi

final_sorted_file="$output_dir/AllFiles-sorted-$column_item.csv"
if [ -f "$final_sorted_file" ]; then 
    
    # check whether all files are integrated (a potential test for mutex synchronization)
    reported_movies_num=$(cat $final_sorted_file | ./check_thread)
    echo -e "The total number of movies in the integrated file is $reported_movies_num"
    
    if [ $reported_movies_num -eq $real_movies_num ]; then
        echo -e "The total number of movies in the integrated file is correct.\n"
        ((score_test_1_2+=5))  
    else
        echo -e "The total number of movies in the integrated file is incorrect. Might miss file or need mutex during caching.\n"
    fi
    
    # check whether the final single output file is correctly sorted
    cat $final_sorted_file | ./check_sorting -c $column_item
    return_code=$(echo $?)
    echo -e "The return code is $return_code"
    
    if [ $return_code -eq 0 ]; then
        echo -e "The final output file is fully correctly sorted.\n"
        ((score_test_1_2+=5))  
    else
        echo -e "The final output file is not fully correctly sorted.\n"
        ((score_test_1_2+=2))
    fi
else
	echo -e "Can not find the final output file."
fi

echo -e "########### Score for test1_2 = $score_test_1_2 ###############\n"


echo -e "\n###############################################################################"
echo -e "################## TEST 2: Test for directory structure #######################"
echo -e "\n*** test2.1  10pts: sorting by movie_title, with -c, -d, -o, involving long sub-directory chain, each contains only one file ***"

############# reset value ############
real_threads_number=32   # reset value to handle special case
real_movies_num=320      # reset value to handle special case
######################################

score_test_2_1=0
column_item="movie_title"
input_dir="./test2/test2.1"
output_dir="./collections_for_output_files/output2/output2.1"

# obtain the final single output file
$input_dir/sorter -c $column_item -d $input_dir -o $output_dir

# check whether the reported number of threads is correct
echo -e "\n"
echo -n "Enter the reported number of threads and press [ENTER]: "
read reported_threads_number
if [ $reported_threads_number -eq $real_threads_number ]; then
    echo -e "The reported number of threads is correct.\n"
    ((score_test_2_1+=4))
else
    echo -e "The reported number of threads is incorrect.\n"
fi

final_sorted_file="$output_dir/AllFiles-sorted-$column_item.csv"
if [ -f "$final_sorted_file" ]; then 
    
    # check whether all files are integrated (a potential test for mutex synchronization)
    reported_movies_num=$(cat $final_sorted_file | ./check_thread)
    echo -e "The total number of movies in the integrated file is $reported_movies_num"
    
    if [ $reported_movies_num -eq $real_movies_num ]; then
        echo -e "The total number of movies in the integrated file is correct.\n"
        ((score_test_2_1+=4))  
    else
        echo -e "The total number of movies in the integrated file is incorrect. Might miss file or need mutex during caching.\n"
    fi
    
    # check whether the final single output file is correctly sorted
    cat $final_sorted_file | ./check_sorting -c $column_item
    return_code=$(echo $?)
    echo -e "The return code is $return_code"
    
    if [ $return_code -eq 0 ]; then
        echo -e "The final output file is fully correctly sorted.\n"
        ((score_test_2_1+=2))  
    else
        echo -e "The final output file is not fully correctly sorted.\n"
    fi
else
	echo -e "Can not find the final output file."
fi

echo -e "########### Score for test2_1 = $score_test_2_1 ###############\n"


###############################################################################################################################################
echo -e "\n*** test2.2  10pts: sorting by movie_title, with -c, -d, -o, involving long sub-directory chain, some contain only one file, others contain no file ***"

############# reset value ############
real_threads_number=24   # reset value to handle special case
real_movies_num=160      # reset value to handle special case
######################################

score_test_2_2=0
column_item="movie_title"
input_dir="./test2/test2.2"
output_dir="./collections_for_output_files/output2/output2.2"

# obtain the final single output file
$input_dir/sorter -c $column_item -d $input_dir -o $output_dir

# check whether the reported number of threads is correct
echo -e "\n"
echo -n "Enter the reported number of threads and press [ENTER]: "
read reported_threads_number
if [ $reported_threads_number -eq $real_threads_number ]; then
    echo -e "The reported number of threads is correct.\n"
    ((score_test_2_2+=4))
else
    echo -e "The reported number of threads is incorrect.\n"
fi

final_sorted_file="$output_dir/AllFiles-sorted-$column_item.csv"
if [ -f "$final_sorted_file" ]; then 
    
    # check whether all files are integrated (a potential test for mutex synchronization)
    reported_movies_num=$(cat $final_sorted_file | ./check_thread)
    echo -e "The total number of movies in the integrated file is $reported_movies_num"
    
    if [ $reported_movies_num -eq $real_movies_num ]; then
        echo -e "The total number of movies in the integrated file is correct.\n"
        ((score_test_2_2+=4))  
    else
        echo -e "The total number of movies in the integrated file is incorrect. Might miss file or need mutex during caching.\n"
    fi
    
    # check whether the final single output file is correctly sorted
    cat $final_sorted_file | ./check_sorting -c $column_item
    return_code=$(echo $?)
    echo -e "The return code is $return_code"
    
    if [ $return_code -eq 0 ]; then
        echo -e "The final output file is fully correctly sorted.\n"
        ((score_test_2_2+=2))  
    else
        echo -e "The final output file is not fully correctly sorted.\n"
    fi
else
	echo -e "Can not find the final output file."
fi

echo -e "########### Score for test2_2 = $score_test_2_2 ###############\n"


echo -e "\n###############################################################################"
echo -e "################## TEST 3: Test for file amount #######################"
echo -e "\n*** test3.1  10pts: sorting by movie_title, with -c, -d, -o, involving only one directory (one layer), which contains lots of files ***"

############# reset value ############
real_threads_number=17   # reset value to handle special case
real_movies_num=320      # reset value to handle special case
######################################

score_test_3_1=0
column_item="movie_title"
input_dir="./test3/test3.1"
output_dir="./collections_for_output_files/output3/output3.1"

# obtain the final single output file
$input_dir/sorter -c $column_item -d $input_dir -o $output_dir

# check whether the reported number of threads is correct
echo -e "\n"
echo -n "Enter the reported number of threads and press [ENTER]: "
read reported_threads_number
if [ $reported_threads_number -eq $real_threads_number ]; then
    echo -e "The reported number of threads is correct.\n"
    ((score_test_3_1+=4))
else
    echo -e "The reported number of threads is incorrect.\n"
fi

final_sorted_file="$output_dir/AllFiles-sorted-$column_item.csv"
if [ -f "$final_sorted_file" ]; then 
    
    # check whether all files are integrated (a potential test for mutex synchronization)
    reported_movies_num=$(cat $final_sorted_file | ./check_thread)
    echo -e "The total number of movies in the integrated file is $reported_movies_num"
    
    if [ $reported_movies_num -eq $real_movies_num ]; then
        echo -e "The total number of movies in the integrated file is correct.\n"
        ((score_test_3_1+=4))  
    else
        echo -e "The total number of movies in the integrated file is incorrect. Might miss file or need mutex during caching.\n"
    fi
    
    # check whether the final single output file is correctly sorted
    cat $final_sorted_file | ./check_sorting -c $column_item
    return_code=$(echo $?)
    echo -e "The return code is $return_code"
    
    if [ $return_code -eq 0 ]; then
        echo -e "The final output file is fully correctly sorted.\n"
        ((score_test_3_1+=2))  
    else
        echo -e "The final output file is not fully correctly sorted.\n"
    fi
else
	echo -e "Can not find the final output file."
fi

echo -e "########### Score for test3_1 = $score_test_3_1 ###############\n"


echo -e "\n###############################################################################"
echo -e "#### TEST 4: Combination test for directory structure and file amount, with timing ####"
echo -e "\n*** test4.1  15pts: sorting by movie_title, with -c, -d, -o, combine long sub-directory and lots of files, while timing the accumulated elapsed time by executing sorter 10 times ***"

############# reset value ############
real_threads_number=272   # reset value to handle special case
real_movies_num=5120      # reset value to handle special case
######################################

score_test_4_1=0
column_item="movie_title"
input_dir="./test4/test4.1"
output_dir="./collections_for_output_files/output4/output4.1"

# obtain the final single output file
$input_dir/sorter -c $column_item -d $input_dir -o $output_dir

# check whether the reported number of threads is correct
sleep 1s # wait 1 seconds
echo -e "\n"
echo -n "Enter the reported number of threads and press [ENTER]: "
read reported_threads_number
if [ $reported_threads_number -eq $real_threads_number ]; then
    echo -e "The reported number of threads is correct.\n"
    ((score_test_4_1+=6))
else
    echo -e "The reported number of threads is incorrect.\n"
fi

final_sorted_file="$output_dir/AllFiles-sorted-$column_item.csv"
if [ -f "$final_sorted_file" ]; then 
    
    # check whether all files are integrated (a potential test for mutex synchronization)
    reported_movies_num=$(cat $final_sorted_file | ./check_thread)
    echo -e "The total number of movies in the integrated file is $reported_movies_num"
    
    if [ $reported_movies_num -eq $real_movies_num ]; then
        echo -e "The total number of movies in the integrated file is correct.\n"
        ((score_test_4_1+=5))  
    else
        echo -e "The total number of movies in the integrated file is incorrect. Might miss file or need mutex during caching.\n"
    fi
    
    # check whether the final single output file is correctly sorted
    cat $final_sorted_file | ./check_sorting -c $column_item
    return_code=$(echo $?)
    echo -e "The return code is $return_code"
    
    if [ $return_code -eq 0 ]; then
        echo -e "The final output file is fully correctly sorted.\n"
        ((score_test_4_1+=4))  
    else
        echo -e "The final output file is not fully correctly sorted.\n"
        ((score_test_4_1+=2))
    fi
else
	echo -e "Can not find the final output file."
fi


# obtain accumulated elapsed time by executing sorter for 10 times
ACCUMULATED_WALL_CLOCK_TIME=0
for i in {0..9}
do
  file_to_remove="$output_dir/AllFiles-sorted-$column_item.csv"
  rm -f file_to_remove      # delete the file if exists and does not throw an error if it is non-existing
  START_TIME=`date +%s%N`;  # it returns the seconds and current nanoseconds
  $input_dir/sorter -c $column_item -d $input_dir -o $output_dir
  END_TIME=`date +%s%N`;
  WALL_CLOCK_TIME=$((END_TIME-START_TIME))
  ((WALL_CLOCK_TIME=$WALL_CLOCK_TIME/1000000))  # elapsed time in ms
  echo "The wall clock time for $i-th run is $WALL_CLOCK_TIME ms"
  ((ACCUMULATED_WALL_CLOCK_TIME+=WALL_CLOCK_TIME))
done

echo -e "Accumulated wall clock time for test4_1 = $ACCUMULATED_WALL_CLOCK_TIME milliseconds"
echo -e "########### Score for test4_1 = $score_test_4_1 ###############\n"


echo -e "\n###############################################################################"
echo -e "#################### TEST 5: Test for input argument ##########################"
echo -e "\n*** test5.1  5pts: basic test (1.1) without -o (the default behavior should be to store the sorted file in the current directory)***"

############# reset value ############
real_threads_number=10   # reset value to handle special case
real_movies_num=140      # reset value to handle special case
######################################

score_test_5_1=0
column_item="movie_title"
input_dir="./test5/test5.1"

# obtain the final single output file
./sorter -c $column_item -d $input_dir

# check whether the reported number of threads is correct
echo -e "\n"
echo -n "Enter the reported number of threads and press [ENTER]: "
read reported_threads_number
if [ $reported_threads_number -eq $real_threads_number ]; then
    echo -e "The reported number of threads is correct.\n"
    ((score_test_5_1+=3))
else
    echo -e "The reported number of threads is incorrect.\n"
fi

final_sorted_file="AllFiles-sorted-$column_item.csv"
if [ -f "$final_sorted_file" ]; then 
    
    # check whether all files are integrated (a potential test for mutex synchronization)
    reported_movies_num=$(cat $final_sorted_file | ./check_thread)
    echo -e "The total number of movies in the integrated file is $reported_movies_num"
    
    if [ $reported_movies_num -eq $real_movies_num ]; then
        echo -e "The total number of movies in the integrated file is correct.\n"
        ((score_test_5_1+=1))  
    else
        echo -e "The total number of movies in the integrated file is incorrect. Might miss file or need mutex during caching.\n"
    fi
    
    # check whether the final single output file is correctly sorted
    cat $final_sorted_file | ./check_sorting -c $column_item
    return_code=$(echo $?)
    echo -e "The return code is $return_code"
    
    if [ $return_code -eq 0 ]; then
        echo -e "The final output file is fully correctly sorted.\n"
        ((score_test_5_1+=1))  
    else
        echo -e "The final output file is not fully correctly sorted.\n"
    fi
else
	echo -e "Can not find the final output file."
fi

echo -e "########### Score for test5_1 = $score_test_5_1 ###############\n"


###############################################################################################################################################
echo -e "\n*** test5.2  5pts: basic test (1.1) with a reversing argument order: -o, -d, -c ***"

############# reset value ############
real_threads_number=10   # reset value to handle special case
real_movies_num=140      # reset value to handle special case
######################################

score_test_5_2=0
column_item="movie_title"
input_dir="./test5/test5.2"
output_dir="./collections_for_output_files/output5/output5.2"

# obtain the final single output file
$input_dir/sorter -o $output_dir -d $input_dir -c $column_item

# check whether the reported number of threads is correct
echo -e "\n"
echo -n "Enter the reported number of threads and press [ENTER]: "
read reported_threads_number
if [ $reported_threads_number -eq $real_threads_number ]; then
    echo -e "The reported number of threads is correct.\n"
    ((score_test_5_2+=3))
else
    echo -e "The reported number of threads is incorrect.\n"
fi

final_sorted_file="$output_dir/AllFiles-sorted-$column_item.csv"
if [ -f "$final_sorted_file" ]; then 
    
    # check whether all files are integrated (a potential test for mutex synchronization)
    reported_movies_num=$(cat $final_sorted_file | ./check_thread)
    echo -e "The total number of movies in the integrated file is $reported_movies_num"
    
    if [ $reported_movies_num -eq $real_movies_num ]; then
        echo -e "The total number of movies in the integrated file is correct.\n"
        ((score_test_5_2+=1))  
    else
        echo -e "The total number of movies in the integrated file is incorrect. Might miss file or need mutex during caching.\n"
    fi
    
    # check whether the final single output file is correctly sorted
    cat $final_sorted_file | ./check_sorting -c $column_item
    return_code=$(echo $?)
    echo -e "The return code is $return_code"
    
    if [ $return_code -eq 0 ]; then
        echo -e "The final output file is fully correctly sorted.\n"
        ((score_test_5_2+=1))  
    else
        echo -e "The final output file is not fully correctly sorted.\n"
    fi
else
	echo -e "Can not find the final output file."
fi

echo -e "########### Score for test5_2 = $score_test_5_2 ###############\n"


echo -e "\n###############################################################################"
echo -e "###################### TEST 6: test for format check ############################"
echo -e "\n*** test6.1  5pts: basic test (1.1) with non-csv files (should ignore them and still work) ***"

############# reset value ############
real_threads_number=10   # reset value to handle special case
real_movies_num=140      # reset value to handle special case
######################################

score_test_6_1=0
column_item="movie_title"
input_dir="./test6/test6.1"
output_dir="./collections_for_output_files/output6/output6.1"

# obtain the final single output file
$input_dir/sorter -c $column_item -d $input_dir -o $output_dir

# check whether the reported number of threads is correct
echo -e "\n"
echo -n "Enter the reported number of threads and press [ENTER]: "
read reported_threads_number
if [ $reported_threads_number -eq $real_threads_number ]; then
    echo -e "The reported number of threads is correct.\n"
    ((score_test_6_1+=3))
else
    echo -e "The reported number of threads is incorrect.\n"
fi

final_sorted_file="$output_dir/AllFiles-sorted-$column_item.csv"
if [ -f "$final_sorted_file" ]; then 
    
    # check whether all files are integrated (a potential test for mutex synchronization)
    reported_movies_num=$(cat $final_sorted_file | ./check_thread)
    echo -e "The total number of movies in the integrated file is $reported_movies_num"
    
    if [ $reported_movies_num -eq $real_movies_num ]; then
        echo -e "The total number of movies in the integrated file is correct.\n"
        ((score_test_6_1+=1))  
    else
        echo -e "The total number of movies in the integrated file is incorrect. Might miss file or need mutex during caching.\n"
    fi
    
    # check whether the final single output file is correctly sorted
    cat $final_sorted_file | ./check_sorting -c $column_item
    return_code=$(echo $?)
    echo -e "The return code is $return_code"
    
    if [ $return_code -eq 0 ]; then
        echo -e "The final output file is fully correctly sorted.\n"
        ((score_test_6_1+=1))  
    else
        echo -e "The final output file is not fully correctly sorted.\n"
    fi
else
	echo -e "Can not find the final output file."
fi

echo -e "########### Score for test6_1 = $score_test_6_1 ###############\n"


#*****************************************************************************************************************************************************
#*****************************************************************************************************************************************************
((TOTAL_BASIC_CREDITS=$score_test_1_1 + $score_test_1_2 + $score_test_2_1 + $score_test_2_2 + $score_test_3_1 + $score_test_4_1 + $score_test_5_1 + $score_test_5_2 + $score_test_6_1))
echo -e "\n\n\n########### Total Basic Credits (without including Documentation) = $TOTAL_BASIC_CREDITS ###############"
echo -e "####### Accumulated Wall Clock Time for Extra Credits = $ACCUMULATED_WALL_CLOCK_TIME milliseconds #########\n\n\n"



