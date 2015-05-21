About " lyrics_full_v2.cpp "

compile :
    g++  lyrics_full_v2.cpp  -o  lyrics_full_v2_exe  -O3

run :
    ./lyrics_full_v2_exe  lyrics.txt
                          (a file contains lyrics in a song )

data :
    define a struct which contains a [int] and a [char[3]].
    [int] records the times of the top five ZhuYin.
    [char[3]] records the top five ZhuYin.

    usage -> top       times            ZhuYin
              1    result[0].count   result[0].ZY
              2    result[1].count   result[1].ZY
              3    result[2].count   result[2].ZY
              4    result[3].count   result[3].ZY
              5    result[4].count   result[4].ZY

PS :
    no output file.